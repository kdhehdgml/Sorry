#include "stdafx.h"
#include "Shaders.h"
#include "ShadowMappingShader.h"
#include "LightingShader.h"

Shaders* Shaders::instance = NULL;

Shaders * Shaders::Get()
{
	if (instance == NULL)
		instance = new Shaders();

	return instance;
}

void Shaders::Delete()
{
	SAFE_DELETE(instance);
}

Shaders::Shaders()
{
	
}

Shaders::~Shaders()
{
	SAFE_RELEASE(m_pShadowMappingShader);
	SAFE_RELEASE(m_pLightingShader);
	for (auto p : m_pEffects)
		SAFE_RELEASE(p.second);
}

void Shaders::Init()
{
	m_pShadowMappingShader = new ShadowMappingShader(); m_pShadowMappingShader->Init();
	m_pLightingShader = new LightingShader(); m_pLightingShader->Init();
}

void Shaders::Render()
{
	m_globalData.ViewMatrix = *g_pCamera->GetViewMatrix();
	m_globalData.ProjMatrix = *g_pCamera->GetProjMatrix();
	m_globalData.WorldCamPos = D3DXVECTOR4(g_pCamera->GetPosition(), 1);

	RenderShadowMapping();
	RenderLighting();
}

void Shaders::AddList(IDisplayObject* pObj, IDisplayObject::RenderMode mode)
{
	if (mode == IDisplayObject::RenderMode_Lighting)
	{
		m_pLightingShader->AddList(pObj);
	}
	else if(mode == IDisplayObject::RenderMode_ShadowMapping)
	{
		m_pShadowMappingShader->AddList(pObj);
	}
}

void Shaders::RemoveList(IDisplayObject* pObj, IDisplayObject::RenderMode mode)
{
	if (mode == IDisplayObject::RenderMode_Lighting)
	{
		m_pLightingShader->RemoveList(pObj);
	}
	else if (mode == IDisplayObject::RenderMode_ShadowMapping)
	{
		m_pShadowMappingShader->RemoveList(pObj);
	}
}

LPD3DXEFFECT Shaders::GetShader(LPCTSTR filePath)
{
	if (m_pEffects.find(filePath) == m_pEffects.end())
	{
		m_pEffects[filePath] = LoadShader(filePath);
	}
	return m_pEffects[filePath];
}

void Shaders::RenderShadowMapping()
{
	m_pCurrentShader = m_pShadowMappingShader;
	
	ShadowMappingShader::ShaderInfo info;
	info.ViewMatrix = m_globalData.ViewMatrix;
	info.ProjMatrix = m_globalData.ProjMatrix;
	D3DXVECTOR3 pos;
	if (Objects::Get()->FindObjectByTag(TAG_PLAYER))
	{
		pos = Objects::Get()->FindObjectByTag(TAG_PLAYER)->GetPosition();
	}
	float offset = 300;
	D3DXVECTOR4 lightPos(pos.x - offset, offset, pos.z - offset, 1);
	info.WorldLightPos = lightPos;
	//info.WorldLightPos = D3DXVECTOR4(-offset, offset, -offset, 1);
	info.WorldCamPos = m_globalData.WorldCamPos;
	info.WorldLightDir = D3DXVECTOR3(1, -1, 1);

	m_pShadowMappingShader->SetInfo(&info);
	
	SAFE_RENDER(m_pShadowMappingShader);
}


void Shaders::RenderLighting()
{
	m_pCurrentShader = m_pLightingShader;
	
	LightingShader::ShaderInfo info;
	info.ViewMatrix = m_globalData.ViewMatrix;
	info.ProjMatrix = m_globalData.ProjMatrix;
	float offset = 300;
	info.WorldLightPos = D3DXVECTOR4(-offset, offset, -offset, 1);
	info.WorldCamPos = m_globalData.WorldCamPos;

	m_pLightingShader->SetInfo(&info);

	SAFE_RENDER(m_pLightingShader);
}

LPD3DXEFFECT Shaders::LoadShader(LPCTSTR fullPath)
{
	LPD3DXEFFECT pEffect = NULL;
	LPD3DXBUFFER pError = NULL;
	DWORD flags = D3DXSHADER_DEBUG;
	
	D3DXCreateEffectFromFile(g_pDevice, fullPath,
		NULL, NULL, flags, NULL, &pEffect, &pError);
		
	
	if (!pEffect && pError)
	{
		int size = pError->GetBufferSize();
		LPVOID errorMsg = pError->GetBufferPointer();
		
		if (errorMsg)
		{
			char* str = new char[size];
			sprintf_s(str, size, (const char*)errorMsg, size);
			
			MessageBoxA(NULL, str, "LoadShader", 0);
			//OutputDebugStringA((str));
			delete[] str;
		}
	}
	
	return pEffect;
}
