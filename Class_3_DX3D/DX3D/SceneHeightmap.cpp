#include "stdafx.h"
#include "SceneHeightmap.h"
#include "HeightMap.h"
#include "AseCharacter.h"
#include "SampleUI.h"
#include "ParticleTest.h"

#include "SkinnedMesh.h"
#include "SkyBox.h"

#include <Psapi.h>

//안개생성
#include "CreateSmog.h"
#include "ColorCube.h"
#include "Player_hands.h"
#include "MONSTER.h"

//중현이코드
#include "UnitBox.h"
#include "Blocks.h"

#include "IUIObject.h"
#include "UIImage.h"

#include "ObjRen.h"// obj 해더


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

	//	m_pSkinnedMesh = NULL;
	volume_music = GSM().volume_music_init;

	// obj 관련
	m_Tree = NULL;
	m_Stone = NULL;
	m_MD = NULL;
	m_wall01 = NULL;
	m_wall02 = NULL;
	m_wall03 = NULL;
	m_wall04 = NULL;
	m_wall05 = NULL;
	m_wall06 = NULL;
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
	//m_pCrosshair->ReleaseAll();
	//m_CreateSmog->Release();
	//SAFE_RELEASE(m_CreateSmog);

	//obj 관련 직접 접근해서 릴리즈함
	m_Tree->~ObjRen();
	m_Stone->~ObjRen();
	m_MD->~ObjRen();
	m_wall01->~ObjRen();
	m_wall02->~ObjRen();
	m_wall03->~ObjRen();
	m_wall04->~ObjRen();
	m_wall05->~ObjRen();
	m_wall06->~ObjRen();

	OnDestructIScene();
}

void SceneHeightmap::Init()
{
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.0f, 0.06f, 1.0f);

	m_pHeightMap = new HeightMap; AddSimpleDisplayObj(m_pHeightMap);
	m_pHeightMap->SetDimension(GSM().mapSize);
	m_pHeightMap->Load("resources/heightmap/HeightMap.raw", &matS);
	m_pHeightMap->Init();
	D3DMATERIAL9 mtl = DXUtil::WHITE_MTRL;


	m_pHeightMap->SetMtlTex(mtl,
		g_pTextureManager->GetTexture(L"resources/heightmap/terrain.jpg"));

	g_pMapManager->AddMap("heightmap", m_pHeightMap);
	g_pMapManager->SetCurrentMap("heightmap");

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
	m_Tree = new ObjRen; m_Tree->Init(80.0f, _T("resources/obj/Tree/TreeStage.obj"), _T("resources/obj/Tree/tree-high_b_dead_clr.png"), 250, 14, 230, 0);
	m_Stone = new ObjRen; m_Stone->Init(80.0f, _T("resources/obj/Stone/StoneStage.obj"), _T("resources/obj/Stone/StoneDetail edit.png"), 250, 5, 230, 0);
	m_MD = new ObjRen; m_MD->Init(90.0f, _T("resources/obj/MD/MD.obj"), _T("resources/obj/MD/MD.png"), 210, 8, 250, 0);
	m_wall01 = new ObjRen; m_wall01->Init(5.0f, _T("resources/obj/wall/wall01.obj"), _T("resources/obj/wall/wall01.png"), 332, 8, 291, 1.6);
	m_wall02 = new ObjRen; m_wall02->Init(5.0f, _T("resources/obj/wall/wall01.obj"), _T("resources/obj/wall/wall01.png"), 243, 8, 356, 1.6);
	m_wall03 = new ObjRen; m_wall03->Init(5.0f, _T("resources/obj/wall/wall02.obj"), _T("resources/obj/wall/wall02.png"), 333, 8, 242, 1.6);
	m_wall04 = new ObjRen; m_wall04->Init(5.0f, _T("resources/obj/wall/wall02.obj"), _T("resources/obj/wall/wall02.png"), 297, 8, 337, 1.6);
	m_wall05 = new ObjRen; m_wall05->Init(5.0f, _T("resources/obj/wall/wall02.obj"), _T("resources/obj/wall/wall02.png"), 187, 8, 240, 1.6);
	m_wall06 = new ObjRen; m_wall06->Init(5.0f, _T("resources/obj/wall/wall02.obj"), _T("resources/obj/wall/wall02.png"), 242, 8, 217, 1.6);


	//중현이코드
	m_pUnit = new UnitBox();
	m_pUnit->SetLocation(m_pHeightMap->SetWall());
	m_pUnit->Init();
	AddSimpleDisplayObj(m_pUnit);


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

	m_minimap = new Minimap;
	m_minimap->Init();
	m_minimap->getPMobFromUnitBox(m_pUnit->getPMob());
	m_minimap->getPTeamFromUnitBox(m_pUnit->getPTeam());

	AddSimpleDisplayObj(m_Player_hands);

	g_pSoundManager->createSound(); // 사운드 세팅								
	g_pSoundManager->playAmbient(0); // 실행 시 환경음 자동 재생 (반복)
}

