#pragma once

struct FRAME_EX 
	: public D3DXFRAME 
{
	//root 부터 자신 프레임 까지의 누적된 행렬정보
	D3DXMATRIXA16 CombinedTM;	
};

struct MESHCONTAINER_EX 
	: public D3DXMESHCONTAINER 
{
	vector<MTLTEX*>	vecMtlTex;

	// 수정하지 않은 원본 매쉬(Update 마다 원본값을 참조해 Anim 연산)
	LPD3DXMESH		pOrigMesh;			

	// Anim 을 적용한 실제 보여줄 매쉬
	LPD3DXMESH		pWorkMesh;		

	// 이 매쉬에 영향을 주는 프레임들의 월드매트릭스 포인터의 배열
	D3DXMATRIX**	ppBoneMatrixPtrs;	

	// 원본 메쉬를 각 프레임의 로컬스페이스로 보내는 매트릭스 배열
	D3DXMATRIX*		pBoneOffsetMatrices;

	// 각 본의 최종 월드매트릭스 배열
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

