#pragma once
#include "IDisplayObject.h"

class ObjLoader;
class CD3Mesh;

class ObjRen
{
public:
	ObjRen();
	~ObjRen();

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
	D3DXMATRIX mT, mR, mS;
	D3DXMATRIX mWorld;
	D3DXMATRIX mWVP, mWI, mWIT, mView, mProj;

	void Init(float size, LPCTSTR objFile, LPCTSTR pngFile, float x, float y, float z, float rotationX, float rotationY, float rotationZ);
	void Update();
	void Render();
};

