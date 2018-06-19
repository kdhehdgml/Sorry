#include "stdafx.h"
#include "WallManager.h"
#include "Wall.h"

WallManager::WallManager()
{
}


WallManager::~WallManager()
{
	for (size_t i = 0; i < walls.size(); i++)
	{
		SAFE_RELEASE(walls[i]);
	}
}

void WallManager::Init()
{
}

void WallManager::Update()
{
	for (size_t i = 0; i < walls.size(); i++)
	{
		SAFE_UPDATE(walls[i]);
	}
}

void WallManager::Render()
{
	for (size_t i = 0; i < walls.size(); i++)
	{
		SAFE_RENDER(walls[i]);
	}
}

void WallManager::addWall(D3DXVECTOR3 _aa, D3DXVECTOR3 _bb)
{
	Wall* tempWall = new Wall(_aa, _bb);
	walls.push_back(tempWall);
	walls.back()->Init();
}

vector<Wall*> WallManager::getWalls()
{
	return walls;
}

bool WallManager::IntersectSphereBox(BoundingSphere * pSphere, BoundingBox * pBox)
{
	float rr = pSphere->radius * pSphere->radius;
	float dmin = 0.0f;
	if (pSphere->center.x < pBox->aa.x) {
		dmin += sqrt(pSphere->center.x - pBox->aa.x);
	}
	else if (pSphere->center.x > pBox->bb.x) {
		dmin += sqrt(pSphere->center.x - pBox->bb.x);
	}

	if (pSphere->center.y < pBox->aa.y) {
		dmin += sqrt(pSphere->center.y - pBox->aa.y);
	}
	else if (pSphere->center.y > pBox->bb.y) {
		dmin += sqrt(pSphere->center.y - pBox->bb.y);
	}

	if (pSphere->center.z < pBox->aa.z) {
		dmin += sqrt(pSphere->center.z - pBox->aa.z);
	}
	else if (pSphere->center.z > pBox->bb.z) {
		dmin += sqrt(pSphere->center.z - pBox->bb.z);
	}
	if (dmin <= rr) {
		return true;
	}
	return false;
}
