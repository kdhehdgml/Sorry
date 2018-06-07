#include "stdafx.h"
#include "SkyBox.h"
#include "IDisplayObject.h"

#define SKYBOXSIZE 1

SkyBox::SkyBox()
{
	m_pd3dDevice = NULL;

	for (int i = 0; i < MAX_SKY_TEX; i++) 
		m_pTex[i] = NULL;
	m_pVB = NULL;

}


SkyBox::~SkyBox()
{
	_Destroy();
}

HRESULT SkyBox::Create(LPDIRECT3DDEVICE9 pDev,string lpTexFilename[MAX_SKY_TEX])
{
	m_pd3dDevice = pDev;
	if (FAILED(_LoadTextures(lpTexFilename))) { _Destroy(); return E_FAIL; }
	if (FAILED(_CreateVertex())) { _Destroy(); return E_FAIL; }

	return S_OK;
}

HRESULT SkyBox::_Destroy()
{
	if (m_pVB != NULL)
		m_pVB->Release();

	for (int i = 0; i < MAX_SKY_TEX; i++)
	{
		if (m_pTex[i] != NULL)
			m_pTex[i]->Release();
	}

	return S_OK;
	
}

HRESULT SkyBox::_LoadTextures(string lpTexFilename[MAX_SKY_TEX])
{
	m_pTex[0] = g_pTextureManager->GetTexture(lpTexFilename[0]);
	m_pTex[1] = g_pTextureManager->GetTexture(lpTexFilename[1]);
	m_pTex[2] = g_pTextureManager->GetTexture(lpTexFilename[2]);
	m_pTex[3] = g_pTextureManager->GetTexture(lpTexFilename[3]);
	m_pTex[4] = g_pTextureManager->GetTexture(lpTexFilename[4]);
	m_pTex[5] = g_pTextureManager->GetTexture(lpTexFilename[5]);

	return S_OK;
}

HRESULT SkyBox::_CreateVertex()
{
	if (FAILED(m_pd3dDevice->CreateVertexBuffer(24 * sizeof(SKYVERTEX), 0, D3DFVF_SKYVERTEX,
		D3DPOOL_DEFAULT, &m_pVB, NULL)))
	{
		_Destroy();
		return E_FAIL;
	}

	float SkyboxSize = GSM().mapSize;

	SKYVERTEX vertices[24] =
	{
		{ -SkyboxSize,  SkyboxSize, -SkyboxSize, 0.0f, 0.0f },		// Top vertices
		{  SkyboxSize,  SkyboxSize, -SkyboxSize, 1.0f, 0.0f },
		{ -SkyboxSize,  SkyboxSize,  SkyboxSize, 0.0f, 1.0f },
		{  SkyboxSize,  SkyboxSize,  SkyboxSize, 1.0f, 1.0f },
		{ -SkyboxSize,  SkyboxSize,  SkyboxSize, 0.0f, 0.0f },		// Front vertices
		{  SkyboxSize,  SkyboxSize,  SkyboxSize, 1.0f, 0.0f },
		{ -SkyboxSize, -SkyboxSize,  SkyboxSize, 0.0f, 1.0f },
		{  SkyboxSize, -SkyboxSize,  SkyboxSize, 1.0f, 1.0f },
		{  SkyboxSize,  SkyboxSize, -SkyboxSize, 0.0f, 0.0f },		// Back vertices
		{ -SkyboxSize,  SkyboxSize, -SkyboxSize, 1.0f, 0.0f },
		{  SkyboxSize, -SkyboxSize, -SkyboxSize, 0.0f, 1.0f },
		{ -SkyboxSize, -SkyboxSize, -SkyboxSize, 1.0f, 1.0f },
		{ -SkyboxSize,  SkyboxSize, -SkyboxSize, 0.0f, 0.0f },		// Left vertices
		{ -SkyboxSize,  SkyboxSize,  SkyboxSize, 1.0f, 0.0f },
		{ -SkyboxSize, -SkyboxSize, -SkyboxSize, 0.0f, 1.0f },
		{ -SkyboxSize, -SkyboxSize,  SkyboxSize, 1.0f, 1.0f },
		{  SkyboxSize,  SkyboxSize,  SkyboxSize, 0.0f, 0.0f },		// Right vertices
		{  SkyboxSize,  SkyboxSize, -SkyboxSize, 1.0f, 0.0f },
		{  SkyboxSize, -SkyboxSize,  SkyboxSize, 0.0f, 1.0f },
		{  SkyboxSize, -SkyboxSize, -SkyboxSize, 1.0f, 1.0f },
		{ -SkyboxSize, -SkyboxSize,  SkyboxSize, 0.0f, 0.0f },		// Bottom vertices
		{  SkyboxSize, -SkyboxSize,  SkyboxSize, 1.0f, 0.0f },
		{ -SkyboxSize, -SkyboxSize, -SkyboxSize, 0.0f, 1.0f },
		{  SkyboxSize, -SkyboxSize, -SkyboxSize, 1.0f, 1.0f }
	};

	VOID* pVertices;
	if (FAILED(m_pVB->Lock(0, 24 * sizeof(SKYVERTEX), (void**)&pVertices, 0)))
	{
		_Destroy();
		return E_FAIL;
	}
	memcpy(pVertices, vertices, 24 * sizeof(SKYVERTEX));
	m_pVB->Unlock();

	return S_OK;
}





