#include "stdafx.h"
#include "Cubeman.h"
#include "CubemanParts.h"

Cubeman::Cubeman()
{
	m_pRootParts = NULL;

	m_isMoving = false;
	m_moveSpeed = 0.2f;
	m_currMoveSpeedRate = 1.0f;
	m_rotationSpeed = 0.1f;

	m_isJumping = false;
	m_jumpPower = 1.0f;
	m_gravity = 0.05f;
	m_currGravity = 0.0f;

	m_maxStepHeight = 2.0f;
	m_baseRotY = D3DX_PI;

	m_forward.z = -1;
	m_pos.y = 3.0f;
	m_destPos = m_pos;

	m_deltaYPos = 7.0f;
	//m_freeCameraMode = true;
}


Cubeman::~Cubeman()
{
	m_pRootParts->ReleaseAll();
}

void Cubeman::Init()
{
	g_pObjMgr->AddToTagList(TAG_PLAYER, this);
	//g_pCamera->SetTarget(&m_pos);
	//g_pKeyboardManager->SetMovingTarget(&m_deltaPos,
	//	&m_deltaRot, &m_isJumping);

	g_pKeyboardManager->SetMovingTarget(&m_keyState);

	CreateAllParts();

	// 실행 시 자동으로 프리카메라 모드
	g_pCamera->setFreeCameraMode(true);
	m_deltaYPos = 70.0f;

	/*D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.5f, 0.5f, 1);
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 150, 150, 0);
	m_matWorld = matS * matT;*/
}

void Cubeman::Update()
{
	//UpdatePosition();
	//IUnitObject::UpdateKeyboardState();
	IUnitObject::UpdatePositionToDestination();
	UpdatePosition();
	UpdatePositionToCamera();

	/*if (GetAsyncKeyState('1') & 0x0001)
	{
		m_isTurnedOnLight = !m_isTurnedOnLight;
	}*/
	if (GetAsyncKeyState('V') & 0x0001) {
		//m_freeCameraMode = !m_freeCameraMode;
		g_pCamera->setFreeCameraMode(!g_pCamera->getFreeCameraMode());
		if (g_pCamera->getFreeCameraMode()) {
			m_deltaYPos = 70.0f;
			ShowCursor(true);
		}
		else {
			m_deltaYPos = 7.0f;
			ShowCursor(false);
		}
	}
	if (g_pCamera->getFreeCameraMode()) {
		if (GetAsyncKeyState('R') & 0x8000) {
			m_deltaYPos += 1.0f;
		}
		else if (GetAsyncKeyState('F') & 0x8000) {
			m_deltaYPos -= 1.0f;
		}
	}

	if (m_isTurnedOnLight == true)
	{
		D3DXVECTOR3 pos = m_pos;
		D3DXVECTOR3 dir = m_forward;
		D3DXCOLOR c = BLUE;
		D3DLIGHT9 light = DXUtil::InitSpot(&dir, &pos, &c);
		light.Phi = D3DX_PI / 4;
		//D3DLIGHT9 light = DXUtil::InitPoint(&pos, &c);
		g_pDevice->SetLight(10, &light);
	}
	g_pDevice->LightEnable(10, m_isTurnedOnLight);

	m_pRootParts->SetMovingState(m_isMoving);
	m_pRootParts->Update();
	
}

void Cubeman::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	//m_pRootParts->Render();
}

void Cubeman::UpdatePosition()
{

	
	m_rot += m_deltaRot * m_rotationSpeed;

	D3DXMATRIXA16 matRotY;
	D3DXMatrixRotationY(&matRotY, m_rot.y);
	D3DXVec3TransformNormal(&m_forward, 
		&D3DXVECTOR3(0, 0, 1), &matRotY);

	D3DXVECTOR3 targetPos;
	float basePosY = 0;
	bool	isIntersected = true;
	float	height = 0;

	if (m_isJumping == true)
	{
		m_currMoveSpeedRate = 0.7f;
		targetPos = m_pos + m_forward * m_deltaPos.z
			* m_moveSpeed * m_currMoveSpeedRate;

		targetPos.y += m_jumpPower - m_currGravity;
		m_currGravity += m_gravity;

		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
		}

		if (isIntersected == false)
		{
			if (g_pCurrentMap != NULL)
			{
				isIntersected = g_pCurrentMap->GetHeight(height, m_pos);
			}
			m_pos.y = targetPos.y;
		}
		else
		{
			m_pos = targetPos;
		}

		if (m_pos.y <= height && m_jumpPower < m_currGravity)
		{
			m_pos.y = height;
			m_isJumping = false;
			m_currGravity = 0;
			m_currMoveSpeedRate = 1.0f;
		}
		//m_pos = targetPos;
	}
	else //m_isJumping == false
	{
		targetPos = m_pos + m_forward * m_deltaPos.z
			* m_moveSpeed * m_currMoveSpeedRate;

		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
			int tmp = 0;
			if (isIntersected == false || fabs(height - m_pos.y) > m_maxStepHeight)
			{

			}
			else
			{
				targetPos.y = height;
				m_pos = targetPos;
			}
		}
		else
		{
			m_pos = targetPos;
		}

		//m_pos = targetPos;
		
	}

	D3DXVECTOR3 v = g_pCamera->getDir();

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	m_matWorld = matRotY * matT;

	if (D3DXVec3LengthSq(&m_deltaRot) > D3DX_16F_EPSILON ||
		D3DXVec3LengthSq(&m_deltaPos) > D3DX_16F_EPSILON)
		m_isMoving = true;
	else
		m_isMoving = false;

	//카메라 높이를 캐릭터 위치에 맞게 조정
	g_pCamera->setPosY(m_pos.y + m_deltaYPos);
}

void Cubeman::UpdatePositionToCamera()
{
	//캐릭터 위치를 카메라 위치로 변경
	m_pos.x = g_pCamera->getPos().x;
	m_pos.z = g_pCamera->getPos().z;
	//m_pos.z -= 10.0f;
	//m_forward = g_pCamera->getDir();
	//m_matWorld = g_pCamera->getMatWorld();
}

void Cubeman::CreateAllParts()
{
	CubemanParts* pParts;
	//몸통
	m_pRootParts = new CubemanParts();
	CreateParts(m_pRootParts, this, D3DXVECTOR3(0.0f, 3.0f, 0.0f),
		D3DXVECTOR3(1.0f, 1.0f, 0.5f), D3DXVECTOR3(0, 0, 0), uvBody);
	//머리
	pParts = new CubemanParts();
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(0.0f, 1.6f, 0.0f),
		D3DXVECTOR3(0.8f, 0.8f, 0.8f), D3DXVECTOR3(0, 0, 0), uvHead);
	//왼팔
	pParts = new CubemanParts(0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-1.5f, 1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLArm);
	//오른팔
	pParts = new CubemanParts(-0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(1.5f, 1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvRArm);
	//왼다리
	pParts = new CubemanParts(-0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-0.5f, -1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLLeg);
	//오른다리
	pParts = new CubemanParts(0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(0.5f, -1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvRLeg);

}

void Cubeman::CreateParts(CubemanParts *& pParts,
	IDisplayObject * pParent, D3DXVECTOR3 pos, 
	D3DXVECTOR3 scale, D3DXVECTOR3 trans,
	vector<vector<int>> &vecUV)
{
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&matT, trans.x, trans.y, trans.z);
	mat = matS * matT;
	pParts->Init(&mat, vecUV);
	pParts->SetPosition(&pos);
	pParent->AddChild(pParts);
}
