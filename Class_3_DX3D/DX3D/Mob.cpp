#include "stdafx.h"
#include "Mob.h"
#include "CubemanParts.h"
#include "MONSTER.h"
#include "UnitBox.h"
Mob::Mob()
{
//	m_pRootParts = NULL;
	m_MONSTER = NULL;//몬스터 클래스 추가
	m_isMoving = false;
	m_maxbullet = 15;
	m_ShootCooldownTime = 0;
	//m_baseRotY = D3DX_PI;
	m_bullet = 5;
	m_reloading = 0;
	m_TeamAINum = NULL;
	m_forward.z = -1;
	m_destPos = m_pos;
	m_move = false;
	num = 0;
	m_shootingbullet = false;
	m_pSphereBody = NULL;
	m_pSphereHead = NULL;
	health = 100;
	status = 1;
	m_BeDetermined = false;
	m_Setdest = false;
	hidingChk = false;
	ani_start = true;
	showBoundingSphere = false;

	m_angle = D3DX_PI / 2;
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
	D3DXCreateSphere(g_pDevice, 2.7f, 10, 10, &m_pSphereBody, NULL);
	m_pBoundingSphereBody = new BoundingSphere(m_pos, 2.7f);

	m_MONSTER = new MONSTER;
	m_MONSTER->Init();
	SaveAction();
	Act_GunShot();
	m_moveSpeed = GSM().mobSpeed;
}

