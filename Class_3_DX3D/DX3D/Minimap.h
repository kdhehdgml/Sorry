#pragma once
#include "IDisplayObject.h"
#include "UIImage.h"

class Minimap :
	public IDisplayObject
{
private:
	LPD3DXSPRITE m_minimapSprite;
	UIImage * m_minimap;
	UIImage * m_playerIcon;
	vector<UIImage*> m_teamIcon;
	vector<UIImage*> m_enemyIcon;
	IUIObject* m_pRootUI;

	float minimapWidth;
	float minimapHeight;

public:
	Minimap();
	~Minimap();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

