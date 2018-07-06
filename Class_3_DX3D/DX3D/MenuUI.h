#pragma once
#include "IDisplayObject.h"
#include "UIBUtton.h"
class MenuUI : public IDisplayObject, public IUIButtonDelegate
{
private:
	LPD3DXSPRITE	m_pSprite;
	IUIObject*		m_pRootUI;
public:
	MenuUI();
	~MenuUI();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	// IUIButtonDelegate을(를) 통해 상속됨
	virtual void OnClick(UIButton * pSender) override;
};

