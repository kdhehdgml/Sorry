#include "stdafx.h"
#include "Minimap.h"

Minimap::Minimap()
{
	m_minimapSprite = NULL;
	m_pRootUI = NULL;
}

Minimap::~Minimap()
{
	SAFE_RELEASE(m_minimapSprite);
	m_pRootUI->ReleaseAll();
}

void Minimap::Init()
{
	D3DXCreateSprite(g_pDevice, &m_minimapSprite);
	m_minimap = new UIImage(m_minimapSprite);
	m_minimap->SetTexture("resources/heightmap/terrain_minimap.png");
	m_minimap->SetPosition(&D3DXVECTOR3(200, 0, 0));
	m_pRootUI = m_minimap;
	m_playerIcon = new UIImage(m_minimapSprite);
	m_pRootUI->AddChild(m_playerIcon);
	m_playerIcon->SetTexture("resources/ui/panel-info.png.png");
	m_playerIcon->SetPosition(&D3DXVECTOR3(0, 0, 0));

	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1);
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 150, 150, 0);
	m_matWorld = matS * matT;
}

void Minimap::Update()
{
	SAFE_UPDATE(m_pRootUI);
}

void Minimap::Render()
{
	g_pDevice->SetTexture(0, NULL);
	m_minimapSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_minimapSprite->SetTransform(&m_matWorld);
	SAFE_RENDER(m_pRootUI);
	m_minimapSprite->End();
}
