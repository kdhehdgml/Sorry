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

	bool			m_isJumping;
	float			m_jumpPower;
	float			m_gravity;
	float			m_currGravity;

	float			m_maxStepHeight;
	float			m_baseRotY;

	int health;

	D3DXVECTOR3		m_destPos;
	D3DXVECTOR3		m_finalDestPos;
	vector<int>		m_vecAStarIndex;

	IUnitObject();

public:
	
	virtual ~IUnitObject();

	void SetTargetPostion(const D3DXVECTOR3 &pos);
	void SetDestination(const D3DXVECTOR3 &pos);
	bool GetMove() { return m_colision; }
	void SetMoveSpeed(int _movespeed) { m_moveSpeed = _movespeed; }
	void UpdateKeyboardState();
	void UpdatePositionToDestination();
	
	int getHealth() { return health; }
	void setHealth(int h) { health = h; }
	
	void SetMove(bool _move) { m_colision = _move; }
	void UpdateTargetPosition(OUT D3DXVECTOR3 &targetPos);
	void ApplyTargetPosition(D3DXVECTOR3 &targetPos);

	void UpdatePosition();
};

