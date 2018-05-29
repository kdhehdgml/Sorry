#pragma once
#include "IScene.h"

class Grid;
class SkyBox;


class SceneTest : public IScene
{
public:
	Grid * m_pGrid;
	SkyBox * m_SkyBox;

	SceneTest();
	~SceneTest();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

