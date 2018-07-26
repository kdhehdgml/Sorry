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

class WallManager;
class Wall;
class SphereWall;
class Minimap;
class MenuUI;
class BulletUI;
class Player_Health_UI;
class WireSphere;

//컬링
//class Frustum;

//중현이코드
class UnitBox;
class Blocks;

//class SkinnedMesh;

class ObjRender;	//obj 클래스

class MARK;

class SceneHeightmap : public IScene
{
private:

	
	HeightMap * m_pHeightMap;
	AseCharacter*	m_pAseCharacter;
	Player_hands*	m_Player_hands;
	//Picking *		m_pPicking;
	//SkinnedMesh *	m_pSkinnedMesh;


	//최적화를 위한 컬링
	//Frustum			*m_Frustum;

	bool			musicPlayCheck;
	bool			musicPlay;
	float			volume_music;

	//중현이코드
	UnitBox *		m_pUnit;
	Blocks *		m_pBlocks;
	bool initCreateMob;
	//

	//obj 관련
	ObjRender*			m_ObjRender;

	MARK*				m_MARK;

	//영락코드
	CreateSmog*		m_CreateSmog;
	SkyBox*			m_SkyBox;
	ColorCube*		m_ColorCube;
	//
	LPD3DXSPRITE m_pCrosshairSprite;
	LPD3DXSPRITE m_pScopeSprite;
	IUBaseObject* m_pCrosshair;
	IUBaseObject* m_pScope;
	UIImage* m_pCrosshairImage;
	UIImage* m_pScopeImage;
	bool m_pCrosshairOn;
	bool m_pScopeOn;
	LPD3DXSPRITE m_pGameOverSprite;
	IUBaseObject* m_pGameOver;
	UIImage* m_pGameOverImage;
	bool m_pGameOverOn;

	LPD3DXSPRITE m_pTalkSprite;
	IUBaseObject* m_pTalk;
	UIImage* m_pTalkImage;
	bool m_pTalkOn;
	LPARAM m_pLParam;
	D3DXMATRIXA16 m_pTalkMatrix;

	Minimap * m_minimap;

	LPD3DXMESH		m_pSphere;
	BoundingSphere* m_pBoundingSphere;

	WallManager * wallManager;

	Ray r;

	D3DXVECTOR3 m_pOldPos;

	LPD3DXFONT	m_pFont;
	CString		m_str;
	int m_talkFontCount;

	MenuUI* m_pMenuUI;
	BulletUI* m_pBulletUI;
	Player_Health_UI* m_pPlayer_Heatl_UI;
	WireSphere* m_pWireSphere;

	int Player_Health;
	int Health_Recovery_Interval = 0;

	D3DXVECTOR3 m_pBombingPos;

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());

public:
	SceneHeightmap();
	~SceneHeightmap();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	void Event();
	void ResetScene();
};