void SceneHeightmap::Update()
{
	//m_CreateSmog->Update();


	SAFE_UPDATE(m_ColorCube);

	SAFE_UPDATE(m_minimap);
	SAFE_UPDATE(m_pCrosshair);
	SAFE_UPDATE(m_pScope);
	SAFE_UPDATE(m_pTalk);
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

	Debug->AddText("시스템 메모리 : ");
	Debug->AddText((int)(pmc.WorkingSetSize / 1024));
	Debug->AddText("KB");
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
	bool getHit = false;
	//float conWidth = cos(30 * D3DX_PI / 180.0f);
	float conWidth = 0.866f;
	//Ray r = Ray::RayAtWorldSpace(SCREEN_POINT(m_pLParam));
	for (auto p : m_pTeam){
		D3DXVECTOR3 teamPos = p->GetPosition(); //팀 위치
		D3DXVECTOR3 playerPos = g_pCamera->getPos(); //내 위치
		teamPos.y += 7.0f;
		D3DXVECTOR3 playerDir = g_pCamera->getDir();
		D3DXVECTOR3 posDiff = teamPos - playerPos;
		D3DXVECTOR3 lookDir;
		D3DXVec3Normalize(&lookDir, &posDiff);
		float viewAngle = D3DXVec3Dot(&playerDir, &lookDir);
		float distance = sqrtf(D3DXVec3Dot(&posDiff, &posDiff)); //아군과의 거리 계산
		if (distance < minDistance) {
			minDistance = distance; //가장 가까운 아군과의 거리만 남긴다
			if (minDistance < 10.0f) {
				if (viewAngle > conWidth) {
					getHit = true;
				}
			}
		}
	}
	if (minDistance < 4.0f) {
		g_pCamera->setPos(m_pPlayerOldPos);
	}
	m_pPlayerOldPos = g_pCamera->getPos();
	if (getHit) {
		m_pTalkOn = true;
	}
	else {
		m_pTalkOn = false;
	}
	Debug->AddText("아군과의 거리 : ");
	Debug->AddText(minDistance);
	Debug->EndLine();
	Debug->AddText("volume(music) : ");
	Debug->AddText(volume_music);
	Debug->EndLine();
}

void SceneHeightmap::Render()
{

	OnRenderIScene();
	SAFE_RENDER(m_ColorCube);
	SAFE_RENDER(m_pBlocks);

	SAFE_RENDER(m_SkyBox);
	SAFE_RENDER(m_minimap);
	m_CreateSmog->Render();
	//m_pPicking->Render();

	//obj 관련
	SAFE_RENDER(m_Tree);
	SAFE_RENDER(m_Stone);
	SAFE_RENDER(m_MD);
	SAFE_RENDER(m_wall01);
	SAFE_RENDER(m_wall02);
	SAFE_RENDER(m_wall03);
	SAFE_RENDER(m_wall04);
	SAFE_RENDER(m_wall05);
	SAFE_RENDER(m_wall06);

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
			SAFE_RENDER(m_pCrosshair);
			m_pCrosshairSprite->End();
		}
	}
	if (m_pTalkOn) {
		g_pDevice->SetTexture(0, NULL);
		m_pTalkSprite->Begin(D3DXSPRITE_ALPHABLEND);
		SAFE_RENDER(m_pTalk);
		m_pTalkSprite->End();
	}
}

void SceneHeightmap::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SAFE_WNDPROC(m_pHeightMap);
	//SAFE_WNDPROC(m_pPicking);
	//SAFE_WNDPROC(m_pUnit);
	
	m_pLParam = lParam;

	switch (message) {
	case WM_RBUTTONDOWN:
		if (m_pCrosshairOn) {
			m_pScopeOn = true;
		}
		break;
	case WM_RBUTTONUP:
		m_pScopeOn = false;
		break;
	}
}
