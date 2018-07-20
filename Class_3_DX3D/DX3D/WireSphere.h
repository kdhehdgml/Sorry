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

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

