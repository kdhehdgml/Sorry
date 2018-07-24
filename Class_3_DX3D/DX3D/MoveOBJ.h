#pragma once

class ObjLoader;
class CD3Mesh;


class MoveOBJ
{
public:
	MoveOBJ();
	~MoveOBJ();


	ObjLoader*	g_pLoader;
	CD3Mesh*	g_pD3DMesh;
	TObjMesh	objMesh;
	TObjMaterial objMate;

	float g_fScale;
	FLOAT g_fFOV;
	FLOAT g_fAspect;
	D3DXMATRIXA16 m_matWorld;
	D3DXVECTOR3 bbSize;
	D3DXVECTOR3 bbCenter;
	FLOAT sizeFactor;
	//D3DXMATRIX mT, mR, mS;
	D3DXMATRIX mWorld;
	D3DXMATRIX mWVP, mWI, mWIT, mView, mProj;
	D3DXMATRIX mT, mRX, mRY, mRZ, mS, mR;
	D3DXVECTOR3 m_pos;
	float m_angle;

	void SetRot(float angle) { m_angle = m_angle+angle; }

	void Init(float size, LPCTSTR objFile, LPCTSTR pngFile, float x, float y, float z, float rotationX, float rotationY, float rotationZ);
	void Update();
	void Render();
};

