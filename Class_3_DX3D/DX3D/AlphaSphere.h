#pragma once
#include "BaseObject.h"
class AlphaSphere :
	public IDisplayObject
{
private:
	LPD3DXMESH m_pSphere;
public:
	AlphaSphere();
	~AlphaSphere();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

