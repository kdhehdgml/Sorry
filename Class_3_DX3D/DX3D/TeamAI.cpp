#include "stdafx.h"
#include "TeamAI.h"
//#include "CubemanParts.h"
#include "TEAM_TEX.h"

//장비
#include "FR_HEADGEAR.h"
//무기
#include "Smle.h"

#define moveSpeed 0.5f
#define DEATH_TIME 10000


TeamAI::TeamAI()
{
	m_TEAM_TEX = NULL;//몬스터 클래스 추가
	m_MobNum = NULL;
	m_isMoving = false;
	m_reloading = 0;
	//m_baseRotY = D3DX_PI / 2;
	m_Action = 팀_대기;
	m_forward.z = -1;
	m_pos.y = 3.0f;
	m_destPos = m_pos;
	m_move = false;
	num = 0;
	m_ShootCooldownTime = 0;
	m_pSphere = NULL;
	health = 100;
	status = 1;
	m_render = true;
	m_bullet = 5;
	m_angle = D3DX_PI / 2;
	m_def = 0;
	ani_state = 서서기본자세;
	m_Ready = true;
	m_Death = false;
	
	deathShout = false;
	reloadShout = false;

	m_level = 1;
	m_expToNextLevel = 4;
	m_FR_HEADGEAR = NULL;

	headgear_state	= true;
	gun_state		= true;
}


TeamAI::~TeamAI()
{

	if (!GSM().Debug_Mode_On)
	{
		SAFE_RELEASE(m_TEAM_TEX);
	}
	SAFE_RELEASE(m_pSphere);
	SAFE_DELETE(m_pBoundingSphere);

	SAFE_RELEASE(m_Smle);
	SAFE_RELEASE(m_FR_HEADGEAR);

}

void TeamAI::Init()
{
	g_pObjMgr->AddToTagList(TAG_TEAM, this);
	D3DXCreateSphere(g_pDevice, 3.0f, 10, 10, &m_pSphere, NULL);

	m_Smle = new Smle;
	m_Smle->Init();
	
	m_FR_HEADGEAR = new FR_HEADGEAR;
	m_FR_HEADGEAR->Init();
	
	if (!GSM().Debug_Mode_On)
	{
		m_TEAM_TEX = new TEAM_TEX;
		m_TEAM_TEX->Init();
	}
	m_moveSpeed = moveSpeed;
	m_pBoundingSphere = new BoundingSphere(m_pos, 3.0f);

	m_Death_count = 0;
	m_Death_Time = 0;
}

