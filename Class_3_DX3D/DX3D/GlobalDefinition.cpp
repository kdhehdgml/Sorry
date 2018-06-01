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
