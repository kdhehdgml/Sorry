#pragma once
#include "IUnitObject.h"
class CubemanParts;
class Mob;
class TEAM_TEX;

enum ANI_TEAMSTATE
{
	�޽�,
	���,
	���,
	����,
	������,
	��������,
	�������
};

/*
0 = ���ĵ� �ڼ� 1
1 = ���ĵ� �ڼ� 2
2 = ���ĵ� �ڼ� 3
3 = ���� �ڼ� 1
4 = ���ĵ� �� 1
5 = ���� ��ٰ� �״� �ڼ�
*/


enum ANI_STATE_TEAM
{
	������1,
	������2,
	������3,
	�����ڼ�,
	�������,
	������ٰ�����
};

enum TEAM_STATE{
	��_���,
	��_����,
	��_���,
	��_������,
	��_�����ο�
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

	//�ִϸ��̼� �ε���
	int ani_state;
	//�ִϸ��̼� ���۰� ��
	bool ani_start;
	//����
	float m_angle;

public:
	TeamAI();
	~TeamAI();
	int				num;
	bool			m_move;
	// IDisplayObject��(��) ���� ��ӵ�
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

