#include "stdafx.h"
#include "UIImage.h"


UIImage::UIImage(LPD3DXSPRITE pSprite, int uiTag)
	:IUBaseObject(pSprite, uiTag)
	,m_pTex(NULL)
{
	m_rotAngle = 0;
	D3DXVECTOR2 center(m_size.x / 2, m_size.y / 2);
	D3DXMatrixTransformation2D(&m_rotMatrix, NULL, NULL, NULL, &center, m_rotAngle, NULL);
}

UIImage::UIImage(LPD3DXSPRITE pSprite, float _rotAngle, int uiTag)
	:IUBaseObject(pSprite, uiTag)
	, m_pTex(NULL)
{
	m_rotAngle = _rotAngle;
	D3DXVECTOR2 center(m_size.x / 2, m_size.y / 2);
	D3DXMatrixTransformation2D(&m_rotMatrix, NULL, NULL, NULL, &center, m_rotAngle, NULL);
}


UIImage::~UIImage()
{
}

void UIImage::Render()
{
	if (m_pTex)
	{
		RECT rect;
		SetRect(&rect, 0, 0, m_size.x, m_size.y);
		m_matWorld = m_matWorld * m_rotMatrix;
		//m_pSprite->SetTransform(&m_matWorld);
		m_pSprite->Draw(m_pTex, &rect, &m_pivot, &m_combinedPos, m_color);
	}

	IUBaseObject::Render();
}

void UIImage::SetTexture(string fullPath)
{
	D3DXIMAGE_INFO info;
	m_pTex = g_pTextureManager->GetTexture(fullPath);
	D3DXGetImageInfoFromFileA(fullPath.c_str(), &info);
	m_size.x = info.Width;
	m_size.y = info.Height;
}
