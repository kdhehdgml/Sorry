#pragma once
#include "IDisplayObject.h"
class WireSphere :
	public IDisplayObject
{
private:
	LPD3DXMESH		m_pSphere;
public:
	WireSphere();
	~WireSphere();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

