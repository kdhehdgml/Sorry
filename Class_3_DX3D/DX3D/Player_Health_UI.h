#pragma once
#include "IDisplayObject.h"
class IUBaseObject;
class UIImage;

class Player_Health_UI : public IDisplayObject
{
private:
	LPD3DXSPRITE	m_pSprite;
	IUBaseObject*	m_pRootUI;
	UIImage*		m_pHealth[3];

public:
	Player_Health_UI();
	~Player_Health_UI();

	int Health;

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

