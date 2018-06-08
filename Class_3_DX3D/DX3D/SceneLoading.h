#pragma once
#include "IScene.h"
#include "IDisplayObject.h"
#include "UIBUtton.h"
#include "UIImage.h"

class SceneLoading :
	public IScene
{
private:
	LPD3DXSPRITE m_pSprite;
	IUIObject * m_pLoadingScreen;
	UIImage* pImage;
	bool m_renderComplete;
public:
	SceneLoading();
	~SceneLoading();

	// IScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

