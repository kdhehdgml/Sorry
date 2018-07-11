#pragma once
#include "IUnitObject.h"

/* �ִϸ��̼� �ε���
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

	//�ִϸ��̼� ������
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
	float						m_angle;
	float						RotSpeed;

	D3DXMATRIXA16				matT, matS, matR;

	bool						m_animationSTATE;

	float						trackSpeed;
	//�۵��Ҳ��ĸ�����
	bool						STATE;


	D3DXMATRIXA16				m_gun_mat;
	D3DXVECTOR3					m_gun_pos;

	D3DXMATRIXA16				m_melee_mat;
	D3DXVECTOR3					m_melee_pos;

public:
	MONSTER();
	~MONSTER();

	// IUnitObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void Load(LPCTSTR path, LPCTSTR filename);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetState(int state) { m_state = state; }
	void SetMatS(D3DXMATRIXA16 S) { matS = S; }
	void SetMatR(D3DXMATRIXA16 R) { matR = R; }
	void SetMatT(D3DXMATRIXA16 T) { matT = T; }
	//�⺻������ ������ �����־ ������
	void SetAngle(float angle) { m_angle = angle; }

	D3DXVECTOR3 GetGunPos() { return m_gun_pos; }
	D3DXMATRIXA16 GetGunMat() { return m_gun_mat; }
	D3DXVECTOR3 GetMeleePos() { return m_melee_pos; }
	D3DXMATRIXA16 GetMeleeMat() { return m_melee_mat; }
private:
	void SetupBoneMatrixPointers(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase);

	void UpdateAnim();
	void UpdateFrameMatrices(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);

	void DrawFrame(LPD3DXFRAME pFrame);
	void DrawMeshContainer(LPD3DXFRAME pFrame);
	void DrawSkeleton(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);

public:
	void SetAnimationIndex(int nIndex) { m_AnimaTionIndex = nIndex; }
	void SetAnimationIndex(int nIndex, bool isBlend);
	void SetRenderSTATE(bool select) { STATE = select; }
	
};

