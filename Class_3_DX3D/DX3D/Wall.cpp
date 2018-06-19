#include "stdafx.h"
#include "Wall.h"


Wall::Wall(D3DXVECTOR3 _aa, D3DXVECTOR3 _bb)
{
	m_pBox = NULL;
	m_pBoundingBox = NULL;
	aa = _aa;
	bb = _bb;
	size = bb - aa;
}


Wall::~Wall()
{
	SAFE_RELEASE(m_pBox);
	SAFE_DELETE(m_pBoundingBox);
}

void Wall::Init()
{
	D3DXCreateBox(g_pDevice, size.x, size.y, size.z, &m_pBox, NULL);
	bb = aa + size;
	m_pBoundingBox = new BoundingBox(aa, bb);
	center = (aa + bb) / 2;
}

void Wall::Update()
{
}

void Wall::Render()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixTranslation(&mat, center.x, center.y, center.z);
	g_pDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pDevice->SetTexture(0, NULL);
	m_pBox->DrawSubset(0);
}

BoundingBox * Wall::getBoundingBox()
{
	return m_pBoundingBox;
}

D3DXVECTOR3 Wall::getCenter()
{
	return center;
}
