#include "stdafx.h"
#include "CD3Mesh.h"


CD3Mesh::CD3Mesh()
{
	vertexSize = 0;
	FVF = 0;
	pVB = NULL;
	m_MtlTex = NULL;
}


CD3Mesh::~CD3Mesh()
{
	SAFE_RELEASE(m_MtlTex);
	SAFE_RELEASE(pVB);
}

typedef std::vector< ObjTriangle > ObjTriangleList;

VOID AddObjFace(ObjTriangleList& objTriangleList, const TObjMesh& objMesh, UINT objFaceIndex, BOOL bFlipTriangles, BOOL bFlipUVs)
{
	const TObjMesh::TFace& objFace = objMesh.faces[objFaceIndex];
	UINT triCount = objFace.vCount - 2;

	for (INT fv = 2; fv < objFace.vCount; fv++)
	{
		ObjTriangle tri;
		tri.Init();

		tri.vertex[0].iPos = objMesh.faceVertices[objFace.firstVertex];
		tri.vertex[1].iPos = objMesh.faceVertices[objFace.firstVertex + fv - 1];
		tri.vertex[2].iPos = objMesh.faceVertices[objFace.firstVertex + fv];
# ifdef DEBUG
		if (tri.vertex[0].iPos >= objMesh.vertices.size()) DebugBreak();
		if (tri.vertex[1].iPos >= objMesh.vertices.size()) DebugBreak();
		if (tri.vertex[2].iPos >= objMesh.vertices.size()) DebugBreak();
# endif


		if (!objMesh.normals.empty() && objFace.firstNormal >= 0)
		{
			tri.vertex[0].iNormal = objMesh.faceNormals[objFace.firstNormal];
			tri.vertex[1].iNormal = objMesh.faceNormals[objFace.firstNormal + fv - 1];
			tri.vertex[2].iNormal = objMesh.faceNormals[objFace.firstNormal + fv];
# ifdef DEBUG
			if (tri.vertex[0].iNormal >= objMesh.normals.size()) DebugBreak();
			if (tri.vertex[1].iNormal >= objMesh.normals.size()) DebugBreak();
			if (tri.vertex[2].iNormal >= objMesh.normals.size()) DebugBreak();
# endif
		}

		if (!objMesh.texCoords.empty() && objFace.firstTexCoord >= 0)
		{
			tri.vertex[0].iTex = objMesh.faceTexCoords[objFace.firstTexCoord];
			tri.vertex[1].iTex = objMesh.faceTexCoords[objFace.firstTexCoord + fv - 1];
			tri.vertex[2].iTex = objMesh.faceTexCoords[objFace.firstTexCoord + fv];
		}

		objTriangleList.push_back(tri);
	}
}

HRESULT CD3Mesh::Create(LPDIRECT3DDEVICE9 pD3DDevice, const TObjMesh & objMesh, BOOL flipTriangles, BOOL flipUVs)
{
	if (objMesh.vertices.empty() || objMesh.numTriangles == 0)
	{
		OutputDebugString(TEXT(__FUNCTION__)TEXT(": obj mesh is invalid!"));
		return E_FAIL;
	}

	bbmin = objMesh.bbmin;
	bbmax = objMesh.bbmax;

	return InitVB(pD3DDevice, objMesh, flipTriangles, flipUVs);
}

HRESULT CD3Mesh::InitVB(LPDIRECT3DDEVICE9 pD3DDevice, const TObjMesh & objMesh, BOOL flipTriangles, BOOL flipUVs)
{
	HRESULT hr;
	SAFE_RELEASE(pVB);

	vertexSize = sizeof(D3DXVECTOR3);
	FVF = D3DFVF_XYZ;

	BOOL hasNormals = TRUE;
	BOOL hasTexCoords = !objMesh.texCoords.empty();

	if (hasNormals) { vertexSize += sizeof(D3DXVECTOR3); FVF |= D3DFVF_NORMAL; }
	if (hasTexCoords) { vertexSize += sizeof(D3DXVECTOR2); FVF |= (D3DFVF_TEX2 | D3DFVF_TEXCOORDSIZE2(0)); }


	ObjTriangleList triList;
	triList.reserve(objMesh.numTriangles);

	for (UINT i = 0; i<objMesh.faces.size(); i++)
		AddObjFace(triList, objMesh, i, FALSE, FALSE);

	triCount = triList.size();


	struct VBVertex
	{
		D3DXVECTOR3 pos, normal;
		D3DXVECTOR2 tex;
	};

	UINT bufferSize = triCount * vertexSize * 3;
	hr = pD3DDevice->CreateVertexBuffer(bufferSize, D3DUSAGE_WRITEONLY, FVF, D3DPOOL_DEFAULT, &pVB, NULL);
	if (FAILED(hr)) return hr;

	BYTE* pVBData = NULL;
	hr = pVB->Lock(0, 0, (VOID**)&pVBData, 0);
	if (FAILED(hr)) return hr;

	UINT vertexOrder[] = { 0, 1, 2 };
	if (flipTriangles)
	{
		vertexOrder[1] = 2; vertexOrder[2] = 1;
	}

	for (UINT i = 0; i<triList.size(); i++)
	{
		ObjTriangle& tri = triList[i];

		D3DXVECTOR3 triNormal;
		if (tri.vertex[0].iNormal < 0)
		{
			D3DXVECTOR3 vec1 = objMesh.vertices[tri.vertex[2].iPos] - objMesh.vertices[tri.vertex[0].iPos];
			D3DXVECTOR3 vec2 = objMesh.vertices[tri.vertex[2].iPos] - objMesh.vertices[tri.vertex[1].iPos];
			if (flipTriangles)
				D3DXVec3Cross(&triNormal, &vec2, &vec1);
			else
				D3DXVec3Cross(&triNormal, &vec1, &vec2);
			D3DXVec3Normalize(&triNormal, &triNormal);
		}

		for (UINT tv = 0; tv < 3; tv++)
		{
			UINT v = vertexOrder[tv];

			VBVertex* pVBVertex = (VBVertex*)pVBData;
			pVBVertex->pos = objMesh.vertices[tri.vertex[v].iPos];
			if (tri.vertex[v].iNormal < 0)
				pVBVertex->normal = triNormal;
			else
				pVBVertex->normal = objMesh.normals[tri.vertex[v].iNormal];

			if (hasTexCoords && tri.vertex[v].iTex >= 0)
			{
				if (flipUVs)
				{
					D3DXVECTOR2 tex = objMesh.texCoords[tri.vertex[v].iTex];
					tex.y = 1 - tex.y;
					pVBVertex->tex = tex;
				}
				else
					pVBVertex->tex = objMesh.texCoords[tri.vertex[v].iTex];
			}

			pVBData += vertexSize;
		}
	}

	pVB->Unlock();

	return S_OK;
}
