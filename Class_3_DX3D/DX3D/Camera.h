#pragma once
#include "IDisplayObject.h"
#include "Mob.h"
#include "Ray.h"

#define g_pCamera Camera::GetInstance()

class Camera
{
	SINGLETON(Camera)

public:
	struct TARGET_DESC
	{
		D3DXVECTOR3* position;
		D3DXVECTOR3* forward;
		float* rotX;
		float* rotY;
	};

	enum CameraType
	{
		Type_LookTarget,
		Type_LookForward,
		Type_SpaceScene,
		Type_NULL
	};
private:
	D3DXVECTOR3		m_eye;
	D3DXVECTOR3		m_lookAt;
	D3DXVECTOR3		m_up;
	D3DXMATRIXA16	m_matView;
	D3DXMATRIXA16	m_matProj;
	D3DXVECTOR3		m_offset;
	D3DXVECTOR3		m_currOffset;

	float			m_basePosY;
	float			m_distance;
	float			m_rotX;
	float			m_rotY;
	bool			m_isLbuttonDown;
	POINT			m_ptPrevMouse;
	D3DXVECTOR3*	m_pTarget;

	TARGET_DESC		m_targetDesc;


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
	int m_magazine;
	int m_running;
	float m_runningRecoilX;
	float m_runningRecoilY;
	float m_accuracyX;
	float m_accuracyY;
	float m_accuracyXDelta;
	float m_accuracyYDelta;
	bool m_zooming;
	float m_prev_rotX;
	float m_deltaY;

	bool debugDisplayCheck;
	bool debugDisplay;

	bool shotCheck; // 총 발사 여부 체크
	int reloadTime; // 재장전 사운드 재생까지의 지연시간

	bool m_pBombingMode;
	int m_pBombingCooldown;

	int m_pShakingCount;
	float m_pShakingDeltaX;
	float m_pShakingDeltaY;
	float m_pShakingDeltaZ;

	D3DXVECTOR3 oldPos;



	//선생님코드

	VARIATION(CameraType, m_type, Type);
	VARIATION_P(float, m_fovY, FovY);
	VARIATION_P(D3DXVECTOR3, m_forward, Forward);
	VARIATION_P(D3DXVECTOR3, m_currForward, CurrForward);
	VARIATION_P(D3DXMATRIXA16, m_matR, MatR);
	VARIATION_P(D3DXMATRIXA16, m_currMatR, CurrMatR);
	void SetOffset(D3DXVECTOR3* v) { m_offset = *v; m_currOffset = *v; }

	//

public:
	void Init();
	void Update();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetTarget(D3DXVECTOR3* pTarget) { m_pTarget = pTarget; }

	D3DXVECTOR3 getDir();
	D3DXVECTOR3 getPos();
	D3DXVECTOR3 getOldPos();
	float getFOV();
	float getSpeedOffset();
	float getAngleX();
	float getRotX();
	void setRotX(float rotX);
	float getAngleY();
	float getRotY();
	void setRotY(float rotY);
	D3DXMATRIXA16 getMatWorld();
	void setPos(D3DXVECTOR3 p);
	void setPosY(float y);
	void setFreeCameraMode(bool f);
	bool getFreeCameraMode();
	bool getBombingMode();
	void setBombingMode(bool b);
	int getCooldown();
	int getMagazine();
	float getDeltaY();
	bool mouseLock;
	bool isPaused;
	bool m_pBombingReady;
	bool m_pBombing;
	int m_pBombingDelay;
	void getPMobFromUnitBox(vector<Mob*>* mob);
	void bombing();
	void shaking(int shakingDelta);

	const D3DXVECTOR3& GetPosition() { return m_eye; }
	D3DXMATRIXA16* GetViewMatrix() { return &m_matView; }
	D3DXMATRIXA16* GetProjMatrix() { return &m_matProj; }
	D3DXMATRIXA16* GetViewProjMatrix() { return &(D3DXMATRIXA16)(m_matView * m_matProj); }

	float getRecoil() { return m_recoilX; 	}
};

