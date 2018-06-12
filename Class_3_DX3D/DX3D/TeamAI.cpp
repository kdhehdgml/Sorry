#include "stdafx.h"
#include "TeamAI.h"
#include "CubemanParts.h"
#include "Ray.h"

TeamAI::TeamAI()
{
	m_pRootParts = NULL;

	m_isMoving = false;
	m_isShoot = false;

	//m_baseRotY = D3DX_PI / 2;
	
	m_forward.z = -1;
	m_pos.y = 3.0f;
	m_destPos = m_pos;
	m_move = false;
	num = 0;
	m_moveSpeed = 0.4f;

	m_pSphere = NULL;
	health = 100;
	status = 1;
}


TeamAI::~TeamAI()
{
	m_pRootParts->ReleaseAll();
	SAFE_RELEASE(m_pSphere);
	SAFE_DELETE(m_pBoundingSphere);
}

void TeamAI::Init()
{
	g_pObjMgr->AddToTagList(TAG_TEAM, this);
	
	D3DXCreateSphere(g_pDevice, 2.5f, 10, 10, &m_pSphere, NULL);
	
	CreateAllParts();
	m_moveSpeed = GSM().mobSpeed;

	m_pBoundingSphere = new BoundingSphere(m_pos, 2.5f);
	
}

void TeamAI::Update()
{
	if (health <= 0) {
		status = 0;
	}
	if (status > 0) {
		UpdatePositionToDestination();
		//UpdatePosition();

		m_pBoundingSphere->center = m_pos;
		m_pBoundingSphere->center.y += 3.0f;

		m_pRootParts->SetMovingState(m_isMoving);
		m_pRootParts->Update();
	}
}

void TeamAI::Render()
{
	g_pDevice->SetRenderState(D3DRS_FOGENABLE, true);
	g_pDevice->SetRenderState(D3DRS_FOGCOLOR, 0xffbbbbbb);
	g_pDevice->SetRenderState(D3DRS_FOGDENSITY, FtoDw(0.3f)); //강도 0~1f
															  //안개적용되는 최소 거리
	g_pDevice->SetRenderState(D3DRS_FOGSTART, FtoDw(GSM().fogMin));
	//안개 최대치로 적용되는 거리
	g_pDevice->SetRenderState(D3DRS_FOGEND, FtoDw(GSM().fogMax));
	g_pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	if (status > 0) {
		g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
		m_pRootParts->Render();

		D3DXMATRIXA16 matI;
		D3DXMatrixIdentity(&matI);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pDevice->SetTransform(D3DTS_WORLD, &matI);
		g_pDevice->SetFVF(VERTEX_PC::FVF);
		g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST,
			1, &Shootpos[0], sizeof(VERTEX_PC));

		D3DXMATRIXA16 mat;
		D3DXMatrixTranslation(&mat, m_pBoundingSphere->center.x, m_pBoundingSphere->center.y, m_pBoundingSphere->center.z);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->SetTexture(0, NULL);
		//m_pSphere->DrawSubset(0);
	}
}

BoundingSphere * TeamAI::getBoundingSphere()
{
	return m_pBoundingSphere;
}

int TeamAI::getHealth()
{
	return health;
}

void TeamAI::setHealth(int h)
{
	health = h;
}

int TeamAI::getStatus()
{
	return status;
}

void TeamAI::setStatus(int s)
{
	status = s;
}

vector<Mob*>* TeamAI::getPMob()
{
	return &m_pMob;
}

void TeamAI::CreateAllParts()
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

void TeamAI::CreateParts(CubemanParts *& pParts, 
	IDisplayObject * pParent, D3DXVECTOR3 pos, 
	D3DXVECTOR3 scale, D3DXVECTOR3 trans, 
	vector<vector<int>>& vecUV)
{
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&matT, trans.x, trans.y, trans.z);
	mat = matS * matT;
	pParts->Init(&mat, vecUV);
	pParts->SetPosition(&pos);
	pParent->AddChild(pParts);
}

bool TeamAI::MobSearch(TeamAI * _team)
{
	D3DXVECTOR3 move_forward;
	move_forward = D3DXVECTOR3(_team->m_destPos.x - _team->m_pos.x, 0, _team->m_destPos.z - _team->m_pos.z);
	if (D3DXVec3LengthSq(&move_forward) > 0)
	{
		_team->forward = D3DXVECTOR3(_team->m_destPos.x - _team->m_pos.x, 0, _team->m_destPos.z - _team->m_pos.z);
	}
	int number = 0;
	for (auto p : (g_pObjMgr->FindObjectsByTag(TAG_MOB)))
	{
		D3DXVECTOR3 DirectPM;
		D3DXVECTOR3 MobPos;

		DirectPM = p->GetPosition() - _team->m_pos;
		if (DirectPM.x < 80 && DirectPM.z < 15)
		{
			DirectPM.y = _team->m_pos.y;
			D3DXVECTOR3 DirectPMnormal = DirectPM;
			D3DXVec3Normalize(&DirectPMnormal, &DirectPMnormal);
			D3DXVec3Normalize(&_team->forward, &_team->forward);
			float Length = abs(p->GetPosition().x - _team->m_pos.x + p->GetPosition().z - _team->m_pos.z);
			float DotPM = D3DXVec3Dot(&DirectPMnormal, &_team->forward);
			float direct = 1.0f / 2.0f;

			if ((Length < 100 && DotPM >= direct))
			{
				m_isShoot = true;
				m_MobNum = number;
				return true;
			}
		}
		number++;
	}
	m_isShoot = false;
	return false;
}

void TeamAI::ShootVertex(TeamAI * _team)
{
	Ray * ray;
	ray = new Ray();

	D3DXVECTOR3 move_forward;
	move_forward = D3DXVECTOR3(_team->m_destPos.x - _team->m_pos.x, 0, _team->m_destPos.z - _team->m_pos.z);
	if (D3DXVec3LengthSq(&move_forward) > 0)
	{
		_team->forward = D3DXVECTOR3((_team->m_destPos.x+ 3) - _team->m_pos.x, _team->m_pos.y, _team->m_destPos.z - _team->m_pos.z);
	}
	else
	{
		_team->forward = D3DXVECTOR3((_team->m_destPos.x + 3) - _team->m_pos.x, _team->m_pos.y, _team->m_destPos.z - _team->m_pos.z);
	}
	D3DXVECTOR3 forwardNomal = _team->forward;
	D3DXVec3Normalize(&forwardNomal, &forwardNomal);
	D3DCOLOR c = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR d = D3DCOLOR_XRGB(0, 255, 0);
	//D3DXVECTOR3 directPMnor = Ppos - _team->m_pos;
	ray->m_pos = { _team->m_pos.x,  _team->m_pos.y + 4.0f, _team->m_pos.z };
	if (m_isShoot == true)
	{
	ray->m_dir = { g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->GetPosition().x ,
		g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->GetPosition().y + 4.0f,
		g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->GetPosition().z };
		Shootpos[0] = (VERTEX_PC(ray->m_pos, c));
		Shootpos[1] = (VERTEX_PC(ray->m_dir, c));
	}
	else
	{
		Shootpos[0] = (VERTEX_PC(ray->m_pos, d));
		Shootpos[1] = (VERTEX_PC(ray->m_pos + (forwardNomal*5), d));
	}

	/*if(ray.CalcIntersectTri(&m_vecObstacle[i], &intersectionDist))
	{
	}*/
}
