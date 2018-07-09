#pragma once
#include "IDisplayObject.h"

class IUBaseObject : public IDisplayObject
{
protected:
	LPD3DXSPRITE m_pSprite;

public:
	int			m_uiTag;
	D3DXVECTOR3 m_combinedPos;
	D3DXVECTOR3 m_pivot;
	D3DXVECTOR2 m_size;
	D3DCOLOR	m_color;

	bool		m_bDrawBorder;

	IUBaseObject(LPD3DXSPRITE pSprite, int uiTag = -1);
	virtual ~IUBaseObject();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void DrawBorder();
	void UpdateCombinedPosition();
	IUBaseObject* FindChildByUITag(int uiTag);
	void GetFinalRect(RECT* rect);
	const D3DXVECTOR3& GetCombinedPosition() { return m_combinedPos; }
};

