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
class Minimap;

//�ø�
//class Frustum;

//�������ڵ�
class UnitBox;
class Blocks;

//class SkinnedMesh;

class ObjRender;	//obj Ŭ����

class SceneHeightmap : public IScene
{
private:
	HeightMap * m_pHeightMap;
	AseCharacter*	m_pAseCharacter;
	Player_hands*	m_Player_hands;
	//Picking *		m_pPicking;
	//SkinnedMesh *	m_pSkinnedMesh;
	

	//����ȭ�� ���� �ø�
	//Frustum			*m_Frustum;

	bool			musicPlayCheck;
	bool			musicPlay;
	float			volume_music;

	//�������ڵ�
	UnitBox *		m_pUnit;
	Blocks *		m_pBlocks;
	//

	//obj ����
	ObjRender*			m_ObjRender;

	//�����ڵ�
	CreateSmog*		m_CreateSmog;
	SkyBox*			m_SkyBox;
	ColorCube*		m_ColorCube;
	//
	LPD3DXSPRITE m_pCrosshairSprite;
	LPD3DXSPRITE m_pScopeSprite;
	IUIObject* m_pCrosshair;
	IUIObject* m_pScope;
	UIImage* m_pCrosshairImage;
	UIImage* m_pScopeImage;
	bool m_pCrosshairOn;
	bool m_pScopeOn;

	LPD3DXSPRITE m_pTalkSprite;
	IUIObject* m_pTalk;
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

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());

public:
	SceneHeightmap();
	~SceneHeightmap();

	// IScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

