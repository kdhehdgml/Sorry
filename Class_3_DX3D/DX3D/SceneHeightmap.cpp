#include "stdafx.h"
#include "SceneHeightmap.h"
#include "HeightMap.h"
#include "AseCharacter.h"
#include "SampleUI.h"
#include "ParticleTest.h"

#include "SkinnedMesh.h"
#include "SkyBox.h"

#include <Psapi.h>
#include "Minimap.h"
#include "WallManager.h"
#include "Wall.h"
#include "SphereWall.h"

//안개생성
#include "CreateSmog.h"
#include "ColorCube.h"
#include "Player_hands.h"
#include "MONSTER.h"
//#include "Frustum.h"

//중현이코드
#include "UnitBox.h"
#include "Blocks.h"

#include "IUIObject.h"
#include "UIImage.h"

#include "ObjRender.h"// obj 해더
#include "BillBoard.h"

#include "MenuUI.h"
#include "BulletUI.h"
#include "Player_Health_UI.h"
#include "WireSphere.h"

#include "MARK.h"


//#include <fstream>

static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
static HANDLE self;
int cpuUsageCount = 0;
float cpuUsage = 0.0f;
D3DXVECTOR3 tempVecs[40];

double getCurrentValue() {
	FILETIME ftime, fsys, fuser;
	ULARGE_INTEGER now, sys, user;
	double percent;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&now, &ftime, sizeof(FILETIME));


	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&sys, &fsys, sizeof(FILETIME));
	memcpy(&user, &fuser, sizeof(FILETIME));
	percent = (sys.QuadPart - lastSysCPU.QuadPart) + (user.QuadPart - lastUserCPU.QuadPart);
	percent /= (now.QuadPart - lastCPU.QuadPart);
	percent /= numProcessors;
	lastCPU = now;
	lastUserCPU = user;
	lastSysCPU = sys;

	return percent * 100;
}

void SceneHeightmap::ResetScene() {
	for (auto p : *m_pUnit->getPMob()) {
		p->setHealth(0);
	}
	for (auto p : *m_pUnit->getPTeam()) {
		p->setStatus(1);
		p->setHealth(100);
	}
	g_pCamera->setRotX(-0.34f);
	g_pCamera->setRotY(1.6f);
	m_pGameOverOn = false;
}

void SceneHeightmap::DrawBrush()
{
	r = Ray::RayAtWorldSpace(SCREEN_POINT(m_pLParam));
	D3DXVECTOR3 m_vBrushPos;
	float height;
	bool isOnMap = m_pHeightMap->CalcPickedPosition(m_vBrushPos, SCREEN_POINT(m_pLParam));
	int nCount = 50;
	float fRadian = D3DX_PI * 2.0f / nCount;
	FLOAT fBrushSize = 100.0f;
	D3DXVECTOR3 vCurPos(1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vNewPos;
	D3DXMATRIXA16 matRot;
	verBrushLine[1].p = vCurPos * fBrushSize + m_vBrushPos;
	bool isIntersected = m_pHeightMap->GetHeight(height, verBrushLine[1].p);
	verBrushLine[1].p.y = height;
	D3DCOLOR d = D3DCOLOR_XRGB(255, 0, 0);
	verBrushLine[1].c = d;
	verBrushLine[0].c = d;
	for (int i = 1; i < nCount; i++) {
		verBrushLine[0] = verBrushLine[1];
		D3DXMatrixRotationY(&matRot, i*fRadian);
		D3DXVec3TransformCoord(&vNewPos, &vCurPos, &matRot);
		D3DXVec3Normalize(&vNewPos, &vNewPos);
		verBrushLine[1].p = vNewPos * fBrushSize + m_vBrushPos;
		bool isIntersected = m_pHeightMap->GetHeight(height, verBrushLine[1].p);
		verBrushLine[1].p.y = height;
	}
}

SceneHeightmap::SceneHeightmap()
{
	m_pHeightMap = NULL;
	m_pAseCharacter = NULL;
	//m_pPicking = NULL;

	//영락코드
	m_CreateSmog = NULL;
	m_SkyBox = NULL;
	m_ColorCube = NULL;
	m_Player_hands = NULL;
	//m_Frustum = NULL;


	//중현이코드
	m_pBlocks = NULL;

	m_pCrosshairSprite = NULL;
	m_pScopeSprite = NULL;
	m_pCrosshair = NULL;
	m_pScope = NULL;
	m_pCrosshairImage = NULL;
	m_pScopeImage = NULL;
	m_pCrosshairOn = false;
	m_pScopeOn = false;
	m_pGameOverSprite = NULL;
	m_pGameOverImage = NULL;
	m_pGameOver = NULL;
	m_pGameOverOn = false;

	m_pTalk = NULL;
	m_pTalkImage = NULL;
	m_pTalkSprite = NULL;
	m_pTalkOn = false;

	m_minimap = NULL;

	m_pSphere = NULL;
	m_pBoundingSphere = NULL;

	m_isBombing = false;

	//	m_pSkinnedMesh = NULL;
	volume_music = GSM().volume_music_init;

	// obj 관련
	m_ObjRender = NULL;
	m_BillBoard = NULL;

	m_pMenuUI = NULL;
	m_pBulletUI = NULL;
	m_pPlayer_Heatl_UI = NULL;
	m_pWireSphere = NULL;
	//m_MapTest0 = NULL;
	m_MARK = NULL;

	initCreateMob = false;

	g_pSceneManager->m_pCurrentLoading = 0;
	g_pSceneManager->m_pMaxLoading = 16;
}

SceneHeightmap::~SceneHeightmap()
{
	SAFE_RELEASE(m_pBlocks);
	SAFE_RELEASE(m_SkyBox);
	SAFE_RELEASE(m_ColorCube);
	SAFE_RELEASE(m_pCrosshairSprite);
	SAFE_RELEASE(m_pScopeSprite);
	SAFE_RELEASE(m_pGameOverSprite);
	//SAFE_RELEASE(m_Player_hands);
	//SAFE_RELEASE(pImage);
	SAFE_RELEASE(m_pCrosshair);
	SAFE_RELEASE(m_pScope);
	SAFE_RELEASE(m_pGameOver);
	SAFE_RELEASE(m_minimap);
	SAFE_RELEASE(m_pTalkSprite);
	SAFE_RELEASE(m_pTalk);
	SAFE_RELEASE(m_pSphere);
	SAFE_DELETE(m_pBoundingSphere);
	SAFE_RELEASE(m_pUnit);
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pMenuUI);
	SAFE_RELEASE(m_pBulletUI);
	SAFE_RELEASE(m_pPlayer_Heatl_UI);
	SAFE_RELEASE(m_MARK);

	//m_pCrosshair->ReleaseAll();

	//obj 관련 직접 접근해서 릴리즈함
	//m_ObjRender->~ObjRender();
	SAFE_DELETE(m_ObjRender);
	//m_BillBoard->~BillBoard();
	SAFE_DELETE(m_BillBoard);

	OnDestructIScene();
}

