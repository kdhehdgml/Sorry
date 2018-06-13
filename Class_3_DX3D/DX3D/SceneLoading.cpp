#include "stdafx.h"
#include "SceneLoading.h"
//#include "SceneHeightmap.h"
//#include "SceneBattlefield.h"

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
	SAFE_RELEASE(m_loadingCircleSprite);
	SAFE_RELEASE(m_loadingCircleTexture);
	OnDestructIScene();
}

void SceneLoading::Init()
{
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.0f, 0.06f, 1.0f);

	D3DXCreateSprite(g_pDevice, &m_loadingCircleSprite);
	D3DXCreateTextureFromFileEx(g_pDevice, _T("resources/ui/LoadingCircle.png"), 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), 0, 0, &m_loadingCircleTexture);
	m_loadingCircle.nCount = 8;
	m_loadingCircle.nIndex = 0;
	m_loadingCircle.dwAniTime = 100;
	m_loadingCircle.dwOldAniTime = GetTickCount();
	m_loadingCircle.pRect = m_loadingCircleRect;
	//m_loadingCircle.pCenter = m_loadingCircleCenter;

	D3DXCreateSprite(g_pDevice, &m_pSprite);
	pImage = new UIImage(m_pSprite);
	pImage->m_bDrawBorder = false;
	pImage->SetTexture("resources/ui/LoadingScreen.png");
	pImage->SetPosition(&D3DXVECTOR3(20.5f, -9.5f, 0.0f));
	m_pLoadingScreen = pImage;

	//g_pSceneManager->SetCurrentScene(SCENE_HEIGHTMAP);
	//g_pSceneManager->m_pCurrSceneString = "SCENE_HEIGHTMAP"; //디버그용 문자
	g_pSceneManager->SetCurrentScene(SCENE_HEIGHTMAP);
	g_pSceneManager->m_pCurrSceneString = "SCENE_HEIGHTMAP";

	//g_pSceneManager->SetCurrentScene(SCENE_XFILE);
	//g_pSceneManager->m_pCurrSceneString = "SCENE_XFILE";
}

void SceneLoading::Update()
{
	SAFE_UPDATE(m_pLoadingScreen);
	OnUpdateIScene();
	DWORD dwCurTime = GetTickCount();
	if (dwCurTime - m_loadingCircle.dwOldAniTime >= m_loadingCircle.dwAniTime) {
		m_loadingCircle.dwOldAniTime = dwCurTime;
		m_loadingCircle.nIndex = ++m_loadingCircle.nIndex % m_loadingCircle.nCount;
	}
	if (g_pTimeManager->GetDeltaTime() > 0.001f && !m_renderComplete) {
		m_renderComplete = true;
		g_pSceneManager->SetCurrentScene(GSM().StartScene); //여기를 바꾸면 시작 씬이 바뀜
		
		switch (GSM().StartScene) //이건 디버그용 문자
		{
		case SCENE_LOADING:
			g_pSceneManager->m_pCurrSceneString = "SCENE_LOADING";
			break;
		case SCENE_HEIGHTMAP:
			g_pSceneManager->m_pCurrSceneString = "SCENE_HEIGHTMAP";
			break;
		case SCENE_GRID:
			g_pSceneManager->m_pCurrSceneString = "SCENE_GRID";
			break;
		case SCENE_OBJMAP:
			g_pSceneManager->m_pCurrSceneString = "SCENE_OBJMAP";
			break;
		case SCENE_TEST:
			g_pSceneManager->m_pCurrSceneString = "SCENE_TEST";
			break;
		case SCENE_XFILE:
			g_pSceneManager->m_pCurrSceneString = "SCENE_XFILE";
			break;
		case SCENE_BATTLEFIELD:
			g_pSceneManager->m_pCurrSceneString = "SCENE_BATTLEFIELD";
			break;
		}
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
	m_loadingCircleSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_loadingCircleSprite->Draw(m_loadingCircleTexture, &m_loadingCircle.pRect[m_loadingCircle.nIndex], &D3DXVECTOR3(64, 64, 0), &D3DXVECTOR3(1200, 640, 0), D3DCOLOR_XRGB(255, 255, 255));
	//SAFE_RENDER(m_pLoadingCircle);
	m_loadingCircleSprite->End();
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