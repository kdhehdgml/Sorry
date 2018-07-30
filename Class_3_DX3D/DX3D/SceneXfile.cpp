#include "stdafx.h"
#include "SceneXfile.h"
#include "SkinnedMesh.h"
#include "SkinnedMeshHLSL.h"

//¹«±â
#include "GUN.h"
#include "SHOVEL.h"
#include "Smle.h"

#include "SkyBox.h"
//Àåºñ
#include "FR_HEADGEAR.h"
//Ä³¸¯ÅÍ
#include "TEAM_TEX.h"
#include "MONSTER.h"

#include "MARK.h"
//#include "ALLTexTURE.h"


SceneXfile::SceneXfile()
{
	m_pSkinnedMesh = NULL;
	m_SkyBox = NULL;
	m_GUN = NULL;
	m_SHOVEL = NULL;
//	m_ALLTexTURE = NULL;
	m_MONSTER = NULL;
	m_TEAM_TEX = NULL;
	m_MARK = NULL;
	m_Smle = NULL;
	m_FR_HEADGEAR = NULL;
}


SceneXfile::~SceneXfile()
{
	//SAFE_RELEASE(m_GUN);
	//SAFE_RELEASE(m_SHOVEL);
	//SAFE_RELEASE(m_pSkinnedMesh);
	//SAFE_RELEASE(m_MONSTER);
	SAFE_RELEASE(m_TEAM_TEX);
	//SAFE_RELEASE(m_MARK);
	SAFE_RELEASE(m_Smle);
	SAFE_RELEASE(m_FR_HEADGEAR);
	

	OnDestructIScene();
	/*m_GUN->Release();
	m_pSkinnedMesh->Release();*/
}

void SceneXfile::Init()
{

	//g_pCamera->SetType(Camera::Type_LookTarget);
	//g_pCamera->SetOffset(&D3DXVECTOR3(0, 5, -10));

	/*m_pSkinnedMesh = new SkinnedMesh;
	m_pSkinnedMesh->Init();*/
	//AddSimpleDisplayObj(m_pSkinnedMesh);

	//m_GUN = new GUN;
	//m_GUN->Init();
	//AddSimpleDisplayObj(m_GUN);

	m_Smle = new Smle;
	m_Smle->Init();
	//AddSimpleDisplayObj(m_Smle);
	m_FR_HEADGEAR = new FR_HEADGEAR;
	m_FR_HEADGEAR->Init();


	m_SkyBox = new SkyBox;
	m_SkyBox->Init();
	AddSimpleDisplayObj(m_SkyBox);

	//m_SHOVEL = new SHOVEL;
	//m_SHOVEL->Init();


	m_TEAM_TEX = new TEAM_TEX;
	m_TEAM_TEX->Init();
	//AddSimpleDisplayObj(m_TEAM_TEX);

	//m_MONSTER = new MONSTER;
	//m_MONSTER->Init();
	//AddSimpleDisplayObj(m_MONSTER);
	
	//IDisplayObject* pObj = NULL;
	//
	//
	//for (int i = 0; i < 1; i++)
	//{

	//	/*
	//	CString path = "resources/xFile/MONSTER_AI/";
	//	CString filename = "MOB_ANI_ALL2.X";
	//	
	//	*/
	//	float radian = D3DX_PI * 2 * i / (10.0f + (int)(i / 10));
	//	float radius = 3.0f + 2.5f * (int)(i / 10);
	//	pObj = new SkinnedMeshHLSL(_T("resources/xFile/zealot/"), _T("zealot.X")); pObj->Init(); AddSimpleDisplayObj(pObj);
	//	//pObj = new SkinnedMesh2(ASSET_PATH + _T("Models/player/"), _T("combine_All.X")); pObj->Init(); AddDisplayObject(pObj);
	//	//pObj->SetPosition(&D3DXVECTOR3(cosf(radian) * radius, 0, sinf(radian) * radius));
	//	pObj->SetPosition(&D3DXVECTOR3(0,0,0));
	//	m_vector3.push_back(D3DXVECTOR3(cosf(radian) * radius, 0, sinf(radian) * radius));
	//	
	//}

	//m_MARK = new MARK;
	//m_MARK->Init();

	g_pCamera->mouseLock = true;
	g_pCamera->setPos(D3DXVECTOR3(0, 0, 0));

}

void SceneXfile::Update()
{
	//Debug->EndLine();
	//for (int i = 0; i < m_vector3.size(); i++)
	//{
	//	Debug->AddText(m_vector3[i]);
	//	Debug->EndLine();
	//}
	D3DXVECTOR3 dir(1.0f, -10.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, true);

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	//m_MARK->Update();
	m_TEAM_TEX->Update();
	m_FR_HEADGEAR->SetMat(m_TEAM_TEX->GetHeadMatRot());
	m_FR_HEADGEAR->SetPos(m_TEAM_TEX->GetHeadPos());
//	m_FR_HEADGEAR->SetAngle(m_TEAM_TEX->GetAngle() + ((D3DX_PI / 2)));

	m_FR_HEADGEAR->Update();
	//m_pSkinnedMesh->Update();
	//m_GUN->SetPos(m_pSkinnedMesh->GetG3unPos());
	//m_MONSTER->Update();

	//if (m_MONSTER->m_AnimaTionIndex != 7)
	//	m_GUN->SetMat(m_MONSTER->GetLeftMat());
	//else
	//	m_GUN->SetMat(m_MONSTER->GetRightMat());
	//	//m_GUN->SetPos(m_MONSTER->GetRightPos());

	//m_GUN->SetAngle(m_MONSTER->GetAngle());
	//m_GUN->SetAniIndex(m_MONSTER->m_AnimaTionIndex);

	//m_GUN->Update();

	//m_Smle->SetMat(m_TEAM_TEX->GetLeftMat());
	m_Smle->SetPos(m_TEAM_TEX->GetLeftPos());
	m_Smle->SetAngle(m_TEAM_TEX->GetAngle() + (-(D3DX_PI/2)));
	m_Smle->SetAniIndex(m_TEAM_TEX->m_AnimaTionIndex);
	m_Smle->Update();

	//m_SHOVEL->SetPos(m_MONSTER->GetRightPos());
	//m_SHOVEL->SetMatR(m_MONSTER->GetRotMat());
	//m_SHOVEL->SetMat(m_MONSTER->GetRightMat());

	//m_SHOVEL->Update();
	
	//Debug->AddText("matPos ÁÂÇ¥: ");
	//Debug->AddText(*m_MONSTER->GetRightPos());
	//Debug->EndLine();
	//Debug->AddText("matScale ÁÂÇ¥: ");
	//Debug->AddText(m_MONSTER->GetScaleMat());
	//Debug->EndLine();
	//Debug->AddText("matXY ÁÂÇ¥: ");
	//Debug->AddText(m_MONSTER->GetXYMat());
	//Debug->EndLine();



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
	//m_GUN->Render();
	//m_SHOVEL->Render();
	m_TEAM_TEX->Render();
	//m_MONSTER->Render();
	m_Smle->Render();
	m_FR_HEADGEAR->Render();
	//m_MARK->Render();
	OnRenderIScene();

}

void SceneXfile::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return;
}