void TeamAI::Update()
{
	if (health <= 0) {
		status = 0;
		m_Action = 팀_죽음;
		m_MobNum = NULL;

		m_Death_count++;

		if (m_Death_count == 1)
		{
			m_Death_Time = GetTickCount();
		}

		//죽은 시간의 끝
		if (GetTickCount() >= m_Death_Time + DEATH_TIME)
		{
			m_Death_count = 0;
			m_Death = true;
			m_pos = { 2000,10,2000 };
		}
		if (!deathShout)
		{
			g_pSoundManager->updateSpeaker(sType::VOICE_DEATH, NULL, m_pos);
			deathShout = true;
		}
	}
	Animation();

	if (status > 0) {

		m_Death = false;
		UpdatePositionToDestination();
		if (abs(m_finalDestPos.x - m_pos.x + m_finalDestPos.z - m_pos.z) <= 5.0f && m_Ready == false)
		{
			m_Action = 팀_대기;
			m_Ready = true;
		}
			
		if (m_Ready == true)
		{
			if ((m_MobNum == NULL && m_bullet < 5) || HaveBullet() == false)
			{
				m_Action = 팀_재장전;
				CanFight = false;
				deathShout = false;
				Reloading();
			}
			if (HaveBullet() == true)
			{
				CanFight = true;
				if (MobSearch() == true)
				{
					m_Action = 팀_사격;
					Shooting();
				}
			}
			//ShootVertex();
		}
		else
		{
			m_Action = 팀_대기;
		}

		m_pBoundingSphere->center = m_pos;
		m_pBoundingSphere->center.y += 4.0f;

		if (m_MobNum == NULL)
			m_angle = 0;
		else
		{
			D3DXVECTOR3 forwardDir = D3DXVECTOR3(g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->GetPosition().x - m_pos.x, 0,
				g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->GetPosition().z - m_pos.z);
			if (forwardDir.x <= 0)
			{
				D3DXVECTOR3 forwardNor = forwardDir;
				D3DXVec3Normalize(&forwardNor, &forwardNor);
				m_angle = D3DXVec3Dot(&forwardNor, &D3DXVECTOR3(0, 0, 1)) + D3DX_PI;
			}
			else
			{
				D3DXVECTOR3 forwardNor = forwardDir;
				D3DXVec3Normalize(&forwardNor, &forwardNor);
				m_angle = -(D3DXVec3Dot(&forwardNor, &D3DXVECTOR3(0, 0, 1)));
			}
		}
		Debug->AddText("아군 체력: ");
		Debug->AddText(health);
		Debug->AddText(" / 총알수: ");
		Debug->AddText(m_bullet);
		Debug->AddText(" / 레벨: ");
		Debug->AddText(m_level);
		Debug->AddText(" / 경험치: ");
		Debug->AddText(m_expToNextLevel);
		/*Debug->AddText(" / 애니: ");
		Debug->AddText(m_Action);
		Debug->AddText(" / 애니스: ");
		Debug->AddText(ani_state);*/
		Debug->EndLine();
	}

	if (m_expToNextLevel <= 0) {
		LevelUp();
	}

	/*Debug->AddText("데스 카운트 :");
	Debug->AddText(m_Death_count);

	Debug->AddText("//  아군 On/oFF(0이 살아있는것) :");
	Debug->AddText(m_Death);

	Debug->AddText("// 랜더 On/oFF:");
	Debug->AddText(m_render);

	Debug->EndLine();*/

	if (!GSM().Debug_Mode_On)
	{
		if (g_pFrustum->IsSphereInsideFrustum(m_pBoundingSphere)
			&& m_Death == false)
		{
			if (status != 0 && m_Death == false)
			{
				m_TEAM_TEX->SetPos(m_pos);
				m_TEAM_TEX->SetAngle(m_angle);
			}
			m_TEAM_TEX->SetAnimationIndex(ani_state);
			m_TEAM_TEX->Update();
			//장비
			m_FR_HEADGEAR->SetMat(m_TEAM_TEX->GetHeadMatRot());
			m_FR_HEADGEAR->SetPos(m_TEAM_TEX->GetHeadPos());
			m_FR_HEADGEAR->Update();

			//무기
			m_Smle->SetPos(m_TEAM_TEX->GetLeftPos());
			m_Smle->SetAngle(m_TEAM_TEX->GetAngle() + (-(D3DX_PI / 2)));
			m_Smle->SetAniIndex(m_TEAM_TEX->m_AnimaTionIndex);
			m_Smle->Update();

		}
	}


	//아군 렌더 할까말까
	if (Keyboard::Get()->KeyDown('H'))
	{
		m_render = !m_render;
	}
	if (Keyboard::Get()->KeyDown(VK_NUMPAD6))
	{
		headgear_state = !headgear_state;
	}
	if (Keyboard::Get()->KeyDown(VK_NUMPAD5))
	{
		gun_state = !gun_state;
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


	if (!GSM().Debug_Mode_On)
	{
		//프러스텀 적용 
		if (g_pFrustum->IsSphereInsideFrustum(m_pBoundingSphere)
			&& m_Death == false && m_render)
		{
			m_TEAM_TEX->Render();
			if(gun_state)
				m_Smle->Render();
			if (headgear_state)
				m_FR_HEADGEAR->Render();
		}
	}
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

void TeamAI::Animation()
{
	switch (m_Action)
	{
	case 팀_대기:
		ani_state = 서서기본자세;
		break;
	case 팀_사격:
		ani_state = 서서쏘기;
		break;
	case 팀_재장전:
		ani_state = 재장전;
		break;
	case 팀_근접싸움:
		ani_state = 근접공격;
		break;
	case 팀_죽음:
		ani_state = 서서죽음;
		break;
	}
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

bool TeamAI::HaveBullet()
{
	if (m_bullet < 1)
		return false;

	return true;
}

bool TeamAI::MobSearch()
{
	if (m_MobNum != NULL)
	{
		if (g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->getHealth() <= 0)
			m_MobNum = NULL;
		else
			return true;
	}
	if (g_pObjMgr->FindObjectsByTag(TAG_MOB).size() > 0)
	{
		D3DXVECTOR3 move_forward;
		move_forward = D3DXVECTOR3(1, 0, 0);
		if (D3DXVec3LengthSq(&move_forward) > 0)
		{
			forward = move_forward;
		}
		int number = 0;
		int targetnum = 0;
		float minLength = 1000;
		//아군인식범위안 적군찾기
		for (auto p : (g_pObjMgr->FindObjectsByTag(TAG_MOB)))
		{
			D3DXVECTOR3 DirectPM = p->GetPosition() - m_pos;
			if (abs(DirectPM.x) < 200 && abs(DirectPM.z) < 40 && p->getHealth()>0)
			{
				DirectPM.y = m_pos.y;
				D3DXVECTOR3 DirectPMnormal = DirectPM;
				D3DXVec3Normalize(&DirectPMnormal, &DirectPMnormal);
				float Length = abs(p->GetPosition().x - m_pos.x + p->GetPosition().z - m_pos.z);
				float DotPM = D3DXVec3Dot(&DirectPMnormal, &forward);
				float direct = 1.0f / 2.0f;
				if (Length < minLength)
				{
					minLength = Length;
					targetnum = number;
				}
			}
			number++;
		}
		if (minLength < 10)
		{
			return TrenchFight(1);
		}
		else if (minLength < 30)
		{
			return TrenchFight(2);
		}
		else if (minLength < 240)
		{
			if (m_MobNum == NULL && g_pObjMgr->FindObjectsByTag(TAG_MOB)[targetnum]->getHealth() > 0)
			{
				m_MobNum = targetnum;
				return true;
			}
		}
		m_MobNum = NULL;
		m_Action = 팀_대기;
		return false;
	}
}

void TeamAI::ShootVertex()
{
	D3DXVECTOR3 myPos = D3DXVECTOR3(m_pos.x, m_pos.y + 4.0f, m_pos.z);
	D3DXVECTOR3 forward = D3DXVECTOR3(myPos.x + 4.0f, myPos.y, myPos.z);
	D3DCOLOR c = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR d = D3DCOLOR_XRGB(0, 255, 0);

	if (m_MobNum != NULL)
	{
		D3DXVECTOR3 Direction = { g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->GetPosition().x ,
		g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->GetPosition().y + 4.0f,
		g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->GetPosition().z };
		Shootpos[0] = (VERTEX_PC(myPos, c));
		Shootpos[1] = (VERTEX_PC(Direction, c));
	}
	else
	{
		Shootpos[0] = (VERTEX_PC(myPos, d));
		Shootpos[1] = (VERTEX_PC(forward, d));
	}
}
//근접전투
bool TeamAI::TrenchFight(int _num) 
{
	float nearEnemy = 100;
	int EnemyNum = NULL;

	//가까운놈 찾기(Min찾는방식)
	for (int i = 0; i < g_pObjMgr->FindObjectsByTag(TAG_MOB).size(); i++)
	{
		float length = D3DXVec3Length(&(g_pObjMgr->FindObjectsByTag(TAG_MOB)[i]->GetPosition() - m_pos));
		if (length < nearEnemy)
		{
			nearEnemy = length;
			EnemyNum = i;
		}
	}
	if (EnemyNum != NULL)
	{
		m_MobNum = EnemyNum;
		
		if (_num == 1)
		{

			if (D3DXVec3Length(&(m_pos - g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->GetPosition())) < 5.0f)
			{
				m_ShootCooldownTime++;
				m_Action = 팀_근접싸움;
				if (m_ShootCooldownTime > 100)
				{
					g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->DecreaseHealth(25.0f);
					g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_MobNum]->SetHitting(true);
					m_ShootCooldownTime = 0;
				}
			}
			return false;
		}
		else
			return true;
	}
}

void TeamAI::Shooting()
{
	m_ShootCooldownTime++;
	if (m_ShootCooldownTime > 100)
	{
		int kill = rand() % 10;
		if (kill < 4 && g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->CanFight == true)
		{
			/*int damage = rand() % 10;
			if (damage < 3)
			{
				g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->DecreaseHealth(100);
				g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_MobNum]->SetHitting(true);
			}
			else*/
			{
				kill = rand() % 30;
				g_pObjMgr->FindObjectsByTag(TAG_MOB)[m_MobNum]->DecreaseHealth(20 + kill);
				g_pObjMgr->FindObjectsByTag(TAG_TEAM)[m_MobNum]->SetHitting(true);
			}
			m_bullet--;

			// 3D 사운드
			kill = rand() % 2;
			g_pSoundManager->updateSpeaker(sType::SHOOT, kill, m_pos);
		}
		m_ShootCooldownTime = 0;
	}
}

void TeamAI::Reloading()
{
	m_reloading++;

	if (m_bullet == 0 && !reloadShout)
	{
		g_pSoundManager->updateSpeaker(sType::VOICE_RELOAD, NULL, m_pos);
		reloadShout = true;
	}
	if (m_reloading > 100)
	{
		m_bullet = 5;
		m_reloading = 0;
		reloadShout = false;
	}
}

void TeamAI::LevelUp()
{
	m_level++;
	m_expToNextLevel = (m_level + 1) * (m_level + 1);
}
