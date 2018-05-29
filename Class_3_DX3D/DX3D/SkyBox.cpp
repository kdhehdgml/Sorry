#include "stdafx.h"
#include "SkyBox.h"
#include "IDisplayObject.h"


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

	SKYVERTEX vertices[24] =
	{
		{ -250.0f, 250.0f, -250.0f, 0.0f, 0.0f },		// Top vertices
		{ 250.0f, 250.0f, -250.0f, 1.0f, 0.0f },
		{ -250.0f, 250.0f,  250.0f, 0.0f, 1.0f },
		{ 250.0f, 250.0f,  250.0f, 1.0f, 1.0f },

		{ -250.0f,  250.0f, 250.0f, 0.0f, 0.0f },		// Front vertices
		{ 250.0f,  250.0f, 250.0f, 1.0f, 0.0f },
		{ -250.0f, -250.0f, 250.0f, 0.0f, 1.0f },
		{ 250.0f, -250.0f, 250.0f, 1.0f, 1.0f },

		{ 250.0f,  250.0f, -250.0f, 0.0f, 0.0f },		// Back vertices
		{ -250.0f,  250.0f, -250.0f, 1.0f, 0.0f },
		{ 250.0f, -250.0f, -250.0f, 0.0f, 1.0f },
		{ -250.0f, -250.0f, -250.0f, 1.0f, 1.0f },

		{ -250.0f,  250.0f, -250.0f, 0.0f, 0.0f },		// Left vertices
		{ -250.0f,  250.0f,  250.0f, 1.0f, 0.0f },
		{ -250.0f, -250.0f, -250.0f, 0.0f, 1.0f },
		{ -250.0f, -250.0f,  250.0f, 1.0f, 1.0f },

		{ 250.0f,  250.0f,  250.0f, 0.0f, 0.0f },		// Right vertices
		{ 250.0f,  250.0f, -250.0f, 1.0f, 0.0f },
		{ 250.0f, -250.0f,  250.0f, 0.0f, 1.0f },
		{ 250.0f, -250.0f, -250.0f, 1.0f, 1.0f },

		{ -250.0f, -250.0f,  250.0f, 0.0f, 0.0f },		// Bottom vertices
		{ 250.0f, -250.0f,  250.0f, 1.0f, 0.0f },
		{ -250.0f, -250.0f, -250.0f, 0.0f, 1.0f },
		{ 250.0f, -250.0f, -250.0f, 1.0f, 1.0f }
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

	Create(g_pDevice,sky);
	
}

void SkyBox::Update()
{
}

void SkyBox::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	// Setup texture
	/* D3DCULL_NONE : �޸��� �ø�(Culling)�� ���� �ʴ´�.
	* D3DCULL_CW   : �޸��� ��ȸ������ �ø�(Culling) �Ѵ�.
	* D3DCULL_CCW  : �޸��� ���� ȸ������ �ø�(Culling) �Ѵ�.
	* D3DCULL_FORCE_DWORD : �� �������� ���������� 32 ��Ʈ ����� ������ �Ѵ�. �� ���� ������ �ʾҴ�.
	*/
	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// D3DSAMP_ADDRESSU : u ��ǥ�� ����ϴ� �ؽ�ó��巹�̸��. ����Ʈ�� D3DTADDRESS_WRAP �̴�. �� �ڼ��� ������, ��D3DTEXTUREADDRESS ���� �����Ұ�. 
	// D3DSAMP_ADDRESSV : v ��ǥ�� ����ϴ� �ؽ�ó��巹�̸��. ����Ʈ�� D3DTADDRESS_WRAP �̴�. �� �ڼ��� ������, ��D3DTEXTUREADDRESS ���� �����Ұ�. 
	// D3DTADDRESS_CLAMP: ���� [0.0, 1.0] �� ������ �ؽ�ó ��ǥ��, ����, 0.0 ���� 1.0 �� �ؽ�ó �÷��� �����ȴ�. 
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);


	D3DXMatrixIdentity(&m_matWorld);
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
