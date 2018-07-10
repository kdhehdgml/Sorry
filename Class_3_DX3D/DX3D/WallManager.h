#pragma once
#include "IUnitObject.h"
class Wall;
class SphereWall;
class WallManager :
	public IUnitObject
{
private:
	vector<Wall*> walls;
	vector<SphereWall*> sphereWalls;
	int wallsNum;
	int sphereWallsNum;
public:
	WallManager();
	~WallManager();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	void addWall(D3DXVECTOR3 _aa, D3DXVECTOR3 _bb);
	void addSphereWall(D3DXVECTOR3 _center, float _size);
	vector<Wall*> getWalls();
	vector<SphereWall*> getSphereWalls();
	bool IntersectSphereBox(BoundingSphere* pSphere, BoundingBox* pBox);
	bool IntersectSphereSphere(BoundingSphere *pSphere1, BoundingSphere *pSphere2);
};

