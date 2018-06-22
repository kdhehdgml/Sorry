#pragma once
#include "IUnitObject.h"
class MONSTER;

enum ANI_STATE
{
	대기상태,
	달리다가서기3,
	달리다가서기2,
	달리닫가서기1,
	달리다가죽기,
	달리면서쏘기2,
	달리면서쏘기,
	수그리면서달리기
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
	몹_숨어서장전,
	몹_숨어있음,
	몹_뛰는중,
	몹_사격중,
};
struct MobAction
{
	MOB_MOVING	_moving;
	MOB_ENGAGE	_engage;
	MOB_GUNSHOT _gunshot;
	MOB_RELOAD	_reload;
	MOB_ACTION	_hiding;
};

class Mob
	: public IUnitObject
{
private:
	MONSTER		*	m_MONSTER;
	VERTEX_PC		Shootpos[2];
	D3DXVECTOR3		forward;
	bool			m_isTurnedOnLight;

	D3DXVECTOR3		m_StartPosition;
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
	bool			m_isMoving;
	bool			m_BeDetermined;//장애물 너로 정했다
	bool			m_randshootbullet;
	bool			m_LocationCanSave;
	bool			m_Setdest;
	vector<D3DXVECTOR3> moveLocation;
	vector<D3DXVECTOR3> Temporary_Storage;
	vector<int> SaveLocationNum;
	vector<int> m_SaveTempNum;
	LPD3DXMESH		m_pSphereBody;
	BoundingSphere* m_pBoundingSphereBody;
	LPD3DXMESH		m_pSphereHead;
	BoundingSphere* m_pBoundingSphereHead;
	int status;
	int ani_state;

public:
	Mob();
	~Mob();
	//유닛박스에서 벽에 숨어있는시간
	int				num;
	//숨었니안숨었니
	bool			m_move;
	MobAction		m_Act;
	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	
	BoundingSphere* getBoundingSphereBody();
	BoundingSphere* getBoundingSphereHead();
	
	int getStatus();
	void setStatus(int s);

	void SaveAction();
	void Act_Moving();
	void Act_Engage();
	void Act_GunShot();
	void Act_Reload();
	void Act_Hiding();
	virtual bool PlayerSearch();
	bool TrenchFight();
	bool CanShooting();
	void Shooting();
	void SetAllSaveLocation(vector<D3DXVECTOR3> m_SaveLocation) { m_AllSaveLocation = m_SaveLocation; }
	void SetMoveTheWall(D3DXVECTOR3 wallLocation, int Locationnum) 
	{ moveLocation.push_back(wallLocation); SaveLocationNum.push_back(Locationnum);}
	void SetTemporary(D3DXVECTOR3 wallLocation, int Locationnum) 
	{ Temporary_Storage.push_back(wallLocation); m_SaveTempNum.push_back(Locationnum);}
	void SetDetermined(bool _boo) { m_BeDetermined = _boo; }
	void SetCanSave(bool _Can) { m_LocationCanSave = _Can; }
	vector<D3DXVECTOR3> GetMoveTheWall() { return moveLocation; }
	vector<int> GetLocationNum() { return SaveLocationNum; }
	vector<D3DXVECTOR3> GetTemporary() { return Temporary_Storage; }
	vector<int> GetTemporaryNum() { return m_SaveTempNum; }
	bool GetDetermined() { return m_BeDetermined; }
	bool HaveBullet();
	bool MaxBullet();
	void EraseLocationSoldier();
	void EraseWallLocation() { moveLocation.pop_back(); SaveLocationNum.pop_back(); }
	void EraseTemporary() { Temporary_Storage.pop_back(); m_SaveTempNum.pop_back(); }
	
	//void LocationChange(int _v1, D3DXVECTOR3 _ChangeLocation) { moveLocation[_v1] = _ChangeLocation; }
	void LocationSwap();
	void TemporarySwap();
	
};

