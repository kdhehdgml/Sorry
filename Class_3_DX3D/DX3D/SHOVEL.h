#pragma once
#include "IUnitObject.h"

class SHOVEL :public IUnitObject
{
protected:
	//총기종류
//	GUN_KINDS Kar98;
	//GUN_KINDS Smle;



	//애니메이션 조절용
	LPD3DXANIMATIONSET			pCurrAnimSet;
	LPD3DXANIMATIONSET			pNextAnimSet;
	D3DXTRACK_DESC				track;

	//

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

	int							m_state;

	bool						m_HandsOption;
	float						angle;

	D3DXMATRIXA16				matT, matS, matR;

	bool						m_animationSTATE;

	float						trackSpeed;
public:
	SHOVEL();
	~SHOVEL();

	// IUnitObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void Load(LPCTSTR path, LPCTSTR filename);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetState(int state) { m_state = state; }
	void SetMat(D3DXMATRIXA16 *mat) { m_matWorld = m_matWorld * (*mat)  ; }
	void SetMatS(D3DXMATRIXA16 S) { matS = S; }
	void SetMatR(D3DXMATRIXA16 R) { matR = R; }
	void SetMatT(D3DXMATRIXA16 T) { matT = T; }
	//기본적으로 우측을 보고있어서 돌려줌
	void SetAngle(float angle) { m_angle = angle; }


private:
	void SetupBoneMatrixPointers(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase);

	void UpdateAnim();
	void UpdateFrameMatrices(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);

	void DrawFrame(LPD3DXFRAME pFrame);
	void DrawMeshContainer(LPD3DXFRAME pFrame);
	void DrawSkeleton(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);

	float m_angle;

public:
	void SetAnimationIndex(int nIndex) { m_AnimaTionIndex = nIndex; }
	void SetAnimationIndex(int nIndex, bool isBlend);
};

