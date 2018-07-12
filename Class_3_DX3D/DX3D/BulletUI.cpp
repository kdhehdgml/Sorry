#include "stdafx.h"
#include "BulletUI.h"
#include "IUIObject.h"
#include "UIImage.h"

BulletUI::BulletUI()
{
	m_pSprite = NULL;
	m_pRootUI = NULL;
	for (int i = 0; i < 5; i++) {
		m_pBullets[i] = NULL;
	}
}


BulletUI::~BulletUI()
{
	SAFE_RELEASE(m_pSprite);
	m_pRootUI->ReleaseAll();
}

void BulletUI::Init()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);
	UIImage* pImage = new UIImage(m_pSprite);
	pImage->SetTexture("resources/ui/blank.png");
	pImage->SetPosition(&D3DXVECTOR3(0, 0, 0));
	pImage->m_bDrawBorder = false;
	m_pRootUI = pImage;
	for (int i = 0; i < 5; i++) {
		m_pBullets[i] = new UIImage(m_pSprite);
		m_pBullets[i]->SetTexture("resources/ui/bullets.png");
		m_pBullets[i]->SetPosition(&D3DXVECTOR3(-(i*35), 0, 0));
		m_pBullets[i]->m_bDrawBorder = false;
		m_pRootUI->AddChild(m_pBullets[i]);
	}

	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1);
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 1220, 560, 0);
	m_matWorld = matS * matT;
}

void BulletUI::Update()
{
	SAFE_UPDATE(m_pRootUI);
}

void BulletUI::Render()
{
	g_pDevice->SetTexture(0, NULL);
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->SetTransform(&m_matWorld);
	//SAFE_RENDER(m_pRootUI);
	for (int i = 0; i < bulletNum; i++) {
		SAFE_RENDER(m_pBullets[i]);
	}
	m_pSprite->End();
}
