#pragma once
#include "IUnitObject.h"
class MONSTER;
enum MOB_MOVING
{
	¸÷_µ¹°ÝÀÌµ¿,
	¸÷_¾öÆóÀÌµ¿
};
enum MOB_ENGAGE
{
	¸÷_Á¦ÀÚ¸®¸ØÃã,
	¸÷_¾öÆó¹°¿¡¼û±â,
	¸÷_¹«½ÃÇÏ°íµ¹°Ý
};
enum MOB_GUNSHOT
{
	¸÷_ÀÏºÎ»ç°Ý,
	¸÷_¼ÒÁø±îÁö»ç°Ý
};
enum MOB_RELOAD
{
	¸÷_ÀåÀüÇÔ,
	¸÷_ÀåÀü¾ÈÇÔ
};
enum MOB_HIDING
{
	¸÷_¼û¾ú´Ù,
	¸÷_¾È¼û¾ú´Ù
};
struct MobAction
{
	MOB_MOVING	_moving;
	MOB_ENGAGE	_engage;
	MOB_GUNSHOT _gunshot;
	MOB_RELOAD	_reload;
	MOB_HIDING	_hiding;
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
	bool			m_isShoot;
	bool			m_BeDetermined;//Àå¾Ö¹° ³Ê·Î Á¤Çß´Ù
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

public:
	Mob();
	~Mob();
	//À¯´Ö¹Ú½º¿¡¼­ º®¿¡ ¼û¾îÀÖ´Â½Ã°£
	int				num;
	//¼û¾ú´Ï¾È¼û¾ú´Ï
	bool			m_move;
	MobAction		m_Act;
	// IDisplayObjectÀ»(¸¦) ÅëÇØ »ó¼ÓµÊ
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

