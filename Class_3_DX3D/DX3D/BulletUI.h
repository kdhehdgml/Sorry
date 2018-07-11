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

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

