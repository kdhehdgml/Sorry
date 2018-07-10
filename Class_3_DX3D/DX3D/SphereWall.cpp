#include "stdafx.h"
#include "SphereWall.h"

SphereWall::SphereWall(D3DXVECTOR3 center, float size)
{
}

SphereWall::~SphereWall()
{
}

void SphereWall::Init()
{
}

void SphereWall::Update()
{
}

void SphereWall::Render()
{
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