void SkyBox::Init()
{
	string	sky[6] =
	{
		"resources/SKY/Top.bmp",
		"resources/SKY/Front.bmp",
		"resources/SKY/Back.bmp",
		"resources/SKY/Right.bmp",
		"resources/SKY/Left.bmp",
		"resources/SKY/Bottom.bmp" 
	};
	D3DXMATRIXA16 matT, matS, matR;
	
	m_pos.x += 160.0f;//왼쪽으로 늘리기
	m_pos.z += 240.0f;//앞뒤로 늘리기
	m_pos.y += 30.0f; //위아래


	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixScaling(&matS, SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	
	m_matWorld =  matS * matT;

	Create(g_pDevice,sky);
	
}

void SkyBox::Update()
{
}

void SkyBox::Render()
{
	g_pDevice->SetRenderState(D3DRS_FOGENABLE, false);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	// Setup texture
	/* D3DCULL_NONE : 뒷면의 컬링(Culling)는 하지 않는다.
	* D3DCULL_CW   : 뒷면을 우회전으로 컬링(Culling) 한다.
	* D3DCULL_CCW  : 뒷면을 왼쪽 회전으로 컬링(Culling) 한다.
	* D3DCULL_FORCE_DWORD : 이 열거형을 강제적으로 32 비트 사이즈에 컴파일 한다. 이 값은 사용되지 않았다.
	*/
	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// D3DSAMP_ADDRESSU : u 좌표로 사용하는 텍스처어드레싱모드. 디폴트는 D3DTADDRESS_WRAP 이다. 더 자세한 정보는, 「D3DTEXTUREADDRESS 」를 참조할것. 
	// D3DSAMP_ADDRESSV : v 좌표로 사용하는 텍스처어드레싱모드. 디폴트는 D3DTADDRESS_WRAP 이다. 더 자세한 정보는, 「D3DTEXTUREADDRESS 」를 참조할것. 
	// D3DTADDRESS_CLAMP: 범위 [0.0, 1.0] 의 외측의 텍스처 좌표가, 각각, 0.0 으로 1.0 의 텍스처 컬러로 설정된다. 
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);


//	D3DXMatrixIdentity(&m_matWorld);
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pd3dDevice->SetFVF(D3DFVF_SKYVERTEX);
	m_pd3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(SKYVERTEX));

	

	for (int i = 0; i < 6; i++)
	{
		m_pd3dDevice->SetTexture(0, m_pTex[i]);
		m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);

		m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	}
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
}
