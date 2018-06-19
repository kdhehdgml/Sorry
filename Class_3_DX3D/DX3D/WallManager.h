#pragma once
#include "IUnitObject.h"
class Wall;
class WallManager :
	public IUnitObject
{
private:
	vector<Wall*> walls;
	int m_pWallsNum;
public:
	WallManager();
	~WallManager();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

