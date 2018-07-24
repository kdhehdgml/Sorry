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
private:
	vector<D3DXVECTOR3> m_vecMovePosit;
	int			MoveNum;

	LPD3DXMESH Load(const char* szFileName);

	LPD3DXMESH				g_pMesh = NULL; // 메시 객체
	D3DMATERIAL9*			g_pMeshMaterials = NULL; // 메시에서 사용할 재질
	LPDIRECT3DTEXTURE9*		g_pMeshTexture = NULL; // 메시에서 사용할 텍스처
	DWORD					g_dwNumMaterials = 0L;	// 메시에서 사용중인 재질의 개수
//x파일 로더 출처
//출처: http://openhead.tistory.com/entry/메시-초기화 [OpenHead]

public:
	MARK();
	~MARK();

	MoveOBJ*		m_mark_main;
	MoveOBJ*		m_mark_sponson;
	MoveOBJ*		m_mark_tire;

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
	void Skin_render();
	void SetMoving(const D3DXVECTOR3 & pos);
};



