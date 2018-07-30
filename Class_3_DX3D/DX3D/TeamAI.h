#pragma once
#include "IUnitObject.h"
//class CubemanParts;
class Mob;
class TEAM_TEX;
class Smle;
class FR_HEADGEAR;

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
	//CubemanParts *	m_pRootParts;
	vector<Mob*>	m_pMob;
	VERTEX_PC		Shootpos[2];
	D3DXVECTOR3		forward;
	//ĳ����
	TEAM_TEX		*m_TEAM_TEX;
	//���
	FR_HEADGEAR *	m_FR_HEADGEAR;
	//����
	Smle *			m_Smle;


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

	//...�׾����� �������ֱ����� ����...//
	int m_Death_count;
	int m_Death_Time;
	bool m_Death;

	// ���� ó���� ����
	
	bool reloadShout;


	//��� �����״�.
	bool headgear_state;
	bool gun_state;

public:
	TeamAI();
	~TeamAI();

	bool deathShout;

	int				num;
	bool			m_move;

	int m_level;
	int m_expToNextLevel;

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
	void LevelUp();
};

