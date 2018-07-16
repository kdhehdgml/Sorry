#include "stdafx.h"
#include "SceneXfile.h"
#include "SkinnedMesh.h"

//무기
#include "GUN.h"
#include "SHOVEL.h"
#include "Smle.h"

#include "SkyBox.h"
//장비
#include "FR_HEADGEAR.h"
#include "DE_HEADGEAR.h"
//캐릭터
#include "TEAM_TEX.h"
#include "MONSTER.h"
//#include "ALLTexTURE.h"


SceneXfile::SceneXfile()
{
	m_pSkinnedMesh = NULL;
	m_SkyBox = NULL;
	m_GUN = NULL;
	m_SHOVEL = NULL;
//	m_ALLTexTURE = NULL;
	m_DE_HEADGEAR = NULL;
	m_FR_HEADGEAR = NULL;
	m_TEAM_TEX = NULL;
}


SceneXfile::~SceneXfile()
{
	SAFE_RELEASE(m_GUN);
	SAFE_RELEASE(m_SHOVEL);
	SAFE_RELEASE(m_pSkinnedMesh);
	SAFE_RELEASE(m_DE_HEADGEAR);
	SAFE_RELEASE(m_FR_HEADGEAR);
	//SAFE_RELEASE(m_MONSTER);
	//SAFE_RELEASE(m_TEAM_TEX);

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

	m_DE_HEADGEAR = new DE_HEADGEAR;
	m_DE_HEADGEAR->Init();

	m_FR_HEADGEAR = new FR_HEADGEAR;
	m_FR_HEADGEAR->Init();

	/*m_TEAM_TEX = new TEAM_TEX;
	m_TEAM_TEX->Init();*/
	//AddSimpleDisplayObj(m_TEAM_TEX);

	m_MONSTER = new MONSTER;
	m_MONSTER->Init();
	AddSimpleDisplayObj(m_MONSTER);


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
	//m_GUN->SetPos(m_pSkinnedMesh->GetG3unPos());

	if(m_MONSTER->m_AnimaTionIndex != 7)
		m_GUN->SetMat(m_MONSTER->GetLeftMat());
	else
		m_GUN->SetMat(m_MONSTER->GetRightMat());

	m_GUN->SetAngle(m_MONSTER->GetAngle());
	m_GUN->SetAniIndex(m_MONSTER->m_AnimaTionIndex);

	m_GUN->Update();

	m_SHOVEL->SetMat(m_MONSTER->GetRightMat());
	m_SHOVEL->Update();

	//m_DE_HEADGEAR->SetMat(m_pSkinnedMesh->GetHeadMat());
	//m_DE_HEADGEAR->Update();

	//m_FR_HEADGEAR->SetMat(m_pSkinnedMesh->GetHeadMat2());
	//m_FR_HEADGEAR->Update();

	Debug->AddText(D3DXVECTOR3(*m_pSkinnedMesh->GetRightMat()));
	Debug->EndLine();
	Debug->AddText(D3DXVECTOR3(*m_pSkinnedMesh->GetHeadMat()));
	Debug->EndLine();
	Debug->AddText(D3DXVECTOR3(*m_pSkinnedMesh->GetHeadMat2()));
	Debug->EndLine();
	//Debug->EndLine();
	//Debug->AddText(m_pSkinnedMesh->GetGunPos());
	//Debug->AddText("/");
	//Debug->AddText(m_GUN->GetPosition());
	//Debug->EndLine();

	OnUpdateIScene();

}

void SceneXfile::Render()
{
	//m_pSkinnedMesh->Render();
	m_GUN->Render();
	m_SHOVEL->Render();
	m_FR_HEADGEAR->Render();
	m_DE_HEADGEAR->Render();
	//m_MONSTER->Render();
	OnRenderIScene();

}

void SceneXfile::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