void SceneHeightmap::Init()
{
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.0f, 0.15f, 1.0f);

	g_pSceneManager->m_pLoadingString = "참호 파는 중...";
	m_pHeightMap = new HeightMap; AddSimpleDisplayObj(m_pHeightMap);
	m_pHeightMap->SetDimension(GSM().mapSize);
	m_pHeightMap->Load("resources/heightmap/HeightMapBF2.raw", &matS);
	m_pHeightMap->Init();
	D3DMATERIAL9 mtl = DXUtil::WHITE_MTRL;

	g_pSceneManager->m_pCurrentLoading++;
	g_pSceneManager->calcLoadingPercentage();
	m_pHeightMap->SetMtlTex(mtl,
		g_pTextureManager->GetTexture(L"resources/heightmap/terrainBF2.png"));

	g_pMapManager->AddMap("heightmap", m_pHeightMap);
	g_pMapManager->SetCurrentMap("heightmap");

	m_pOldPos = g_pCamera->getPos();

	g_pSceneManager->m_pCurrentLoading++;
	g_pSceneManager->calcLoadingPercentage();
	g_pSceneManager->m_pLoadingString = "펜에 잉크 넣는 중...";
	D3DXCreateFont(g_pDevice, 36, 18, FW_BOLD, 1, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("나눔고딕"), &m_pFont);
	m_str = "";

	/*m_pAseCharacter = new AseCharacter;
	m_pAseCharacter->Init();
	AddSimpleDisplayObj(m_pAseCharacter);
	*/

	//m_pPicking = new Picking;
	//m_pPicking->Init();
	//AddSimpleDisplayObj(m_pPicking);

	//IDisplayObject* pObj;
	////pObj = new SampleUI; pObj->Init(); AddSimpleDisplayObj(pObj);
	//pObj = new ParticleTest; pObj->Init(); AddSimpleDisplayObj(pObj);
	//
	g_pSceneManager->m_pCurrentLoading++;
	g_pSceneManager->calcLoadingPercentage();
	g_pSceneManager->m_pLoadingString = "장애물 설치 중...";
	// obj 관련 (크기, obj파일 위치, png파일 위치, x, y, z, 회전) 테스트용으로 넣은것임..
	m_ObjRender = new ObjRender;
	m_ObjRender->Init();
	m_BillBoard = new BillBoard;
	m_BillBoard->Init();

	m_MARK = new MARK;
	m_MARK->Init();
	
	g_pSceneManager->m_pCurrentLoading++;
	g_pSceneManager->calcLoadingPercentage();
	g_pSceneManager->m_pLoadingString = "병사 소집 중...";
	//중현이코드
	m_pUnit = new UnitBox();
	m_pUnit->SetLocation(m_pHeightMap->GetWall());
	m_pUnit->Init();
	//AddSimpleDisplayObj(m_pUnit);

	//프러스텀
	//m_Frustum = new Frustum;
	//m_Frustum->Init();
	//AddSimpleDisplayObj(m_Frustum);


	m_pBlocks = new Blocks();
	m_pBlocks->Init();
	//

	g_pSceneManager->m_pCurrentLoading++;
	g_pSceneManager->calcLoadingPercentage();
	g_pSceneManager->m_pLoadingString = "태양 설치하는 중...";
	D3DXVECTOR3 dir(1.0f, -10.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, true);

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	g_pSceneManager->m_pCurrentLoading++;
	g_pSceneManager->calcLoadingPercentage();
	g_pSceneManager->m_pLoadingString = "연막탄 터트리는 중...";
	//안개생성
	m_CreateSmog = new CreateSmog;
	m_CreateSmog->Init();
	//460.0f, 70.0f, 485.0f
	m_CreateSmog->Insert(D3DXVECTOR3(460.0f, 70.0f, 485.0f), (0.6f));
	m_CreateSmog->Insert(D3DXVECTOR3(400.0f, 70.0f, 405.0f), (0.3f));
	m_CreateSmog->Insert(D3DXVECTOR3(440.0f, 70.0f, 305.0f), (0.5f));
	m_CreateSmog->Insert(D3DXVECTOR3(350.0f, 70.0f, 205.0f), (0.6f));
	m_CreateSmog->Insert(D3DXVECTOR3(400.0f, 70.0f, 155.0f), (0.3f));
	m_CreateSmog->Insert(D3DXVECTOR3(440.0f, 70.0f, 105.0f), (0.8f));

	AddSimpleDisplayObj(m_CreateSmog);


	m_ColorCube = new ColorCube;
	m_ColorCube->Init();

	m_pWireSphere = new WireSphere();
	m_pWireSphere->Init();
	m_pWireSphere->m_pRenderToggle = false;
	AddSimpleDisplayObj(m_pWireSphere);

	//m_CreateSmog->Insert(D3DXVECTOR3(20.0f, 0.0f, 40.0f));
	//m_CreateSmog->Insert(D3DXVECTOR3(30.0f, 0.0f, 30.0f));
	//m_CreateSmog->Insert(D3DXVECTOR3(40.0f, 0.0f, 20.0f));
	//m_CreateSmog->Insert(D3DXVECTOR3(50.0f, 0.0f, 10.0f));


	//m_pSkinnedMesh = new SkinnedMesh;
	//m_pSkinnedMesh->Init();
	//AddSimpleDisplayObj(m_pSkinnedMesh);

	////안개생성
	//if (Mouse::Get()->ButtonDown(VK_LBUTTON))
	//{
	//	m_CreateMode = true;
	//	m_CreateStart = true;
	//}
	//else
	//{
	//	m_CreateMode = false;
	//}

	//if (m_CreateMode)
	//	m_CreateSmog->Insert(D3DXVECTOR3(10.0f, 0.0f, 50.0f));

	//if (m_CreateStart)
	//	m_CreateSmog->Update();
	//까지

	g_pSceneManager->m_pCurrentLoading++;
	g_pSceneManager->calcLoadingPercentage();
	g_pSceneManager->m_pLoadingString = "산 옮기는 중...";
	m_SkyBox = new SkyBox;
	m_SkyBox->Init();

	g_pSceneManager->m_pCurrentLoading++;
	g_pSceneManager->calcLoadingPercentage();
	g_pSceneManager->m_pLoadingString = "플레이어 총 영점조정 중...";
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXCreateSprite(g_pDevice, &m_pCrosshairSprite);
	m_pCrosshairImage = new UIImage(m_pCrosshairSprite);
	m_pCrosshairImage->m_bDrawBorder = false;
	m_pCrosshairImage->SetTexture("resources/ui/Crosshair.png");
	m_pCrosshairImage->SetPosition(&D3DXVECTOR3((rc.left + rc.right) / 2 - 64, (rc.top + rc.bottom) / 2 - 52, 0));
	m_pCrosshair = m_pCrosshairImage;
	g_pSceneManager->m_pCurrentLoading++;
	g_pSceneManager->calcLoadingPercentage();
	D3DXCreateSprite(g_pDevice, &m_pScopeSprite);
	m_pScopeImage = new UIImage(m_pScopeSprite);
	m_pScopeImage->m_bDrawBorder = false;
	m_pScopeImage->SetTexture("resources/ui/Scope.png");
	m_pScopeImage->SetPosition(&D3DXVECTOR3(20.5f, -9.5f, 0.0f));
	m_pScope = m_pScopeImage;
	g_pSceneManager->m_pCurrentLoading++;
	g_pSceneManager->calcLoadingPercentage();
	D3DXCreateSprite(g_pDevice, &m_pGameOverSprite);
	m_pGameOverImage = new UIImage(m_pGameOverSprite);
	m_pGameOverImage->m_bDrawBorder = false;
	m_pGameOverImage->SetTexture("resources/ui/GameOverScreen.png");
	m_pGameOverImage->SetPosition(&D3DXVECTOR3(20.5f, -9.5f, 0.0f));
	m_pGameOver = m_pGameOverImage;

	g_pSceneManager->m_pCurrentLoading++;
	g_pSceneManager->calcLoadingPercentage();
	D3DXCreateSprite(g_pDevice, &m_pTalkSprite);
	m_pTalkImage = new UIImage(m_pTalkSprite);
	m_pTalkImage->m_bDrawBorder = false;
	m_pTalkImage->SetTexture("resources/ui/talk.png");
	m_pTalkImage->SetPosition(&D3DXVECTOR3(200, 100, 0));
	m_pTalk = m_pTalkImage;

	g_pSceneManager->m_pCurrentLoading++;
	g_pSceneManager->calcLoadingPercentage();
	g_pSceneManager->m_pLoadingString = "플레이어 깨우는 중...";
	m_Player_hands = new Player_hands;
	m_Player_hands->Init();
	AddSimpleDisplayObj(m_Player_hands);
	g_pSceneManager->m_pCurrentLoading++;
	g_pSceneManager->calcLoadingPercentage();
	g_pSceneManager->m_pLoadingString = "GPS 장비 켜는 중...";
	m_minimap = new Minimap;
	m_minimap->Init();
	m_minimap->getPMobFromUnitBox(m_pUnit->getPMob());
	m_minimap->getPTeamFromUnitBox(m_pUnit->getPTeam());

	wallManager = new WallManager();
	wallManager->Init();
	AddSimpleDisplayObj(wallManager);

	//D3DXVECTOR3 aa(150.0f, 5.0f, 540.0f); //임시 BoundingBox 좌표1
	//D3DXVECTOR3 bb(240.0f, 35.0f, 545.0f); //임시 BoundingBox 좌표2

	//D3DXVECTOR3 aa2(150.0f, 5.0f, 185.0f); //임시 BoundingBox 좌표1
	//D3DXVECTOR3 bb2(240.0f, 35.0f, 190.0f); //임시 BoundingBox 좌표2

	//D3DXVECTOR3 aa3(130.0f, 5.0f, 220.0f); //임시 BoundingBox 좌표1
	//D3DXVECTOR3 bb3(135.0f, 35.0f, 510.0f); //임시 BoundingBox 좌표2


	//wallManager->addWall(aa, bb); //새로 벽 추가하고 싶을땐 이렇게
	//wallManager->addWall(aa2, bb2);
	//wallManager->addWall(aa3, bb3);
	//(aa가 수치가 작은 쪽 좌표, bb가 큰 쪽 좌표)

	//wallManager->addSphereWall(aa, 10.0f);
	g_pSceneManager->m_pCurrentLoading++;
	g_pSceneManager->calcLoadingPercentage();
	g_pSceneManager->m_pLoadingString = "나머지 잡다한 거 로딩 중...";
	D3DXCreateSphere(g_pDevice, 5.0f, 10, 10, &m_pSphere, NULL);
	m_pBoundingSphere = new BoundingSphere(g_pCamera->getPos(), 5.0f);

	g_pSoundManager->createSound(); // 사운드 세팅								
	g_pSoundManager->playAmbient(0); // 실행 시 환경음 자동 재생 (반복)

	m_pPlayer_Heatl_UI = new Player_Health_UI();
	m_pPlayer_Heatl_UI->Init();
	m_pMenuUI = new MenuUI();
	m_pMenuUI->Init();
	m_pBulletUI = new BulletUI();
	m_pBulletUI->Init();

	SYSTEM_INFO sysInfo;
	FILETIME ftime, fsys, fuser;
	GetSystemInfo(&sysInfo);
	numProcessors = sysInfo.dwNumberOfProcessors;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&lastCPU, &ftime, sizeof(FILETIME));


	self = GetCurrentProcess();
	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
	memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));

	g_pCamera->mouseLock = true;
	g_pSeqManager->Init();

	/*std::fstream fp("resources/wall/SphereWall.txt");
	int tempInt, tempFloat;
	D3DXVECTOR3 tempVec(0.0f, 27.0f, 0.0f);
	char inputString[100];
	fp.getline(inputString, 100);
	tempInt = std::atoi(inputString);
	for (int i = 0; i < tempInt; i++) {
	fp.getline(inputString, 100);
	tempFloat = std::atof(inputString);
	tempVec.x = tempFloat;
	fp.getline(inputString, 100);
	tempFloat = std::atof(inputString);
	tempVec.z = tempFloat;
	wallManager->addSphereWall(tempVec, 6.0f);
	tempVecs[i] = tempVec;
	}
	fp.close();*/
}

