#include "stdafx.h"
#include "BOSS.h"


BOSS::BOSS()
{
}


BOSS::~BOSS()
{
}

void BOSS::Init()
{
	Load("resources/xFile/boss/Mark.X");

}

void BOSS::Update()
{
}

void BOSS::Render()
{
}

LPD3DXMESH BOSS::Load(const char * szFileName)
{
	
	LPD3DXMESH mesh = NULL;

	if (FAILED(( (LPCWSTR)szFileName, D3DXMESH_SYSTEMMEM, g_pDevice, NULL, NULL, NULL, NULL, &mesh)))
	{
	MessageBox(g_hWnd, L"모델 로딩 실패 ", L"실패", MB_OK);

	}
	
	return mesh;
}

LPD3DXEFFECT BOSS::LoadShader(const char * szFileName)
{
	return LPD3DXEFFECT();
}
