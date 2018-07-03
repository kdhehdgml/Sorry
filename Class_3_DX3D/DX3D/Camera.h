#pragma once
#include "IDisplayObject.h"
#include "Mob.h"
#include "Ray.h"

#define g_pCamera Camera::GetInstance()

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
	int getMagazine();
	bool mouseLock;
	void getPMobFromUnitBox(vector<Mob*>* mob);
};

