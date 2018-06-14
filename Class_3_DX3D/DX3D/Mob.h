#pragma once
#include "IUnitObject.h"
class MONSTER;
enum MOB_STATE
{
	¼û´Â¾Ö,
	¾È¼û´Â¾Ö,
	Á¦ÀÚ¸®»ç°Ý,
	¾öÆó»ç°Ý,
	¾öÆó¿·¿¡¼­»ç°Ý,
	¹«½ÃÇÏ°íÀÌµ¿,
	ÃÑÀÏºÎ¸¸½ô,
	ÃÑ¾Ë¼ÒÁø±îÁö½ô
};
class Mob
	: public IUnitObject
{
private:
	MONSTER		*	m_MONSTER;
	VERTEX_PC		Shootpos[2];
	D3DXVECTOR3		forward;
	bool			m_isTurnedOnLight;

	D3DXVECTOR3		m_deltaPos;
	D3DXVECTOR3		m_deltaRot;
	D3DXVECTOR3		m_forward;
	D3DXVECTOR3		m_Mobpos;

	int				m_ShootCooldownTime;
	bool			m_isMoving;
	bool			m_isShoot;
	bool			m_BeDetermined;
	vector<MOB_STATE>		m_Action;
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
	int				num;
	bool			m_move;
	// IDisplayObjectÀ»(¸¦) ÅëÇØ »ó¼ÓµÊ
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	
	BoundingSphere* getBoundingSphereBody();
	BoundingSphere* getBoundingSphereHead();
	
	int getStatus();
	void setStatus(int s);

	virtual bool PlayerSearch();
	void ShootVertex();
	void GetMoveTheWall(D3DXVECTOR3 wallLocation, int Locationnum) 
	{ moveLocation.push_back(wallLocation); SaveLocationNum.push_back(Locationnum);}
	void GetTemporary(D3DXVECTOR3 wallLocation, int Locationnum) 
	{ Temporary_Storage.push_back(wallLocation); m_SaveTempNum.push_back(Locationnum);}
	void GetDetermined(bool _boo) { m_BeDetermined = _boo; }
	void InsertAction(int _hide, int _behavior, int _shootmount);
	
	vector<D3DXVECTOR3> SetMoveTheWall() { return moveLocation; }
	vector<int> SetLocationNum() { return SaveLocationNum; }
	vector<D3DXVECTOR3> SetTemporary() { return Temporary_Storage; }
	vector<int> SetTemporaryNum() { return m_SaveTempNum; }
	bool SetDetermined() { return m_BeDetermined; }
	vector<MOB_STATE> SetAction() { return m_Action; }
	void EraseWallLocation() { moveLocation.pop_back(); SaveLocationNum.pop_back(); }
	void EraseTemporary() { Temporary_Storage.pop_back(); m_SaveTempNum.pop_back(); }
	void LocationSwap(int _v1, int _v2);
	void TemporarySwap(int _v1, int _v2);
	void LocationChange(int _v1, D3DXVECTOR3 _ChangeLocation) { moveLocation[_v1] = _ChangeLocation; }
};

