#pragma once

struct FRAME_EX 
	: public D3DXFRAME 
{
	//root ���� �ڽ� ������ ������ ������ �������
	D3DXMATRIXA16 CombinedTM;	
};

struct MESHCONTAINER_EX 
	: public D3DXMESHCONTAINER 
{
	vector<MTLTEX*>	vecMtlTex;

	// �������� ���� ���� �Ž�(Update ���� �������� ������ Anim ����)
	LPD3DXMESH		pOrigMesh;			

	// Anim �� ������ ���� ������ �Ž�
	LPD3DXMESH		pWorkMesh;		

	// �� �Ž��� ������ �ִ� �����ӵ��� �����Ʈ���� �������� �迭
	D3DXMATRIX**	ppBoneMatrixPtrs;	

	// ���� �޽��� �� �������� ���ý����̽��� ������ ��Ʈ���� �迭
	D3DXMATRIX*		pBoneOffsetMatrices;

	// �� ���� ���� �����Ʈ���� �迭
	D3DXMATRIX*		pFinalBoneMatrices;
};

class AllocateHierarchy 
	: public ID3DXAllocateHierarchy
{
protected:
	CString m_path;

public:
	AllocateHierarchy() {}
	AllocateHierarchy(CString path) { m_path = path; }
	~AllocateHierarchy() {}


	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name,
		LPD3DXFRAME *ppNewFrame) override;


	STDMETHOD(CreateMeshContainer)(THIS_
		LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer) override;


	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree) override;

	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree) override;
};

