#include "stdafx.h"
#include "Minimap.h"

#define zoomScale 1.75f
#define Chai 104.0f

Minimap::Minimap()
{
	m_minimapSprite = NULL;
	m_pRootUI = NULL;
	minimapWidth = 256.0f * zoomScale;
	minimapHeight = 256.0f * zoomScale;
	m_pMobNum = 0;
	m_pMobOldNum = 0;
	m_pTeamNum = 0;
	m_pTeamOldNum = 0;
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
	m_minimap->SetTexture("resources/heightmap/terrain_minimapBF.png");
	m_minimap->SetPosition(&D3DXVECTOR3(0, 0, 0));
	m_pRootUI = m_minimap;
	m_playerIcon = new UIImage(m_minimapSprite);
	m_pRootUI->AddChild(m_playerIcon);
	m_playerIcon->SetTexture("resources/ui/point01.bmp");
	m_playerIcon->SetPosition(&D3DXVECTOR3(-5, -5, -1));
	m_pScaleBuf = GSM().mapSize / minimapWidth;

	/*for (int i = 0; i <= m_pMob.size(); i++) {
		UIImage* tempUIImage = new UIImage(m_minimapSprite);
		m_enemyIcon.push_back(tempUIImage);
		m_pRootUI->AddChild(m_enemyIcon.back());
		m_enemyIcon.back()->SetTexture("resources/ui/point02.bmp");
		m_enemyIcon.back()->SetPosition(&D3DXVECTOR3(0, 0, 0));
	}*/

	//D3DXMATRIXA16 matS;
	//D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1);
	//D3DXMATRIXA16 matT;
	//D3DXMatrixTranslation(&matT, 0, 464, 0);
	D3DXMATRIXA16 matR;
	//270도 회전
	D3DXMatrixTransformation2D(&matR, NULL, NULL, NULL, &D3DXVECTOR2(128, 128), 270 * D3DX_PI / 180, &D3DXVECTOR2(0, 464));
	//m_matWorld = matS * matT;
	m_matWorld = matR;
}

void Minimap::Update()
{
	SAFE_UPDATE(m_pRootUI);
	//플레이어 위치 미니맵 표시 계산
	D3DXVECTOR3 playerPos = g_pCamera->getPos();

	float tempX = (playerPos.x / m_pScaleBuf) - Chai / 2;
	float tempZ = (playerPos.z / m_pScaleBuf) + Chai;
	
	if (isInMap(tempX, tempZ))
	{
		tempZ = minimapWidth - tempZ;
		m_playerIcon->SetPosition(&D3DXVECTOR3(tempX, tempZ, 0));
	}
	else
		m_playerIcon->SetPosition(&D3DXVECTOR3(-5, -5, -1));
	//플레이어 위치 미니맵 표시 계산 끝

	//적 위치 미니맵 표시 계산
	for (int i = 0; i < m_enemyIcon.size();i++) {
		if (m_pMob[i]->getStatus() != 0) {
			D3DXVECTOR3 enemyPos = m_pMob[i]->GetPosition();
			tempX = (enemyPos.x / m_pScaleBuf) - Chai / 2;
			tempZ = (enemyPos.z / m_pScaleBuf) + Chai;
			if (isInMap(tempX, tempZ))
			{
				tempZ = minimapWidth - tempZ;
				m_enemyIcon[i]->SetPosition(&D3DXVECTOR3(tempX, tempZ, 0));
			}
			else
				m_enemyIcon[i]->SetPosition(&D3DXVECTOR3(-5, -5, -1));
		}
		else {
			m_enemyIcon[i]->SetPosition(&D3DXVECTOR3(-5, -5, -1)); //죽었으면 화면에서 제거
		}
	}
	//적 위치 미니맵 표시 계산 끝

	//팀 위치 미니맵 표시 계산
	for (int i = 0; i < m_teamIcon.size(); i++) {
		if (m_pTeam[i]->getStatus() != 0) {
			D3DXVECTOR3 enemyPos = m_pTeam[i]->GetPosition();
			tempX = (enemyPos.x / m_pScaleBuf) - Chai / 2;
			tempZ = (enemyPos.z / m_pScaleBuf) + Chai;
			if (isInMap(tempX, tempZ))
	{
		tempZ = minimapWidth - tempZ;
		m_teamIcon[i]->SetPosition(&D3DXVECTOR3(tempX, tempZ, 0));
	}
	else
		m_teamIcon[i]->SetPosition(&D3DXVECTOR3(-5, -5, -1));
		}
		else {
			m_teamIcon[i]->SetPosition(&D3DXVECTOR3(-5, -5, -1)); //죽었으면 화면에서 제거
		}
	}
	//팀 위치 미니맵 표시 계산 끝
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
	m_pMobNum = mob->size();
	if (m_pMobNum != m_pMobOldNum) {
		for (int i = 0; i < m_pMobNum - m_pMobOldNum; i++) {
			addEnemy();
		}
	}
	m_pMobOldNum = m_pMobNum;
}

void Minimap::getPTeamFromUnitBox(vector<TeamAI*>* team)
{
	m_pTeam = *team;
	m_pTeamNum = team->size();
	if (m_pTeamNum != m_pTeamOldNum) {
		for (int i = 0; i < m_pTeamNum - m_pTeamOldNum; i++) {
			addTeam();
		}
	}
	m_pTeamOldNum = m_pTeamNum;
}

void Minimap::addEnemy()
{
	UIImage* tempUIImage = new UIImage(m_minimapSprite);
	m_pRootUI->AddChild(tempUIImage);
	tempUIImage->SetTexture("resources/ui/point02.bmp");
	tempUIImage->SetPosition(&D3DXVECTOR3(-5, -5, -1));
	m_enemyIcon.push_back(tempUIImage);
}

void Minimap::addTeam()
{
	UIImage* tempUIImage = new UIImage(m_minimapSprite);
	m_pRootUI->AddChild(tempUIImage);
	tempUIImage->SetTexture("resources/ui/point03.bmp");
	tempUIImage->SetPosition(&D3DXVECTOR3(-5, -5, -1));
	m_teamIcon.push_back(tempUIImage);
}

bool Minimap::isInMap(float tempX, float tempZ)
{	
	if (tempX > 20
		&& tempZ > 218
		&& tempX < minimapWidth / 2 + 6
		&& tempZ < minimapHeight - 20)
		return true;
	return false;
}
