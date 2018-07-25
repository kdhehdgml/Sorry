#pragma once

class ShadowMappingShader : public IShader
{	
	enum EFFECT_TYPE
	{
		CREATE,
		APPLY
	};
public:
	struct ShaderInfo
	{
		D3DXMATRIXA16 ViewMatrix;
		D3DXMATRIXA16 ProjMatrix;
		D3DXVECTOR4 WorldCamPos;
		D3DXVECTOR4 WorldLightPos;
		D3DXVECTOR3 WorldLightDir;
	};
private:
	LPD3DXEFFECT m_pCreateEffect;
	LPD3DXEFFECT m_pApplyEffect;
	ShaderInfo m_info;
	EFFECT_TYPE m_effectType;

	LPDIRECT3DTEXTURE9 m_pShadowRenderTarget;
	LPDIRECT3DSURFACE9 m_pShadowDepthStencil;

public:

	ShadowMappingShader();
	~ShadowMappingShader();

	void Init();
	void Render();

	void SetInfo(ShaderInfo* info) { m_info = *info; }
	void SetWorldMatrix(D3DXMATRIXA16* pWorldMatrix);
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture);
	void Commit();
};

