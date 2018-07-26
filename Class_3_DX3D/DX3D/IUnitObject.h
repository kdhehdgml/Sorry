#pragma once
#include "IDisplayObject.h"

class IUnitObject : public IDisplayObject
{
protected:
	D3DXVECTOR3		m_deltaPos;
	D3DXVECTOR3		m_deltaRot;
	D3DXVECTOR3		m_forward;
	D3DXVECTOR3		m_baseRotation;


	KEYBOARD_STATE	m_keyState;
	bool			m_colision;
	bool			m_isMoving;
	bool			m_start;
	bool			m_hit;
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

	D3DXMATRIXA16				m_L_mat;
	D3DXVECTOR3					m_L_pos;

	D3DXMATRIXA16				m_R_mat;
	D3DXVECTOR3					m_R_pos;

	D3DXMATRIXA16				m_mat;
	D3DXVECTOR3					m_mat_pos;

	D3DXMATRIXA16				m_head_mat;
	D3DXMATRIXA16				m_head_mat2;
	D3DXVECTOR3					m_head_pos;



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
	void SetHitting(bool _hit) { m_hit = _hit; }
	float GetMoveSpeed() { return m_moveSpeed; }
	void SetMove(bool _move) { m_colision = _move; }
	void UpdateTargetPosition(OUT D3DXVECTOR3 &targetPos);
	void ApplyTargetPosition(D3DXVECTOR3 &targetPos);
	void UpdatePosition();
	void DecreaseHealth(int h);
	//D3DXQUATERNION* OutRotation
	//객체 행렬값에서 회전 행렬값 구하는 함수
	void GetScaleAndRotation(const D3DXMATRIX& val, D3DXVECTOR3* OutScale, D3DXMATRIX& rotmat);

	//테스트
	D3DXVECTOR3* GetLeftPos() { return &m_L_pos; }
	LPD3DXMATRIXA16 GetLeftMat() { return &m_L_mat; } //왼손매트릭스
													  //void SetMat(D3DXMATRIXA16 *mat) { m_Hand_mat = (*mat); }

	D3DXVECTOR3* GetRightPos() { return&m_R_pos; }
	LPD3DXMATRIXA16 GetRightMat() { return &m_R_mat; }//오른손매트릭스

	LPD3DXMATRIXA16 GetRotMat() { return &m_rotMat; }
	D3DXVECTOR3 GetScaleMat() { return m_scaleMat; }

	LPD3DXMATRIXA16 GetMat() { return &m_mat; }
	D3DXVECTOR3 GetPos() { return m_mat_pos; }

	LPD3DXMATRIXA16 GetHeadMat() { return &m_head_mat; }
	LPD3DXMATRIXA16 GetHeadMat2() { return &m_head_mat2; }
	D3DXVECTOR3		GetHeadPos() { return m_head_pos; }

	void SetAngle(float angle) { m_angle = angle; }
	float GetAngle() { return m_angle; }

};