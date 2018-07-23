#pragma once
#include "IUnitObject.h"

class MoveOBJ;

//struct STATE
//{
//
//};

enum TANK_PATTEN
{
	멈춤,
	이동,
	//테스트용
	좌이동,
	우이동,
	상이동,
	하이동,
	//
	기관총공격,
	참호부수기
};

class MARK : public IUnitObject
{
public:
	MARK();
	~MARK();

	MoveOBJ*		m_mark;
	//충돌박스
	BoundingSphere* m_pBoundingSphere;
	LPD3DXMESH		m_pSphere;

	int			MaxHP;
	int			HP;
	float		MoveSpeed;
	float		RotSpeed;
	int			ATK;
	int			DEF;
	int			state;

	float		size;
	

	float x, y, z, xR, yR, zR;

	// IUnitObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};



