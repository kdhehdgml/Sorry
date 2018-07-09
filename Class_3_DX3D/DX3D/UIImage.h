#pragma once
#include "IUIObject.h"

class UIImage : public IUBaseObject
{
public:
	LPDIRECT3DTEXTURE9 m_pTex;

	UIImage(LPD3DXSPRITE pSprite, int uiTag = -1);
	virtual ~UIImage();

	virtual void Render() override;

	void SetTexture(string fullPath);
};

