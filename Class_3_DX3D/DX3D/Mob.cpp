#include "stdafx.h"
#include "Mob.h"
#include "CubemanParts.h"
#include "MONSTER.h"
Mob::Mob()
{
//	m_pRootParts = NULL;
	m_MONSTER = NULL;//몬스터 클래스 추가
	m_isMoving = false;
	m_isShoot = false;
	m_ShootCooldownTime = 0;
	//m_baseRotY = D3DX_PI;
	m_bullet = 5;

	m_TeamAINum = NULL;
	m_forward.z = -1;
	m_pos.y = 3.0f;
	m_destPos = m_pos;
	m_move = false;
	num = 0;
	m_moveSpeed = 0.4f;

	m_pSphereBody = NULL;
	m_pSphereHead = NULL;
	health = 100;
	status = 1;
	m_BeDetermined = false;
}


Mob::~Mob()
{
	//m_pRootParts->ReleaseAll();
	SAFE_RELEASE(m_MONSTER);
	SAFE_RELEASE(m_pSphereBody);
	SAFE_RELEASE(m_pSphereHead);
	SAFE_DELETE(m_pBoundingSphereBody);
	SAFE_DELETE(m_pBoundingSphereHead);
	
}

void Mob::Init()
{
	g_pObjMgr->AddToTagList(TAG_MOB, this);

	D3DXCreateSphere(g_pDevice, 1.5f, 10, 10, &m_pSphereHead, NULL);
	m_pBoundingSphereHead = new BoundingSphere(m_pos, 1.5f);
	D3DXCreateSphere(g_pDevice, 2.0f, 10, 10, &m_pSphereBody, NULL);
	m_pBoundingSphereBody = new BoundingSphere(m_pos, 2.0f);

	m_MONSTER = new MONSTER;
	m_MONSTER->Init();
	SaveAction();

	//CreateAllParts();
	IUnitObject::m_moveSpeed = GSM().mobSpeed;
	
	//m_pMob[i]->SetPosition(&D3DXVECTOR3(50.0f, 5.0f, (i + 1) * 10));
}

void Mob::Update()
{
	if (health <= 0) {
		status = 0;
		m_pos = { 1000,10,1000 };
	}
	if (status > 0) {
		IUnitObject::UpdateKeyboardState();
		IUnitObject::UpdatePositionToDestination();
		
		m_pBoundingSphereBody->center = m_pos;
		m_pBoundingSphereBody->center.y += 2.0f;
		m_pBoundingSphereHead->center = m_pos;
		m_pBoundingSphereHead->center.y += 5.0f;

		//m_pRootParts->SetMovingState(m_isMoving);
		//m_pRootParts->Update();
		m_MONSTER->SetPos(m_pos);
		m_MONSTER->Update();

		Debug->AddText("몹 체력:");
		Debug->AddText(health);
		Debug->EndLine();
	}
}

void Mob::Render()
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
		//m_pRootParts->Render();
		m_MONSTER->Render();

		D3DXMATRIXA16 matI;
		D3DXMatrixIdentity(&matI);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pDevice->SetTransform(D3DTS_WORLD, &matI);
		g_pDevice->SetFVF(VERTEX_PC::FVF);
		g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST,
			1, &Shootpos[0], sizeof(VERTEX_PC));

		D3DXMATRIXA16 mat;
		D3DXMatrixTranslation(&mat, m_pBoundingSphereBody->center.x, m_pBoundingSphereBody->center.y, m_pBoundingSphereBody->center.z);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->SetTexture(0, NULL);
		m_pSphereBody->DrawSubset(0);
		//D3DXMATRIXA16 mat2;
		D3DXMatrixIdentity(&mat);
		D3DXMatrixTranslation(&mat, m_pBoundingSphereHead->center.x, m_pBoundingSphereHead->center.y, m_pBoundingSphereHead->center.z);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->SetTexture(0, NULL);
		m_pSphereHead->DrawSubset(0);
	}
}

BoundingSphere * Mob::getBoundingSphereBody()
{
	return m_pBoundingSphereBody;
}

BoundingSphere * Mob::getBoundingSphereHead()
{
	return m_pBoundingSphereHead;
}

int Mob::getStatus()
{
	return status;
}

void Mob::setStatus(int s)
{
	status = s;
}

