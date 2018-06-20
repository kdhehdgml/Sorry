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

	g_pSoundManager->createSound();
	g_pSoundManager->play3D(0);
}

void SceneTest::Update()
{
	g_pSoundManager->update3D(0, g_pCamera->getPos(), SpeakerPos);

	if (GetKeyState('1') & 0x8000)
	{
		SpeakerPos = g_pSoundManager->getListenerPos();
	}

	Debug->AddText("Listener Pos : ");
	Debug->AddText(g_pSoundManager->getListenerPos());
	Debug->EndLine();
	Debug->AddText("Speaker Pos : ");
	Debug->AddText(g_pSoundManager->getSpeakerPos());
	Debug->EndLine();
	Debug->AddText("L--S Distance : ");
	Debug->AddText(g_pSoundManager->getSpeakerPos() - g_pSoundManager->getListenerPos());
	Debug->EndLine();

	OnUpdateIScene();
}

void SceneTest::Render()
{
	OnRenderIScene();
	
}

void SceneTest::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
