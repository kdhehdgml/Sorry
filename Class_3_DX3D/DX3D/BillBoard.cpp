#include "stdafx.h"
#include "BillBoard.h"


BillBoard::BillBoard()
{
	g_pTexBillboard = NULL;
	check = false;
}


BillBoard::~BillBoard()
{
	SAFE_RELEASE(g_pTexBillboard);
}

void BillBoard::Init()
{
	D3DXCreateTextureFromFile(g_pDevice, _T("resources/explosion.jpg"), &g_pTexBillboard);

	D3DXMatrixIdentity(&m_matWorld);
}

void BillBoard::Update()
{
}

void BillBoard::Render(float xP, float yP, float zP)
{
	static int		nStep = 0;
	static DWORD	nTick = 0;

	g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x08);
	g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	struct UV
	{
		float u, v;
	};

	struct MYVERTEX
	{
		enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
		float px, py, pz;
		UV uv;
	};

	static MYVERTEX vtx[4] =
	{
		{ -60,   0, 0,  0, 1 },
		{ -60,  90, 0,  0, 0 },
		{  60,   0, 0, 60, 1 },
		{  60,  90, 0, 60, 0 }
	};
	static UV tblUV[16][4] =
	{
		{ { 0.00f, 0.25f },{ 0.00f, 0.00f },{ 0.25f, 0.25f },{ 0.25f, 0.00f } },
		{ { 0.25f, 0.25f },{ 0.25f, 0.00f },{ 0.50f, 0.25f },{ 0.50f, 0.00f } },
		{ { 0.50f, 0.25f },{ 0.50f, 0.00f },{ 0.75f, 0.25f },{ 0.75f, 0.00f } },
		{ { 0.75f, 0.25f },{ 0.75f, 0.00f },{ 1.00f, 0.25f },{ 1.00f, 0.00f } },

		{ { 0.00f, 0.50f },{ 0.00f, 0.25f },{ 0.25f, 0.50f },{ 0.25f, 0.25f } },
		{ { 0.25f, 0.50f },{ 0.25f, 0.25f },{ 0.50f, 0.50f },{ 0.50f, 0.25f } },
		{ { 0.50f, 0.50f },{ 0.50f, 0.25f },{ 0.75f, 0.50f },{ 0.75f, 0.25f } },
		{ { 0.75f, 0.50f },{ 0.75f, 0.25f },{ 1.00f, 0.50f },{ 1.00f, 0.25f } },

		{ { 0.00f, 0.75f },{ 0.00f, 0.50f },{ 0.25f, 0.75f },{ 0.25f, 0.50f } },
		{ { 0.25f, 0.75f },{ 0.25f, 0.50f },{ 0.50f, 0.75f },{ 0.50f, 0.50f } },
		{ { 0.50f, 0.75f },{ 0.50f, 0.50f },{ 0.75f, 0.75f },{ 0.75f, 0.50f } },
		{ { 0.75f, 0.75f },{ 0.75f, 0.50f },{ 1.00f, 0.75f },{ 1.00f, 0.50f } },

		{ { 0.00f, 1.00f },{ 0.00f, 0.75f },{ 0.25f, 1.00f },{ 0.25f, 0.75f } },
		{ { 0.25f, 1.00f },{ 0.25f, 0.75f },{ 0.50f, 1.00f },{ 0.50f, 0.75f } },
		{ { 0.50f, 1.00f },{ 0.50f, 0.75f },{ 0.75f, 1.00f },{ 0.75f, 0.75f } },
		{ { 0.75f, 1.00f },{ 0.75f, 0.75f },{ 1.00f, 1.00f },{ 1.00f, 0.75f } },
	};

	D3DXMATRIXA16	matBillboard;
	D3DXMatrixIdentity(&matBillboard);


	if ((GetTickCount() - nTick) > 100)
	{
		nStep = (nStep++) % 16;
		if (nStep == 16)
			check = false;
		nTick = GetTickCount();
	}

	g_pDevice->SetTexture(1, NULL);
	g_pDevice->SetFVF(MYVERTEX::FVF);

	if (TRUE)
	{
		matBillboard._11 = g_pCamera->GetViewMatrix()->_11;
		matBillboard._13 = g_pCamera->GetViewMatrix()->_13;
		matBillboard._31 = g_pCamera->GetViewMatrix()->_31;
		matBillboard._33 = g_pCamera->GetViewMatrix()->_33;
		D3DXMatrixInverse(&matBillboard, NULL, &matBillboard);
	}

	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	if (TRUE)
	{
		matBillboard = *g_pCamera->GetViewMatrix();
		D3DXMatrixInverse(&matBillboard, NULL, &matBillboard);
	}
	
	matBillboard._41 = xP - 5.0f;
	matBillboard._42 = yP - 10.0f;
	matBillboard._43 = zP;
	g_pDevice->SetTexture(0, g_pTexBillboard);

	vtx[0].uv = tblUV[nStep][0];
	vtx[1].uv = tblUV[nStep][1];
	vtx[2].uv = tblUV[nStep][2];
	vtx[3].uv = tblUV[nStep][3];


	g_pDevice->SetTransform(D3DTS_WORLD, &matBillboard);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx, sizeof(MYVERTEX));

	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

}
