#pragma once
#include "IUnitObject.h"
class MONSTER;

enum ANI_STATE_MOB
{
	�޸��ٰ�����3,
	�޸��ٰ�����2,
	�޸��ݰ�����1,
	
	�޸��鼭���,
	�޸��鼭���2,
};

enum MOB_MOVING
{
	��_�����̵�,
	��_�����̵�
};
enum MOB_ENGAGE
{
	��_���ڸ�����,
	��_���󹰿�����,
	��_�����ϰ���
};
enum MOB_GUNSHOT
{
	��_�Ϻλ��,
	��_�����������
};
enum MOB_RELOAD
{
	��_������,
	��_��������
};
enum MOB_ACTION
{
	��_������,
	��_�޸���,
	��_����,
	��_�޸��ٰ��ױ�,
	��_�¾�����,
	��_�������,
	��_�������,
	��_�ڷξɾƼ�����,
	��_��������,
	��_Į�����
};
enum MOB_SITUATION
{
	�ֺ�������,
	����_�Ÿ�����,
	����_�Ÿ��ȴ���,
	���Ÿ��ν�
};
struct MobAction
{
	MOB_MOVING	_moving;
	MOB_ENGAGE	_engage;
	MOB_GUNSHOT _gunshot;
	MOB_RELOAD	_reload;
	MOB_ACTION	_action;
	MOB_SITUATION _situation;
};

class Mob
	: public IUnitObject
{
private:
	MONSTER * m_MONSTER;
	VERTEX_PC		Shootpos[2];
	D3DXVECTOR3		forward;

	D3DXVECTOR3		m_deltaPos;
	D3DXVECTOR3		m_deltaRot;
	D3DXVECTOR3		m_forward;
	D3DXVECTOR3		m_Mobpos;
	vector<D3DXVECTOR3> m_AllSaveLocation;
	int				m_maxbullet;
	int				m_reloading;
	int				m_bullet;
	int				m_shootingbullet;
	int				m_TeamAINum;
	int				m_ShootCooldownTime;
	int				m_DestTime;
	bool			m_isMoving;
	bool			m_BeDetermined;//��ֹ� �ʷ� ���ߴ�
	bool			m_randshootbullet;
	bool			m_LocationCanSave;
	bool			m_Setdest;
	vector<int> CanSeeDriection;
	vector<int> TemporaryDirection;
	vector<D3DXVECTOR3> moveLocation;
	vector<D3DXVECTOR3> Temporary_Storage;
	vector<int> SaveLocationNum;
	vector<int> m_SaveTempNum;
	LPD3DXMESH		m_pSphereBody;
	BoundingSphere* m_pBoundingSphereBody;
	LPD3DXMESH		m_pSphereHead;
	BoundingSphere* m_pBoundingSphereHead;
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

	// ���� ó���� ����
	bool deathShout;

public:
	Mob();
	~Mob();
	//���ֹڽ����� ���� �����ִ½ð�
	int				num;
	//�����Ͼȼ�����
	bool			m_move;
	MobAction		m_Act;
	bool			hidingChk;
	bool showBoundingSphere;
	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	BoundingSphere* getBoundingSphereBody();
	BoundingSphere* getBoundingSphereHead();

	int getStatus();
	void setStatus(int s);
	void SetAngle(float angle) { m_angle = angle; }
	void SaveAction();
	void SelectAction();
	void Act_Moving();
	void Act_Engage();
	void Act_GunShot();
	void Act_Reload();
	void Act_Action();
	MOB_SITUATION PlayerSearch();
	MOB_SITUATION TrenchFight();
	MOB_SITUATION CanShooting();
	void Shooting();
	void SetAllSaveLocation(vector<D3DXVECTOR3> m_SaveLocation) { m_AllSaveLocation = m_SaveLocation; }
	void SetMoveTheWall(D3DXVECTOR3 wallLocation, int Locationnum, int _CanseeDirection)
	{
		moveLocation.push_back(wallLocation); SaveLocationNum.push_back(Locationnum); CanSeeDriection.push_back(_CanseeDirection);
	}
	void SetTemporary(D3DXVECTOR3 wallLocation, int Locationnum, int _CanseeDirection)
	{
		Temporary_Storage.push_back(wallLocation); m_SaveTempNum.push_back(Locationnum); TemporaryDirection.push_back(_CanseeDirection);
	}
	void SetDetermined(bool _boo) { m_BeDetermined = _boo; }
	void SetCanSave(bool _Can) { m_LocationCanSave = _Can; }
	vector<D3DXVECTOR3> GetMoveTheWall() { return moveLocation; }
	vector<int> GetLocationNum() { return SaveLocationNum; }
	vector<D3DXVECTOR3> GetTemporary() { return Temporary_Storage; }
	vector<int> GetTemporaryNum() { return m_SaveTempNum; }
	vector<int> GetTemporaryDirection() { return TemporaryDirection; }
	bool GetDetermined() { return m_BeDetermined; }
	bool GetCollision() { return m_colision; }
	bool HaveBullet();
	bool MaxBullet();
	void EraseLocationSoldier();
	void EraseWallLocation() { moveLocation.pop_back(); SaveLocationNum.pop_back(); CanSeeDriection.pop_back(); }
	void EraseTemporary() { Temporary_Storage.pop_back(); m_SaveTempNum.pop_back(); TemporaryDirection.pop_back(); }
	void FindCanMoveroad(int _num) { m_avoidObstDir = _num; }
	int GetAvoidObstDir() { return m_avoidObstDir; }
	void ResetAll();
	//void LocationChange(int _v1, D3DXVECTOR3 _ChangeLocation) { moveLocation[_v1] = _ChangeLocation; }
	void LocationSwap();
	void TemporarySwap();


};

