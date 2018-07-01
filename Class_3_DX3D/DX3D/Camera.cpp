#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	m_distance = 10.0f;
	m_basePosY = 5.0f;
	m_eye = D3DXVECTOR3(0, m_basePosY, -m_distance);
	m_lookAt = D3DXVECTOR3(0, 0, 0);
	m_up = D3DXVECTOR3(0, 1, 0);
	m_rotX = 0.0f;
	m_rotY = 0.0f;
	m_isLbuttonDown = false;
	m_pTarget = NULL;

	pos.x = GSM().camPos.x;
	pos.z = GSM().camPos.z;
	pos.y = GSM().camPos.y;


	m_FOV = D3DX_PI / 4.0f;
	m_speedOffset = 0.4f;
	m_freeCameraMode = true;
	m_sensitivity = 200.0f;

	m_recoilX = 0.0f;
	m_recoilY = 0.0f;
	m_recoilXDelta = 0.0f;
	m_recoilYDelta = 0.0f;

	m_cooldown = 0;

	m_running = 0;
	m_runningRecoilX = 0.0f;
	m_runningRecoilY = 0.0f;
	m_accuracyX = 0.0f;
	m_accuracyY = 0.0f;
	m_accuracyXDelta = 0.0f;
	m_accuracyYDelta = 0.0f;
	m_zooming = false;

	m_prev_rotX = 0.0f;

	debugDisplay = false;
	debugDisplayCheck = false;

	shotCheck = false;
	reloadTime = 0;

	m_magazine = 5;
}


Camera::~Camera()
{
}

