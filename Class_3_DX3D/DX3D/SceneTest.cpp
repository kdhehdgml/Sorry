#include "stdafx.h"
#include "SceneTest.h"
#include "Frustum.h"
#include "Grid.h"
#include "ParticleTest.h"
#include "SkyBox.h"

SceneTest::SceneTest()
{
	m_pGrid = NULL;
	m_SkyBox = NULL;
}


SceneTest::~SceneTest()
{
	
	OnDestructIScene();
}

void SceneTest::Init()
{
	m_pGrid = new Grid; m_pGrid->Init();

	//IDisplayObject* pObj = NULL;
	//pObj = new Frustum; pObj->Init(); AddSimpleDisplayObj(pObj);
	//pObj = new ParticleTest; pObj->Init(); AddSimpleDisplayObj(pObj);


	D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, true);

	//g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	//g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//g_pDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//g_pDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	m_SkyBox = new SkyBox;
	m_SkyBox->Init();
	AddSimpleDisplayObj(m_SkyBox);
}

void SceneTest::Update()
{
	g_pSeqManager->Update();

	OnUpdateIScene();
}

void SceneTest::Render()
{
	OnRenderIScene();
	
}

void SceneTest::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
