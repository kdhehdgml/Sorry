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

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

