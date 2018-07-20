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

	bool m_pRenderToggle;
	D3DXVECTOR3 getPos();
	void setPos(D3DXVECTOR3 _pos);
	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};
