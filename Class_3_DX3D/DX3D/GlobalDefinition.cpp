#include "stdafx.h"
#include "GlobalDefinition.h"

CString ASSET_PATH = _T("../../_Assets/");

WORD g_aCubeIndex[36] = {
	0, 1, 2, 0, 2, 3,	// 후
	7, 6, 5, 7, 5, 4,	// 전
	4, 5, 1, 4, 1, 0,	// 좌
	3, 2, 6, 3, 6, 7,	// 우
	1, 5, 6, 1, 6, 2,	// 상
	4, 0, 3, 4, 3, 7	// 하
};

#define RADIUS 1.0f

D3DXVECTOR3 g_aCubeVertex[8] = {
	D3DXVECTOR3(-1.0f, -1.0f, -1.0f),
	D3DXVECTOR3(-1.0f,  1.0f, -1.0f),
	D3DXVECTOR3(1.0f,  1.0f, -1.0f),
	D3DXVECTOR3(1.0f, -1.0f, -1.0f),
	D3DXVECTOR3(-1.0f, -1.0f,  1.0f),
	D3DXVECTOR3(-1.0f,  1.0f,  1.0f),
	D3DXVECTOR3(1.0f,  1.0f,  1.0f),
	D3DXVECTOR3(1.0f, -1.0f,  1.0f)
};

D3DXVECTOR3 g_Cube_TesT[8] = {
	D3DXVECTOR3(-CUBE_RADIUS, -CUBE_RADIUS, -CUBE_RADIUS),
	D3DXVECTOR3(-CUBE_RADIUS,  CUBE_RADIUS, -CUBE_RADIUS),
	D3DXVECTOR3(CUBE_RADIUS,  CUBE_RADIUS, -CUBE_RADIUS),
	D3DXVECTOR3(CUBE_RADIUS, -CUBE_RADIUS, -CUBE_RADIUS),
	D3DXVECTOR3(-CUBE_RADIUS, -CUBE_RADIUS,  CUBE_RADIUS),
	D3DXVECTOR3(-CUBE_RADIUS,  CUBE_RADIUS,  CUBE_RADIUS),
	D3DXVECTOR3(CUBE_RADIUS,  CUBE_RADIUS,  CUBE_RADIUS),
	D3DXVECTOR3(CUBE_RADIUS, -CUBE_RADIUS,  CUBE_RADIUS)
};

DWORD FtoDw(float f)
{
	return *((DWORD*)&f);
}

float GetRandomFloat(float lowBound, float highBound)
{
	float f = (rand() % 10000) * 0.0001f;

	return (f * (highBound - lowBound)) + lowBound;
}

bool CompareStr(const char * str1, const char * str2)
{
	return strcmp(str1, str2) == 0;

}

D3DXMATRIXA16 & Matrix::Identity()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	return mat;
}

D3DXMATRIXA16 & Matrix::Translation(float x, float y, float z)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixTranslation(&mat, x, y, z);
	return mat;
}

D3DXMATRIXA16 & Matrix::Translation(D3DXVECTOR3 v)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixTranslation(&mat, v.x, v.y, v.z);
	return mat;
}

D3DXMATRIXA16 & Matrix::RotationX(float angle)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixRotationX(&mat, angle);
	return mat;
}

D3DXMATRIXA16 & Matrix::RotationY(float angle)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixRotationY(&mat, angle);
	return mat;
}

D3DXMATRIXA16& Matrix::RotationZ(float angle)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixRotationZ(&mat, angle);
	return mat;
}

D3DXMATRIXA16 & Matrix::Scaling(float x, float y, float z)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixScaling(&mat, x, y, z);
	return mat;
}

D3DXMATRIXA16 & Matrix::Scaling(D3DXVECTOR3 v)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixScaling(&mat, v.x, v.y, v.z);
	return mat;
}

D3DXMATRIXA16 & Matrix::Scaling(float xyz)
{
	D3DXMATRIXA16 mat;
	D3DXMatrixScaling(&mat, xyz, xyz, xyz);
	return mat;
}

const D3DXVECTOR3 & Vector3::Create(float xyz)
{
	return D3DXVECTOR3(xyz, xyz, xyz);
}
