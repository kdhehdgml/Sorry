#pragma once
#include "IUIObject.h"

class UIImage : public IUBaseObject
{
public:
	LPDIRECT3DTEXTURE9 m_pTex;
	D3DXMATRIXA16 m_rotMatrix;
	float m_rotAngle;
	bool m_rotMode;

	UIImage(LPD3DXSPRITE pSprite, int uiTag = -1);
	UIImage(LPD3DXSPRITE pSprite, float _rotAngle, int uiTag = -1);
	virtual ~UIImage();

	virtual void Render() override;

	void SetTexture(string fullPath);
};

