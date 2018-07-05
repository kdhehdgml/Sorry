
#pragma once
#include "IScene.h"

class SkinnedMesh;
class SkyBox;
class GUN;




class SceneXfile : public IScene
{
private:
	SkinnedMesh * m_pSkinnedMesh;
	GUN *		m_GUN;
	SkyBox *		m_SkyBox;
public:
	SceneXfile();
	~SceneXfile();

	// IScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

