#pragma once
#include "IScene.h"


class SceneShader :
	public IScene
{
private:

	//�� ���Ǿ�
	LPD3DXMESH m_pSphere;
	//�÷����̴�
	LPD3DXEFFECT m_pColorShader;

	//LPCWSTR		m_szFileName;

public:
	SceneShader();
	~SceneShader();

	// IScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

	LPD3DXMESH Load(const char* szFileName);
	LPD3DXEFFECT LoadShader(const char* szFileName);
};

