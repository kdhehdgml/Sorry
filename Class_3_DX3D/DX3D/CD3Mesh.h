#pragma once
class CD3Mesh
{
public:
	CD3Mesh();
	~CD3Mesh();

	UINT triCount;
	UINT vertexSize;
	DWORD FVF;
	LPDIRECT3DVERTEXBUFFER9 pVB;
	D3DXVECTOR3 bbmin, bbmax;

	MTLTEX*					m_MtlTex;

	HRESULT Create(LPDIRECT3DDEVICE9 pD3DDevice, const TObjMesh& objMesh, BOOL flipTriangles, BOOL flipUVs);
	HRESULT InitVB(LPDIRECT3DDEVICE9 pD3DDevice, const TObjMesh& objMesh, BOOL flipTriangles, BOOL flipUVs);

};

