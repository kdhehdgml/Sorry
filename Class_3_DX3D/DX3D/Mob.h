#pragma once
#include "IUnitObject.h"
class MONSTER;

enum ANI_STATE_MOB
{
	달리다가서기3,
	달리다가서기2,
	달리닫가서기1,
	
	달리면서쏘기,
	달리면서쏘기2,
};

enum MOB_MOVING
{
	몹_돌격이동,
	몹_엄폐이동
};
enum MOB_ENGAGE
{
	몹_제자리멈춤,
	몹_엄폐물에숨기,
	몹_무시하고돌격
};
enum MOB_GUNSHOT
{
	몹_일부사격,
	몹_소진까지사격
};
enum MOB_RELOAD
{
	몹_장전함,
	몹_장전안함
};
enum MOB_ACTION
{
	몹_대기상태,
	몹_달리기,
	몹_죽음,
	몹_달리다가죽기,
	몹_좌엄폐사격,
	몹_우엄폐사격,
	몹_서서쏘기,
	몹_뒤로앉아서장전,
	몹_근접전투,
	몹_칼든상태
};
enum MOB_SITUATION
{
	주변적없음,
	근접_거리닿음,
	근접_거리안닿음,
	원거리인식
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
	bool			m_BeDetermined;//장애물 너로 정했다
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

	// 사운드 처리용 변수
	bool deathShout;

public:
	Mob();
	~Mob();
	//유닛박스에서 벽에 숨어있는시간
	int				num;
	//숨었니안숨었니
	bool			m_move;
	MobAction		m_Act;
	bool			hidingChk;
	bool showBoundingSphere;
	// IDisplayObject을(를) 통해 상속됨
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

