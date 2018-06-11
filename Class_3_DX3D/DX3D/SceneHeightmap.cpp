#include "stdafx.h"
#include "SceneHeightmap.h"
#include "HeightMap.h"
#include "AseCharacter.h"
//#include "Picking.h"
#include "SampleUI.h"
#include "ParticleTest.h"

#include "SkinnedMesh.h"
#include "SkyBox.h"

#include <Psapi.h>

//안개생성
#include "CreateSmog.h"
#include "ColorCube.h"
#include "Player_hands.h"

//중현이코드
#include "UnitBox.h"
#include "Blocks.h"

#include "IUIObject.h"
#include "UIImage.h"



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

	m_pSprite = NULL;
	m_pSprite2 = NULL;
	m_pCrosshair = NULL;
	m_pScope = NULL;
	pImage = NULL;
	pImage2 = NULL;
	m_pCrosshairOn = false;
	m_pCrosshairOn = false;

	//	m_pSkinnedMesh = NULL;

}


SceneHeightmap::~SceneHeightmap()
{
	SAFE_RELEASE(m_pBlocks);
	SAFE_RELEASE(m_SkyBox);
	SAFE_RELEASE(m_ColorCube);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pSprite2);
	//SAFE_RELEASE(m_Player_hands);
	//SAFE_RELEASE(pImage);
	SAFE_RELEASE(m_pCrosshair);
	SAFE_RELEASE(m_pScope);
	//m_pCrosshair->ReleaseAll();
	//m_CreateSmog->Release();
	//SAFE_RELEASE(m_CreateSmog);


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

	D3DXCreateSprite(g_pDevice, &m_pSprite);
	pImage = new UIImage(m_pSprite);
	pImage->m_bDrawBorder = false;
	pImage->SetTexture("resources/ui/Crosshair.png");
	pImage->SetPosition(&D3DXVECTOR3((rc.left + rc.right) / 2 - 64, (rc.top + rc.bottom) / 2 - 52, 0));
	m_pCrosshair = pImage;
	D3DXCreateSprite(g_pDevice, &m_pSprite2);
	pImage2 = new UIImage(m_pSprite2);
	pImage2->m_bDrawBorder = false;
	pImage2->SetTexture("resources/ui/Scope.png");
	pImage2->SetPosition(&D3DXVECTOR3(20.5f, -9.5f, 0.0f));
	m_pScope = pImage2;

	m_Player_hands = new Player_hands;
	m_Player_hands->Init();

	AddSimpleDisplayObj(m_Player_hands);

	g_pSoundManager->createSound(); // 음악 세팅
	g_pSoundManager->createSound(); // 사운드 세팅								
	g_pSoundManager->playAmbient(0); // 실행 시 환경음 자동 재생 (반복)
}

void SceneHeightmap::Update()
{
	//m_CreateSmog->Update();


	SAFE_UPDATE(m_ColorCube);


	SAFE_UPDATE(m_pCrosshair);
	SAFE_UPDATE(m_pScope);
	OnUpdateIScene();

	if (g_pCamera->getFreeCameraMode()) {
		m_pCrosshairOn = false;
	}
	else {
		m_pCrosshairOn = true;
	}

	g_pCamera->getPMobFromUnitBox(m_pUnit->getPMob());

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

	if (musicPlay)
		soundSt = "[ Music Play ]";
	else
		soundSt = "[ Music Stop ]";

	Debug->AddText(soundSt);
	Debug->EndLine();

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

void SceneHeightmap::Render()
{

	OnRenderIScene();
	SAFE_RENDER(m_ColorCube);
	SAFE_RENDER(m_pBlocks);

	SAFE_RENDER(m_SkyBox);
	m_CreateSmog->Render();
	//m_pPicking->Render();

	if (m_pCrosshairOn) {
		if (m_pScopeOn & g_pCamera->getCooldown() <= 0) {
			g_pDevice->SetTexture(0, NULL);
			m_pSprite2->Begin(D3DXSPRITE_ALPHABLEND);
			D3DXMATRIX mat;
			D3DXVECTOR2 scaling(1.5f, 1.5f);
			D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &D3DXVECTOR2(0.0f, 0.0f), 0.0f, &D3DXVECTOR2(-160.0f, 0.0f));
			m_pSprite2->SetTransform(&mat);
			SAFE_RENDER(m_pScope);
			m_pSprite2->End();
		}
		else {
			g_pDevice->SetTexture(0, NULL);
			m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
			//m_pSprite->SetTransform(&m_matWorld);
			SAFE_RENDER(m_pCrosshair);
			m_pSprite->End();
		}
	}

}

void SceneHeightmap::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SAFE_WNDPROC(m_pHeightMap);
	//SAFE_WNDPROC(m_pPicking);
	//SAFE_WNDPROC(m_pUnit);
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
