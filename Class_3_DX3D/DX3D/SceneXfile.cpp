#include "stdafx.h"
#include "SceneXfile.h"
#include "SkinnedMesh.h"

#include "GUN.h"
#include "SHOVEL.h"

#include "SkyBox.h"

//#include "ALLTexTURE.h"


SceneXfile::SceneXfile()
{
	m_pSkinnedMesh = NULL;
	m_SkyBox = NULL;
	m_GUN = NULL;
	m_SHOVEL = NULL;
//	m_ALLTexTURE = NULL;
}


SceneXfile::~SceneXfile()
{

	OnDestructIScene();
	/*m_GUN->Release();
	m_pSkinnedMesh->Release();*/
}

void SceneXfile::Init()
{
	m_pSkinnedMesh = new SkinnedMesh;
	m_pSkinnedMesh->Init();
	//AddSimpleDisplayObj(m_pSkinnedMesh);

	m_GUN = new GUN;
	m_GUN->Init();
	//AddSimpleDisplayObj(m_GUN);

	m_SkyBox = new SkyBox;
	m_SkyBox->Init();
	AddSimpleDisplayObj(m_SkyBox);

	m_SHOVEL = new SHOVEL;
	m_SHOVEL->Init();


}

void SceneXfile::Update()
{
	D3DXVECTOR3 dir(1.0f, -10.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, true);

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	
	m_pSkinnedMesh->Update();
	//m_GUN->SetPos(m_pSkinnedMesh->GetGunPos());
	m_GUN->SetMat(m_pSkinnedMesh->GetGunMat());
	m_GUN->Update();

	Debug->EndLine();
	Debug->AddText(m_pSkinnedMesh->GetGunPos());
	Debug->AddText("/");
	Debug->AddText(m_GUN->GetPosition());
	Debug->EndLine();

	OnUpdateIScene();

}

void SceneXfile::Render()
{
	m_pSkinnedMesh->Render();
	m_GUN->Render();
	OnRenderIScene();

}

void SceneXfile::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
