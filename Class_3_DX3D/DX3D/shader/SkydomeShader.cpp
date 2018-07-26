#include "stdafx.h"
#include "SkydomeShader.h"



SkydomeShader::SkydomeShader()
{

}


SkydomeShader::~SkydomeShader()
{

}


void SkydomeShader::Init()
{
	m_pEffect = Shaders::Get()->GetShader(SHADER_PATH + _T("Skydome.fx"));
}

void SkydomeShader::Render()
{
	if (m_pList.size() <= 0) return;

	m_pEffect->SetMatrix(hViewMatrix, &m_info.ViewMatrix);
	m_pEffect->SetMatrix(hProjMatrix, &m_info.ProjMatrix);

	m_pEffect->SetVector(hLightColor, &m_info.LightColor);
	m_pEffect->SetVector(hWorldLightPos, &m_info.WorldLightPos);
	//m_pEffect->SetVector(hWorldCamPos, &m_info.WorldCamPos);

	UINT numPasses = 0;
	m_pEffect->Begin(&numPasses, NULL);
	DX::GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	for (int i = 0; i < numPasses; i++)
	{
		m_pEffect->BeginPass(i);
		
		for (auto p : m_pList)
		{
			p->RenderUseShader_0();
		}

		m_pEffect->EndPass();
	}
	DX::GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pEffect->End();
}

void SkydomeShader::SetWorldMatrix(D3DXMATRIXA16 * pWorldMatrix)
{
	m_pEffect->SetMatrix(hWorldMatrix, pWorldMatrix);
}

void SkydomeShader::SetTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pEffect->SetTexture(hDiffuseMapTex, pTexture);
}

void SkydomeShader::SetMaterial(D3DMATERIAL9* pMtl)
{
	D3DXVECTOR4 diffuse((*(D3DXVECTOR4*)&pMtl->Diffuse));
	D3DXVECTOR4 ambient((*(D3DXVECTOR4*)&pMtl->Ambient));
	D3DXVECTOR4 specular((*(D3DXVECTOR4*)&pMtl->Specular));
	float power = pMtl->Power;

	m_pEffect->SetVector(hMtl_D, &diffuse);
	m_pEffect->SetVector(hMtl_A, &ambient);
	m_pEffect->SetVector(hMtl_S, &specular);
	m_pEffect->SetFloat(hMtl_P, power);
}

void SkydomeShader::Commit()
{
	m_pEffect->CommitChanges();
}