void SceneHeightmap::Update()
{
	m_pUnit->LivingPlayer(m_Player_hands->getHealth());

	//m_CreateSmog->Update();
	if (!g_pCamera->isPaused && !m_pGameOverOn) {

		SAFE_UPDATE(m_ColorCube);
		SAFE_UPDATE(m_pUnit);

		SAFE_UPDATE(m_minimap);
		SAFE_UPDATE(m_pCrosshair);
		SAFE_UPDATE(m_pScope);
		SAFE_UPDATE(m_pGameOver);
		SAFE_UPDATE(m_pTalk);
		SAFE_UPDATE(m_pBulletUI);
		SAFE_UPDATE(m_pPlayer_Heatl_UI);


		SAFE_UPDATE(m_MARK);

		/*g_pSoundManager->update3D(0, g_pCamera->getPos(), SpeakerPos, g_pCamera->getDir());
		if (GetKeyState('1') & 0x8000)
		{
		SpeakerPos = g_pSoundManager->getListenerPos();
		int r2 = rand() % 2;
		g_pSoundManager->play3D(r2);
		}*/

		float height;
		D3DXVECTOR3 currentPos = g_pCamera->getPos();
		bool isIntersected = g_pCurrentMap->GetHeight(height, currentPos);
		if (!g_pCamera->getFreeCameraMode() && height > 20.0f) {
			g_pCamera->setPos(m_pOldPos);
		}
		/*if (!g_pCamera->getFreeCameraMode()) {
		float oldHeight;
		isIntersected = g_pCurrentMap->GetHeight(oldHeight, m_pOldPos);
		float dxdy = oldHeight - height;
		D3DXVECTOR3 cPosDiff = currentPos - m_pOldPos;
		D3DXVECTOR3 cPosPush(0.0f, 0.0f, 0.0f);
		if (dxdy < -0.3) {
		float dx1, dx2, dy1, dy2;
		currentPos.x += 0.2f;
		isIntersected = g_pCurrentMap->GetHeight(dx1, currentPos);
		currentPos.x -= 0.2f;
		currentPos.z += 0.2f;
		isIntersected = g_pCurrentMap->GetHeight(dy1, currentPos);
		currentPos.z -= 0.2f;
		currentPos.x -= 0.2f;
		isIntersected = g_pCurrentMap->GetHeight(dx2, currentPos);
		currentPos.x += 0.2f;
		currentPos.z -= 0.2f;
		isIntersected = g_pCurrentMap->GetHeight(dy2, currentPos);
		currentPos.z += 0.2f;
		if (oldHeight - dx1 < -0.3f) {
		cPosPush.x -= 0.4f;
		}
		if (oldHeight - dx2 < -0.3f) {
		cPosPush.x += 0.4f;
		}
		if (oldHeight - dy1 < -0.3f) {
		cPosPush.z -= 0.4f;
		}
		if (oldHeight - dy2 < -0.3f) {
		cPosPush.z += 0.4f;
		}
		g_pCamera->setPos(m_pOldPos + cPosPush);
		}
		}*/

		/*if (!g_pCamera->getFreeCameraMode()) {
			float dx1, dx2, dy1, dy2, wallDx;
			const float distanceDiffBuffer = 0.3f;
			const float heightDiffBuffer = 1.0f;
			currentPos.x += distanceDiffBuffer;
			isIntersected = g_pCurrentMap->GetHeight(dx1, currentPos);
			currentPos.z += distanceDiffBuffer;
			isIntersected = g_pCurrentMap->GetHeight(dy1, currentPos);
			currentPos.z -= distanceDiffBuffer;
			currentPos.x -= distanceDiffBuffer;
			isIntersected = g_pCurrentMap->GetHeight(dx2, currentPos);
			currentPos.x += distanceDiffBuffer;
			currentPos.z -= distanceDiffBuffer;
			isIntersected = g_pCurrentMap->GetHeight(dy2, currentPos);
			currentPos.z += distanceDiffBuffer;
			dx1 -= height;
			dy1 -= height;
			dx2 -= height;
			dy2 -= height;
			D3DXVECTOR3 cPosDiff = currentPos - m_pOldPos;
			cPosDiff.y = 0;
			if (dx1 > heightDiffBuffer && cPosDiff.x > 0) {
				cPosDiff.x = 0;
			}
			if (dy1 > heightDiffBuffer && cPosDiff.z > 0) {
				cPosDiff.z = 0;
			}
			if (dx2 > heightDiffBuffer && cPosDiff.x < 0) {
				cPosDiff.x = 0;
			}
			if (dy2 > heightDiffBuffer && cPosDiff.z < 0) {
				cPosDiff.z = 0;
			}
			g_pCamera->setPos(m_pOldPos + cPosDiff);
		}*/
		currentPos = g_pCamera->getPos();
		isIntersected = g_pCurrentMap->GetHeight(height, currentPos);
		currentPos.y = height + GSM().playerHeight;
		if (g_pCamera->getFreeCameraMode()) {
			currentPos.y += 61.5f;
			currentPos.y += g_pCamera->getDeltaY();
		}
		g_pCamera->setPos(currentPos);

		if (g_pCamera->getFreeCameraMode()) {
			m_pCrosshairOn = false;
		}
		else {
			m_pCrosshairOn = true;
		}

		g_pCamera->getPMobFromUnitBox(m_pUnit->getPMob());
		m_minimap->getPMobFromUnitBox(m_pUnit->getPMob());
		m_minimap->getPTeamFromUnitBox(m_pUnit->getPTeam());

		PROCESS_MEMORY_COUNTERS pmc;
		GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));

		Debug->AddText("메모리 사용량 : ");
		Debug->AddText((int)(pmc.WorkingSetSize / 1024));
		Debug->AddText("KB");
		Debug->EndLine();

		if (cpuUsageCount <= 0) {
			cpuUsage = getCurrentValue();
			cpuUsageCount = 60;
		}
		else {
			cpuUsageCount--;
		}

		Debug->AddText("CPU 사용량 : ");
		Debug->AddText(cpuUsage);
		Debug->AddText("%");
		Debug->EndLine();

		m_pPlayer_Heatl_UI->Health = m_Player_hands->getHealth();

		// 0 키 누르면 음악 재생 ON / OFF
		if ((GetAsyncKeyState('0') & 0x8000))
		{
			if (!musicPlayCheck)
			{
				musicPlayCheck = true;

				if (!musicPlay)
				{
					musicPlay = true;
					g_pSoundManager->playMusic(0);
				}
				else
				{
					musicPlay = false;
					g_pSoundManager->stopMusic(0);
				}
			}
		}
		else if (musicPlayCheck)
			musicPlayCheck = false;

		if (!g_pCamera->getFreeCameraMode()) // 프리카메라가 OFF 일 경우
		{
			if ((GetAsyncKeyState('W') & GetAsyncKeyState(VK_SHIFT) & 0x8000))
			{
				g_pSoundManager->RunSound();
			}
			else if (GetAsyncKeyState('W') ||
				GetAsyncKeyState('A') ||
				GetAsyncKeyState('D') ||
				GetAsyncKeyState('S') & 0x8000)
			{
				g_pSoundManager->WalkSound();
			}
		}

		if ((GetAsyncKeyState('I') & 0x8000))
		{
			if (volume_music <= 10.0f)
				volume_music += 0.049999f;
			g_pSoundManager->volumeControl_Music(volume_music);
		}
		if ((GetAsyncKeyState('K') & 0x8000))
		{
			if (volume_music >= 0.049999f)
				volume_music -= 0.049999f;
			g_pSoundManager->volumeControl_Music(volume_music);
		}
		if ((GetAsyncKeyState(VK_F10) & 0x8000)) {
			m_pGameOverOn = true;
		}
		vector<TeamAI*> m_pTeam = *m_pUnit->getPTeam();
		float minDistance = 9999999.0f;
		bool talkAble = false;
		int tempIndex = 0, teamIndex = -1;
		//float conWidth = cos(30 * D3DX_PI / 180.0f);
		float conWidth = 0.866f; //대화가 가능한 각도 (현재 각도 : 30도) cos(각도 * 파이 / 180)
		for (auto p : m_pTeam) {
			D3DXVECTOR3 teamPos = p->GetPosition(); //팀 위치
			D3DXVECTOR3 playerPos = g_pCamera->getPos(); //내 위치
			teamPos.y += GSM().playerHeight;
			D3DXVECTOR3 playerDir = g_pCamera->getDir(); //내가 보는 방향
			D3DXVECTOR3 posDiff = teamPos - playerPos; //팀원 위치랑 내 위치의 차이
			D3DXVECTOR3 lookDir;
			D3DXVec3Normalize(&lookDir, &posDiff); //벡터 정규화
			float viewAngle = D3DXVec3Dot(&playerDir, &lookDir); //내가 보는 각도
			float distance = sqrtf(D3DXVec3Dot(&posDiff, &posDiff)); //아군과의 거리 계산
			if (distance < minDistance) {
				minDistance = distance; //가장 가까운 아군과의 거리만 남긴다
				if (minDistance < 10.0f) { //대화가 가능한 거리라면
					if (viewAngle > conWidth) { //대화가 가능한 각도라면
						talkAble = true; //대화 가능
						teamIndex = tempIndex; //현재 대화 가능한 아군의 인덱스
					}
				}
			}
			if (distance < 4.0f) { //아군과의 거리가 너무 가까우면
								   //플레이어와 아군 사이의 벡터를 구해 그 역벡터를 구하고,
								   //가까울수록 밀어내는 힘을 강하게 하기 위해 거리로 나눈다.
				D3DXVECTOR3 lookDirInverse = -1.2f * lookDir / distance;
				lookDirInverse.y = 0; //y축 값은 필요없다.
				g_pCamera->setPos(g_pCamera->getPos() + lookDirInverse); //역벡터만큼 플레이어를 밀어낸다.
			}
			tempIndex++;
		}
		if (talkAble) {
			m_pTalkOn = true;
		}
		else {
			m_pTalkOn = false;
		}
		vector<TeamAI*> pTeam = *m_pUnit->getPTeam();
		if ((GetAsyncKeyState('E') & 0x0001))
		{
			if (m_pTalkOn) {
				//TCHAR str[100];
				//wsprintf(str, TEXT("%d 번 아군과 대화하였습니다."), teamIndex);
				//MessageBox(NULL, str, TEXT("DEBUG"), MB_OK);
				m_str.Empty();
				CString _str = to_string(teamIndex).c_str();
				m_str.Append(_str);
				m_str.Append(_T("번 아군의 레벨 : "));
				_str = to_string(pTeam[teamIndex]->m_level).c_str();
				m_str.Append(_str);
				m_str.Append(_T("\n다음 레벨까지 필요한 경험치 : "));
				_str = to_string(pTeam[teamIndex]->m_expToNextLevel).c_str();
				m_str.Append(_str);
				m_talkFontCount = GetTickCount() + 3000;
			}
		}

		if (GetAsyncKeyState(VK_NUMPAD1) & 0x0001) {
			m_Player_hands->setHealth(1);
		}
		else if (GetAsyncKeyState(VK_NUMPAD2) & 0x0001) {
			m_Player_hands->setHealth(2);
		}
		else if (GetAsyncKeyState(VK_NUMPAD3) & 0x0001) {
			m_Player_hands->setHealth(3);
		}
		else if (GetAsyncKeyState(VK_NUMPAD4) & 0x0001) {
			m_Player_hands->setHealth(4);
		}

		if (GetTickCount() >= m_talkFontCount) {
			m_str.Empty();
		}


		m_pBoundingSphere->center = g_pCamera->getPos();
		m_pBoundingSphere->center.y = height + 4.0f;

		r = Ray::RayAtWorldSpace(SCREEN_POINT(m_pLParam));
		bool getHitBox = false;
		bool getCollision = false;
		for (auto p : wallManager->getWalls()) {
			D3DXVECTOR3 wallPos = p->getCenter(); //벽 위치
			D3DXVECTOR3 playerPos = g_pCamera->getPos(); //내 위치
			D3DXVECTOR3 posDiff = wallPos - playerPos; //벽 위치랑 내 위치의 차이
			D3DXVECTOR3 lookDir;
			D3DXVec3Normalize(&lookDir, &posDiff); //벡터 정규화
			getCollision = wallManager->IntersectSphereBox(m_pBoundingSphere, p->getBoundingBox());
			if (getCollision) {
				D3DXVECTOR3 camPosDiff = playerPos - m_pOldPos;
				if ((p->getSize().z + 5.0f) / 2.0f > abs(posDiff.z)) {
					camPosDiff.x = 0;
				}
				else {
					camPosDiff.z = 0;
				}
				camPosDiff.y = 0;
				g_pCamera->setPos(m_pOldPos + camPosDiff);
			}
			bool tempGetHitBox = false;
			tempGetHitBox = r.CalcIntersectBox(p->getBoundingBox());
			if (tempGetHitBox) {
				getHitBox = true;
			}
		}
		D3DXVECTOR3 lookDirInverse(0.0f, 0.0f, 0.0f);
		for (auto p : wallManager->getSphereWalls()) {
			D3DXVECTOR3 wallPos = p->getCenter(); //벽 위치
			D3DXVECTOR3 playerPos = g_pCamera->getPos(); //내 위치
			D3DXVECTOR3 posDiff = wallPos - playerPos; //벽 위치랑 내 위치의 차이
			D3DXVECTOR3 lookDir;
			D3DXVec3Normalize(&lookDir, &posDiff); //벡터 정규화
			float distance = sqrtf(D3DXVec3Dot(&posDiff, &posDiff)); //벽과의 거리 계산
			if (distance < (p->getSize() + 5.0f)) { //벽과의 거리가 너무 가까우면
													//플레이어와 벽 사이의 벡터를 구해 그 역벡터를 구하고,
													//가까울수록 밀어내는 힘을 강하게 하기 위해 거리로 나눈다.
				lookDirInverse = -10.0f * lookDir / distance;
				lookDirInverse.y = 0; //y축 값은 필요없다.
				g_pCamera->setPos(g_pCamera->getPos() + lookDirInverse); //역벡터만큼 플레이어를 밀어낸다.
			}
		}

		D3DXVECTOR3 posCorrection = g_pCamera->getPos();
		if (!g_pCamera->getFreeCameraMode()) {
			if (posCorrection.z > 540.0f) {
				posCorrection.z = 540.0f;
				posCorrection.x = min(posCorrection.x, 220.0f);
			}
			else if (posCorrection.z < 190.0f) {
				posCorrection.z = 190.0f;
				posCorrection.x = min(posCorrection.x, 224.0f);
			}
			else if (posCorrection.z > 530.0f && posCorrection.z <= 540.0f) {
				posCorrection.x = min(posCorrection.x, 220.0f);
			}
			else if (posCorrection.z > 512.0f && posCorrection.z <= 530.0f) {
				posCorrection.x = min(posCorrection.x, 240.0f - (posCorrection.z - 512.0f) * 1.11f);
			}
			else if (posCorrection.z > 480.0f && posCorrection.z <= 512.0f) {
				posCorrection.x = min(posCorrection.x, 240.0f);
			}
			else if (posCorrection.z > 460.0f && posCorrection.z <= 480.0f) {
				posCorrection.x = min(posCorrection.x, 228.0f + (posCorrection.z - 460.0f) * 0.6f);
			}
			else if (posCorrection.z > 440.0f && posCorrection.z <= 460.0f) {
				posCorrection.x = min(posCorrection.x, 240.0f - (posCorrection.z - 440.0f) * 0.6f);
			}
			else if (posCorrection.z > 420.0f && posCorrection.z <= 440.0f) {
				posCorrection.x = min(posCorrection.x, 240.0f);
			}
			else if (posCorrection.z > 402.0f && posCorrection.z <= 420.0f) {
				posCorrection.x = min(posCorrection.x, 254.0f - (posCorrection.z - 402.0f) * 0.78f);
			}
			else if (posCorrection.z > 374.0f && posCorrection.z <= 402.0f) {
				posCorrection.x = min(posCorrection.x, 254.0f);
			}
			else if (posCorrection.z > 360.0f && posCorrection.z <= 374.0f) {
				posCorrection.x = min(posCorrection.x, 226.0f + (posCorrection.z - 360.0f) * 2.0f);
			}
			else if (posCorrection.z > 352.0f && posCorrection.z <= 360.0f) {
				posCorrection.x = min(posCorrection.x, 226.0f);
			}
			else if (posCorrection.z > 326.0f && posCorrection.z <= 352.0f) {
				posCorrection.x = min(posCorrection.x, 248.0f - (posCorrection.z - 326.0f) * 0.85f);
			}
			else if (posCorrection.z > 310.0f && posCorrection.z <= 326.0f) {
				posCorrection.x = min(posCorrection.x, 248.0f);
			}
			else if (posCorrection.z > 299.0f && posCorrection.z <= 310.0f) {
				posCorrection.x = min(posCorrection.x, 240.0f + (posCorrection.z - 299.0f) * 0.73f);
			}
			else if (posCorrection.z > 282.0f && posCorrection.z <= 299.0f) {
				posCorrection.x = min(posCorrection.x, 257.0f - (posCorrection.z - 282.0f) * 1.0f);
			}
			else if (posCorrection.z > 265.0f && posCorrection.z <= 282.0f) {
				posCorrection.x = min(posCorrection.x, 257.0f);
			}
			else if (posCorrection.z > 251.0f && posCorrection.z <= 265.0f) {
				posCorrection.x = min(posCorrection.x, 251.0f + (posCorrection.z - 251.0f) * 0.43f);
			}
			else if (posCorrection.z > 240.0f && posCorrection.z <= 251.0f) {
				posCorrection.x = min(posCorrection.x, 258.0f - (posCorrection.z - 240.0f) * 0.64f);
			}
			else if (posCorrection.z > 218.0f && posCorrection.z <= 240.0f) {
				posCorrection.x = min(posCorrection.x, 258.0f);
			}
			else if (posCorrection.z > 195.0f && posCorrection.z <= 218.0f) {
				posCorrection.x = min(posCorrection.x, 224.0f + (posCorrection.z - 195.0f) * 1.48f);
			}
			else if (posCorrection.x >= 190.0f && posCorrection.z <= 195.0f) {
				posCorrection.x = min(posCorrection.x, 224.0f);
			}

			if (posCorrection.x < 135.0f) {
				posCorrection.x = 135.0f;
			}
		}
		g_pCamera->setPos(posCorrection);

		m_pOldPos = g_pCamera->getPos();

		// 이벤트 매니저
		Event();

		if (!m_isBombing && g_pCamera->m_pBombing && GetTickCount() > g_pCamera->m_pBombingDelay - 2000) {
			g_pSoundManager->effectSound(eType::ART_FIRE, NULL);
			m_isBombing = true;
		}

		if (g_pCamera->m_pBombing && GetTickCount() > g_pCamera->m_pBombingDelay) {
			vector<Mob*> pMob = *m_pUnit->getPMob();
			g_pSoundManager->effectSound(eType::ART_EXP, NULL);
			for (auto p : pMob) {
				BoundingSphere* s = p->getBoundingSphereBody();
				bool getHit = m_pWireSphere->getHit(s);
				if (getHit) {
					p->setHealth(0);
				}
			}
			g_pCamera->bombing();
			g_pCamera->shaking();
			m_pWireSphere->m_pRenderToggle = false;
			m_BillBoard->check = true;
		}

		/*Debug->AddText("아군과의 거리 : ");
		Debug->AddText(minDistance);
		Debug->EndLine();*/
		Debug->AddText("현재 높이 : ");
		Debug->AddText(height);
		Debug->EndLine();
		//Debug->AddText("현재 위치 : ");
		//Debug->AddText(m_pOldPos);
		//Debug->EndLine(); // 숫자 4 누르면 나오는 카메라 디버그 텍스트에 있음
		Debug->AddText("잔탄 수 : ");
		Debug->AddText(g_pCamera->getMagazine());
		if (g_pCamera->getMagazine() == 5 && g_pCamera->getCooldown() > GetTickCount()) {
			m_pBulletUI->bulletNum = 0;
		}
		else {
			m_pBulletUI->bulletNum = g_pCamera->getMagazine();
		}
		Debug->EndLine();
		if (m_pUnit->GameOver()) {
			m_pGameOverOn = true;
		}
		D3DXVECTOR3 wireSpherePos;
		if (g_pCamera->m_pBombing) {
			m_pWireSphere->setPos(m_pBombingPos);
		}
		else {
			bool isOnMap = m_pHeightMap->CalcPickedPosition(wireSpherePos, SCREEN_POINT(m_pLParam));
			if (isOnMap) {
				m_pWireSphere->setPos(wireSpherePos);
			}
			else {
				m_pWireSphere->setPos(D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f));
			}
		}
		if (g_pCamera->getBombingMode()) {
			if (g_pCamera->m_pBombingReady) {
				m_pWireSphere->m_pRenderToggle = true;
			}
			else {
				m_pWireSphere->m_pRenderToggle = false;
			}
		}
		else {
			m_pWireSphere->m_pRenderToggle = false;
		}
		//DrawBrush();
		/*Debug->AddText("SphereWalls 좌표들 : ");
		for (int i = 0; i < 38; i++) {
		Debug->AddText(tempVecs[i]);
		Debug->EndLine();
		}*/
		/*Debug->AddText("Bounding Box Collision with Ray: ");
		Debug->AddText(getHitBox);
		Debug->EndLine();
		Debug->AddText("Bounding Box Collision with Player: ");
		Debug->AddText(getCollision);
		Debug->EndLine();*/
		/*Debug->AddText("volume(music) : ");
		Debug->AddText(volume_music);
		Debug->EndLine();*/
		//m_pWireSphere->m_pRenderToggle = g_pCamera->getFreeCameraMode();
		OnUpdateIScene();
	}
	else {
		SAFE_UPDATE(m_pMenuUI);
	}
	g_pSoundManager->updateListener(g_pCamera->getPos());
	//m_ObjRender->Update();
	if ((GetAsyncKeyState(VK_F1) & 0x8000)) {
		ResetScene();
	}
}

