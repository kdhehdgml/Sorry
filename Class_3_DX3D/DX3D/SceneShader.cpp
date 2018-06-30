#include "stdafx.h"
#include "SceneShader.h"


SceneShader::SceneShader()
{
	m_pSphere		= NULL;
	m_pColorShader	= NULL;
}


SceneShader::~SceneShader()
{
	m_pSphere->Release();
	m_pColorShader->Release();
}

void SceneShader::Init()
{
	Load("resources/xFile/TEAM_AI/TEAM.X");

	//월드 행렬정의
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	//뷰행렬정의
	D3DXVECTOR3	vEye(0.0f, 0.0f, -100.0f);

}

void SceneShader::Update()
{
}

void SceneShader::Render()
{
}

void SceneShader::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}

LPD3DXMESH SceneShader::Load(const char * szFileName)
{
	LPD3DXMESH ret = NULL;

	if (FAILED(D3DXLoadMeshFromX( (LPCWSTR)szFileName, D3DXMESH_SYSTEMMEM, g_pDevice, NULL, NULL, NULL, NULL, &ret)))
	{
		MessageBox(g_hWnd, L"모델 로딩 실패 ", L"실패", MB_OK);

	}

	return ret;
}

LPD3DXEFFECT SceneShader::LoadShader(const char * szFileName)
{
	LPD3DXEFFECT ret = NULL; //반환변수
	LPD3DXBUFFER pError = NULL; // 에러체크변수
	
	DWORD dwShaderFlags = 0;

	D3DXCreateEffectFromFile(g_pDevice, (LPCWSTR)szFileName, NULL, NULL, dwShaderFlags, NULL, &ret, &pError);

	if (!ret && pError)//에러가 있을경우
	{
		//에러메시지 크기
		int nSize = pError->GetBufferSize();
		//에러메시지 포인터 ??
		void *ack = pError->GetBufferPointer();

		if (ack)
		{
			char* str = new char[nSize];
			memcpy(str, (const char*)ack, nSize);
			//에러메시지 출력
			OutputDebugString((LPCWSTR)str);

			delete[] str;
		}
	}

	return ret;
}
