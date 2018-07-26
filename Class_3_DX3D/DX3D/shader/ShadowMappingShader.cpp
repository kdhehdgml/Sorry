#include "stdafx.h"
#include "ShadowMappingShader.h"


static D3DXHANDLE hLightViewMatrix = "gLightViewMatrix";
static D3DXHANDLE hLightProjMatrix = "gLightProjMatrix";
static D3DXHANDLE hShadowMapTex = "ShadowMap_Tex";


ShadowMappingShader::ShadowMappingShader()
{
	
}


ShadowMappingShader::~ShadowMappingShader()
{
	SAFE_RELEASE(m_pShadowRenderTarget);
	SAFE_RELEASE(m_pShadowDepthStencil);
}


void ShadowMappingShader::Init()
{
	m_pCreateEffect = Shaders::Get()->GetShader(SHADER_PATH + _T("CreateShadow.fx"));
	m_pApplyEffect = Shaders::Get()->GetShader(SHADER_PATH + _T("ApplyShadow.fx"));
	
	const int SHADOWMAP_SIZE = 4096;
	D3DXCreateTexture(DX::GetDevice(), SHADOWMAP_SIZE, SHADOWMAP_SIZE, 1,
		D3DUSAGE_RENDERTARGET, D3DFMT_R32F, D3DPOOL_DEFAULT, &m_pShadowRenderTarget);

	DX::GetDevice()->CreateDepthStencilSurface(SHADOWMAP_SIZE, SHADOWMAP_SIZE, 
		D3DFMT_D24X8, D3DMULTISAMPLE_NONE, 0, true, &m_pShadowDepthStencil, NULL);
}


void ShadowMappingShader::Render()
{
	if (m_pList.size() <= 0) return;
	
	D3DXMATRIXA16 matLightView;
	D3DXMATRIXA16 matLightProj;
	D3DXMATRIXA16 matLightVP;
	
	D3DXVECTOR3 eye(m_info.WorldLightPos.x, m_info.WorldLightPos.y, m_info.WorldLightPos.z);
	D3DXVECTOR3 at(eye + m_info.WorldLightDir);
	D3DXVECTOR3 up(0, 1, 0);
	
	D3DXMatrixLookAtLH(&matLightView, &eye, &at, &up);
	D3DXMatrixPerspectiveFovLH(&matLightProj, D3DX_PI / 2.0f, 1, 1, 1000);
	matLightVP = matLightView * matLightProj;

	LPDIRECT3DSURFACE9 pHWRenderTarget = NULL;
	LPDIRECT3DSURFACE9 pHWDepthStencil = NULL;
	DX::GetDevice()->GetRenderTarget(0, &pHWRenderTarget);
	DX::GetDevice()->GetDepthStencilSurface(&pHWDepthStencil);

	LPDIRECT3DSURFACE9 pShadowSurface = NULL;
	if (SUCCEEDED(m_pShadowRenderTarget->GetSurfaceLevel(0, &pShadowSurface)))
	{
		DX::GetDevice()->SetRenderTarget(0, pShadowSurface);
		pShadowSurface->Release();
	}
	
	DX::GetDevice()->SetDepthStencilSurface(m_pShadowDepthStencil);
	DX::GetDevice()->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xFFFFFFFF, 1, 0);

	m_pCreateEffect->SetVector(hWorldLightPos, &m_info.WorldLightPos);
	m_pCreateEffect->SetMatrix(hLightViewMatrix, &matLightView);
	m_pCreateEffect->SetMatrix(hLightProjMatrix, &matLightProj);
	
	m_effectType = EFFECT_TYPE::CREATE;
	UINT numPasses = 0;
	m_pCreateEffect->Begin(&numPasses, NULL);
	
	for (int i = 0; i < numPasses; i++)
	{
		m_pCreateEffect->BeginPass(i);
		
		for (auto p : m_pList)
		{
			p->RenderUseShader_0();
		}

		m_pCreateEffect->EndPass();
	}

	m_pCreateEffect->End();
	
	DX::GetDevice()->SetRenderTarget(0, pHWRenderTarget);
	DX::GetDevice()->SetDepthStencilSurface(pHWDepthStencil);

	pHWRenderTarget->Release();
	pHWDepthStencil->Release();


	m_pApplyEffect->SetMatrix(hViewMatrix, &m_info.ViewMatrix);
	m_pApplyEffect->SetMatrix(hProjMatrix, &m_info.ProjMatrix);
	m_pApplyEffect->SetMatrix(hLightViewMatrix, &matLightView);
	m_pApplyEffect->SetMatrix(hLightProjMatrix, &matLightProj);
	m_pApplyEffect->SetVector(hWorldLightPos, &m_info.WorldLightPos);
	m_pApplyEffect->SetTexture(hShadowMapTex, m_pShadowRenderTarget);
	m_pApplyEffect->SetVector(hWorldCamPos, &m_info.WorldCamPos);
	
	m_effectType = EFFECT_TYPE::APPLY;
	numPasses = 0;
	m_pApplyEffect->Begin(&numPasses, NULL);
	
	for (int i = 0; i < numPasses; i++)
	{
		m_pApplyEffect->BeginPass(i);

		for (auto p : m_pList)
		{
			p->RenderUseShader_1();
		}

		m_pApplyEffect->EndPass();
	}

	m_pApplyEffect->End();
}

void ShadowMappingShader::SetWorldMatrix(D3DXMATRIXA16 * pWorldMatrix)
{
	if (m_effectType == EFFECT_TYPE::CREATE)
	{
		m_pCreateEffect->SetMatrix(hWorldMatrix, pWorldMatrix);
	}
	else if (m_effectType == EFFECT_TYPE::APPLY)
	{
		m_pApplyEffect->SetMatrix(hWorldMatrix, pWorldMatrix);
	}
}

void ShadowMappingShader::SetTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pApplyEffect->SetTexture(hDiffuseMapTex, pTexture);
}

void ShadowMappingShader::Commit()
{
	if (m_effectType == EFFECT_TYPE::CREATE)
	{
		m_pCreateEffect->CommitChanges();
	}
	else if (m_effectType == EFFECT_TYPE::APPLY)
	{
		m_pApplyEffect->CommitChanges();
	}
}
