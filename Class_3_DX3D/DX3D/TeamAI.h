#pragma once
#include "IUnitObject.h"
class CubemanParts;
class Mob;
class TEAM_TEX;

enum TEAM_STATE{
	ÆÀ_¾öÆó,
	ÆÀ_°ø°Ý
};
class TeamAI :
	public IUnitObject
{
private:
	CubemanParts *	m_pRootParts;
	vector<Mob*>	m_pMob;
	VERTEX_PC		Shootpos[2];
	D3DXVECTOR3		forward;
	TEAM_TEX		*m_TEAM_TEX;
	TEAM_STATE		m_Action;

	D3DXVECTOR3		m_deltaPos;
	D3DXVECTOR3		m_deltaRot;
	D3DXVECTOR3		m_forward;
	
	int				m_MobNum;
	int				m_CooldownTime;
	bool			m_isMoving;
	bool			m_isShoot;
	
	LPD3DXMESH		m_pSphere;
	BoundingSphere* m_pBoundingSphere;
	int status;
public:
	TeamAI();
	~TeamAI();
	int				num;
	bool			m_move;
	// IDisplayObjectÀ»(¸¦) ÅëÇØ »ó¼ÓµÊ
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	BoundingSphere* getBoundingSphere();
	int getStatus();
	void setStatus(int s);
	void GetMob(vector<Mob*> _mob) { m_pMob = _mob; }
	vector<Mob*>* getPMob();

	virtual bool MobSearch();
	void ShootVertex();
};

