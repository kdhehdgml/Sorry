#include "stdafx.h"
#include "Mob.h"
#include "CubemanParts.h"
#include "Ray.h"
Mob::Mob()
{
	m_pRootParts = NULL;

	m_isMoving = false;
	m_moveSpeed = 0.2f;
	m_currMoveSpeedRate = 1.0f;
	m_rotationSpeed = 0.1f;
	m_isShoot = false;
	m_isJumping = false;
	m_jumpPower = 1.0f;
	m_gravity = 0.05f;
	m_currGravity = 0.0f;

	m_maxStepHeight = 2.0f;
	m_baseRotY = D3DX_PI;

	m_forward.z = -1;
	m_pos.y = 3.0f;

	m_destPos = m_pos;
}


Mob::~Mob()
{
	m_pRootParts->ReleaseAll();
}

void Mob::Init()
{
	IUnitObject::m_moveSpeed = 0.1f;
	g_pObjMgr->AddToTagList(TAG_MOB, this);
	/*g_pKeyboardManager->SetMovingTarget(&m_deltaPos,
		&m_deltaRot, &m_isJumping);*/
	CreateAllParts();
}

void Mob::Update()
{

	

	//UpdatePosition();
	IUnitObject::UpdateKeyboardState();
	IUnitObject::UpdatePositionToDestination();

	//if (GetAsyncKeyState('1') & 0x0001)
	//{
	//	m_isTurnedOnLight = !m_isTurnedOnLight;
	//}

	//if (m_isTurnedOnLight == true)
	//{
	//	D3DXVECTOR3 pos = m_pos;
	//	D3DXVECTOR3 dir = m_forward;
	//	D3DXCOLOR c = BLUE;
	//	D3DLIGHT9 light = DXUtil::InitSpot(&dir, &pos, &c);
	//	light.Phi = D3DX_PI / 4;
	//	//D3DLIGHT9 light = DXUtil::InitPoint(&pos, &c);
	//	g_pDevice->SetLight(10, &light);
	//}
	//g_pDevice->LightEnable(10, m_isTurnedOnLight);

	m_pRootParts->SetMovingState(m_isMoving);
	m_pRootParts->Update();

}

void Mob::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pRootParts->Render();

	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pDevice->SetFVF(VERTEX_PC::FVF);
	g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		1, &Shootpos[0], sizeof(VERTEX_PC));
}

void Mob::UpdatePosition()
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

	targetPos = m_pos + m_forward * m_deltaPos.z
		* m_moveSpeed * m_currMoveSpeedRate;

	if (g_pCurrentMap != NULL)
	{
		isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
		int tmp = 0;
		if (isIntersected == false || fabs(height - m_pos.y) > m_maxStepHeight)
		{
			m_pos.y = height;
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

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	m_matWorld = matRotY * matT;

	if (D3DXVec3LengthSq(&m_deltaRot) > D3DX_16F_EPSILON ||
		D3DXVec3LengthSq(&m_deltaPos) > D3DX_16F_EPSILON)
		m_isMoving = true;
	else
		m_isMoving = false;
}

void Mob::CreateAllParts()
{
	CubemanParts* pParts;
	//¸öÅë
	m_pRootParts = new CubemanParts();
	CreateParts(m_pRootParts, this, D3DXVECTOR3(0.0f, 3.0f, 0.0f),
		D3DXVECTOR3(1.0f, 1.0f, 0.5f), D3DXVECTOR3(0, 0, 0), uvBody);
	//¸Ó¸®
	pParts = new CubemanParts();
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(0.0f, 1.6f, 0.0f),
		D3DXVECTOR3(0.8f, 0.8f, 0.8f), D3DXVECTOR3(0, 0, 0), uvHead);
	//¿ÞÆÈ
	pParts = new CubemanParts(0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-1.5f, 1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLArm);
	//¿À¸¥ÆÈ
	pParts = new CubemanParts(-0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(1.5f, 1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvRArm);
	//¿Þ´Ù¸®
	pParts = new CubemanParts(-0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-0.5f, -1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLLeg);
	//¿À¸¥´Ù¸®
	pParts = new CubemanParts(0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(0.5f, -1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvRLeg);
}

void Mob::CreateParts(CubemanParts *& pParts,
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

bool Mob::PlayerSearch(D3DXVECTOR3 Ppos, Mob* mob)
{
	
	D3DXVECTOR3 move_forward;
	move_forward = D3DXVECTOR3(mob->m_destPos.x - mob->m_pos.x, 0, mob->m_destPos.z - mob->m_pos.z);
	if (D3DXVec3LengthSq(&move_forward) > 0)
	{
		mob->forward = D3DXVECTOR3(mob->m_destPos.x - mob->m_pos.x, 0, mob->m_destPos.z - mob->m_pos.z);
	}
	

	D3DXVECTOR3 DirectPM;
	D3DXVECTOR3 MobPos;
	DirectPM = Ppos - mob->m_pos;
	DirectPM.y = 0;
	D3DXVECTOR3 DirectPMnormal = DirectPM;
	D3DXVec3Normalize(&DirectPMnormal, &DirectPMnormal);
	D3DXVec3Normalize(&mob->forward, &mob->forward);
	float Length = abs(Ppos.x - mob->m_pos.x + Ppos.z - mob->m_pos.z);
	float DotPM = D3DXVec3Dot(&DirectPMnormal, &mob->forward);
	float direct = sqrt(3) / 2.0f;
	/*Debug->AddText("¸÷À§Ä¡");
	Debug->AddText(DotPM);
	Debug->EndLine();*/
	Debug->AddText("°¢µµ");
	Debug->AddText(forward);
	Debug->EndLine();
	if ((Length < 15 && DotPM >= direct))
	{
		m_isShoot = true;
		return true;
	}
		
	m_isShoot = false;
	return false;
}

void Mob::ShootVertex(D3DXVECTOR3 Ppos, Mob* mob)
{
	Ray * ray;
	ray = new Ray();

	D3DXVECTOR3 move_forward;
	move_forward = D3DXVECTOR3(mob->m_destPos.x - mob->m_pos.x, 0, mob->m_destPos.z - mob->m_pos.z);
	if (D3DXVec3LengthSq(&move_forward) > 0)
	{
		mob->forward = D3DXVECTOR3(mob->m_destPos.x - mob->m_pos.x, 0, mob->m_destPos.z - mob->m_pos.z);
	}
	
	D3DCOLOR c = D3DCOLOR_XRGB(255,0,0);
	D3DCOLOR d = D3DCOLOR_XRGB(0, 255, 0);
	//D3DXVECTOR3 directPMnor = Ppos - mob->m_pos;
	ray->m_pos = { mob->m_pos.x,  mob->m_pos.y + 4.0f, mob->m_pos.z};
	
	ray->m_dir = { Ppos.x , Ppos.y + 4.0f, Ppos.z};
	if (m_isShoot == true)
	{
		Shootpos[0] = (VERTEX_PC(ray->m_pos, c));
		Shootpos[1] = (VERTEX_PC(ray->m_dir, c));
	}
	else
	{
		Shootpos[0] = (VERTEX_PC(ray->m_pos, d));
		Shootpos[1] = (VERTEX_PC(ray->m_dir, d));
	}
	
	/*if(ray.CalcIntersectTri(&m_vecObstacle[i], &intersectionDist))
	{
	}*/

	
}
