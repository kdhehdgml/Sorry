#include "stdafx.h"
#include "Minimap.h"

#define zoomScale 1.75f
#define Chai 104.0f

Minimap::Minimap()
{
	m_minimapSprite = NULL;
	m_playerSprite = NULL;
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
	SAFE_RELEASE(m_playerSprite);
	m_pRootUI->ReleaseAll();
}

void Minimap::Init()
{
	D3DXCreateSprite(g_pDevice, &m_minimapSprite);
	D3DXCreateSprite(g_pDevice, &m_playerSprite);
	m_minimap = new UIImage(m_minimapSprite);
	m_minimap->m_bDrawBorder = false;
	m_minimap->SetTexture("resources/heightmap/terrain_minimapBF.png");
	m_minimap->SetPosition(&D3DXVECTOR3(0, 0, 0));
	m_pRootUI = m_minimap;
	m_playerIcon = new UIImage(m_playerSprite);
	m_playerIcon->m_bDrawBorder = false;
	//m_pRootUI->AddChild(m_playerIcon);
	m_playerIcon->SetTexture("resources/ui/point01.png");
	m_playerIcon->SetPosition(&D3DXVECTOR3(0, 0, 0));
	m_pScaleBuf = minimapWidth / GSM().mapSize;

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
	m_playerIconPos.x = 0;
	m_playerIconPos.y = 0;
}

void Minimap::Update()
{
	SAFE_UPDATE(m_pRootUI);
	//플레이어 위치 미니맵 표시 계산
	D3DXVECTOR3 playerPos = g_pCamera->getPos();
	D3DXMatrixTransformation2D(&m_playerIconRotation, NULL, NULL, NULL, &D3DXVECTOR2(4.0f, 4.0f), g_pCamera->getAngleY() + (270 * D3DX_PI / 180), &m_playerIconPos);

	playerPos.z = min(playerPos.z, 540.0f);
	playerPos.z = max(playerPos.z, 190.0f);
	playerPos.x = min(playerPos.x, 500.0f);
	playerPos.x = max(playerPos.x, 135.0f);

	float tempX = ((GSM().mapSize - playerPos.x) * m_pScaleBuf);
	float tempZ = ((GSM().mapSize - playerPos.z) * m_pScaleBuf);

	//m_playerIcon->SetPosition(&D3DXVECTOR3(tempX, tempZ, 0));
	m_playerIconPos.x = tempZ - 106.0f;
	m_playerIconPos.y = tempX + 324.0f;

	Debug->AddText("m_playerIconPos : ");
	Debug->AddText(m_playerIconPos.x);
	Debug->AddText(", ");
	Debug->AddText(m_playerIconPos.y);
	Debug->EndLine();

	m_playerIcon->m_rotAngle = g_pCamera->getAngleX();
	//플레이어 위치 미니맵 표시 계산 끝

	//적 위치 미니맵 표시 계산
	for (int i = 0; i < m_enemyIcon.size();i++) {
		if (m_pMob[i]->getStatus() != 0) {
			D3DXVECTOR3 enemyPos = m_pMob[i]->GetPosition();
			tempX = (enemyPos.x * m_pScaleBuf) - Chai / 2;
			tempZ = (enemyPos.z * m_pScaleBuf) + Chai;
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
			tempX = (enemyPos.x * m_pScaleBuf) - Chai / 2;
			tempZ = (enemyPos.z * m_pScaleBuf) + Chai;
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
	m_playerSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_playerSprite->SetTransform(&m_playerIconRotation);
	SAFE_RENDER(m_playerIcon);
	m_playerSprite->End();
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

/*bool Minimap::isInMapPlayer(D3DXVECTOR3 _playerPos)
{
	if (_playerPos.z <= 540.0f && _playerPos.z >= 190.0f && _playerPos.x >= 135.0f && _playerPos.x <= 500.0f) {
		return true;
	}
	return false;
}*/
