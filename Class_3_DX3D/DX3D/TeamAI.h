#pragma once
#include "IUnitObject.h"
class CubemanParts;
class Mob;
class TEAM_TEX;

/*

3 = �����ڼ�
2 = ��������
1 = �����⺻�ڼ�
0 = �������

*/


enum ANI_STATE_TEAM
{
	�������,
	�����⺻�ڼ�,
	��������,
	�����ڼ�,
	�ȱ�,
	��������,
	������
	//�ڷξɾƼ�����, Į������, Į�����, �������, ��������, ������
};

enum TEAM_STATE{
	��_�޸���,
	��_���,
	��_���,
	��_������,
	��_�����ο�,
	��_����
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

	//�ִϸ��̼� �ε���
	int ani_state;
	//�ִϸ��̼� ���۰� ��
	bool ani_start;
	//����
	float m_angle;

	//...�׾����� �������ֱ����� ����...//
	int m_Death_count;
	int m_Death_Time;
	bool m_Death;


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

