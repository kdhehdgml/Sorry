#include "stdafx.h"
#include "SceneXfile.h"
#include "SkinnedMesh.h"
#include "SkyBox.h"


SceneXfile::SceneXfile()
{
	m_pSkinnedMesh = NULL;
	m_SkyBox = NULL;
}


SceneXfile::~SceneXfile()
{
	OnDestructIScene();
}

void SceneXfile::Init()
{
	m_pSkinnedMesh = new SkinnedMesh;
	m_pSkinnedMesh->Init();
	AddSimpleDisplayObj(m_pSkinnedMesh);

	m_SkyBox = new SkyBox;
	m_SkyBox->Init();
	AddSimpleDisplayObj(m_SkyBox);

}

void SceneXfile::Update()
{
	OnUpdateIScene();

}

void SceneXfile::Render()
{
	OnRenderIScene();

}

void SceneXfile::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
