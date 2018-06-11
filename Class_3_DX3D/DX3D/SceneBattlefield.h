#pragma once
#include "IScene.h"
#include "IDisplayObject.h"
#include "UIBUtton.h"
#include "UIImage.h"

class HeightMap;
class AseCharacter;
class Picking;

class CreateSmog;

class SkyBox;
class ColorCube;
class Player_hands;

//중현이코드
class UnitBox;
class Blocks;

//class SkinnedMesh;



class SceneBattlefield : public IScene
{
private:
	HeightMap * m_pHeightMap;
	AseCharacter*	m_pAseCharacter;
	Player_hands*	m_Player_hands;
	//Picking *		m_pPicking;
	//SkinnedMesh *	m_pSkinnedMesh;

	string			soundSt;
	bool			musicPlayCheck;
	bool			musicPlay;

	//중현이코드
	UnitBox *		m_pUnit;
	Blocks *		m_pBlocks;
	//

	//영락코드
	CreateSmog*		m_CreateSmog;
	SkyBox*			m_SkyBox;
	ColorCube*		m_ColorCube;
	//
	LPD3DXSPRITE m_pSprite;
	LPD3DXSPRITE m_pSprite2;
	IUIObject* m_pCrosshair;
	IUIObject* m_pScope;
	UIImage* pImage;
	UIImage* pImage2;
	bool m_pCrosshairOn;
	bool m_pScopeOn;

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());

public:
	SceneBattlefield();
	~SceneBattlefield();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

