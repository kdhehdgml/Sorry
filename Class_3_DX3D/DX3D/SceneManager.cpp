#include "stdafx.h"
#include "SceneManager.h"
#include "IScene.h"
#include "SceneGrid.h"
#include "SceneObjMap.h"
#include "SceneHeightmap.h"
#include "SceneTest.h"
#include "SceneXfile.h"
#include "SceneLoading.h"
#include "SceneMainScreen.h"

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	m_vecScene.push_back(new SceneMainScreen());
	m_vecScene.push_back(new SceneLoading());
	SetCurrentScene(GSM().InitScene);
	//SetCurrentScene(SCENE_LOADING);
	//m_pCurrSceneString = "SCENE_LOADING";
	//SAFE_RENDER(m_pCurrScene);
	m_vecScene.push_back(new SceneHeightmap());
	m_vecScene.push_back(new SceneGrid());
	m_vecScene.push_back(new SceneObjMap());
	m_vecScene.push_back(new SceneTest());
	m_vecScene.push_back(new SceneXfile());

	//SetCurrentScene(SCENE_GRID);
	//SetCurrentScene(SCENE_OBJMAP);
	//SetCurrentScene(SCENE_HEIGHTMAP);
	//SetCurrentScene(SCENE_TEST);
	//SetCurrentScene(SCENE_XFILE);

	
}

void SceneManager::Destroy()
{
	for (auto p : m_vecScene)
	{
 		SAFE_RELEASE(p);
	}
}

void SceneManager::Update()
{
	SAFE_UPDATE(m_pCurrScene);
	/*Debug->AddText("ÇöÀç ¾À : ");
	Debug->AddText(m_pCurrSceneString);
	Debug->EndLine();*/
}

void SceneManager::Render()
{
	SAFE_RENDER(m_pCurrScene);
}

void SceneManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//if (m_pCurrScene) m_pCurrScene->WndProc(hWnd, message, wParam, lParam);

	SAFE_WNDPROC(m_pCurrScene);
}

void SceneManager::SetCurrentScene(size_t index)
{
	if (index >= m_vecScene.size()) return;

	IScene* pScene = m_vecScene[index];
	if (pScene)
	{
		pScene->Init();
		m_pCurrScene = pScene;
	}

}

void SceneManager::calcLoadingPercentage(int currentLoading, int maxLoading)
{
	m_pLoadingPercentage = (float)currentLoading / (float)maxLoading * 100.0f;
}

void SceneManager::calcLoadingPercentage()
{
	m_pLoadingPercentage = (float)m_pCurrentLoading / (float)m_pMaxLoading * 100.0f;
}

void SceneManager::calcLoadingExtra(int currentLoading, int maxLoading)
{
	CString temp, temp2;
	temp.Append(_T("( "));
	temp2 = to_string(currentLoading).c_str();
	temp.Append(temp2);
	temp.Append(_T(" / "));
	temp2 = to_string(maxLoading).c_str();
	temp.Append(temp2);
	temp.Append(_T(" ) "));
	m_pLoadingStringExtra = temp;
}