void SceneHeightmap::Render()
{

	OnRenderIScene();
	SAFE_RENDER(m_ColorCube);
	SAFE_RENDER(m_pBlocks);
	SAFE_RENDER(m_pUnit);
	SAFE_RENDER(m_SkyBox);
	SAFE_RENDER(m_minimap);
	SAFE_RENDER(m_pBulletUI);
	SAFE_RENDER(m_MARK);
	
	g_pDevice->SetFVF(VERTEX_PC::FVF);
	g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, verBrushLine, sizeof(VERTEX_PC));

	if (m_pGameOverOn) {
		g_pDevice->SetTexture(0, NULL);
		m_pGameOverSprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXMATRIX g_mat;
		D3DXVECTOR2 scaling(1.5f, 1.5f);
		D3DXMatrixTransformation2D(&g_mat, NULL, 0.0, &scaling, &D3DXVECTOR2(0.0f, 0.0f), 0.0f, &D3DXVECTOR2(-160.0f, 0.0f));
		m_pGameOverSprite->SetTransform(&g_mat);
		SAFE_RENDER(m_pGameOver);
		m_pGameOverSprite->End();
	}
	m_CreateSmog->Render();
	//m_pPicking->Render();

	

	//obj 관련
	m_ObjRender->Render();
	if (m_BillBoard->check == true)
	{
		m_BillBoard->Render(m_pWireSphere->m_pos.x, m_pWireSphere->m_pos.y, m_pWireSphere->m_pos.z);
	}
	
	if (g_pCamera->isPaused) {
		SAFE_RENDER(m_pMenuUI);
	}

	if (m_pCrosshairOn) {
		if (m_pScopeOn & g_pCamera->getCooldown() <= 0) {
			g_pDevice->SetTexture(0, NULL);
			m_pScopeSprite->Begin(D3DXSPRITE_ALPHABLEND);
			D3DXMATRIX mat;
			D3DXVECTOR2 scaling(1.5f, 1.5f);
			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &D3DXVECTOR2(0.0f, 0.0f), 0.0f, &D3DXVECTOR2(-160.0f, 0.0f));
			m_pScopeSprite->SetTransform(&mat);
			SAFE_RENDER(m_pScope);
			m_pScopeSprite->End();
		}
		else {
			g_pDevice->SetTexture(0, NULL);
			m_pCrosshairSprite->Begin(D3DXSPRITE_ALPHABLEND);
			//m_pSprite->SetTransform(&m_matWorld);
			//SAFE_RENDER(m_pCrosshair);
			m_pCrosshairSprite->End();
		}
	}
	if (m_pTalkOn) {
		g_pDevice->SetTexture(0, NULL);
		m_pTalkSprite->Begin(D3DXSPRITE_ALPHABLEND);
		SAFE_RENDER(m_pTalk);
		m_pTalkSprite->End();
	}
	D3DXMATRIXA16 mat;
	D3DXMatrixTranslation(&mat, m_pBoundingSphere->center.x, m_pBoundingSphere->center.y, m_pBoundingSphere->center.z);
	g_pDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pDevice->SetTexture(0, NULL);
	//m_pSphere->DrawSubset(0);
	if (m_Player_hands->GetRenderState())
		Shaders::Get()->Render();

	SAFE_RENDER(m_pPlayer_Heatl_UI);
	RECT rc;
	SetRect(&rc, 100, 400, 800, 600);
	m_pFont->DrawText(NULL, m_str, m_str.GetLength(), &rc,
		DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));



}

