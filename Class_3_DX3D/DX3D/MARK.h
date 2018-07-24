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
	�̵�,
	//�׽�Ʈ��
	���̵�,
	���̵�,
	���̵�,
	���̵�,
	//
	����Ѱ���,
	��ȣ�μ���
};

class MARK : public IUnitObject
{
public:
	MARK();
	~MARK();

	MoveOBJ*		m_mark;
	//�浹�ڽ�
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

	// IUnitObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};



