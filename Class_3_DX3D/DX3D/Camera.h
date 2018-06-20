#pragma once
#include "IDisplayObject.h"
#include "Mob.h"
#include "Ray.h"

#define g_pCamera Camera::GetInstance()

enum PLAYER_STATE
{
	줌_모드,
	볼트액션,
	달리기해제,
	달리는중,
	달리기준비,
	줌아웃,
	줌인,
	기본상태
};

class Camera
{
	SINGLETON(Camera)
private:
	D3DXVECTOR3		m_eye;
	D3DXVECTOR3		m_lookAt;
	D3DXVECTOR3		m_up;
	D3DXMATRIXA16	m_matView;
	D3DXMATRIXA16	m_matProj;
	float			m_basePosY;
	float			m_distance;
	float			m_rotX;
	float			m_rotY;
	bool			m_isLbuttonDown;
	POINT			m_ptPrevMouse;
	D3DXVECTOR3*	m_pTarget;

	D3DXVECTOR3 dir;
	D3DXVECTOR3 pos;
	D3DXMATRIXA16 m_matWorld;
	float m_FOV;
	float m_speedOffset;
	bool m_freeCameraMode;
	bool m_loadingComplete;
	POINT m_currPoint;
	float m_sensitivity;
	float m_recoilX;
	float m_recoilY;
	float m_recoilXDelta;
	float m_recoilYDelta;
	vector<Mob*> m_pMob;
	int m_cooldown;
	int m_running;
	float m_runningRecoilX;
	float m_runningRecoilY;
	float m_accuracyX;
	float m_accuracyY;
	float m_accuracyXDelta;
	float m_accuracyYDelta;
	float m_prev_rotX;

	bool debugDisplayCheck;
	bool debugDisplay;

	bool shotCheck; // 총 발사 여부 체크
	int reloadTime; // 재장전 사운드 재생까지의 지연시간

public:
	void Init();
	void Update();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetTarget(D3DXVECTOR3* pTarget) { m_pTarget = pTarget; }

	D3DXVECTOR3 getDir();
	D3DXVECTOR3 getPos();
	float getFOV();
	float getSpeedOffset();
	float getAngleX();
	float getAngleY();
	D3DXMATRIXA16 getMatWorld();
	void setPos(D3DXVECTOR3 p);
	void setPosY(float y);
	void setFreeCameraMode(bool f);
	bool getFreeCameraMode();
	int getCooldown();

	void getPMobFromUnitBox(vector<Mob*>* mob);
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

	//렌더 껏다키기
	bool						m_Render;
	bool						m_Reload;
	bool						m_zooming;

	float						angleX, angleY;

	int							count;

	D3DXMATRIXA16				matT, matS, matR;

	float m_baseRotY;

public:
	void Load(LPCTSTR path, LPCTSTR filename);
	void SetPosToCamera();
	void SetAnimationIndex(int nIndex, bool isBlend);

private:
	void SetupBoneMatrixPointers(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase);

	void UpdateAnim();
	void UpdateFrameMatrices(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);

	void DrawFrame(LPD3DXFRAME pFrame);
	void DrawMeshContainer(LPD3DXFRAME pFrame);
	void DrawSkeleton(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
};

