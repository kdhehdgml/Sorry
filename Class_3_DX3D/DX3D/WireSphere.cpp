#include "stdafx.h"
#include "WireSphere.h"


WireSphere::WireSphere()
{
	m_pSphere = NULL;
}


WireSphere::~WireSphere()
{
	SAFE_RELEASE(m_pSphere);
}

void WireSphere::Init()
{
	D3DXCreateSphere(g_pDevice, 10.0f, 10, 10, &m_pSphere, NULL);
}

void WireSphere::Update()
{
}

void WireSphere::Render()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixTranslation(&mat, m_pos.x, m_pos.y, m_pos.z);
	g_pDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pDevice->SetTexture(0, NULL);
	m_pSphere->DrawSubset(0);
}
