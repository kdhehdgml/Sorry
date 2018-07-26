#pragma once
#include "stdafx.h"

class SkydomeShader : public IShader
{
public:
	struct ShaderInfo
	{
		D3DXMATRIXA16 ViewMatrix;
		D3DXMATRIXA16 ProjMatrix;
		D3DXVECTOR4 WorldCamPos;
		D3DXVECTOR4 WorldLightPos;
		D3DXVECTOR4 LightColor;
	};
private:
	LPD3DXEFFECT m_pEffect;
	ShaderInfo m_info;

public:

	SkydomeShader();
	~SkydomeShader();

	void Init();
	void Render();

	void SetInfo(ShaderInfo* info) { m_info = *info; }
	void SetWorldMatrix(D3DXMATRIXA16* pWorldMatrix);
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetMaterial(D3DMATERIAL9* pMtl);
	void Commit();
};

