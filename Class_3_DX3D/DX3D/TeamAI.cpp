#include "stdafx.h"
#include "TeamAI.h"
#include "CubemanParts.h"
#include "TEAM_TEX.h"

TeamAI::TeamAI()
{
	m_TEAM_TEX = NULL;//몬스터 클래스 추가
	m_MobNum = NULL;
	m_isMoving = false;
	m_isShoot = false;

	//m_baseRotY = D3DX_PI / 2;
	m_Action = 팀_공격;
	m_forward.z = -1;
	m_pos.y = 3.0f;
	m_destPos = m_pos;
	m_move = false;
	num = 0;
	m_moveSpeed = 0.4f;
	m_CooldownTime = 0;
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
		m_pos = { 1000,10,-1000 };
	}
	if (status > 0) {
		UpdatePositionToDestination();
		//UpdatePosition();

		m_pBoundingSphere->center = m_pos;
		m_pBoundingSphere->center.y += 4.0f;

		m_TEAM_TEX->SetPos(m_pos);
		m_TEAM_TEX->Update();
	}
}

void TeamAI::Render()
{
	//g_pDevice->SetRenderState(D3DRS_FOGENABLE, true);
	//g_pDevice->SetRenderState(D3DRS_FOGCOLOR, 0xffbbbbbb);
	//g_pDevice->SetRenderState(D3DRS_FOGDENSITY, FtoDw(0.3f)); //강도 0~1f
	//														  //안개적용되는 최소 거리
	//g_pDevice->SetRenderState(D3DRS_FOGSTART, FtoDw(GSM().fogMin));
	////안개 최대치로 적용되는 거리
	//g_pDevice->SetRenderState(D3DRS_FOGEND, FtoDw(GSM().fogMax));
	//g_pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	if (status > 0) 
	{
		//g_pDevice->SetRenderState(D3DRS_LIGHTING, false);

		//g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
		m_TEAM_TEX->Render();



		D3DXMATRIXA16 matI;
		D3DXMatrixIdentity(&matI);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pDevice->SetTransform(D3DTS_WORLD, &matI);
		g_pDevice->SetFVF(VERTEX_PC::FVF);
		g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST,
			1, &Shootpos[0], sizeof(VERTEX_PC));

	


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

D3DXMATRIXA16 TeamAI::getMatWorld()
{
	return m_matWorld;
}

bool TeamAI::MobSearch()
{
	if (g_pObjMgr->FindObjectsByTag(TAG_MOB).size() > 0)
	{
		D3DXVECTOR3 move_forward;
		move_forward = D3DXVECTOR3(m_destPos.x - m_pos.x, 0, m_destPos.z - m_pos.z);
		if (D3DXVec3LengthSq(&move_forward) > 0)
		{
			forward = move_forward;
		}
		int number = 0;
		
		for (auto p : (g_pObjMgr->FindObjectsByTag(TAG_MOB)))
		{
			D3DXVECTOR3 DirectPM;

			DirectPM = p->GetPosition() - m_pos;
			if (DirectPM.x < 90 && DirectPM.z < 25)
			{
				DirectPM.y = m_pos.y;
				D3DXVECTOR3 DirectPMnormal = DirectPM;
				D3DXVec3Normalize(&DirectPMnormal, &DirectPMnormal);
				D3DXVec3Normalize(&forward, &forward);
				float Length = abs(p->GetPosition().x - m_pos.x + p->GetPosition().z - m_pos.z);
				float DotPM = D3DXVec3Dot(&DirectPMnormal, &forward);
				float direct = 1.0f / 2.0f;
				
				if (Length < 15)
				{
					m_isShoot = true;
					m_MobNum = number;
					return true;
				}
				else if (Length < 30 && DotPM >= direct)
				{
					m_isShoot = true;
					if (m_MobNum == NULL)
					{
						m_MobNum = number;
					}
					return true;
				}
				else if (Length < 110 && DotPM >= direct)
				{
					m_isShoot = true;
					if (m_MobNum == NULL)
					{
						m_MobNum = number;
					}
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
	D3DXVECTOR3 myPos = D3DXVECTOR3(m_pos.x, m_pos.y + 4.0f, m_pos.z);
	D3DXVECTOR3 forward = D3DXVECTOR3(myPos.x, myPos.y, myPos.z);
	D3DCOLOR c = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR d = D3DCOLOR_XRGB(0, 255, 0);
	//D3DXVECTOR3 directPMnor = Ppos - m_pos;

	if (m_isShoot == true)
	{
		D3DXVECTOR3 Direction = { g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->GetPosition().x ,
		g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->GetPosition().y + 4.0f,
		g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->GetPosition().z };
		Shootpos[0] = (VERTEX_PC(myPos, c));
		Shootpos[1] = (VERTEX_PC(Direction, c));

		float kill = rand() % 10;

		m_CooldownTime++;
		
		if (m_CooldownTime > 50)
		{
			if (kill < 5)
			{
				int damage = rand() % 10;
				if (damage < 3)
				{
					g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->setHealth(0);
				}
				else
				{
					g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->setHealth(g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->getHealth() - 50);
				}
				if (g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->getHealth() <= 0)
				{
					m_MobNum = NULL;
				}
			}
			m_CooldownTime = 0;
			m_Action = TEAM_STATE(rand() % 2);
		}
	}
	else
	{
		Shootpos[0] = (VERTEX_PC(myPos, d));
		Shootpos[1] = (VERTEX_PC(forward, d));
	}
	
	/*if(ray.CalcIntersectTri(&m_vecObstacle[i], &intersectionDist))
	{
	}*/
}
