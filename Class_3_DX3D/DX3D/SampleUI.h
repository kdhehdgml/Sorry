#pragma once
#include "IDisplayObject.h"
#include "UIBUtton.h"

class IUIObject;

class SampleUI : public IDisplayObject, public IUIButtonDelegate
{
private:
	LPD3DXSPRITE	m_pSprite;
	IUIObject*		m_pRootUI;

public:
	SampleUI();
	~SampleUI();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	// IUIButtonDelegate��(��) ���� ��ӵ�
	virtual void OnClick(UIButton * pSender) override;
};

