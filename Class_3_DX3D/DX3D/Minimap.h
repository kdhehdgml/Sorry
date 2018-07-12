#pragma once
#include "IDisplayObject.h"
#include "UIImage.h"
#include "Mob.h"
#include "TeamAI.h"

class Minimap :
	public IDisplayObject
{
private:
	LPD3DXSPRITE m_minimapSprite;
	LPD3DXSPRITE m_playerSprite;
	UIImage * m_minimap;
	UIImage * m_playerIcon;
	D3DXMATRIXA16 m_playerIconRotation;
	D3DXVECTOR2 m_playerIconPos;
	vector<UIImage*> m_teamIcon;
	vector<UIImage*> m_enemyIcon;
	IUBaseObject* m_pRootUI;

	float minimapWidth;
	float minimapHeight;

	vector<Mob*> m_pMob;
	vector<TeamAI*> m_pTeam;
	int m_pMobNum;
	int m_pMobOldNum;
	int m_pTeamNum;
	int m_pTeamOldNum;

	float m_pScaleBuf;

public:
	Minimap();
	~Minimap();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void getPMobFromUnitBox(vector<Mob*>* mob);
	void getPTeamFromUnitBox(vector<TeamAI*>* team);
	void addEnemy();
	void addTeam();
	bool isInMap(float tempX, float tempZ);
};

