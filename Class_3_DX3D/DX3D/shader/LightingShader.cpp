#include "stdafx.h"
#include "LightingShader.h"



LightingShader::LightingShader()
{
	
}


LightingShader::~LightingShader()
{
	
}


void LightingShader::Init()
{
	m_pEffect = Shaders::Get()->GetShader(SHADER_PATH + _T("Lighting.fx"));
}

void LightingShader::Render()
{
	if (m_pList.size() <= 0) return;
	
	m_pEffect->SetMatrix(hViewMatrix, &m_info.ViewMatrix);
	m_pEffect->SetMatrix(hProjMatrix, &m_info.ProjMatrix);
	
	m_pEffect->SetVector(hLightColor, &m_info.LightColor);
	m_pEffect->SetVector(hWorldCamPos, &m_info.WorldCamPos);
	m_pEffect->SetFloatArray(hWorldLightDir, (float*)&m_info.WorldLightDir, 3);

	UINT numPasses = 0;
	m_pEffect->Begin(&numPasses, NULL);
	
	for (int i = 0; i < numPasses; i++)
	{
		m_pEffect->BeginPass(i);

		for (auto p : m_pList)
		{
			p->RenderUseShader_0();
		}

		m_pEffect->EndPass();
	}

	m_pEffect->End();
}

void LightingShader::SetWorldMatrix(D3DXMATRIXA16 * pWorldMatrix)
{
	m_pEffect->SetMatrix(hWorldMatrix, pWorldMatrix);
}

void LightingShader::SetTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pEffect->SetTexture(hDiffuseMapTex, pTexture);
}

void LightingShader::SetMaterial(D3DMATERIAL9* pMtl)
{
	D3DXVECTOR4 diffuse( (*(D3DXVECTOR4*)&pMtl->Diffuse));
	D3DXVECTOR4 ambient( (*(D3DXVECTOR4*)&pMtl->Ambient));
	D3DXVECTOR4 specular( (*(D3DXVECTOR4*)&pMtl->Specular));
	float power = pMtl->Power;

	m_pEffect->SetVector(hMtl_D, &diffuse);
	m_pEffect->SetVector(hMtl_A, &ambient);
	m_pEffect->SetVector(hMtl_S, &specular);
	m_pEffect->SetFloat(hMtl_P,power);
}

void LightingShader::Commit()
{
	m_pEffect->CommitChanges();
}
