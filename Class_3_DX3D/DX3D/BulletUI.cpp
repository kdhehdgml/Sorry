#include "stdafx.h"
#include "BulletUI.h"
#include "IUIObject.h"
#include "UIImage.h"

BulletUI::BulletUI()
{
	m_pSprite = NULL;
	m_pRootUI = NULL;
}


BulletUI::~BulletUI()
{
	SAFE_RELEASE(m_pSprite);
	m_pRootUI->ReleaseAll();
}

void BulletUI::Init()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);

	{
		UIImage* pImage = new UIImage(m_pSprite);
		pImage->SetTexture("resources/ui/panel-info.png.png");
		pImage->SetPosition(&D3DXVECTOR3(200, 0, 0));
		m_pRootUI = pImage;
	}
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.5f, 0.5f, 1);
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 150, 150, 0);
	m_matWorld = matS * matT;
}

void BulletUI::Update()
{
}

void BulletUI::Render()
{
}
