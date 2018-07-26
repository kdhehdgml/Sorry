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
private:
	vector<D3DXVECTOR3> m_vecMovePosit;
	int			MoveNum;

	LPD3DXMESH Load(const char* szFileName);

	LPD3DXMESH				g_pMesh = NULL; // �޽� ��ü
	D3DMATERIAL9*			g_pMeshMaterials = NULL; // �޽ÿ��� ����� ����
	LPDIRECT3DTEXTURE9*		g_pMeshTexture = NULL; // �޽ÿ��� ����� �ؽ�ó
	DWORD					g_dwNumMaterials = 0L;	// �޽ÿ��� ������� ������ ����
//x���� �δ� ��ó
//��ó: http://openhead.tistory.com/entry/�޽�-�ʱ�ȭ [OpenHead]

public:
	MARK();
	~MARK();

	MoveOBJ*		m_mark_main;
	MoveOBJ*		m_mark_sponson;
	MoveOBJ*		m_mark_tire;

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
	void Skin_render();
	void SetMoving(const D3DXVECTOR3 & pos);
};



