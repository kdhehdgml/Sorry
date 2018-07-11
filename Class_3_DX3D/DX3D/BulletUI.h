#pragma once
#include "IDisplayObject.h"
class IUBaseObject;
class UIImage;
class BulletUI :
	public IDisplayObject
{
private:
	LPD3DXSPRITE	m_pSprite;
	IUBaseObject*	m_pRootUI;
	UIImage* m_pBullets[5];

public:
	int bulletNum;
	BulletUI();
	~BulletUI();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

