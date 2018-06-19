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

void WallManager::addWall(D3DXVECTOR3 _aa, D3DXVECTOR3 _bb, D3DXVECTOR3 _size)
{
	Wall* tempWall = new Wall(_aa, _bb, _size);
	walls.push_back(tempWall);
}

vector<Wall*> WallManager::getWalls()
{
	return walls;
}
