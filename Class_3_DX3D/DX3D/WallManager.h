#pragma once
#include "IUnitObject.h"
class Wall;
class WallManager :
	public IUnitObject
{
private:
	vector<Wall*> walls;
	int wallsNum;
public:
	WallManager();
	~WallManager();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	void addWall(D3DXVECTOR3 _aa, D3DXVECTOR3 _bb, D3DXVECTOR3 _size);
	vector<Wall*> getWalls();
};

