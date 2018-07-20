#pragma once
#include "IDisplayObject.h"

class IUnitObject : public IDisplayObject
{
protected:
	D3DXVECTOR3		m_deltaPos;
	D3DXVECTOR3		m_deltaRot;
	D3DXVECTOR3		m_forward;

	KEYBOARD_STATE	m_keyState;
	bool			m_colision;
	bool			m_isMoving;
	bool			m_start;
	float			m_moveSpeed;
	float			m_currMoveSpeedRate;
	float			m_rotationSpeed;
	int				m_def;
	bool			m_isJumping;
	float			m_jumpPower;
	float			m_gravity;
	float			m_currGravity;
	//각도
	float			m_angle;
	float			m_maxStepHeight;
	float			m_baseRotY;
	int				m_avoidObstDir;
	int health;
	D3DXVECTOR3		m_destPos;
	D3DXVECTOR3		m_finalDestPos;
	D3DXVECTOR3		m_SaveFinal;
	vector<int>		m_vecAStarIndex;

	D3DXMATRIXA16				m_rotMat;
	D3DXVECTOR3					m_scaleMat;

	IUnitObject();

public:
	bool CanFight;
	virtual ~IUnitObject();

	void SetTargetPostion(const D3DXVECTOR3 &pos);
	void SetDestination(const D3DXVECTOR3 &pos);
	void TrenchSetDestination(const D3DXVECTOR3 &pos);
	bool GetMove() { return m_colision; }
	void SetMoveSpeed(int _movespeed) { m_moveSpeed = _movespeed; }
	void UpdateKeyboardState();
	void UpdatePositionToDestination();
	int getHealth() { return health; }
	void setHealth(int h) { health = h; }

	float GetMoveSpeed() { return m_moveSpeed; }
	void SetMove(bool _move) { m_colision = _move; }
	void UpdateTargetPosition(OUT D3DXVECTOR3 &targetPos);
	void ApplyTargetPosition(D3DXVECTOR3 &targetPos);
	void UpdatePosition();
	void DecreaseHealth(int h);
	//D3DXQUATERNION* OutRotation
	//객체 행렬값에서 회전 행렬값 구하는 함수
	void GetScaleAndRotation(const D3DXMATRIX& val, D3DXVECTOR3* OutScale, D3DXMATRIX& rotmat);
};