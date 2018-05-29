#pragma once

#ifndef _SKYBOX_H_
#define _SKYBOX_H_


struct SKYVERTEX
{
	float x, y, z, u, v;
};

#define D3DFVF_SKYVERTEX (D3DFVF_XYZ | D3DFVF_TEX1 )
#define MAX_SKY_TEX 6

class SkyBox : public IDisplayObject
{

private:
	LPDIRECT3DDEVICE9			m_pd3dDevice;					/// 출력용 D3D디바이스
	LPDIRECT3DTEXTURE9			m_pTex[6];					/// 텍스처
	LPDIRECT3DVERTEXBUFFER9		m_pVB;							/// 지형출력용 정점버퍼

public:
	SkyBox();
	~SkyBox();
	HRESULT Create(LPDIRECT3DDEVICE9 pDev, string lpTexFilename[MAX_SKY_TEX]);

private:
	HRESULT		_Destroy();
	HRESULT		_LoadTextures(string lpTexFilename[MAX_SKY_TEX]);
	HRESULT		_CreateVertex();


public:


	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

#endif