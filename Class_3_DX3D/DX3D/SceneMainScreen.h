#pragma once
#include "IScene.h"
#include "IDisplayObject.h"
#include "UIBUtton.h"
#include "UIImage.h"
#include "MainScreenUI.h"
class SceneMainScreen :
	public IScene
{
public:
	SceneMainScreen();
	~SceneMainScreen();

	MainScreenUI* mainScreenUI;

	// IScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

