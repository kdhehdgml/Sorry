#pragma once
#include "IUnitObject.h"

class SkinnedMesh : public IUnitObject
{
protected:
	LPD3DXFRAME					m_pRootFrame;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;

	int							m_AnimaTionIndex;
	float						m_fBlendTime;
	float						m_fPassedBlendTime;

	LPD3DXMESH					m_pSphereMesh;
	bool						m_bWireFrame;
	bool						m_bDrawFrame;
	bool						m_bDrawSkeleton;
	int							m_numFrame;
	int							m_numMesh;

	D3DXMATRIXA16				matT, matS, matR;

	float						m_angle;
	/*D3DXVECTOR3					m_gun_pos;
	D3DXMATRIXA16				m_gun_mat;*/

	D3DXMATRIXA16				asdf;

	int							count;

public:
	SkinnedMesh();
	virtual ~SkinnedMesh();

	// IUnitObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void Load(LPCTSTR path, LPCTSTR filename);
private:
	void SetupBoneMatrixPointers(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase);

	void UpdateAnim();
	void UpdateFrameMatrices(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);

	void DrawFrame(LPD3DXFRAME pFrame);
	void DrawMeshContainer(LPD3DXFRAME pFrame);
	void DrawSkeleton(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);


	D3DXMATRIXA16				m_L_mat;
	D3DXVECTOR3					m_L_pos;

	D3DXMATRIXA16				m_R_mat;
	D3DXVECTOR3					m_R_pos;

public:
	void SetAnimationIndex(int nIndex, bool isBlend);
	D3DXVECTOR3 GetLeftPos() { return m_L_pos; }
	LPD3DXMATRIXA16 GetLeftMat() { return &m_L_mat; } //왼손매트릭스
	//void SetMat(D3DXMATRIXA16 *mat) { m_Hand_mat = (*mat); }

	D3DXVECTOR3 GetRightPos() { return m_R_pos; }
	LPD3DXMATRIXA16 GetRightMat() { return &m_R_mat; }//오른손매트릭스

	float		GetGunAngle() { return m_angle; }


private:
	int Weapon_Mode;


};

// OnInit
// pMeshContainerEx->ppBoneMatrixPtrs[i] = &pFrameExInfluence->CombinedTM;

// OnUpdate
// pFrameEx->CombinedTM = pFrameEx->TransformationMatrix * ((FRAME_EX*)pParent)->CombinedTM;
//
// pMeshContainerEx->pFinalBoneMatrices[i] =
// pMeshContainerEx->pBoneOffsetMatrices[i] * *(pMeshContainerEx->ppBoneMatrixPtrs[i]);
