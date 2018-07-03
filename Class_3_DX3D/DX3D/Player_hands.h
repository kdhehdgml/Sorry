#pragma once
/*테스트 모드
0 = 모두장전
1 = 볼트액션
2 = 기본상태


*/


/* 구버전
0 기본상태
0~5 줌인
5~10 줌아웃
10~20 달리기준비
20~30 달리는중
30~45 달리기해제
45~85 볼트액션
5~5   줌 기본상태

*/
// x파일 로더가 애니메이션 셋을 받아올떄 거꾸로 받아오기때문에 거꾸로 해줘야한다!
//아마 중간에 끝에서부터 시작되는 이유도 그게 문제지 않을까 싶다.
//플레이어 액션 상태값
enum PLAYER_STATE
{
	줌_모드,
	달리는중,
	전탄장전,
	볼트액션,
	기본상태
};



class Player_hands : public IUnitObject
{
protected:

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
	
	//렌더 껏다키기
	bool						m_Render;
	bool						m_Reload;
	bool						m_zooming;

	float						angleX, angleY;

	int							count;

	D3DXMATRIXA16				matT, matS, matR;

	float						m_FrameTime;

	//쏘자마자 장전하는거 방지용
	int							m_bulletActionCount;

public:
	Player_hands();
	~Player_hands();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Load(LPCTSTR path, LPCTSTR filename);
	void SetPosToCamera();

private:
	void SetupBoneMatrixPointers(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase);

	void UpdateAnim();
	void UpdateFrameMatrices(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);

	void DrawFrame(LPD3DXFRAME pFrame);
	void DrawMeshContainer(LPD3DXFRAME pFrame);
	void DrawSkeleton(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);

public:
	void SetAnimationIndex(int nIndex, bool isBlend);
};
