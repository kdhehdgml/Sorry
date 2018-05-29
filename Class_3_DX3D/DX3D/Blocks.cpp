#include "stdafx.h"
#include "Blocks.h"

vector<vector<int>> uvBody = {
	{ 0, 0, 0, 1, 1, 1, 1, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 0 }
};

Blocks::Blocks()
{
	
}


Blocks::~Blocks()
{
	SAFE_RELEASE(m_tex);
}


void Blocks::Render()
{
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetTexture(0, m_tex);
	g_pDevice->SetFVF(VERTEX_PT::FVF);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecPTVertex.size() / 3,
		&m_vecPTVertex[0], sizeof(VERTEX_PT));
}

void Blocks::Update()
{
}


void Blocks::InitTT(D3DXMATRIXA16* pMat, vector<vector<int>> &vecUV)
{
	vector<D3DXVECTOR3> vecVertex;
	for (int i = 0; i < CUBE_VERTEX_SIZE; i++)
	{
		vecVertex.push_back(g_aCubeVertex[i]);
	}
	for (int i = 0; i < vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&vecVertex[i],
			&vecVertex[i], pMat);
	}
	D3DXCreateTextureFromFile(g_pDevice, _T("resources/textures/cratse.jpg"), &m_tex);
	SetPTVertexTT(m_vecPTVertex, vecVertex, vecUV);
}

void Blocks::SetPTVertexTT(vector<VERTEX_PT>& vecOut, vector<D3DXVECTOR3>& vecVertex, vector<vector<int>>& uv)
{
	vector<D3DXVECTOR2> vecUV4Vertex;
	MakeUVListTT(vecUV4Vertex, uv);

	for (int i = 0; i < CUBE_INDEX_SIZE; i++)
	{
		vecOut.push_back(VERTEX_PT(vecVertex[g_aCubeIndex[i]], vecUV4Vertex[i]));
	}
}

void Blocks::MakeUVListTT(vector<D3DXVECTOR2>& out,
	vector<vector<int>>& uv)
{
	for (size_t i = 0; i < uv.size(); i++)
	{
		out.push_back(D3DXVECTOR2(uv[i][0], uv[i][1]));
		out.push_back(D3DXVECTOR2(uv[i][2], uv[i][3]));
		out.push_back(D3DXVECTOR2(uv[i][4], uv[i][5]));

		out.push_back(D3DXVECTOR2(uv[i][0], uv[i][1]));
		out.push_back(D3DXVECTOR2(uv[i][4], uv[i][5]));
		out.push_back(D3DXVECTOR2(uv[i][6], uv[i][7]));
	}
}

void Blocks::Init()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMATRIXA16			matS, matT, mat;
	D3DXMatrixScaling(&matS, 5.5f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&matT, 5.5f, 5.0f, 17.5f);
	mat = matS * matT;
	InitTT(&mat, uvBody);

	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&matT, 5.5f, 5.0f, 9.0f);
	mat = matS * matT;
	InitTT(&mat, uvBody);

	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&matT, 3.5f, 5.0f, 9.0f);
	mat = matS * matT;
	InitTT(&mat, uvBody);

	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 2.0f);
	D3DXMatrixTranslation(&matT, 7.0f, 5.0f, 4.0f);
	mat = matS * matT;
	InitTT(&mat, uvBody);
}
