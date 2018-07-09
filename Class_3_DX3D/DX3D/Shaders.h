#pragma once
#include "stdafx.h"

class ShadowMappingShader;
class LightingShader;

class Shaders
{
	struct GlobalData
	{
		D3DXVECTOR4 WorldLightPos;
		D3DXVECTOR4 WorldCamPos;
		D3DXMATRIXA16 ViewMatrix;
		D3DXMATRIXA16 ProjMatrix;
	};
public:
	static Shaders*	Get();
	static void		Delete();
private:
	static Shaders*	instance;
	Shaders();
	~Shaders();

	map<CString, LPD3DXEFFECT> m_pEffects;
	IShader* m_pCurrentShader;
	GlobalData m_globalData;

public:
	void Init();
	void Render();

	IShader* GetCurrentShader() { return m_pCurrentShader; }
	void AddList(IDisplayObject* pObj, IDisplayObject::RenderMode mode);
	void RemoveList(IDisplayObject* pObj, IDisplayObject::RenderMode mode);

	LPD3DXEFFECT GetShader(LPCTSTR filePath);
private:
	LPD3DXEFFECT LoadShader(LPCTSTR fullPath);

	/////ShadowMappingShader/////
private:
	ShadowMappingShader* m_pShadowMappingShader;
public:
	void RenderShadowMapping();
	/////ShadowMappingShader/////


	/////LightingShader/////
private:
	LightingShader * m_pLightingShader;
public:
	void RenderLighting();
	/////LightingShader/////
};