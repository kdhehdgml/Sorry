#pragma once
#include "IUnitObject.h"

/* 애니메이션 인덱스
7. Crouched_run
6.rifle_run
5.rifle_run2
4.run_die
3.run_to_stop
2.run_to_stop2
1.run_to_stop3
0.stand_idle

*/




class MONSTER : public IUnitObject
{

protected:

	//애니메이션 조절용
	LPD3DXANIMATIONSET			pCurrAnimSet;
	LPD3DXANIMATIONSET			pNextAnimSet;
	D3DXTRACK_DESC				track;

	//

	LPD3DXFRAME					m_pRootFrame;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;

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
	float						m_angle;
	float						RotSpeed;

	D3DXMATRIXA16				matT, matS, matR;

	bool						m_animationSTATE;

	float						trackSpeed;
	//작동할꺼냐말꺼냐
	bool						STATE;


	D3DXMATRIXA16				m_L_mat;
	D3DXVECTOR3					m_L_pos;

	D3DXMATRIXA16				m_R_mat;
	D3DXVECTOR3					m_R_pos;

	D3DXMATRIXA16				m_head_mat;
	D3DXMATRIXA16				m_head_mat2;

	D3DXVECTOR3				m_matScale;
	D3DXVECTOR3				m_matXY;

public:
	MONSTER();
	~MONSTER();

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
	//기본적으로 우측을 보고있어서 돌려줌
	void SetAngle(float angle) { m_angle = angle; }
	float GetAngle() { return m_angle; }

	D3DXVECTOR3* GetLeftPos() { return &m_L_pos; }
	LPD3DXMATRIXA16 GetLeftMat() { return &m_L_mat; } //왼손매트릭스
													  //void SetMat(D3DXMATRIXA16 *mat) { m_Hand_mat = (*mat); }

	D3DXVECTOR3* GetRightPos() { return& m_R_pos; }
	LPD3DXMATRIXA16 GetRightMat() { return &m_R_mat; }//오른손매트릭스

	//테스트
	LPD3DXMATRIXA16 GetPosMat() { return &m_matPos; }
	LPD3DXMATRIXA16 GetXYMat() { return &m_matXY; }
	LPD3DXMATRIXA16 GetScaleMat() { return &m_matScale; }

	LPD3DXMATRIXA16 GetHeadMat() { return &m_head_mat; }
	LPD3DXMATRIXA16 GetHeadMat2() { return &m_head_mat2; }

private:
	void SetupBoneMatrixPointers(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase);

	void UpdateAnim();
	void UpdateFrameMatrices(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);

	void DrawFrame(LPD3DXFRAME pFrame);
	void DrawMeshContainer(LPD3DXFRAME pFrame);
	void DrawSkeleton(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);

public:
	int							m_AnimaTionIndex;

	void SetAnimationIndex(int nIndex) { m_AnimaTionIndex = nIndex; }
	void SetAnimationIndex(int nIndex, bool isBlend);
	void SetRenderSTATE(bool select) { STATE = select; }
	
};

