#pragma once
#include "IUnitObject.h"
class CubemanParts;
class Mob;
class TEAM_TEX;

/*

3 = 앉은자세
2 = 서서죽음
1 = 서서기본자세
0 = 서서쏘기

*/


enum ANI_STATE_TEAM
{
	서서쏘기,
	서서기본자세,
	서서죽음,
	앉은자세,
	걷기,
	근접공격,
	재장전
	//뒤로앉아서장전, 칼빵대전, 칼든상태, 서서쏘기, 서서죽음, 대기상태
};

enum TEAM_STATE{
	팀_달리기,
	팀_대기,
	팀_사격,
	팀_재장전,
	팀_근접싸움,
	팀_죽음
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
	bool			m_Ready;
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

	//...죽었을떄 딜레이주기위한 변수...//
	int m_Death_count;
	int m_Death_Time;
	bool m_Death;


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
	void Animation();
	void setStatus(int s);
	void GetMob(vector<Mob*> _mob) { m_pMob = _mob; }
	vector<Mob*>* getPMob();
	D3DXMATRIXA16 getMatWorld();
	bool HaveBullet();
	virtual bool MobSearch();
	void ShootVertex();
	bool TrenchFight(int _num);
	void Shooting();
	void Reloading();
	void SetReady(bool _ready) { m_Ready = _ready; }

};

