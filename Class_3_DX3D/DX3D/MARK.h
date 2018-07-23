#pragma once
#include "IUnitObject.h"

class MoveOBJ;

//struct STATE
//{
//
//};

enum TANK_PATTEN
{
	����,
	���̵�,
	���̵�,
	���̵�,
	���̵�,
	����Ѱ���,
	��ȣ�μ���
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

	// IUnitObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};



