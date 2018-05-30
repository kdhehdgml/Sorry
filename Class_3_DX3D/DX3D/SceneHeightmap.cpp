#include "stdafx.h"
#include "SceneHeightmap.h"
#include "HeightMap.h"
#include "AseCharacter.h"
#include "Picking.h"
#include "SampleUI.h"
#include "ParticleTest.h"

#include "SkinnedMesh.h"
#include "SkyBox.h"


//안개생성
#include "CreateSmog.h"

//중현이코드
#include "Cubeman.h"
#include "Mob.h"
#include "Blocks.h"

SceneHeightmap::SceneHeightmap()
{
	m_pHeightMap = NULL;
	m_pAseCharacter = NULL;
	m_pPicking = NULL;

	//영락코드
	m_CreateSmog = NULL;
	m_SkyBox = NULL;


	//중현이코드
	m_pCubeman = NULL;
	m_pBlocks = NULL;


//	m_pSkinnedMesh = NULL;
}


SceneHeightmap::~SceneHeightmap()
{
	SAFE_RELEASE(m_pBlocks);
	SAFE_RELEASE(m_SkyBox);
	m_CreateSmog->Relese();
	OnDestructIScene();
	
	
	
	
}

void SceneHeightmap::Init()
{
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 0.2f, 0.03f, 0.2f);

	m_pHeightMap = new HeightMap; AddSimpleDisplayObj(m_pHeightMap);
	m_pHeightMap->SetDimension(257);
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

	//m_pPicking = new Picking; m_pPicking->Init();
	//	AddSimpleDisplayObj(m_pPicking);

	//IDisplayObject* pObj;
	////pObj = new SampleUI; pObj->Init(); AddSimpleDisplayObj(pObj);
	//pObj = new ParticleTest; pObj->Init(); AddSimpleDisplayObj(pObj);
	//


	//중현이코드
	m_pCubeman = new Cubeman; m_pCubeman->Init();
	AddSimpleDisplayObj(m_pCubeman);

	m_pMob.resize(5);
	for (size_t i = 0; i < m_pMob.size(); i++)
	{
		m_pMob[i] = new Mob;
		m_pMob[i]->Init();
		m_pMob[i]->SetPosition(&D3DXVECTOR3(50.0f, 5.0f, (i + 1) * 10));
		AddSimpleDisplayObj(m_pMob[i]);
	}

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

	m_CreateSmog->Insert(D3DXVECTOR3(10.0f, 0.0f, 50.0f));
	
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


}

void SceneHeightmap::Update()
{
	
	m_CreateSmog->Update();

	OnUpdateIScene();

	if (m_pMob[0]->PlayerSearch(m_pCubeman->GetPosition(), m_pMob[0]) == true)
	{
		m_pMob[0]->Update();
		m_pMob[0]->SetDestination(m_pCubeman->GetPosition());


	}
	if (m_pMob[1]->PlayerSearch(m_pCubeman->GetPosition(), m_pMob[1]) == true)
	{
		m_pMob[1]->Update();
		m_pMob[1]->SetDestination(m_pCubeman->GetPosition());

	}
	if (m_pMob[2]->PlayerSearch(m_pCubeman->GetPosition(), m_pMob[2]) == true)
	{
		m_pMob[2]->Update();
		m_pMob[2]->SetDestination(m_pCubeman->GetPosition());

	}
	if (m_pMob[3]->PlayerSearch(m_pCubeman->GetPosition(), m_pMob[3]) == true)
	{
		m_pMob[3]->Update();
		m_pMob[3]->SetDestination(m_pCubeman->GetPosition());

	}
	if (m_pMob[4]->PlayerSearch(m_pCubeman->GetPosition(), m_pMob[4]) == true)
	{
		m_pMob[4]->Update();
		m_pMob[4]->SetDestination(m_pCubeman->GetPosition());

	}
	m_pMob[0]->ShootVertex(m_pCubeman->GetPosition(), m_pMob[0]);
	m_pMob[1]->ShootVertex(m_pCubeman->GetPosition(), m_pMob[1]);
	m_pMob[2]->ShootVertex(m_pCubeman->GetPosition(), m_pMob[2]);
	m_pMob[3]->ShootVertex(m_pCubeman->GetPosition(), m_pMob[3]);
	m_pMob[4]->ShootVertex(m_pCubeman->GetPosition(), m_pMob[4]);
}

void SceneHeightmap::Render()
{

	OnRenderIScene();
	
	SAFE_RENDER(m_pBlocks);

	SAFE_RENDER(m_SkyBox);
	m_CreateSmog->Render();
	
}

void SceneHeightmap::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SAFE_WNDPROC(m_pHeightMap);
	//SAFE_WNDPROC(m_pPicking);
}
