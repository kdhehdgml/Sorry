#pragma once
#include "IUnitObject.h"
class SphereWall :
	public IUnitObject
{
private:
	LPD3DXMESH m_pSphere;
	BoundingSphere* m_pBoundingSphere;
public:
	SphereWall(D3DXVECTOR3 center, float size);
	~SphereWall();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	BoundingSphere* getBoundingSphere();
	D3DXVECTOR3 getCenter();
	float getSize();
};

