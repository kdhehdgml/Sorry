#pragma once
#include "IDisplayObject.h"
class IUBaseObject;
class BulletUI :
	public IDisplayObject
{
private:
	LPD3DXSPRITE	m_pSprite;
	IUBaseObject*		m_pRootUI;

public:
	int bulletNum;
	BulletUI();
	~BulletUI();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

