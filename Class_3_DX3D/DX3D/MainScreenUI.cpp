#include "stdafx.h"
#include "MainScreenUI.h"
#include "IUIObject.h"
#include "UIImage.h"
#include "UIText.h"

MainScreenUI::MainScreenUI()
{
	m_pSprite = NULL;
	m_pRootUI = NULL;
}


MainScreenUI::~MainScreenUI()
{
	SAFE_RELEASE(m_pSprite);
	//SAFE_RELEASE(m_pRootUI);
	m_pRootUI->ReleaseAll();
}

void MainScreenUI::Init()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);
	g_pCamera->mouseLock = false;

	{
		UIImage* pImage = new UIImage(m_pSprite);
		pImage->SetTexture("resources/ui/MainScreen.png");
		pImage->SetPosition(&D3DXVECTOR3(20.5f, -9.5f, 0.0f));
		pImage->m_bDrawBorder = false;
		m_pRootUI = pImage;
	}
	{
		UIButton* pButton = new UIButton(this, m_pSprite, 1);
		m_pRootUI->AddChild(pButton);
		pButton->SetPosition(&D3DXVECTOR3(380, 330, 0));
		pButton->SetTexture(
			"resources/ui/btn-med-up.png.png",
			"resources/ui/btn-med-over.png.png",
			"resources/ui/btn-med-down.png.png");
		pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST), _T("게임 시작"));
	}
	{
		UIButton* pButton = new UIButton(this, m_pSprite, 2);
		m_pRootUI->AddChild(pButton);
		pButton->SetPosition(&D3DXVECTOR3(380, 400, 0));
		pButton->SetTexture(
			"resources/ui/btn-med-up.png.png",
			"resources/ui/btn-med-over.png.png",
			"resources/ui/btn-med-down.png.png");
		pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST), _T("게임 종료"));
	}
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.4f, 1.4f, 1);
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, -140, 0, 0);
	m_matWorld = matS * matT;
}

void MainScreenUI::Update()
{
	SAFE_UPDATE(m_pRootUI);
}

void MainScreenUI::Render()
{
	g_pDevice->SetTexture(0, NULL);
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->SetTransform(&m_matWorld);
	SAFE_RENDER(m_pRootUI);
	m_pSprite->End();
}

void MainScreenUI::OnClick(UIButton * pSender)
{
	if (pSender->m_uiTag == 1)
	{
		g_pSceneManager->SetCurrentScene(SCENE_LOADING);
		g_pSceneManager->m_pCurrSceneString = "SCENE_LOADING";
	}
	else if (pSender->m_uiTag == 2)
	{
		PostQuitMessage(0);
	}
}
