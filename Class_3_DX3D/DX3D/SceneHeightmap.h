#pragma once
#include "IScene.h"

class HeightMap;
class AseCharacter;
class Picking;

class CreateSmog;

class SkyBox;
class ColorCube;

//�������ڵ�
class UnitBox;
class Blocks;

//class SkinnedMesh;

class SceneHeightmap : public IScene
{
private:
	HeightMap *		m_pHeightMap;
	AseCharacter*	m_pAseCharacter;
	Picking *		m_pPicking;
	//SkinnedMesh *	m_pSkinnedMesh;

	//�������ڵ�
	UnitBox *		m_pUnit;
	Blocks *		m_pBlocks;
	//

	//�����ڵ�
	CreateSmog*		m_CreateSmog;
	SkyBox*			m_SkyBox;
	ColorCube*		m_ColorCube;
	//
	
public:
	SceneHeightmap();
	~SceneHeightmap();

	// IScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

