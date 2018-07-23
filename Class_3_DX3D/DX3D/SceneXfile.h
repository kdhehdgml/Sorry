
#pragma once
#include "IScene.h"

class SkinnedMesh;
class SkyBox;
class GUN;
class SHOVEL;

class TEAM_TEX;
class MONSTER;
class Smle;





class SceneXfile : public IScene
{
private:
	SkinnedMesh *	m_pSkinnedMesh;
	SkyBox *		m_SkyBox;

	//무기
	SHOVEL *		m_SHOVEL;
	GUN *			m_GUN;
	Smle *			m_Smle;


	
	//캐릭터
	TEAM_TEX *		m_TEAM_TEX;
	MONSTER*		m_MONSTER;

public:
	SceneXfile();
	~SceneXfile();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

