
#pragma once
#include "IScene.h"

class SkinnedMesh;
class SkyBox;
class GUN;
class SHOVEL;






class SceneXfile : public IScene
{
private:
	SkinnedMesh * m_pSkinnedMesh;
	GUN *		m_GUN;
	SkyBox *		m_SkyBox;
	SHOVEL *		m_SHOVEL;
public:
	SceneXfile();
	~SceneXfile();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

