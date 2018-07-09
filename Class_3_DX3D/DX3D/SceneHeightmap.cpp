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

#include "MenuUI.h"
//#include "seqManager.h"

static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
static HANDLE self;
int cpuUsageCount = 0;
float cpuUsage = 0.0f;

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

	m_pTalk = NULL;
	m_pTalkImage = NULL;
	m_pTalkSprite = NULL;
	m_pTalkOn = false;

	m_minimap = NULL;

	m_pSphere = NULL;
	m_pBoundingSphere = NULL;

	//	m_pSkinnedMesh = NULL;
	volume_music = GSM().volume_music_init;

	// obj 관련
	m_ObjRender = NULL;

	m_pMenuUI = NULL;
	//m_MapTest0 = NULL;

}

SceneHeightmap::~SceneHeightmap()
{
	SAFE_RELEASE(m_pBlocks);
	SAFE_RELEASE(m_SkyBox);
	SAFE_RELEASE(m_ColorCube);
	SAFE_RELEASE(m_pCrosshairSprite);
	SAFE_RELEASE(m_pScopeSprite);
	//SAFE_RELEASE(m_Player_hands);
	//SAFE_RELEASE(pImage);
	SAFE_RELEASE(m_pCrosshair);
	SAFE_RELEASE(m_pScope);
	SAFE_RELEASE(m_minimap);
	SAFE_RELEASE(m_pTalkSprite);
	SAFE_RELEASE(m_pTalk);
	SAFE_RELEASE(m_pSphere);
	SAFE_DELETE(m_pBoundingSphere);
	SAFE_RELEASE(m_pUnit);
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pMenuUI);


	//m_pCrosshair->ReleaseAll();

	//obj 관련 직접 접근해서 릴리즈함
	//m_ObjRender->~ObjRender();
	SAFE_DELETE(m_ObjRender);

	OnDestructIScene();
}

void SceneHeightmap::Init()
{
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.0f, 0.15f, 1.0f);

	m_pHeightMap = new HeightMap; AddSimpleDisplayObj(m_pHeightMap);
	m_pHeightMap->SetDimension(GSM().mapSize);
	m_pHeightMap->Load("resources/heightmap/HeightMapBF2.raw", &matS);
	m_pHeightMap->Init();
	D3DMATERIAL9 mtl = DXUtil::WHITE_MTRL;


	m_pHeightMap->SetMtlTex(mtl,
		g_pTextureManager->GetTexture(L"resources/heightmap/terrainBF.png"));

	g_pMapManager->AddMap("heightmap", m_pHeightMap);
	g_pMapManager->SetCurrentMap("heightmap");

	m_pOldPos = g_pCamera->getPos();
	
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

	// obj 관련 (크기, obj파일 위치, png파일 위치, x, y, z, 회전) 테스트용으로 넣은것임..
	m_ObjRender = new ObjRender;
	m_ObjRender->Init();

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

	D3DXVECTOR3 dir(1.0f, -10.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, true);

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);


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

	m_SkyBox = new SkyBox;
	m_SkyBox->Init();

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXCreateSprite(g_pDevice, &m_pCrosshairSprite);
	m_pCrosshairImage = new UIImage(m_pCrosshairSprite);
	m_pCrosshairImage->m_bDrawBorder = false;
	m_pCrosshairImage->SetTexture("resources/ui/Crosshair.png");
	m_pCrosshairImage->SetPosition(&D3DXVECTOR3((rc.left + rc.right) / 2 - 64, (rc.top + rc.bottom) / 2 - 52, 0));
	m_pCrosshair = m_pCrosshairImage;
	D3DXCreateSprite(g_pDevice, &m_pScopeSprite);
	m_pScopeImage = new UIImage(m_pScopeSprite);
	m_pScopeImage->m_bDrawBorder = false;
	m_pScopeImage->SetTexture("resources/ui/Scope.png");
	m_pScopeImage->SetPosition(&D3DXVECTOR3(20.5f, -9.5f, 0.0f));
	m_pScope = m_pScopeImage;

	D3DXCreateSprite(g_pDevice, &m_pTalkSprite);
	m_pTalkImage = new UIImage(m_pTalkSprite);
	m_pTalkImage->m_bDrawBorder = false;
	m_pTalkImage->SetTexture("resources/ui/talk.png");
	m_pTalkImage->SetPosition(&D3DXVECTOR3(200, 100, 0));
	m_pTalk = m_pTalkImage;

	m_Player_hands = new Player_hands;
	m_Player_hands->Init();
	AddSimpleDisplayObj(m_Player_hands);

	m_minimap = new Minimap;
	m_minimap->Init();
	m_minimap->getPMobFromUnitBox(m_pUnit->getPMob());
	m_minimap->getPTeamFromUnitBox(m_pUnit->getPTeam());

	wallManager = new WallManager();
	wallManager->Init();
	AddSimpleDisplayObj(wallManager);

	D3DXVECTOR3 aa(200.0f, 25.0f, 300.0f); //임시 BoundingBox 좌표1
	D3DXVECTOR3 bb(310.0f, 35.0f, 310.0f); //임시 BoundingBox 좌표2

	D3DXVECTOR3 aa2(0.0f, 25.0f, 100.0f); //임시 BoundingBox 좌표1
	D3DXVECTOR3 bb2(10.0f, 35.0f, 310.0f); //임시 BoundingBox 좌표2

	D3DXVECTOR3 aa3(100.0f, 25.0f, 400.0f); //임시 BoundingBox 좌표1
	D3DXVECTOR3 bb3(210.0f, 35.0f, 410.0f); //임시 BoundingBox 좌표2


	//wallManager->addWall(aa, bb); //새로 벽 추가하고 싶을땐 이렇게
								  //(aa가 수치가 작은 쪽 좌표, bb가 큰 쪽 좌표)

	D3DXCreateSphere(g_pDevice, 5.0f, 10, 10, &m_pSphere, NULL);
	m_pBoundingSphere = new BoundingSphere(g_pCamera->getPos(), 5.0f);

	g_pSoundManager->createSound(); // 사운드 세팅								
	g_pSoundManager->playAmbient(0); // 실행 시 환경음 자동 재생 (반복)

	m_pMenuUI = new MenuUI();
	m_pMenuUI->Init();

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
}