bool Mob::PlayerSearch()
{
	//참호근처까지갔을때
	if (m_pos.x < 160.0f)
	{
		float nearAI = 100;
		int AINum;
		//가까운놈 찾기(Min찾는방식)
		for (int i = 0; i < g_pObjMgr->FindObjectsByTag(TAG_TEAM).size(); i++)
		{
			float length = D3DXVec3Length(&(g_pObjMgr->FindObjectsByTag(TAG_TEAM)[i]->GetPosition() - m_pos));
			if (length < nearAI)
			{
				nearAI = length;
				AINum = i;
			}
		}
	}
	//멀리서 각도안에 인식가능한지
	else if (m_pos.x < 230.0f)
	{
		if (g_pObjMgr->FindObjectsByTag(TAG_TEAM).size() > 0)
		{
			D3DXVECTOR3 move_forward;
			D3DXVECTOR3 DirectPM;
			move_forward = D3DXVECTOR3(m_destPos.x - m_pos.x, 0, m_destPos.z - m_pos.z);
			if (D3DXVec3LengthSq(&move_forward) > 0)
			{
				forward = move_forward;
			}
			int number = 0;

			for (auto p : (g_pObjMgr->FindObjectsByTag(TAG_TEAM)))
			{
				DirectPM = D3DXVECTOR3(p->GetPosition().x - m_pos.x, 0, p->GetPosition().z - m_pos.z);
				if (DirectPM.x < 90 && DirectPM.z < 25)
				{

					D3DXVECTOR3 DirectPMnormal = DirectPM;
					D3DXVec3Normalize(&DirectPMnormal, &DirectPMnormal);
					D3DXVec3Normalize(&forward, &forward);
					float Length = abs(p->GetPosition().x - m_pos.x + p->GetPosition().z - m_pos.z);
					float DotPM = D3DXVec3Dot(&DirectPMnormal, &forward);
					float direct = 1.0f / 2.0f;

					if (Length < 15)
					{
						m_isShoot = true;
						m_TeamAINum = number;
						return true;
					}
					else if (Length < 30 && DotPM >= direct)
					{
						m_isShoot = true;
						if (m_TeamAINum == NULL)
						{
							m_TeamAINum = number;
						}
						return true;
					}
					else if (Length < 110 && DotPM >= direct)
					{
						m_isShoot = true;
						if (m_TeamAINum == NULL)
						{
							m_TeamAINum = number;
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
	//너무멀면 그냥 불가
	else
	{
		return false;
	}
}

void Mob::ShootVertex()
{
	D3DXVECTOR3 myPos = D3DXVECTOR3(m_pos.x, m_pos.y + 4.0f, m_pos.z);
	D3DXVECTOR3 forward = D3DXVECTOR3(myPos.x - 5.0f, myPos.y, myPos.z);
	D3DCOLOR c = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR d = D3DCOLOR_XRGB(0, 255, 0);
	//D3DXVECTOR3 directPMnor = Ppos - m_pos;

	if (m_isShoot == true)
	{
		D3DXVECTOR3 Direction = { g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->GetPosition().x ,
			g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->GetPosition().y + 4.0f,
			g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->GetPosition().z };

		Shootpos[0] = (VERTEX_PC(myPos, d));
		Shootpos[1] = (VERTEX_PC(Direction, d));

		float kill = rand() % 10;

		m_ShootCooldownTime++;

		if (m_ShootCooldownTime > 100)
		{
			if (kill < 5)
			{
				int damage = rand() % 10;
				if (damage < 3)
				{
					g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->setHealth(0);
				}
				else
				{
					g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->setHealth(g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->getHealth() - 50);
				}
				if (g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->getHealth() <= 0)
				{
					m_TeamAINum = NULL;
				}
			}
			m_ShootCooldownTime = 0;
			m_bullet--;
		}
	}
	else
	{
		Shootpos[0] = (VERTEX_PC(myPos, c));
		Shootpos[1] = (VERTEX_PC(forward, c));
	}
}

void Mob::EraseLocationSoldier()
{
	for (int j = moveLocation.size() - 1; j >= 0; j--)
	{
		if (m_pos.x > moveLocation[j].x)
			EraseWallLocation();
		else
			break;
	}
	for (int j = Temporary_Storage.size() - 1; j >= 0; j--)
	{
		if (m_pos.x > Temporary_Storage[j].x)
			EraseTemporary();
		else
			break;
	}
}

void Mob::LocationSwap(int _v1, int _v2)
{
	D3DXVECTOR3 temp;
	temp = moveLocation[_v1];
	moveLocation[_v1] = moveLocation[_v2];
	moveLocation[_v2] = temp;

	int Itemp;
	Itemp = SaveLocationNum[_v1];
	SaveLocationNum[_v1] = SaveLocationNum[_v2];
	SaveLocationNum[_v2] = Itemp;
}

void Mob::TemporarySwap(int _v1, int _v2)
{
	D3DXVECTOR3 temp;
	temp = Temporary_Storage[_v1];
	Temporary_Storage[_v1] = Temporary_Storage[_v2];
	Temporary_Storage[_v2] = temp;

	int Itemp;
	Itemp = m_SaveTempNum[_v1];
	m_SaveTempNum[_v1] = m_SaveTempNum[_v2];
	m_SaveTempNum[_v2] = Itemp;
}

void Mob::SaveAction()
{
	int r1 = rand() % 10;
	if (r1 < 4) { r1 = 0; }
	else { r1 = 1; }

	int r2 = rand() % 10;
	if (r2 < 4) { r2 = 0; }
	else if (r2 < 6) { r2 = 1; }
	else { r2 = 2; }

	int r3 = rand() % 10;
	if (r3 < 4) { r3 = 0; }
	else { r3 = 1; }

	int r4 = rand() % 10;
	if (r4 < 8) { r4 = 0; }
	else { r4 = 1; }

	//엄폐이동&무시하고돌격은 수정
	if (r1 == 1 && r2 == 2) { r2 = 1; }
	
	m_Act._moving = MOB_MOVING(r1);
	m_Act._engage = MOB_ENGAGE(r2);
	m_Act._gunshot = MOB_GUNSHOT(r3);
	m_Act._reload = MOB_RELOAD(r4);
	m_Act._hiding = MOB_HIDING(1);
}
