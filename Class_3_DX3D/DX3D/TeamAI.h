#pragma once
#include "IUnitObject.h"
class CubemanParts;
class Mob;
class TEAM_TEX;

enum ANI_TEAMSTATE
{
	휴식,
	경계,
	사격,
	엄폐,
	재장전,
	근접돌격,
	근접대기
};

/*
0 = 스탠드 자세 1
1 = 스탠드 자세 2
2 = 스탠드 자세 3
3 = 앉은 자세 1
4 = 스탠드 샷 1
5 = 서서 쏘다가 죽는 자세
*/


enum ANI_STATE_TEAM
{
	대기상태1,
	대기상태2,
	대기상태3,
	앉은자세,
	서서쏘기,
	서서쏘다가죽음
};

enum TEAM_STATE{
	팀_대기,
	팀_엄폐,
	팀_사격,
	팀_재장전,
	팀_근접싸움
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
	int				m_reloading;
	int				m_MobNum;
	int				m_ShootCooldownTime;
	bool			m_isMoving;
	bool			m_isShoot;
	int				m_bullet;
	bool			m_render;
	
	LPD3DXMESH		m_pSphere;
	BoundingSphere* m_pBoundingSphere;
	int status;

	//애니메이션 인덱스
	int ani_state;
	//애니메이션 시작과 끝
	bool ani_start;
	//각도
	float m_angle;

public:
	TeamAI();
	~TeamAI();
	int				num;
	bool			m_move;
	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	BoundingSphere* getBoundingSphere();
	int getStatus();
	void setStatus(int s);
	void GetMob(vector<Mob*> _mob) { m_pMob = _mob; }
	vector<Mob*>* getPMob();
	D3DXMATRIXA16 getMatWorld();
	bool HaveBullet();
	virtual bool MobSearch();
	void ShootVertex();
	void TrenchFight(int _num);
	void Shooting();
	void Reloading();


};

