#include "stdafx.h"
#include "Player_Health_UI.h"
#include "IUIObject.h"
#include "UIImage.h"

Player_Health_UI::Player_Health_UI()
{
	m_pSprite = NULL;
	m_pRootUI = NULL;
	for (int i = 0; i < 3; i++)
	{
		m_pHealth[i] = NULL;
	}
	Health = 4;
}

Player_Health_UI::~Player_Health_UI()
{
	SAFE_RELEASE(m_pSprite);
	m_pRootUI->ReleaseAll();
}

void Player_Health_UI::Init()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);
	UIImage* pImage = new UIImage(m_pSprite);
	pImage->SetTexture("resources/ui/blank.png");
	pImage->SetPosition(&D3DXVECTOR3(0, 0, 0));
	pImage->m_bDrawBorder = false;
	m_pRootUI = pImage;

	for (int i = 0; i < 3; i++)
	{
		m_pHealth[i] = new UIImage(m_pSprite);
		m_pHealth[i]->SetPosition(&D3DXVECTOR3(0, 0, 0));
		m_pHealth[i]->m_bDrawBorder = false;
	}

	m_pHealth[0]->SetTexture("resources/ui/Player_HP1.png");
	m_pHealth[1]->SetTexture("resources/ui/Player_HP2.png");
	m_pHealth[2]->SetTexture("resources/ui/Player_HP3.png");

	for (int i = 0; i < 3; i++)
	{
		m_pRootUI->AddChild(m_pHealth[i]);
	}


	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.25f, 1.45f, 1);
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	m_matWorld = matS * matT;
}

void Player_Health_UI::Update()
{
	SAFE_UPDATE(m_pRootUI);
}

void Player_Health_UI::Render()
{
	g_pDevice->SetTexture(0, NULL);
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->SetTransform(&m_matWorld);
	
	switch (Health)
	{
	case 0:
		SAFE_RENDER(m_pHealth[2]);
		break;
	case 1:
		SAFE_RENDER(m_pHealth[2]);
		break;
	case 2:
		SAFE_RENDER(m_pHealth[1]);
		break;
	case 3:
		SAFE_RENDER(m_pHealth[0]);
		break;
	}
	m_pSprite->End();
}