void Mob::Update()
{
	if (health <= 0) {
		status = 0;
		m_pos = { 1000,10,1000 };
	}
	if (status > 0) {
		Act_Moving();
		SelectAction();

		IUnitObject::UpdatePositionToDestination();

		m_pBoundingSphereBody->center = m_pos;
		m_pBoundingSphereHead->center = m_pos;
		if (m_Act._action == 몹_좌엄폐사격 || m_Act._action == 몹_우엄폐사격) {
			m_pBoundingSphereBody->center.y += 2.9f;
			m_pBoundingSphereHead->center.y += 4.4f;
		}
		else {
			m_pBoundingSphereBody->center.y += 3.4f;
			m_pBoundingSphereHead->center.y += 7.4f;
		}

		//m_pRootParts->SetMovingState(m_isMoving);
		//m_pRootParts->Update();
	/*	m_MONSTER->SetPos(m_pos);
		m_MONSTER->Update();*/
		Debug->AddText("몹 체력: ");
		Debug->AddText(health);
		Debug->AddText(" / 장전: ");
		Debug->AddText(m_bullet);
		Debug->AddText(" / 탄약: ");
		Debug->AddText(m_maxbullet);
		Debug->AddText(" / 높이: ");
		Debug->AddText(m_pBoundingSphereBody->center.y);
		Debug->EndLine();
		
		
	}
	Act_Action();
	
	
	//Debug->AddText("m_rot: ");
	//Debug->AddText(m_rot.y);
	//Debug->EndLine();

	//살아있을때만 포지션을 받아온다
	m_MONSTER->SetPos(m_pos);


	m_MONSTER->SetAngle(m_rot.y);


	
	if (g_pFrustum->IsMobAIFrustum(this))
	{
		m_MONSTER->SetAnimationIndex(ani_state);

		m_MONSTER->Update();
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
	
	
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	if (g_pFrustum->IsMobAIFrustum(this))
	{
		m_MONSTER->SetRenderSTATE(true);
		m_MONSTER->Render();
	}


	if (status > 0) {
		D3DXMATRIXA16 matI;
		D3DXMatrixIdentity(&matI);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pDevice->SetTransform(D3DTS_WORLD, &matI);
		g_pDevice->SetFVF(VERTEX_PC::FVF);
		g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST,
			1, &Shootpos[0], sizeof(VERTEX_PC));

		if (showBoundingSphere) {
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
	//무시하고돌격은 장전안함
	if (r2 == 2) { r4 = 1; }
	m_Act._moving = MOB_MOVING(r1);
	m_Act._engage = MOB_ENGAGE(r2);
	m_Act._gunshot = MOB_GUNSHOT(r3);
	m_Act._reload = MOB_RELOAD(r4);
	m_Act._action = MOB_ACTION(1);
}

void Mob::SelectAction()
{
	if (health > 0 ) 
	{
		CanFight = true;
		if (m_Act._engage != 몹_무시하고돌격)
		{
			switch (PlayerSearch())
			{
			case 주변적없음:
				if (hidingChk)
				{
					m_Act._action = 몹_대기상태; 
					CanFight = false;
				}
				else
				{
					m_Act._action = 몹_달리기;
					m_moveSpeed = GSM().mobSpeed;
				}
				break;
			case 근접_거리닿음:
				m_Act._action = 몹_근접전투;
					break;
			case 근접_거리안닿음:
				m_Act._action = 몹_칼든상태;
				break;
			case 원거리인식:
				Act_Engage();
				Shooting();
				if (hidingChk == false)
				{
					
					if (m_Act._engage != 몹_제자리멈춤)
						m_Act._action = 몹_달리기;
					else
						m_Act._action = 몹_서서쏘기;
					
				}
				else
				{
					if (HaveBullet() == true)
					{
						if (m_Act._engage == 몹_제자리멈춤)
						{
							m_Act._action = 몹_서서쏘기;
						}
						else
						{
							switch (CanSeeDriection.back())
							{
							case 0:
								m_Act._action = 몹_서서쏘기;
								break;
							case 1:
								m_Act._action = 몹_우엄폐사격;
								break;
							case 2:
								m_Act._action = 몹_좌엄폐사격;
								break;
							}
						}
					}
					else
					{
						Act_Reload();
					}
				}
				break;
			}
		}
		else
		{
			switch (PlayerSearch())
			{
			case 주변적없음:
				m_Act._action = 몹_달리기;
				break;
			case 근접_거리닿음:
				m_Act._action = 몹_근접전투;
				break;
			case 근접_거리안닿음:
				m_Act._action = 몹_칼든상태;
				break;
			}
		}
	}
	else
	{
		m_moveSpeed > 0 ? m_Act._action = 몹_달리다가죽기 : m_Act._action = 몹_죽음;
	}
}

void Mob::Act_Moving()
{
	switch (m_Act._moving)
	{
	case 몹_돌격이동:
		EraseLocationSoldier();
		if (PlayerSearch() == false && TrenchFight() == false)
		{
			if (m_Act._action == 주변적없음)
				SetDestination(D3DXVECTOR3(NODE_POSITSIZEX + 90.0f, 2.67f, m_pos.z));
		}
		break;
	case 몹_엄폐이동:
		break;
	}
}

void Mob::Act_Engage()
{
	switch (m_Act._engage)
	{
	case 몹_제자리멈춤:
		if (HaveBullet())
			m_moveSpeed = 0;
		break;
	case 몹_엄폐물에숨기:
		break;
	case 몹_무시하고돌격:
		if (m_Act._action != 근접_거리안닿음&& m_Act._action != 근접_거리닿음)
		{
			SetDestination(D3DXVECTOR3(NODE_POSITSIZEX + 90.0f, 2.67f, m_pos.z));
		}
		break;
	}
}

void Mob::Act_GunShot()
{
	switch (m_Act._gunshot)
	{
	case 몹_일부사격:
		m_shootingbullet = rand() % 4 + 1;
		break;
	case 몹_소진까지사격:
		m_shootingbullet = 5;
		break;
	}
}
//총알은다쓰고 장전해야할때
void Mob::Act_Reload()
{
	CanFight = false;
	switch (m_Act._reload)
	{
	case 몹_장전함:
		if (MaxBullet())
		{
			m_Act._action = 몹_뒤로앉아서장전;
			m_reloading++;
			if (m_reloading > 100)
			{
				int Temp_bullet = m_bullet;
				if (m_maxbullet < 5)
					m_bullet = m_maxbullet;
				else
					m_bullet = 5;
				m_maxbullet -= 5 - Temp_bullet;
				Act_GunShot();
				m_reloading = 0;
				CanFight = true;
			}
		}
		else
			m_Act._reload = 몹_장전안함;
		break;
	case 몹_장전안함:
		moveLocation.clear();
		m_maxbullet = 0;
		break;
	}
}

void Mob::Act_Action()
{
	ani_state = m_Act._action;
}

MOB_SITUATION Mob::PlayerSearch()
{
	//참호근처까지갔을때
	if (m_pos.x < NODE_POSITSIZEX + 100.0f)
	{	
		return TrenchFight();
	}
	//멀리서 각도안에 인식가능한지
	else if (m_pos.x < NODE_POSITSIZEX + 270.0f && m_Act._engage !=몹_무시하고돌격)
	{
		return CanShooting();
	}
	//너무멀면 그냥 불가
	m_TeamAINum = NULL;
	return 주변적없음;
}

MOB_SITUATION Mob::TrenchFight()
{
	moveLocation.clear();
	SaveLocationNum.clear();
	float nearAI = 150;
	int AINum = NULL;
	//가까운놈 찾기(Min찾는방식)
	for (int i = 0; i < g_pObjMgr->FindObjectsByTag(TAG_TEAM).size(); i++)
	{
		if (g_pObjMgr->FindObjectsByTag(TAG_TEAM)[i]->getHealth() > 0)
		{
			float length = D3DXVec3Length(&(g_pObjMgr->FindObjectsByTag(TAG_TEAM)[i]->GetPosition() - m_pos));
			if (length < nearAI)
			{
				nearAI = length;
				AINum = i;
			}
		}
	}
	if (AINum != NULL)
	{
		m_TeamAINum = AINum;
		D3DXVECTOR3 TeamAIPos = g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->GetPosition();
		D3DXVECTOR3 Direction = { TeamAIPos.x ,TeamAIPos.y + 4.0f, TeamAIPos.z };
		D3DXVECTOR3 myPos = D3DXVECTOR3(m_pos.x, m_pos.y + 4.0f, m_pos.z);
		D3DCOLOR d = D3DCOLOR_XRGB(0, 255, 0);
		Shootpos[0] = (VERTEX_PC(myPos, d));
		Shootpos[1] = (VERTEX_PC(Direction, d));
		
		if (abs(m_pos.x - TeamAIPos.x + m_pos.z - TeamAIPos.z) > 5.0f)
		{
			SetTargetPostion(g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->GetPosition());
			return 근접_거리안닿음;
		}
		else
		{
			m_moveSpeed = 0;
			m_ShootCooldownTime++;
			if (m_ShootCooldownTime > 100)
			{
				g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->DecreaseHealth(25.0f);
				m_ShootCooldownTime = 0;
			}
			if (g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->getHealth() <= 0)
			{
				m_TeamAINum = NULL;
				m_Setdest = true;
				return 근접_거리안닿음;
			}
			return 근접_거리닿음;
		}
	}
	return 근접_거리안닿음;
}

MOB_SITUATION Mob::CanShooting()
{
	if (!HaveBullet() && !MaxBullet())
		return 주변적없음;
	if (m_TeamAINum != NULL)
	{
		if (HaveBullet() == true)
			return 원거리인식;
	}
	if (g_pObjMgr->FindObjectsByTag(TAG_TEAM).size() > 0)
	{
		D3DXVECTOR3 move_forward;
		D3DXVECTOR3 DirectPM;
		move_forward = D3DXVECTOR3(m_destPos.x - m_pos.x, 0, m_destPos.z - m_pos.z);

		if (D3DXVec3LengthSq(&move_forward) > 0)
			forward = move_forward;
		
		int number = 0;

		for (auto p : (g_pObjMgr->FindObjectsByTag(TAG_TEAM)))
		{
			DirectPM = D3DXVECTOR3(p->GetPosition().x - m_pos.x, 0, p->GetPosition().z - m_pos.z);
			D3DXVECTOR3 AbsPm = { abs(DirectPM.x),0,abs(DirectPM.z) };
			if (AbsPm.x > 0 && AbsPm.x < 240 && AbsPm.z < 60 && AbsPm.z > 0)
			{

				D3DXVECTOR3 DirectPMnormal = DirectPM;
				D3DXVec3Normalize(&DirectPMnormal, &DirectPMnormal);
				D3DXVec3Normalize(&forward, &forward);
				float Length = abs(m_pos.x - p->GetPosition().x) + abs(m_pos.z - p->GetPosition().z);
				float DotPM = D3DXVec3Dot(&DirectPMnormal, &forward);
				float direct = 0.5f / 2.0f;

				if (Length > 0 && Length < 240 && DotPM >= direct)
				{
					if (m_TeamAINum == NULL && g_pObjMgr->FindObjectsByTag(TAG_TEAM)[number]->getHealth() > 0)
					{
						m_TeamAINum = number;
						return 원거리인식;
					}
				}
			}
			number++;
		}
		return 주변적없음;
	}
	return 주변적없음;
}

void Mob::Shooting()
{
	D3DXVECTOR3 myPos = D3DXVECTOR3(m_pos.x, m_pos.y + 4.0f, m_pos.z);
	D3DXVECTOR3 forward = D3DXVECTOR3(myPos.x - 5.0f, myPos.y, myPos.z);
	D3DCOLOR c = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR d = D3DCOLOR_XRGB(0, 255, 0);

	if (CanShooting() == 원거리인식)
	{
		D3DXVECTOR3 Direction = { g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->GetPosition().x ,
			g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->GetPosition().y + 4.0f,
			g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->GetPosition().z };

		Shootpos[0] = (VERTEX_PC(myPos, d));
		Shootpos[1] = (VERTEX_PC(Direction, d));

		if (HaveBullet() == true)
		{
			if (m_Act._action == 몹_서서쏘기 || m_Act._action == 몹_좌엄폐사격 || m_Act._action == 몹_우엄폐사격)
			{
				
				m_ShootCooldownTime++;
				if (m_ShootCooldownTime > 100)
				{
					float kill = rand() % 20;
					if (kill < 3 && g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->CanFight == true)
					{
						/*int damage = rand() % 10;
						if (damage == 1)
						{
							g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->DecreaseHealth(100);
						}
						else*/
						{
							g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->DecreaseHealth(50);
						}
					}
					m_ShootCooldownTime = 0;
					m_shootingbullet--;
					m_bullet--;
				}
			}
		}
		else if (m_maxbullet < 0)
		{
			moveLocation.clear();
			SaveLocationNum.clear();
		}
		if (g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_TeamAINum]->getHealth() <= 0)
		{
			m_TeamAINum = NULL;
			if (m_Act._moving == 몹_돌격이동)
			{
				m_Setdest = false;
				m_isMoving = false;
			}
		}
	}
	
	if (CanShooting() == 주변적없음 || m_TeamAINum == NULL)
	{
		Shootpos[0] = (VERTEX_PC(myPos, c));
		Shootpos[1] = (VERTEX_PC(forward, c));
	}
}

bool Mob::HaveBullet()
{
	if (m_bullet < 1 || m_shootingbullet < 1)
		return false;

	return true;
}

bool Mob::MaxBullet()
{
	if (m_maxbullet > 0) return true;

	return false;
}

void Mob::EraseLocationSoldier()
{
	if (moveLocation.empty() == false)
	{
		for (int j = moveLocation.size() - 1; j >= 0; j--)
		{
			if (m_pos.x + 1.0f < moveLocation[j].x)
				EraseWallLocation();
			else
				break;
		}
		for (int j = Temporary_Storage.size() - 1; j >= 0; j--)
		{
			if (m_pos.x + 1.0f < Temporary_Storage[j].x)
				EraseTemporary();
			else
				break;
		}
	}
}

void Mob::ResetAll()
{
	m_TeamAINum = NULL;
	m_isMoving = false;
	m_maxbullet = 15;
	m_ShootCooldownTime = 0;
	m_bullet = 5;
	m_reloading = 0;
	m_forward.z = -1;
	m_move = false;
	num = 0;
	m_shootingbullet = false;
	health = 100;
	status = 1;
	m_BeDetermined = false;
	m_Setdest = false;
	hidingChk = false;
	ani_start = true;
	moveLocation.clear(); SaveLocationNum.clear(); CanSeeDriection.clear();
	Temporary_Storage.clear(); m_SaveTempNum.clear(); TemporaryDirection.clear();
	SetPosition(&D3DXVECTOR3(GSM().mobPos.x + (rand() % 40), 2.67f, GSM().mobPos.z + (rand() % 350)));
	SaveAction();
	Act_GunShot();
	m_moveSpeed = GSM().mobSpeed;

}

void Mob::LocationSwap()
{
	//저장한위치들의 정렬(뒤로갈수록 내위치와 가까움)
	if (moveLocation.size() > 1)
	{
		for (int i = 0; i < moveLocation.size() - 1; i++)
		{
			for (int j = 0; j < moveLocation.size() - 1; j++)
			{
				if (moveLocation[j].x > moveLocation[j + 1].x)
				{
					D3DXVECTOR3 temp;
					temp = moveLocation[j];
					moveLocation[j] = moveLocation[j + 1];
					moveLocation[j + 1] = temp;

					int Itemp;
					Itemp = SaveLocationNum[j];
					SaveLocationNum[j] = SaveLocationNum[j + 1];
					SaveLocationNum[j + 1] = Itemp;

					int Itemp2;
					Itemp2 = CanSeeDriection[j];
					CanSeeDriection[j] = CanSeeDriection[j + 1];
					CanSeeDriection[j + 1] = Itemp2;
				}
			}
		}
	}
}

void Mob::TemporarySwap()
{
	//임시저장한위치들의 정렬(뒤로갈수록 시작지점과 가까움)
	if (Temporary_Storage.size() > 1)
	{
		for (int i = 0; i < Temporary_Storage.size() - 1; i++)
		{
			for (int j = 0; j < Temporary_Storage.size() - 1; j++)
			{
				if (Temporary_Storage[j].x > Temporary_Storage[j + 1].x)
				{
					D3DXVECTOR3 temp;
					temp = Temporary_Storage[j];
					Temporary_Storage[j] = Temporary_Storage[j + 1];
					Temporary_Storage[j + 1] = temp;

					int Itemp;
					Itemp = m_SaveTempNum[j];
					m_SaveTempNum[j] = m_SaveTempNum[j + 1];
					m_SaveTempNum[j + 1] = Itemp;

					int Itemp2;
					Itemp2 = TemporaryDirection[j];
					TemporaryDirection[j] = TemporaryDirection[j + 1];
					TemporaryDirection[j + 1] = Itemp2;
				}
			}
		}
	}
}