#pragma once
#include "IUnitObject.h"
class CubemanParts;
class MONSTER;


class Mob
	: public IUnitObject
{
private:
	CubemanParts *	m_pRootParts;
	MONSTER		*	m_MONSTER;

	VERTEX_PC		Shootpos[2];
	D3DXVECTOR3		forward;
	bool			m_isTurnedOnLight;

	D3DXVECTOR3		m_deltaPos;
	D3DXVECTOR3		m_deltaRot;
	D3DXVECTOR3		m_forward;
	D3DXVECTOR3		m_Mobpos;

	bool			m_isMoving;
	bool			m_isShoot;
	bool			m_BeDetermined;
	vector<D3DXVECTOR3> moveLocation;
	vector<D3DXVECTOR3> Temporary_Storage;
	vector<int> SaveLocationNum;
	vector<int> m_SaveTempNum;
	LPD3DXMESH		m_pSphereBody;
	BoundingSphere* m_pBoundingSphereBody;
	LPD3DXMESH		m_pSphereHead;
	BoundingSphere* m_pBoundingSphereHead;
	int health;
	int status;

public:
	Mob();
	~Mob();
	int				num;
	bool			m_move;
	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	
	BoundingSphere* getBoundingSphereBody();
	BoundingSphere* getBoundingSphereHead();
	int getHealth();
	void setHealth(int h);
	int getStatus();
	void setStatus(int s);

	void CreateAllParts();
	void CreateParts(CubemanParts* &pParts, IDisplayObject* pParent,
		D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 trans,
		vector<vector<int>> &vecUV);

	virtual bool PlayerSearch(Mob * mob);
	void ShootVertex(Mob * mob);
	void GetMoveTheWall(D3DXVECTOR3 wallLocation, int Locationnum) 
	{ moveLocation.push_back(wallLocation); SaveLocationNum.push_back(Locationnum);}
	void GetTemporary(D3DXVECTOR3 wallLocation, int Locationnum) 
	{ Temporary_Storage.push_back(wallLocation); m_SaveTempNum.push_back(Locationnum);}
	void GetDetermined(bool _boo) { m_BeDetermined = _boo; }
	void GetMove(bool _move) { m_colision = _move; }
	
	vector<D3DXVECTOR3> SetMoveTheWall() { return moveLocation; }
	vector<int> SetLocationNum() { return SaveLocationNum; }
	vector<D3DXVECTOR3> SetTemporary() { return Temporary_Storage; }
	vector<int> SetTemporaryNum() { return m_SaveTempNum; }
	bool SetDetermined() { return m_BeDetermined; }
	bool SetMove() { return m_colision; }
	void EraseWallLocation() { moveLocation.pop_back(); SaveLocationNum.pop_back(); }
	void EraseTemporary() { Temporary_Storage.pop_back(); m_SaveTempNum.pop_back(); }
	void LocationSwap(int _v1, int _v2);
	void TemporarySwap(int _v1, int _v2);
	void LocationChange(int _v1, D3DXVECTOR3 _ChangeLocation) { moveLocation[_v1] = _ChangeLocation; }
	vector<vector<int>> uvBody = {
		{ 32, 32, 32, 20, 40, 20, 40, 32 },	// 후
	{ 20, 32, 20, 20, 28, 20, 28, 32 },	// 전
	{ 28, 32, 28, 20, 32, 20, 32, 32 },	// 좌
	{ 16, 32, 16, 20, 20, 20, 20, 32 },	// 우
	{ 20, 20, 20, 16, 28, 16, 28, 20 },	// 상
	{ 28, 16, 28, 20, 36, 20, 36, 16 }	// 하
	};

	vector<vector<int>> uvHead = {
		{ 24, 16, 24, 8, 32, 8, 32, 16 },	// 후
	{ 8, 16, 8, 8, 16, 8, 16, 16 },		// 전
	{ 16, 16, 16, 8, 24, 8, 24, 16 },	// 좌
	{ 0, 16, 0, 8, 8, 8, 8, 16 },		// 우
	{ 8, 8, 8, 0, 16, 0, 16, 8 },		// 상
	{ 16, 0, 16, 8, 24, 8, 24, 0 }		// 하
	};

	vector<vector<int>> uvLArm = {
		{ 44, 32, 44, 20, 48, 20, 48, 32 },	// 후
	{ 52, 32, 52, 20, 56, 20, 56, 32 },	// 전
	{ 40, 32, 40, 20, 44, 20, 44, 32 },	// 좌
	{ 48, 32, 48, 20, 52, 20, 52, 32 },	// 우
	{ 44, 20, 44, 16, 48, 16, 48, 20 },	// 상
	{ 48, 16, 48, 20, 52, 20, 52, 16 }	// 하
	};

	vector<vector<int>> uvRArm = {
		{ 48, 32, 48, 20, 44, 20, 44, 32 },	// 후
	{ 56, 32, 56, 20, 52, 20, 52, 32 },	// 전
	{ 48, 32, 48, 20, 52, 20, 52, 32 },	// 좌
	{ 40, 32, 40, 20, 44, 20, 44, 32 },	// 우
	{ 48, 20, 48, 16, 44, 16, 44, 20 },	// 상
	{ 52, 16, 52, 20, 48, 20, 48, 16 }	// 하
	};

	vector<vector<int>> uvLLeg = {
		{ 12, 32, 12, 20, 16, 20, 16, 32 },	// 후
	{ 4, 32, 4, 20, 8, 20, 8, 32 },		// 전
	{ 8, 32, 8, 20, 12, 20, 12, 32 },	// 좌
	{ 0, 32, 0, 20, 4, 20, 4, 32 },		// 우
	{ 4, 20, 4, 16, 8, 16, 8, 20 },		// 상
	{ 8, 16, 8, 20, 12, 20, 12, 16 }	// 하
	};

	vector<vector<int>> uvRLeg = {
		{ 16, 32, 16, 20, 12, 20, 12, 32 },	// 후
	{ 8, 32, 8, 20, 4, 20, 4, 32 },		// 전
	{ 4, 32, 4, 20, 0, 20, 0, 32 },		// 좌
	{ 12, 32, 12, 20, 8, 20, 8, 32 },	// 우
	{ 8, 20, 8, 16, 4, 16, 4, 20 },		// 상
	{ 12, 16, 12, 20, 8, 20, 8, 16 }	// 하
	};
};

