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
	

	FOV = D3DX_PI / 4.0f;
	speedOffset = 0.4f;
	freeCameraMode = true;
	sensitivity = 200.0f;
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
	currPoint = p;
	m_ptPrevMouse = currPoint;

	loadingComplete = false;

	D3DXMatrixLookAtLH(&m_matView,
		&m_eye, &m_lookAt, &m_up);
	g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj,
		FOV, rc.right / (float)rc.bottom, 1.0f, 10000.0f);
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
	D3DXMatrixPerspectiveFovLH(&matProj, FOV, rc.right / (float)rc.bottom, 1.0f, 10000.0f);
	g_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_matWorld = matWorld;
	m_matView = matView;
	m_matProj = matProj;



	if (GetKeyState('A') & 0x8000)
	{
		D3DXVECTOR3 v;
		D3DXVec3Cross(&v, &dir, &D3DXVECTOR3(0, 1, 0));
		pos.x += (v.x* speedOffset);
		pos.z += (v.z* speedOffset);
	}
	else if (GetKeyState('D') & 0x8000)
	{
		D3DXVECTOR3 v;
		D3DXVec3Cross(&v, &dir, &D3DXVECTOR3(0, 1, 0));
		pos.x -= (v.x* speedOffset);
		pos.z -= (v.z* speedOffset);
	}

	if (GetKeyState('W') & 0x8000)
	{
		pos.x += (dir.x* speedOffset);
		pos.z += (dir.z* speedOffset);
	}
	else if (GetKeyState('S') & 0x8000)
	{
		pos.x -= (dir.x* speedOffset);
		pos.z -= (dir.z* speedOffset);
	}

	if (GetKeyState(VK_SHIFT) & 0x8000) {
		if (freeCameraMode) {
			speedOffset = 4.0f;
		}
		else {
			speedOffset = 0.8f;
		}
	}
	else {
		if (freeCameraMode) {
			speedOffset = 2.0f;
		}
		else {
			speedOffset = 0.4f;
		}
	}

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

	if (g_pTimeManager->GetDeltaTime() > 0.001f) { //DeltaTime이 Epsilon보다 크면 로딩이 완료된 걸로 간주
		loadingComplete = true;
		ShowCursor(false);
	}
}

void Camera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_isLbuttonDown = true;
		//m_ptPrevMouse.x = LOWORD(lParam);
		//m_ptPrevMouse.y = HIWORD(lParam);
	}
	break;
	case WM_LBUTTONUP:
	{
		m_isLbuttonDown = false;
	}
	break;
	case WM_RBUTTONDOWN:
		FOV = D3DX_PI / 8;
		sensitivity = 800.0f;
		break;
	case WM_RBUTTONUP:
		FOV = D3DX_PI / 4;
		sensitivity = 200.0f;
		break;
	case WM_MOUSEMOVE:
	{
		//POINT currPoint;
		currPoint.x = LOWORD(lParam);
		currPoint.y = HIWORD(lParam);
		if (loadingComplete)
		{
			float diff_x = currPoint.x - m_ptPrevMouse.x;
			float diff_y = currPoint.y - m_ptPrevMouse.y;

			if (diff_x == 0 && diff_y == 0) {
				break;
			}

			m_rotY += diff_x / sensitivity;
			m_rotX -= diff_y / sensitivity;

			if (m_rotX <= -D3DX_PI * 0.5f + D3DX_16F_EPSILON)
			{
				m_rotX = -D3DX_PI * 0.5f + D3DX_16F_EPSILON;
			}
			if (m_rotX >= D3DX_PI * 0.3f - D3DX_16F_EPSILON)
			{
				m_rotX = D3DX_PI * 0.3f - D3DX_16F_EPSILON;
			}

			dir.x = sin(m_rotY);
			dir.z = cos(m_rotY);
			dir.y = tan(m_rotX);

			m_ptPrevMouse = currPoint;
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
			m_ptPrevMouse = currPoint;
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
	return FOV;
}

float Camera::getSpeedOffset()
{
	return speedOffset;
}

D3DXMATRIXA16 Camera::getMatWorld()
{
	return m_matWorld;
}

void Camera::setPos(D3DXVECTOR3)
{
}

void Camera::setPosY(float y)
{
	pos.y = y;
}

void Camera::setFreeCameraMode(bool f)
{
	freeCameraMode = f;
}