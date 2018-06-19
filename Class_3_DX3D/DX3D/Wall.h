#pragma once
#include "IUnitObject.h"
class Wall :
	public IUnitObject
{
private:
	LPD3DXMESH m_pBox;
	BoundingBox* m_pBoundingBox;
	D3DXVECTOR3 aa;
	D3DXVECTOR3 bb;
	D3DXVECTOR3 size;
	D3DXVECTOR3 center;
public:
	Wall(D3DXVECTOR3 _aa, D3DXVECTOR3 _bb, D3DXVECTOR3 _size);
	~Wall();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	BoundingBox* getBoundingBox();
};

