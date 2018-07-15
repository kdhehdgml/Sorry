
#pragma once
#include "IScene.h"

class SkinnedMesh;
class SkyBox;
class GUN;
class SHOVEL;
class DE_HEADGEAR;
class FR_HEADGEAR;
class TEAM_TEX;
class MONSTER;
class Smle;





class SceneXfile : public IScene
{
private:
	SkinnedMesh *	m_pSkinnedMesh;
	SkyBox *		m_SkyBox;

	//����
	SHOVEL *		m_SHOVEL;
	GUN *			m_GUN;
	Smle *			m_Smle;

	//���
	DE_HEADGEAR *	m_DE_HEADGEAR;
	FR_HEADGEAR *	m_FR_HEADGEAR;
	
	//ĳ����
	TEAM_TEX *		m_TEAM_TEX;
	MONSTER*		m_MONSTER;

public:
	SceneXfile();
	~SceneXfile();

	// IScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

