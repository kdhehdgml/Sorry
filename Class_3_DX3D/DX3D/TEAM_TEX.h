#pragma once
#include "IUnitObject.h"

class TEAM_TEX : public IUnitObject
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

	int							m_state;

	bool						m_HandsOption;
	float						angle;

	D3DXMATRIXA16				matT, matS, matR;


public:
	TEAM_TEX();
	~TEAM_TEX();

	// IUnitObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void Load(LPCTSTR path, LPCTSTR filename);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetState(int state) { m_state = state; }
	void SetMatS(D3DXMATRIXA16 S) { matS = S; }
	void SetMatR(D3DXMATRIXA16 R) { matR = R; }
	void SetMatT(D3DXMATRIXA16 T) { matT = T; }
	//void SetAnimation(int animationIndex) { m_AnimaTionIndex = animationIndex; }
	//기본적으로 우측을 보고있어서 돌려줌
	void SetAngle(float angle) { m_angle = angle + D3DX_PI / 2  + D3DX_PI; }
	

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
	void SetAnimationIndex(int nIndex, bool isBlend);
};
