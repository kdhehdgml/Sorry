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

D3DXVECTOR3 WireSphere::getPos()
{
	return m_pos;
}

void WireSphere::setPos(D3DXVECTOR3 _pos)
{
	m_pos = _pos;
}

void WireSphere::Init()
{
	D3DXCreateSphere(g_pDevice, 10.0f, 10, 10, &m_pSphere, NULL);
	m_pRenderToggle = false;
}

void WireSphere::Update()
{
	if (m_pRenderToggle) {
		m_rot.y += 0.01f;
	}
}

void WireSphere::Render()
{
	if (m_pRenderToggle) {
		D3DXMATRIXA16 matS, matR, matT;
		D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
		D3DXMatrixRotationY(&matR, m_rot.y);
		D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
		m_matWorld = matS * matR * matT;
		g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		g_pDevice->SetTexture(0, NULL);
		m_pSphere->DrawSubset(0);
		g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}
