#pragma once
#include "IScene.h"

class HeightMap;
class AseCharacter;
class Picking;

class CreateSmog;

class SkyBox;
class ColorCube;

//중현이코드
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

	//중현이코드
	UnitBox *		m_pUnit;
	Blocks *		m_pBlocks;
	//

	//영락코드
	CreateSmog*		m_CreateSmog;
	SkyBox*			m_SkyBox;
	ColorCube*		m_ColorCube;
	//
	
public:
	SceneHeightmap();
	~SceneHeightmap();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

