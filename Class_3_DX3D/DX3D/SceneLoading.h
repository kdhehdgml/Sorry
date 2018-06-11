#pragma once
#include "IScene.h"
#include "IDisplayObject.h"
#include "UIBUtton.h"
#include "UIImage.h"

struct LoadingCircle {
	int nCount;
	int nIndex;
	DWORD dwAniTime;
	DWORD dwOldAniTime;
	RECT *pRect;
	D3DXVECTOR3 *pCenter;
};

class SceneLoading :
	public IScene
{
private:
	LPD3DXSPRITE m_pSprite;
	IUIObject * m_pLoadingScreen;
	UIImage* pImage;
	bool m_renderComplete;
	LPD3DXSPRITE m_loadingCircleSprite;
	LPDIRECT3DTEXTURE9 m_loadingCircleTexture;
	LoadingCircle m_loadingCircle;
	int m_loadingCircleIndex;
	RECT m_loadingCircleRect[8] = { {0,0,128,128},{128,0,256,128},{256,0,384,128},{384,0,512,128},{512,0,640,128},{640,0,768,128},{768,0,896,128},{896,0,1024,128} };
	//D3DXVECTOR3 m_loadingCircleCenter[8] = { D3DXVECTOR3(64,64,0) , D3DXVECTOR3(192,64,0),D3DXVECTOR3(320,64,0),D3DXVECTOR3(448,64,0),D3DXVECTOR3(576,64,0),D3DXVECTOR3(704,64,0),D3DXVECTOR3(832,64,0),D3DXVECTOR3(960,64,0) };
public:
	SceneLoading();
	~SceneLoading();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

