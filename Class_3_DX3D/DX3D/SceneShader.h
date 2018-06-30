#pragma once
#include "IScene.h"


class SceneShader :
	public IScene
{
private:

	//모델 스피어
	LPD3DXMESH m_pSphere;
	//컬러셰이더
	LPD3DXEFFECT m_pColorShader;

	//LPCWSTR		m_szFileName;

public:
	SceneShader();
	~SceneShader();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

	LPD3DXMESH Load(const char* szFileName);
	LPD3DXEFFECT LoadShader(const char* szFileName);
};

