#include "stdafx.h"
#include "MoveOBJ.h"

#include "ObjLoader.h"
#include "CD3Mesh.h"

MoveOBJ::MoveOBJ()
{
	g_pLoader = NULL;
	g_pD3DMesh = NULL;

	g_fFOV = 45.5f;
	g_fAspect = 1.333f;
}


MoveOBJ::~MoveOBJ()
{
	SAFE_DELETE(g_pD3DMesh);

}

void MoveOBJ::Init(float size, LPCTSTR objFile, LPCTSTR pngFile, float x, float y, float z, float rotationX, float rotationY, float rotationZ)
{
	g_fScale = size;
	g_pLoader->LoadObj(objFile, &objMesh);

	g_pD3DMesh = new CD3Mesh;
	g_pD3DMesh->Create(g_pDevice, objMesh, NULL, NULL);

	bbSize = g_pD3DMesh->bbmax - g_pD3DMesh->bbmin;
	bbCenter = g_pD3DMesh->bbmax - bbSize / 2;
	sizeFactor = MAX(bbSize.z, MAX(bbSize.x, bbSize.y));
	if (sizeFactor > 0)
		sizeFactor = 5 / sizeFactor;
	else
		sizeFactor = 1;

	sizeFactor *= g_fScale;


	m_angle = rotationY;
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixScaling(&mS, sizeFactor, sizeFactor, sizeFactor);

	D3DXMatrixTranslation(&mT, -bbCenter.x + x, -bbCenter.y + y, -bbCenter.z + z);

	m_pos.x = -bbCenter.x + x;
	m_pos.y = -bbCenter.y + y;
	m_pos.z = -bbCenter.z + z;

	D3DXMatrixRotationX(&mRX, rotationX);
	D3DXMatrixRotationY(&mRY, rotationY);
	D3DXMatrixRotationZ(&mRZ, rotationZ);


	g_pD3DMesh->m_MtlTex = new MTLTEX;

	g_pD3DMesh->m_MtlTex->id = 0;

	g_pD3DMesh->m_MtlTex->material.Ambient.a = 1.0f;
	g_pD3DMesh->m_MtlTex->material.Ambient.b = objMate.Ka[0];
	g_pD3DMesh->m_MtlTex->material.Ambient.g = objMate.Ka[1];
	g_pD3DMesh->m_MtlTex->material.Ambient.r = objMate.Ka[2];

	g_pD3DMesh->m_MtlTex->material.Diffuse.a = 1.0f;
	g_pD3DMesh->m_MtlTex->material.Diffuse.b = objMate.Kd[0];
	g_pD3DMesh->m_MtlTex->material.Diffuse.g = objMate.Kd[1];
	g_pD3DMesh->m_MtlTex->material.Diffuse.r = objMate.Kd[2];

	g_pD3DMesh->m_MtlTex->material.Specular.a = 1.0f;
	g_pD3DMesh->m_MtlTex->material.Specular.b = objMate.Ks[0];
	g_pD3DMesh->m_MtlTex->material.Specular.g = objMate.Ks[1];
	g_pD3DMesh->m_MtlTex->material.Specular.r = objMate.Ks[2];

	g_pD3DMesh->m_MtlTex->material.Specular.a = 1.0f;
	g_pD3DMesh->m_MtlTex->material.Specular.b = objMate.Ks[0];
	g_pD3DMesh->m_MtlTex->material.Specular.g = objMate.Ks[1];
	g_pD3DMesh->m_MtlTex->material.Specular.r = objMate.Ks[2];

	g_pD3DMesh->m_MtlTex->SetTexture(g_pTextureManager->GetTexture(pngFile));
}

void MoveOBJ::Update()
{
	D3DXMatrixTranslation(&mT, m_pos.x, m_pos.y, m_pos.z);
	//D3DXMatrixRotationY(&mRY, m_angle);


	if (obj_Index == 1)
	{
		D3DXMATRIXA16 RX;
		D3DXMATRIXA16 RY;
		D3DXMATRIXA16 RZ;
		D3DXMatrixIdentity(&RX);
		D3DXMatrixIdentity(&RY);
		D3DXMatrixIdentity(&RZ);
		D3DXMatrixRotationX(&RX, D3DX_PI/2);
		D3DXMatrixRotationY(&RY, 0);
		D3DXMatrixRotationZ(&RZ, D3DX_PI / 2);
		mR = RX * RY * RZ*head_rot ;
	}
	else
	{
		mR = mRX * mRY * mRZ;
	}
	m_matWorld = mS * mR *  mT;

}

void MoveOBJ::Render()
{
	g_pDevice->SetTexture(0, g_pD3DMesh->m_MtlTex->pTexture);
	g_pDevice->SetMaterial(&g_pD3DMesh->m_MtlTex->material);
	//g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_FORCE_DWORD);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetStreamSource(0, g_pD3DMesh->pVB, 0, g_pD3DMesh->vertexSize);
	g_pDevice->SetFVF(g_pD3DMesh->FVF);

	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, g_pD3DMesh->triCount);
}
