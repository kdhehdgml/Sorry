#pragma once
#include "IScene.h"
#include "IDisplayObject.h"
#include "UIBUtton.h"
#include "UIImage.h"
#include "Minimap.h"

class HeightMap;
class AseCharacter;
class Picking;

class CreateSmog;

class SkyBox;
class ColorCube;
class Player_hands;


//�������ڵ�
class UnitBox;
class Blocks;

//class SkinnedMesh;
class ObjRen;	//obj Ŭ����


class SceneHeightmap : public IScene
{
private:
	HeightMap *		m_pHeightMap;
	AseCharacter*	m_pAseCharacter;
	Player_hands*	m_Player_hands;
	//Picking *		m_pPicking;
	//SkinnedMesh *	m_pSkinnedMesh;

	bool			musicPlayCheck;
	bool			musicPlay;
	float			volume_music;

	//�������ڵ�
	UnitBox *		m_pUnit;
	Blocks *		m_pBlocks;
	//

	//obj ����
	ObjRen*			m_Tree;			//��¥ �̹���
	ObjRen*			m_Stone;
	ObjRen*			m_MD;
	ObjRen*			m_wall01;		//���� �̹���
	ObjRen*			m_wall02;
	ObjRen*			m_wall03;
	ObjRen*			m_wall04;
	ObjRen*			m_wall05;
	ObjRen*			m_wall06;

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

	Minimap * m_minimap;

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

