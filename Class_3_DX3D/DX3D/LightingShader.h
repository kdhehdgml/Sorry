#pragma once

class LightingShader : public IShader
{	
public:
	struct ShaderInfo
	{
		D3DXMATRIXA16 ViewMatrix;
		D3DXMATRIXA16 ProjMatrix;
		D3DXVECTOR4 WorldCamPos;
		D3DXVECTOR4 WorldLightPos;
	};
private:
	LPD3DXEFFECT m_pEffect;
	ShaderInfo m_info;

public:
	
	LightingShader();
	~LightingShader();

	void Init();
	void Render();

	void SetInfo(ShaderInfo* info) { m_info = *info; }
	void SetWorldMatrix(D3DXMATRIXA16* pWorldMatrix);
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetMaterial(D3DMATERIAL9* pMtl);
	void Commit();
};

