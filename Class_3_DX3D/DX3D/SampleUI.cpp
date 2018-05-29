#include "stdafx.h"
#include "SampleUI.h"
#include "IUIObject.h"
#include "UIImage.h"
#include "UIText.h"

enum
{
	UITAG_TEXTVIEW,
	UITAG_BUTTON1,
	UITAG_BUTTON2
};


SampleUI::SampleUI()
{
	m_pSprite = NULL;
	m_pRootUI = NULL;
}


SampleUI::~SampleUI()
{
	SAFE_RELEASE(m_pSprite);
	//SAFE_RELEASE(m_pRootUI);
	m_pRootUI->ReleaseAll();
}

void SampleUI::Init()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);

	{
		UIImage* pImage = new UIImage(m_pSprite);
		pImage->SetTexture("resources/ui/panel-info.png.png");
		pImage->SetPosition(&D3DXVECTOR3(200, 0, 0));
		m_pRootUI = pImage;
	}
	{
		UIText* pText = new UIText(g_pFontMgr->GetFont(FONT::NORMAL),
			m_pSprite, UITAG_TEXTVIEW);
		m_pRootUI->AddChild(pText);
		pText->m_text = _T("Push the button");
		//pText->m_drawTextFormat = DT_LEFT | DT_TOP | DT_NOCLIP;
		pText->m_size = D3DXVECTOR2(312, 200);
		pText->SetPosition(&D3DXVECTOR3(100, 100, 0));
	}
	{
		UIButton* pButton = new UIButton(this, m_pSprite, UITAG_BUTTON1);
		m_pRootUI->AddChild(pButton);
		pButton->SetPosition(&D3DXVECTOR3(135, 330, 0));
		pButton->SetTexture(
			"resources/ui/btn-med-up.png.png",
			"resources/ui/btn-med-over.png.png",
			"resources/ui/btn-med-down.png.png");
		pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST), _T("Button1"));
	}
	{
		UIButton* pButton = new UIButton(this, m_pSprite, UITAG_BUTTON2);
		m_pRootUI->AddChild(pButton);
		pButton->SetPosition(&D3DXVECTOR3(135, 400, 0));
		pButton->SetTexture(
			"resources/ui/btn-med-up.png.png",
			"resources/ui/btn-med-over.png.png",
			"resources/ui/btn-med-down.png.png");
		pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST), _T("Button2"));
	}
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.5f, 0.5f, 1);
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 150, 150, 0);
	m_matWorld = matS * matT;
}

void SampleUI::Update()
{
	SAFE_UPDATE(m_pRootUI);
}

void SampleUI::Render()
{
	g_pDevice->SetTexture(0, NULL);
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->SetTransform(&m_matWorld);
	SAFE_RENDER(m_pRootUI);
	m_pSprite->End();
}

void SampleUI::OnClick(UIButton * pSender)
{
	if (pSender->m_uiTag == UITAG_BUTTON1)
	{
		UIText* pText = (UIText*)m_pRootUI->FindChildByUITag(UITAG_TEXTVIEW);
		pText->m_text = _T("Button1 pushed");
	}
	else if (pSender->m_uiTag == UITAG_BUTTON2)
	{
		UIText* pText = (UIText*)m_pRootUI->FindChildByUITag(UITAG_TEXTVIEW);
		pText->m_text = _T("Button2 pushed");
	}
}
