#include "stdafx.h"
#include "Minimap.h"

Minimap::Minimap()
{
	m_minimapSprite = NULL;
	m_pRootUI = NULL;
	minimapWidth = 256.0f;
	minimapHeight = 256.0f;
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
	m_minimap->m_bDrawBorder = false;
	m_minimap->SetTexture("resources/heightmap/terrain_minimap.png");
	m_minimap->SetPosition(&D3DXVECTOR3(0, 0, 0));
	m_pRootUI = m_minimap;
	m_playerIcon = new UIImage(m_minimapSprite);
	m_pRootUI->AddChild(m_playerIcon);
	m_playerIcon->SetTexture("resources/ui/point01.bmp");
	m_playerIcon->SetPosition(&D3DXVECTOR3(0, 0, 0));

	//D3DXMATRIXA16 matS;
	//D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1);
	//D3DXMATRIXA16 matT;
	//D3DXMatrixTranslation(&matT, 0, 464, 0);
	D3DXMATRIXA16 matR;
	D3DXMatrixTransformation2D(&matR, NULL, NULL, NULL, &D3DXVECTOR2(128, 128), 270 * D3DX_PI / 180, &D3DXVECTOR2(0, 464));
	//m_matWorld = matS * matT;
	m_matWorld = matR;
}

void Minimap::Update()
{
	SAFE_UPDATE(m_pRootUI);
	//플레이어 위치 미니맵 표시 계산
	D3DXVECTOR3 playerPos = g_pCamera->getPos();
	float tempX = playerPos.x / 1.953125;
	float tempZ = playerPos.z / 1.953125;
	if (tempX < 0) tempX = 0;
	if (tempZ < 0) tempZ = 0;
	if (tempX > minimapWidth) tempX = minimapWidth;
	if (tempZ > minimapHeight) tempZ = minimapHeight;
	tempZ = minimapWidth - tempZ;
	m_playerIcon->SetPosition(&D3DXVECTOR3(tempX, tempZ, 0));
	//플레이어 위치 미니맵 표시 계산 끝

	//적 위치 미니맵 표시 계산
	for (auto p : m_pMob) {

	}
}

void Minimap::Render()
{
	g_pDevice->SetTexture(0, NULL);
	m_minimapSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_minimapSprite->SetTransform(&m_matWorld);
	SAFE_RENDER(m_pRootUI);
	m_minimapSprite->End();
}

void Minimap::getPMobFromUnitBox(vector<Mob*>* mob)
{
	m_pMob = *mob;
}