void Camera::Init()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	POINT p;
	p.x = (rc.right - rc.left) / 2;
	p.y = (rc.bottom - rc.top) / 2;
	ClientToScreen(g_hWnd, &p);
	SetCursorPos(p.x, p.y);
	m_currPoint = p;
	m_ptPrevMouse = m_currPoint;

	m_loadingComplete = false;

	D3DXMatrixLookAtLH(&m_matView,
		&m_eye, &m_lookAt, &m_up);
	g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj,
		m_FOV, rc.right / (float)rc.bottom, 1.0f, 10000.0f);
	g_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void Camera::Update()
{
	/*//m_eye = D3DXVECTOR3(0, m_basePosY, -m_distance);
	m_eye = D3DXVECTOR3(pos.x, pos.y, -pos.z);

	D3DXMATRIXA16 matRotX, matRotY, matRot;
	D3DXMatrixRotationX(&matRotX, m_rotX);
	D3DXMatrixRotationY(&matRotY, m_rotY);
	matRot = matRotX * matRotY;

	D3DXVec3TransformCoord(&m_eye, &m_eye, &matRot);

	if (m_pTarget)
	{
	m_lookAt = *m_pTarget;
	m_eye = *m_pTarget + m_eye;
	}

	D3DXMatrixLookAtLH(&m_matView,
	&m_eye, &m_lookAt, &m_up);
	g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);*/

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProj;
	D3DXMatrixTranslation(&matWorld, 0, 0, 0);
	D3DXVECTOR3 vEyePt(pos.x, pos.y, pos.z);
	D3DXVECTOR3 vLookatPt(pos.x + dir.x, pos.y + dir.y, pos.z + dir.z);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pDevice->SetTransform(D3DTS_VIEW, &matView);
	//D3DXMatrixPerspectiveFovLH(시야 행렬, 시야각, 종횡비, 최소시야, 최대시야);
	D3DXMatrixPerspectiveFovLH(&matProj, m_FOV, rc.right / (float)rc.bottom, 1.0f, 10000.0f);
	g_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_matWorld = matWorld;
	m_matView = matView;
	m_matProj = matProj;

	m_prev_rotX = m_rotX;

	if (GetKeyState('A') & 0x8000)
	{
		D3DXVECTOR3 v;
		D3DXVec3Cross(&v, &dir, &D3DXVECTOR3(0, 1, 0));
		pos.x += (v.x* m_speedOffset);
		pos.z += (v.z* m_speedOffset);
	}
	else if (GetKeyState('D') & 0x8000)
	{
		D3DXVECTOR3 v;
		D3DXVec3Cross(&v, &dir, &D3DXVECTOR3(0, 1, 0));
		pos.x -= (v.x* m_speedOffset);
		pos.z -= (v.z* m_speedOffset);
	}

	if (GetKeyState('W') & 0x8000)
	{
		pos.x += (dir.x* m_speedOffset);
		pos.z += (dir.z* m_speedOffset);
	}
	else if (GetKeyState('S') & 0x8000)
	{
		pos.x -= (dir.x* m_speedOffset);
		pos.z -= (dir.z* m_speedOffset);
	}

	if (GetKeyState(VK_SHIFT) & GetKeyState('W') & 0x8000) {
		if (m_freeCameraMode) {
			m_speedOffset = 4.0f;
		}
		else {
			m_speedOffset = 0.8f;
		}
		m_running++;
		if (m_running >= 41) {
			m_running = 1;
		}
	}
	else {
		if (m_freeCameraMode) {
			m_speedOffset = 2.0f;
		}
		else {
			m_speedOffset = 0.4f;
		}
		m_running = 0;
	}

	if (m_running >= 1 && m_running < 10) {
		m_runningRecoilX = m_running * 0.005f;
		m_runningRecoilY = m_running * -0.005f;
	}
	else if (m_running >= 11 && m_running < 20) {
		m_runningRecoilX = (20 - m_running) * 0.005f;
		m_runningRecoilY = (20 - m_running) * -0.005f;
	}
	else if (m_running >= 21 && m_running < 30) {
		m_runningRecoilX = (m_running - 20) * 0.005f;
		m_runningRecoilY = (m_running - 20) * 0.005f;
	}
	else if (m_running >= 31 && m_running < 40) {
		m_runningRecoilX = (40 - m_running) * 0.005f;
		m_runningRecoilY = (40 - m_running) * 0.005f;
	}
	else {
		if (m_runningRecoilX > 0) {
			m_runningRecoilX -= 0.005f;
		}
		else {
			m_runningRecoilX = 0;
		}
		if (abs(m_runningRecoilY) > 0.01f) {
			if (m_runningRecoilY > 0) {
				m_runningRecoilY -= 0.005f;
			}
			else {
				m_runningRecoilY += 0.005f;
			}
		}
		else {
			m_runningRecoilY = 0;
		}
	}

	m_recoilX += m_recoilXDelta;
	m_recoilY += m_recoilYDelta;

	if (m_recoilXDelta > 0) {
		m_recoilXDelta -= 0.02f;
	}
	else {
		m_recoilXDelta = 0;
		if (m_recoilX > 0) {
			m_recoilX -= 0.01f;
		}
		else {
			m_recoilX = 0;
		}
	}
	if (abs(m_recoilYDelta) > 0.02f) {
		if (m_recoilYDelta > 0) {
			m_recoilYDelta -= 0.01f;
		}
		else {
			m_recoilYDelta += 0.01f;
		}
	}
	else {
		m_recoilYDelta = 0;
		if (abs(m_recoilY) > 0.01f) {
			if (m_recoilY > 0) {
				m_recoilY -= 0.005f;
			}
			else {
				m_recoilY += 0.005f;
			}
		}
		else {
			m_recoilY = 0;
		}
	}

	int accuracyBuffer = rand() % 100;
	if (accuracyBuffer < 2) {
		m_accuracyXDelta -= 0.005f;
	}
	else if (accuracyBuffer >= 98) {
		m_accuracyXDelta += 0.005f;
	}
	accuracyBuffer = rand() % 100;
	if (accuracyBuffer < 2) {
		m_accuracyYDelta -= 0.005f;
	}
	else if (accuracyBuffer >= 98) {
		m_accuracyYDelta += 0.005f;
	}
	if (m_accuracyXDelta > 0.05f) {
		m_accuracyXDelta = 0.05f;
	}
	else if (m_accuracyXDelta < -0.05f) {
		m_accuracyXDelta = -0.05f;
	}
	if (m_accuracyYDelta > 0.05f) {
		m_accuracyYDelta = 0.05f;
	}
	else if (m_accuracyYDelta < -0.05f) {
		m_accuracyYDelta = -0.05f;
	}
	if (abs(m_accuracyX - m_accuracyXDelta) > D3DX_16F_EPSILON) {
		if (m_accuracyX > m_accuracyXDelta) {
			m_accuracyX -= 0.0001f;
		}
		else if (m_accuracyX < m_accuracyXDelta) {
			m_accuracyX += 0.0001f;
		}
	}
	if (abs(m_accuracyY - m_accuracyYDelta) > D3DX_16F_EPSILON) {
		if (m_accuracyY > m_accuracyYDelta) {
			m_accuracyY -= 0.0001f;
		}
		else if (m_accuracyY < m_accuracyYDelta) {
			m_accuracyY += 0.0001f;
		}
	}

	if (m_freeCameraMode) {
		m_runningRecoilX = 0.0f;
		m_runningRecoilY = 0.0f;
		m_accuracyX = 0.0f;
		m_accuracyXDelta = 0.0f;
		m_accuracyY = 0.0f;
		m_accuracyYDelta = 0.0f;
	}

	if ((m_rotX + m_recoilX + m_runningRecoilX + m_accuracyX) <= -D3DX_PI * 0.4f + D3DX_16F_EPSILON)
	{
		m_rotX = m_prev_rotX;
	}
	if ((m_rotX + m_recoilX + m_runningRecoilX + m_accuracyX) >= D3DX_PI * 0.3f - D3DX_16F_EPSILON)
	{
		m_rotX = m_prev_rotX;
	}

	dir.x = sin(m_rotY + m_recoilY + m_runningRecoilY + m_accuracyY);
	dir.z = cos(m_rotY + m_recoilY + m_runningRecoilY + m_accuracyY);
	dir.y = tan(m_rotX + m_recoilX + m_runningRecoilX + m_accuracyX);

	if (m_cooldown >= 1) {
		m_cooldown--;
	}

	if (m_zooming && m_cooldown <= 0) {
		m_FOV = D3DX_PI / 8;
		m_sensitivity = 800.0f;
	}
	else {
		m_FOV = D3DX_PI / 4;
		m_sensitivity = 200.0f;
	}

	if ((GetAsyncKeyState('4') & 0x8000))
	{
		if (!debugDisplayCheck)
		{
			debugDisplayCheck = true;

			if (!debugDisplay)
				debugDisplay = true;
			else
				debugDisplay = false;
		}
	}
	else if (debugDisplayCheck)
		debugDisplayCheck = false;

	if (debugDisplay)
	{
		Debug->AddText("마우스 좌표:");
		Debug->AddText(pos);
		Debug->EndLine();
		Debug->AddText("카메라 각도:");
		Debug->AddText(dir);
		Debug->EndLine();
		Debug->AddText("m_rotX : ");
		Debug->AddText(m_rotX);
		Debug->AddText(" m_rotY : ");
		Debug->AddText(m_rotY);
		Debug->EndLine();
		Debug->AddText("m_recoilX : ");
		Debug->AddText(m_recoilX);
		Debug->AddText(" m_recoilY : ");
		Debug->AddText(m_recoilY);
		Debug->EndLine();
		Debug->AddText("m_runningRecoilX : ");
		Debug->AddText(m_runningRecoilX);
		Debug->AddText(" m_runningRecoilY : ");
		Debug->AddText(m_runningRecoilY);
		Debug->EndLine();
		Debug->AddText("m_accuracyX : ");
		Debug->AddText(m_accuracyX);
		Debug->AddText(" m_accuracyY : ");
		Debug->AddText(m_accuracyY);
		Debug->EndLine();
		Debug->AddText("프리카메라 모드 : ");
		if (m_freeCameraMode)
			Debug->AddText("ON");
		else
			Debug->AddText("OFF");
		Debug->EndLine();
	}

	if (shotCheck)
		reloadTime++;

	if (reloadTime >= 15) // 재장전 사운드 재생 지연 시간
	{
		g_pSoundManager->ReloadSound();
		shotCheck = false;
		reloadTime = 0;
	}


	if (g_pTimeManager->GetDeltaTime() > 0.001f) { //DeltaTime이 Epsilon보다 크면 로딩이 완료된 걸로 간주
		m_loadingComplete = true;
		//ShowCursor(false);
	}
}

