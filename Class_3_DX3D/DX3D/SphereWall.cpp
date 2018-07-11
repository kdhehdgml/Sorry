#include "stdafx.h"
#include "SphereWall.h"

SphereWall::SphereWall(D3DXVECTOR3 _center, float _size)
{
	center = _center;
	size = _size;
}

SphereWall::~SphereWall()
{
	SAFE_RELEASE(m_pSphere);
	SAFE_DELETE(m_pBoundingSphere);
}

void SphereWall::Init()
{
	D3DXCreateSphere(g_pDevice, size, 10, 10, &m_pSphere, NULL);
	m_pBoundingSphere = new BoundingSphere(center, size);
}

void SphereWall::Update()
{
}

void SphereWall::Render()
{
	D3DXMATRIXA16 mat, matR, matW;
	D3DXMatrixTranslation(&mat, center.x, center.y, center.z);
	D3DXMatrixRotationY(&matR, m_rot.y);
	matW = mat * matR;
	g_pDevice->SetTransform(D3DTS_WORLD, &matW);
	g_pDevice->SetTexture(0, NULL);
	//m_pSphere->DrawSubset(0);
}

BoundingSphere * SphereWall::getBoundingSphere()
{
	return m_pBoundingSphere;
}

D3DXVECTOR3 SphereWall::getCenter()
{
	return m_pBoundingSphere->center;
}

float SphereWall::getSize()
{
	return m_pBoundingSphere->radius;
}
