#pragma once
#include "stdafx.h"

class IShader : public BaseObject
{
protected:

	list<LPDisplayObject> m_pList;
public:
	virtual ~IShader() {};
	void AddList(LPDisplayObject pObj) { m_pList.push_back(pObj); }
	void RemoveList(LPDisplayObject pObj) { m_pList.remove(pObj); }
	virtual void SetWorldMatrix(D3DXMATRIXA16* pWorldMatrix) {}
	virtual void SetTexture(LPDIRECT3DTEXTURE9 pTexture) {}
	virtual void SetMaterial(D3DMATERIAL9* pMtl) {}
	virtual void Commit() {}

protected:
	const D3DXHANDLE hWorldMatrix = "gWorldMatrix";
	const D3DXHANDLE hViewMatrix = "gViewMatrix";
	const D3DXHANDLE hProjMatrix = "gProjMatrix";
	const D3DXHANDLE hVPMatrix = "gVPMatrix";
	const D3DXHANDLE hWVPMatrix = "gWVPMatrix";
	const D3DXHANDLE hWorldLightPos = "gWorldLightPos";
	const D3DXHANDLE hWorldCamPos = "gWorldCameraPos";
	const D3DXHANDLE hDiffuseMapTex = "DiffuseMap_Tex";
	const D3DXHANDLE hSpecularMapTex = "SpecularMap_Tex";
	const D3DXHANDLE hNormalMapTex = "NormalMap_Tex";
	const D3DXHANDLE hMtl_D = "gMtl_D";
	const D3DXHANDLE hMtl_A = "gMtl_A";
	const D3DXHANDLE hMtl_S = "gMtl_S";
	const D3DXHANDLE hMtl_P = "gMtl_P";

};