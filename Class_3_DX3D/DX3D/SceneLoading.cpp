#include "stdafx.h"
#include "SceneLoading.h"
#include "SceneHeightmap.h"

SceneLoading::SceneLoading()
{
	m_pSprite = NULL;
	m_pLoadingScreen = NULL;
	pImage = NULL;
	m_renderComplete = false;
}


SceneLoading::~SceneLoading()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pLoadingScreen);
	OnDestructIScene();
}

void SceneLoading::Init()
{
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.0f, 0.06f, 1.0f);

	D3DXCreateSprite(g_pDevice, &m_pSprite);
	pImage = new UIImage(m_pSprite);
	pImage->m_bDrawBorder = false;
	pImage->SetTexture("resources/ui/LoadingScreen.png");
	pImage->SetPosition(&D3DXVECTOR3(20.5f, -9.5f, 0.0f));
	m_pLoadingScreen = pImage;

	g_pSceneManager->SetCurrentScene(SCENE_HEIGHTMAP);
	g_pSceneManager->m_pCurrSceneString = "SCENE_HEIGHTMAP";
}

void SceneLoading::Update()
{
	SAFE_UPDATE(m_pLoadingScreen);
	OnUpdateIScene();
	if (g_pTimeManager->GetDeltaTime() > 0.001f && !m_renderComplete) {
		m_renderComplete = true;
		g_pSceneManager->SetCurrentScene(SCENE_HEIGHTMAP);
		g_pSceneManager->m_pCurrSceneString = "SCENE_HEIGHTMAP";
	}
}

void SceneLoading::Render()
{
	g_pDevice->SetTexture(0, NULL);
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX mat;
	D3DXVECTOR2 scaling(1.5f, 1.5f);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &D3DXVECTOR2(0.0f, 0.0f), 0.0f, &D3DXVECTOR2(-160.0f, 0.0f));
	m_pSprite->SetTransform(&mat);
	SAFE_RENDER(m_pLoadingScreen);
	m_pSprite->End();
}

void SceneLoading::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*switch (message) {
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_NUMPAD2:
			g_pSceneManager->SetCurrentScene(SCENE_HEIGHTMAP);
			break;
		}
		break;
	}*/
}