void Camera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		//m_isLbuttonDown = true;
		//m_ptPrevMouse.x = LOWORD(lParam);
		//m_ptPrevMouse.y = HIWORD(lParam);
		if (m_cooldown == 0 && !g_pCamera->getFreeCameraMode()) {
			m_recoilXDelta += (float)((float)(rand() % 4) + 8.0f) / 100.0f;
			m_recoilYDelta += (float)((float)(rand() % 12) - 6.0f) / 100.0f;
			Ray r = Ray::RayAtWorldSpace(SCREEN_POINT(lParam));

			// 발사음 테스트
			g_pSoundManager->ShotSound();
			shotCheck = true; // 총 발사 체크
			float minDistance = 9999999.0f;
			int tempIndex = 0, enemyIndex = -1, damageGiven = 0;
			for (auto p : m_pMob)
			{
				D3DXVECTOR3 enemyPos = p->GetPosition(); //적 위치
				D3DXVECTOR3 playerPos = g_pCamera->getPos(); //내 위치
				enemyPos.y += 7.0f;
				D3DXVECTOR3 playerDir = g_pCamera->getDir(); //내가 보는 방향
				D3DXVECTOR3 posDiff = enemyPos - playerPos; //적 위치랑 내 위치의 차이
				float distance = sqrtf(D3DXVec3Dot(&posDiff, &posDiff)); //적과의 거리 계산
				bool getHitHead = false;
				getHitHead = r.CalcIntersectSphere(p->getBoundingSphereHead());
				if (getHitHead && p->getStatus() == 1) {
					//p->setHealth(p->getHealth() - 100);
					//break;
					damageGiven = 100;
					if (distance < minDistance) {
						minDistance = distance;
						enemyIndex = tempIndex;
					}
				}
				bool getHitBody = false;
				getHitBody = r.CalcIntersectSphere(p->getBoundingSphereBody());
				if (!getHitHead && getHitBody && p->getStatus() == 1) {
					//p->setHealth(p->getHealth() - 50);
					//break;
					damageGiven = 50;
					if (distance < minDistance) {
						minDistance = distance;
						enemyIndex = tempIndex;
					}
				}
				tempIndex++;
			}
			if (enemyIndex != -1) {
				D3DXVECTOR3 rayPos = r.getPos();
				D3DXVECTOR3 rayDir = r.getDir();
				float rayHeight;
				bool isIntersected, rayHit = false;
				for (int i = 0; i < 100; i++) {
					if (i < 50) {
						rayPos = rayPos + rayDir * 2;
					}
					else {
						rayPos = rayPos + rayDir * 5;
					}
					isIntersected = g_pCurrentMap->GetHeight(rayHeight, rayPos);

					if (rayPos.y < rayHeight) {
						//MessageBox(NULL, TEXT("총알이 땅에 부딪혔습니다."), TEXT("DEBUG"), MB_OK);
						rayHit = true;
						break;
					}
				}
				D3DXVECTOR3 enemyPos = m_pMob[enemyIndex]->GetPosition();
				D3DXVECTOR3 playerPos = g_pCamera->getPos();
				enemyPos.y += 7.0f;
				D3DXVECTOR3 posDiff1 = enemyPos - playerPos;
				D3DXVECTOR3 posDiff2 = rayPos - playerPos;
				float distance1 = sqrtf(D3DXVec3Dot(&posDiff1, &posDiff1));
				float distance2 = sqrtf(D3DXVec3Dot(&posDiff2, &posDiff2));
				if (rayHit && distance2 < distance1) {
					MessageBox(NULL, TEXT("총알이 땅에 부딪혔습니다."), TEXT("DEBUG"), MB_OK);
				}
				else {
					m_pMob[enemyIndex]->setHealth(m_pMob[enemyIndex]->getHealth() - 50);
				}
			}
			


			m_magazine--;
			if (m_magazine > 0) {
				m_cooldown = 60;
			}
			else {
				m_magazine = 5;
				m_cooldown = 150;
			}
			//m_cooldown = 60; //쿨타임 (단위 : 프레임)
		}
	}
	break;
	case WM_LBUTTONUP:
	{
		//m_isLbuttonDown = false;
	}
	break;
	case WM_RBUTTONDOWN:
		//m_FOV = D3DX_PI / 8;
		//m_sensitivity = 800.0f;
		m_zooming = true;
		break;
	case WM_RBUTTONUP:
		//m_FOV = D3DX_PI / 4;
		//m_sensitivity = 200.0f;
		m_zooming = false;
		break;
	case WM_MOUSEMOVE:
	{
		//POINT currPoint;
		m_currPoint.x = LOWORD(lParam);
		m_currPoint.y = HIWORD(lParam);
		if (m_loadingComplete)
		{
			float diff_x = m_currPoint.x - m_ptPrevMouse.x;
			float diff_y = m_currPoint.y - m_ptPrevMouse.y;

			if (diff_x == 0 && diff_y == 0) {
				break;
			}

			m_rotY += diff_x / m_sensitivity;
			m_rotX -= diff_y / m_sensitivity;

			if ((m_rotX + m_recoilX + m_runningRecoilX + m_accuracyX) <= -D3DX_PI * 0.4f + D3DX_16F_EPSILON)
			{
				m_rotX = m_prev_rotX;
			}
			if ((m_rotX + m_recoilX + m_runningRecoilX + m_accuracyX) >= D3DX_PI * 0.3f - D3DX_16F_EPSILON)
			{
				m_rotX = m_prev_rotX;
			}

			//dir.x = sin(m_rotY + m_recoilY);
			//dir.z = cos(m_rotY + m_recoilY);
			//dir.y = tan(m_rotX + m_recoilX);

			m_ptPrevMouse = m_currPoint;
			if (diff_x || diff_y) //마우스 위치가 변했을때 마우스 위치를 화면 중앙으로 이동
			{
				RECT rc; GetClientRect(g_hWnd, &rc);
				POINT p = { (rc.right - rc.left) / 2 , (rc.bottom - rc.top) / 2 };
				ClientToScreen(g_hWnd, &p);
				SetCursorPos(p.x, p.y);

				m_ptPrevMouse.x = (rc.right - rc.left) / 2;
				m_ptPrevMouse.y = (rc.bottom - rc.top) / 2;
			}

		}
		else {
			m_ptPrevMouse = m_currPoint;
			//여기 있는 m_rotX와 m_rotY를 수정해서 카메라 초기값 수정가능
			m_rotX = -0.34f;
			m_rotY = 1.6f;
			dir.x = sin(m_rotY);
			dir.z = cos(m_rotY);
			dir.y = tan(m_rotX);
		}
		break;
	}
	case WM_MOUSEWHEEL:
		/*m_distance -= GET_WHEEL_DELTA_WPARAM(wParam) / 50.0f;
		if (m_distance <= 2) m_distance = 2;
		if (m_distance >= 100) m_distance = 100;*/

		//pos.y += GET_WHEEL_DELTA_WPARAM(wParam) / 50.0f;

		break;
	}
}

D3DXVECTOR3 Camera::getDir()
{
	return dir;
}

D3DXVECTOR3 Camera::getPos()
{
	return pos;
}

float Camera::getFOV()
{
	return m_FOV;
}

float Camera::getSpeedOffset()
{
	return m_speedOffset;
}

float Camera::getAngleX()
{
	return m_rotX + m_recoilX + m_runningRecoilX + m_accuracyX;
}

float Camera::getAngleY()
{
	return m_rotY + m_recoilY + m_runningRecoilY + m_accuracyY;
}

D3DXMATRIXA16 Camera::getMatWorld()
{
	return m_matWorld;
}

void Camera::setPos(D3DXVECTOR3 p)
{
	pos = p;
}

void Camera::setPosY(float y)
{
	pos.y = y;
}

void Camera::setFreeCameraMode(bool f)
{
	m_freeCameraMode = f;
}

bool Camera::getFreeCameraMode()
{
	return m_freeCameraMode;
}

int Camera::getCooldown()
{
	return m_cooldown;
}

int Camera::getMagazine()
{
	return m_magazine;
}

void Camera::getPMobFromUnitBox(vector<Mob*>* mob)
{
	m_pMob = *mob;
}
