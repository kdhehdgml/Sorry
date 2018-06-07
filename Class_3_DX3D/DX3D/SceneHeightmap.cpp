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


	//중현이코드
	m_pBlocks = NULL;

	m_pSprite = NULL;
	m_pCrosshair = NULL;
	pImage = NULL;
	m_pCrosshairOn = false;

//	m_pSkinnedMesh = NULL;

}


SceneHeightmap::~SceneHeightmap()
{
	SAFE_RELEASE(m_pBlocks);
	SAFE_RELEASE(m_SkyBox);
	SAFE_RELEASE(m_ColorCube);
	SAFE_RELEASE(m_pSprite);
	//SAFE_RELEASE(pImage);
	SAFE_RELEASE(m_pCrosshair);
	//m_pCrosshair->ReleaseAll();
	//m_CreateSmog->Release();
	//SAFE_RELEASE(m_CreateSmog);


	OnDestructIScene();
}

void SceneHeightmap::Init()
{
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.0f, 0.06f , 1.0f);

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
	//맨왼쪾 맨위 좌표
	//460.0f, 70.0f, 485.0f
	m_CreateSmog->Insert(D3DXVECTOR3(460.0f, 70.0f, 485.0f ),(0.6f));
	m_CreateSmog->Insert(D3DXVECTOR3(400.0f, 70.0f, 405.0f), (0.3f));
	m_CreateSmog->Insert(D3DXVECTOR3(440.0f, 70.0f, 305.0f), (0.5f));
	m_CreateSmog->Insert(D3DXVECTOR3(350.0f, 70.0f, 205.0f), (0.6f));
	m_CreateSmog->Insert(D3DXVECTOR3(400.0f, 70.0f, 155.0f), (0.3f));
	m_CreateSmog->Insert(D3DXVECTOR3(440.0f, 70.0f, 105.0f), (0.8f));
	//m_CreateSmog->Insert(D3DXVECTOR3(460.0f, 70.0f, 485.0f), (0.6f));
	//m_CreateSmog->Insert(D3DXVECTOR3(460.0f, 70.0f, 485.0f), (0.6f));
	//m_CreateSmog->Insert(D3DXVECTOR3(460.0f, 70.0f, 485.0f), (0.6f));
	
	
	AddSimpleDisplayObj(m_CreateSmog);


	m_ColorCube = new ColorCube;
	m_ColorCube->Init();


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
	pImage->SetTexture("resources/ui/crosshair.png");
	pImage->SetPosition(&D3DXVECTOR3((rc.left + rc.right) / 2 - 60, (rc.top + rc.bottom) / 2 - 56, 0));
	m_pCrosshair = pImage;

	g_pSoundManager->setMusic(); // 음악 세팅
}

void SceneHeightmap::Update()
{
	//m_CreateSmog->Update();

	
	SAFE_UPDATE(m_ColorCube);
	
	
	SAFE_UPDATE(m_pCrosshair);
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
	Debug->AddText((int)(pmc.WorkingSetSize/1024));
	Debug->AddText("KB");
	Debug->EndLine();



	

	// F5 키 누르면 음악 재생 ON / OFF
	if ((GetAsyncKeyState(VK_F5) & 0x8000))
	{
		if (!musicPlayCheck)
		{
			musicPlayCheck = true;

			if (!musicPlay)
			{
				musicPlay = true;
				g_pSoundManager->playSound(0);
			}
			else
			{
				musicPlay = false;
				g_pSoundManager->stopSound(0);
			}
		}
	}
	else if (musicPlayCheck)
		musicPlayCheck = false;

	if(musicPlay)
		soundSt = "[ Music Play ]";
	else
		soundSt = "[ Music Stop ]";

	Debug->AddText(soundSt);
	Debug->EndLine();
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
		g_pDevice->SetTexture(0, NULL);
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		//m_pSprite->SetTransform(&m_matWorld);
		SAFE_RENDER(m_pCrosshair);
		m_pSprite->End();
	}

}

void SceneHeightmap::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SAFE_WNDPROC(m_pHeightMap);
	//SAFE_WNDPROC(m_pPicking);
	//SAFE_WNDPROC(m_pUnit);
}