void SceneHeightmap::Update()
{
	//m_CreateSmog->Update();


	SAFE_UPDATE(m_ColorCube);
	SAFE_UPDATE(m_pUnit);

	SAFE_UPDATE(m_minimap);
	SAFE_UPDATE(m_pCrosshair);
	SAFE_UPDATE(m_pScope);
	SAFE_UPDATE(m_pTalk);
	SAFE_UPDATE(m_pMenuUI);

	float height;
	D3DXVECTOR3 currentPos = g_pCamera->getPos();
	bool isIntersected = g_pCurrentMap->GetHeight(height, currentPos);
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

	bool isWallDx = false;
	if (!g_pCamera->getFreeCameraMode()) {
		float dx1, dx2, dy1, dy2, wallDx;
		const float distanceDiffBuffer = 0.3f;
		const float heightDiffBuffer = 0.3f;
		currentPos.x += distanceDiffBuffer;
		isIntersected = g_pCurrentMap->GetHeight(dx1, currentPos);
		currentPos.x += distanceDiffBuffer * 3;
		isIntersected = g_pCurrentMap->GetHeight(wallDx, currentPos);
		currentPos.x -= distanceDiffBuffer * 4;
		currentPos.z += distanceDiffBuffer;
		isIntersected = g_pCurrentMap->GetHeight(dy1, currentPos);
		currentPos.z -= distanceDiffBuffer;
		currentPos.x -= distanceDiffBuffer;
		isIntersected = g_pCurrentMap->GetHeight(dx2, currentPos);
		currentPos.x += distanceDiffBuffer;
		currentPos.z -= distanceDiffBuffer;
		isIntersected = g_pCurrentMap->GetHeight(dy2, currentPos);
		currentPos.z += distanceDiffBuffer;
		wallDx -= height;
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
		if (wallDx > heightDiffBuffer) {
			isWallDx = true;
		}
		g_pCamera->setPos(m_pOldPos + cPosDiff);
	}
	currentPos = g_pCamera->getPos();
	isIntersected = g_pCurrentMap->GetHeight(height, currentPos);
	currentPos.y = height + GSM().playerHeight;
	if (g_pCamera->getFreeCameraMode()) {
		currentPos.y += 61.5f;
		currentPos.y += g_pCamera->getDeltaY();
	}
	/*else {
		if (isWallDx) {
			currentPos.y += 5.0f;
		}
	}*/
	g_pCamera->setPos(currentPos);


	OnUpdateIScene();

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
	if ((GetAsyncKeyState('E') & 0x0001))
	{
		if (m_pTalkOn) {
			//TCHAR str[100];
			//wsprintf(str, TEXT("%d 번 아군과 대화하였습니다."), teamIndex);
			//MessageBox(NULL, str, TEXT("DEBUG"), MB_OK);
			m_str.Empty();
			CString _str = to_string(teamIndex).c_str();
			m_str.Append(_str);
			m_str.Append(_T("번 아군 : 안녕하세요!"));
			m_talkFontCount = GetTickCount() + 3000;
		}
	}

	if (GetTickCount() >= m_talkFontCount) {
		m_str.Empty();
	}


	m_pBoundingSphere->center = g_pCamera->getPos();
	m_pBoundingSphere->center.y = height + 3.0f;

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

	m_pOldPos = g_pCamera->getPos();

	g_pSeqManager->Update();

	/*Debug->AddText("아군과의 거리 : ");
	Debug->AddText(minDistance);
	Debug->EndLine();*/
	Debug->AddText("현재 높이 : ");
	Debug->AddText(height);
	Debug->EndLine();
	/*Debug->AddText("현재 위치 : ");
	Debug->AddText(m_pOldPos);
	Debug->EndLine();*/ // 숫자 4 누르면 나오는 카메라 디버그 텍스트에 있음
	Debug->AddText("잔탄 수 : ");
	Debug->AddText(g_pCamera->getMagazine());
	Debug->EndLine();
	/*Debug->AddText("Bounding Box Collision with Ray: ");
	Debug->AddText(getHitBox);
	Debug->EndLine();
	Debug->AddText("Bounding Box Collision with Player: ");
	Debug->AddText(getCollision);
	Debug->EndLine();*/
	/*Debug->AddText("volume(music) : ");
	Debug->AddText(volume_music);
	Debug->EndLine();*/
}

void SceneHeightmap::Render()
{

	OnRenderIScene();
	SAFE_RENDER(m_ColorCube);
	SAFE_RENDER(m_pBlocks);
	SAFE_RENDER(m_pUnit);
	SAFE_RENDER(m_SkyBox);
	SAFE_RENDER(m_minimap);
	m_CreateSmog->Render();
	//m_pPicking->Render();

	//obj 관련
	m_ObjRender->Render();
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
