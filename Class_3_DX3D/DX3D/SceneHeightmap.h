#pragma once
#include "IScene.h"

class HeightMap;
class AseCharacter;
class Picking;

class CreateSmog;

class SkyBox;

//�������ڵ�
class Cubeman;
class Mob;
class Blocks;

class SceneHeightmap : public IScene
{
private:
	HeightMap *		m_pHeightMap;
	AseCharacter*	m_pAseCharacter;
	Picking *		m_pPicking;
	//SkinnedMesh *	m_pSkinnedMesh;

	//�������ڵ�
	Cubeman *		m_pCubeman;
	vector<Mob*>	m_pMob;
	Blocks *		m_pBlocks;
	//

	//�����ڵ�
	CreateSmog*		m_CreateSmog;
	SkyBox*			m_SkyBox;
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

