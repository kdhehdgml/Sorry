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
	UIImage * m_minimap;
	UIImage * m_playerIcon;
	vector<UIImage*> m_teamIcon;
	vector<UIImage*> m_enemyIcon;
	IUIObject* m_pRootUI;

	float minimapWidth;
	float minimapHeight;

	vector<Mob*> m_pMob;
	vector<TeamAI*> m_pTeam;
	int m_pMobNum;
	int m_pMobOldNum;
	int m_pTeamNum;
	int m_pTeamOldNum;

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
};

