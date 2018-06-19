#pragma once
#include "IUnitObject.h"
class Wall :
	public IUnitObject
{
private:
	LPD3DXMESH m_pBox;
	BoundingBox* m_pBoundingBox;
public:
	Wall();
	~Wall();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	BoundingBox* getBoundingBox();
};

