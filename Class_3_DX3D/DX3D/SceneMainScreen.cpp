#include "stdafx.h"
#include "SceneMainScreen.h"


SceneMainScreen::SceneMainScreen()
{
	mainScreenUI = NULL;
}


SceneMainScreen::~SceneMainScreen()
{
	SAFE_RELEASE(mainScreenUI);
}

void SceneMainScreen::Init()
{
	mainScreenUI = new MainScreenUI();
	mainScreenUI->Init();
}

void SceneMainScreen::Update()
{
	SAFE_UPDATE(mainScreenUI);
}

void SceneMainScreen::Render()
{
	SAFE_RENDER(mainScreenUI);
}

void SceneMainScreen::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
