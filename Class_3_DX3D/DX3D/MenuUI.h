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

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	// IUIButtonDelegate��(��) ���� ��ӵ�
	virtual void OnClick(UIButton * pSender) override;
};

