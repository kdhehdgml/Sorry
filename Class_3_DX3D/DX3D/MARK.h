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
	좌이동,
	우이동,
	상이동,
	하이동,
	기관총공격,
	참호부수기
};

class MARK : public IUnitObject
{
public:
	MARK();
	~MARK();

	MoveOBJ*	m_mark;

	int			maxHP;
	int			HP;
	float			MoveSpeed;
	int			ATK;
	int			DEF;
	int			state;
	

	float x, y, z, xR, yR, zR;

	// IUnitObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};



