#include "stdafx.h"
#include "WallManager.h"
#include "Wall.h"
#include "SphereWall.h"

WallManager::WallManager()
{
}


WallManager::~WallManager()
{
	for (size_t i = 0; i < walls.size(); i++)
	{
		SAFE_RELEASE(walls[i]);
	}
	for (size_t i = 0; i < sphereWalls.size(); i++) {
		SAFE_RELEASE(sphereWalls[i]);
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
	for (size_t i = 0; i < sphereWalls.size(); i++) {
		SAFE_UPDATE(sphereWalls[i]);
	}
}

void WallManager::Render()
{
	for (size_t i = 0; i < walls.size(); i++)
	{
		SAFE_RENDER(walls[i]);
	}
	for (size_t i = 0; i < sphereWalls.size(); i++) {
		SAFE_RENDER(sphereWalls[i]);
	}
}

void WallManager::addWall(D3DXVECTOR3 _aa, D3DXVECTOR3 _bb)
{
	Wall* tempWall = new Wall(_aa, _bb);
	walls.push_back(tempWall);
	walls.back()->Init();
}

void WallManager::addSphereWall(D3DXVECTOR3 _center, float _size)
{
	SphereWall* tempSphereWall = new SphereWall(_center, _size);
	sphereWalls.push_back(tempSphereWall);
	sphereWalls.back()->Init();
}

vector<Wall*> WallManager::getWalls()
{
	return walls;
}

vector<SphereWall*> WallManager::getSphereWalls()
{
	return sphereWalls;
}

bool WallManager::IntersectSphereBox(BoundingSphere * pSphere, BoundingBox * pBox)
{
	float rr = sqrt(pSphere->radius);
	float dmin = 0.0f;
	if (pSphere->center.x < pBox->aa.x) {
		dmin += sqrt(abs(pSphere->center.x - pBox->aa.x));
	}
	else if (pSphere->center.x > pBox->bb.x) {
		dmin += sqrt(abs(pSphere->center.x - pBox->bb.x));
	}

	if (pSphere->center.y < pBox->aa.y) {
		dmin += sqrt(abs(pSphere->center.y - pBox->aa.y));
	}
	else if (pSphere->center.y > pBox->bb.y) {
		dmin += sqrt(abs(pSphere->center.y - pBox->bb.y));
	}

	if (pSphere->center.z < pBox->aa.z) {
		dmin += sqrt(abs(pSphere->center.z - pBox->aa.z));
	}
	else if (pSphere->center.z > pBox->bb.z) {
		dmin += sqrt(abs(pSphere->center.z - pBox->bb.z));
	}
	if (dmin <= rr) {
		return true;
	}
	return false;
}

bool WallManager::IntersectSphereSphere(BoundingSphere * pSphere1, BoundingSphere * pSphere2)
{

	return false;
}