void SceneHeightmap::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SAFE_WNDPROC(m_pHeightMap);
	//SAFE_WNDPROC(m_pPicking);
	//SAFE_WNDPROC(m_pUnit);
	SAFE_WNDPROC(m_Player_hands);


	m_pLParam = lParam;

	switch (message) {
	case WM_LBUTTONDOWN:
		if (g_pCamera->getBombingMode() && g_pCamera->m_pBombingReady && !g_pCamera->m_pBombing) {
			g_pCamera->m_pBombingReady = false;
			g_pCamera->m_pBombing = true;
			g_pCamera->m_pBombingDelay = GetTickCount() + 3000;
			m_pBombingPos = m_pWireSphere->m_pos;
			m_isBombing = false;
		}
	case WM_RBUTTONDOWN:
		if (m_pCrosshairOn) {
			//m_pScopeOn = true;
		}
		break;
	case WM_RBUTTONUP:
		m_pScopeOn = false;
		break;
	case WM_MOUSEMOVE:
		m_Player_hands->SetPosToCamera();
		break;
	}
}

void SceneHeightmap::Event()
{
	if (Player_Health != m_Player_hands->getHealth())
	{
		Health_Recovery_Interval = 0;
		Player_Health = m_Player_hands->getHealth();
	}
	if(Player_Health < 4)
	{
		if (Health_Recovery_Interval < 300)
			Health_Recovery_Interval++;
		else
		{
			m_Player_hands->setHealth(Player_Health + 1);
			Health_Recovery_Interval = 0;
		}
		Debug->AddText("체력 회복: ");
		Debug->AddText(Health_Recovery_Interval);
		Debug->EndLine();
	}
	
	if (GetKeyState('6') & 0x8000)
	{
		int Health = m_Player_hands->getHealth();
		m_Player_hands->setHealth(Health + 1);
	}
	if (GetKeyState('5') & 0x8000)
	{
		int Health = m_Player_hands->getHealth();
		m_Player_hands->setHealth(Health - 1);
	}
	if (GetKeyState(VK_F3) & 0x8000)
	{
		if (g_pSeqManager->stopUpdate = true)
			g_pSeqManager->stopUpdate = false;
	}
	if (GetKeyState(VK_F2) & 0x8000)
	{
		if (!initCreateMob)
		{
			m_pUnit->CreateMob(50);
			initCreateMob = true;
		}
	}

	g_pSeqManager->Update();
	if (g_pSeqManager->spawnNum != 0)
	{
		m_pUnit->GameWaveSetting(g_pSeqManager->spawnNum);
		if (m_pUnit->MobStart == false)
			m_pUnit->MobStart = true;
		g_pSoundManager->effectSound(eType::WHISTLE, 0);
		g_pSeqManager->spawnNum = 0;
	}
	if (m_pUnit->ClearWave() == 1)
		m_pUnit->MobStart = false;
}
