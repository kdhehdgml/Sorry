#include "stdafx.h"
#include "TeamAI.h"
#include "CubemanParts.h"
#include "Ray.h"
#include "TEAM_TEX.h"

TeamAI::TeamAI()
{
	m_TEAM_TEX = NULL;//몬스터 클래스 추가

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
	SAFE_RELEASE(m_TEAM_TEX);
	SAFE_RELEASE(m_pSphere);
	SAFE_DELETE(m_pBoundingSphere);
}

void TeamAI::Init()
{
	g_pObjMgr->AddToTagList(TAG_TEAM, this);
	
	D3DXCreateSphere(g_pDevice, 3.0f, 10, 10, &m_pSphere, NULL);

	m_TEAM_TEX = new TEAM_TEX;
	m_TEAM_TEX->Init();


	
	m_moveSpeed = GSM().mobSpeed;

	m_pBoundingSphere = new BoundingSphere(m_pos, 3.0f);
	
}

void TeamAI::Update()
{
	if (health <= 0) {
		status = 0;
	}
	if (status > 0) {
		UpdatePositionToDestination();
		//UpdatePosition();

		if (MobSearch() == true)
		{
			//m_pTeam[i]->SetDestination(m_pCubeman->GetPosition());
			//m_pTeam[i]->UpdatePositionToDestination();
		}
		ShootVertex();

		m_pBoundingSphere->center = m_pos;
		m_pBoundingSphere->center.y += 4.0f;

		m_TEAM_TEX->SetPos(m_pos);
		m_TEAM_TEX->Update();

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
	if (status > 0) 
	{
		//g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	



		D3DXMATRIXA16 matI;
		D3DXMatrixIdentity(&matI);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pDevice->SetTransform(D3DTS_WORLD, &matI);
		g_pDevice->SetFVF(VERTEX_PC::FVF);
		g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST,
			1, &Shootpos[0], sizeof(VERTEX_PC));

		m_TEAM_TEX->Render();
		/*D3DXMATRIXA16 mat;
		D3DXMatrixTranslation(&mat, m_pBoundingSphere->center.x, m_pBoundingSphere->center.y, m_pBoundingSphere->center.z);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->SetTexture(0, NULL);
		m_pSphere->DrawSubset(0);*/
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

bool TeamAI::MobSearch()
{
	if (g_pObjMgr->FindObjectsByTag(TAG_MOB).size() > 0)
	{
		D3DXVECTOR3 move_forward;
		move_forward = D3DXVECTOR3(m_destPos.x - m_pos.x, 0, m_destPos.z - m_pos.z);
		if (D3DXVec3LengthSq(&move_forward) > 0)
		{
			forward = D3DXVECTOR3(m_destPos.x - m_pos.x, 0, m_destPos.z - m_pos.z);
		}
		int number = 0;

		for (auto p : (g_pObjMgr->FindObjectsByTag(TAG_MOB)))
		{
			D3DXVECTOR3 DirectPM;
			D3DXVECTOR3 MobPos;

			DirectPM = p->GetPosition() - m_pos;
			if (DirectPM.x < 80 && DirectPM.z < 15)
			{
				DirectPM.y = m_pos.y;
				D3DXVECTOR3 DirectPMnormal = DirectPM;
				D3DXVec3Normalize(&DirectPMnormal, &DirectPMnormal);
				D3DXVec3Normalize(&forward, &forward);
				float Length = abs(p->GetPosition().x - m_pos.x + p->GetPosition().z - m_pos.z);
				float DotPM = D3DXVec3Dot(&DirectPMnormal, &forward);
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
}

void TeamAI::ShootVertex()
{
	Ray * ray;
	ray = new Ray();

	D3DXVECTOR3 move_forward;
	move_forward = D3DXVECTOR3(m_destPos.x - m_pos.x, 0, m_destPos.z - m_pos.z);
	forward = D3DXVECTOR3((m_destPos.x + 3) - m_pos.x, m_pos.y, m_destPos.z - m_pos.z);
	D3DXVECTOR3 forwardNormal = forward;
	D3DXVec3Normalize(&forwardNormal, &forwardNormal);
	D3DCOLOR c = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR d = D3DCOLOR_XRGB(0, 255, 0);
	//D3DXVECTOR3 directPMnor = Ppos - m_pos;
	ray->m_pos = { m_pos.x,  m_pos.y + 4.0f, m_pos.z };
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
		Shootpos[1] = (VERTEX_PC(ray->m_pos + (forwardNormal*5), d));
	}

	/*if(ray.CalcIntersectTri(&m_vecObstacle[i], &intersectionDist))
	{
	}*/
}
