#include "stdafx.h"
#include "UnitBox.h"
#include "Cubeman.h"
#include "Mob.h"
#include "Ray.h"
#include "TeamAI.h"
UnitBox::UnitBox()
{
	m_pCubeman = NULL;
	m_SameChk = false;
	MobNum = 0;
	MobStart = false;
}


UnitBox::~UnitBox()
{
	for (size_t i = 0; i < m_pMob.size(); i++)
	{
		SAFE_RELEASE(m_pMob[i]);
	}
	for (size_t i = 0; i < m_pTeam.size(); i++)
	{
		SAFE_RELEASE(m_pTeam[i]);
	}
	SAFE_RELEASE(m_pCubeman);
}



void UnitBox::Init()
{
	m_pCubeman = new Cubeman; m_pCubeman->Init();
	m_CanSave.resize(m_SaveLocation.size(),true);
	FindEmptyWallDirection();
	//아군AI생성
	TeamNum = 20;
	m_pTeam.resize(TeamNum);
	for (int i = 0; i < TeamNum; i++)
	{
		m_pTeam[i] = new TeamAI;
		m_pTeam[i]->Init();
		m_pTeam[i]->SetPosition(&D3DXVECTOR3((GSM().TeamPos.x + NODE_POSITSIZEX), 2.67f, GSM().TeamPos.z + (16 * i)));
	}
}

void UnitBox::Update()
{
	SAFE_UPDATE(m_pCubeman);
	Debug->EndLine();
	if (GetAsyncKeyState(VK_F2) & 0x0001)
		CreateMob(20);
	if (GetAsyncKeyState(VK_F3) & 0x0001)
		MobStart = true;
	if (GetAsyncKeyState(VK_F4) & 0x0001)
		ReSetMob();
	//후방 제대 소환
	if (GetAsyncKeyState(VK_F5) & 0x0001)
	{
		teamSummon();
	}
	//후방 제대 지원
	if (GetAsyncKeyState(VK_F6) & 0x0001)
	{
		for (int i = 40; i < m_pTeam.size(); i++)
		{
			m_pTeam[i]->SetTargetPostion(D3DXVECTOR3((GSM().TeamPos.x + NODE_POSITSIZEX), m_pTeam[i]->GetPosition().y, m_pTeam[i]->GetPosition().z));
			m_pTeam[i]->UpdatePositionToDestination();
		}
	}
	if (GetAsyncKeyState('J') & 0x0001) {
		for (int i = 0; i < m_pMob.size(); i++) {
			m_pMob[i]->showBoundingSphere = !m_pMob[i]->showBoundingSphere;
		}
	}

	////내가 지나간곳들 장애물 저장한위치 없앰
	//for (auto p : m_pMob)
	//{
	//	if(p->m_Act._moving==몹_돌격이동)
	//		p->EraseLocationSoldier();
	//}
	//아군Ai가 적Ai인식하는 내용
	if (m_pTeam.size() > 0)
	{
		for (size_t i = 0; i < m_pTeam.size(); i++)
		{
			SAFE_UPDATE(m_pTeam[i]);
		}
	}
	if (MobStart)
	{
		//타겟을따라서 움직이는 내용
		if (m_pMob.size() > 0)
		{
			for (size_t i = 0; i < m_pMob.size(); i++)
			{
				SAFE_UPDATE(m_pMob[i]);
				//장애물뒤에 숨기
				if (m_pMob[i]->GetPosition().x > NODE_POSITSIZEX + 150.0f)
				{
					MobMoveInTheWall(i);
				}
			}
		}
	}
}

void UnitBox::Render()
{
	for (size_t i = 0; i < m_pMob.size(); i++)
	{
		SAFE_RENDER(m_pMob[i]);
	}
	for (size_t i = 0; i < m_pTeam.size(); i++)
	{
		SAFE_RENDER(m_pTeam[i]);
	}
	SAFE_RENDER(m_pCubeman);
}

void UnitBox::FindEmptyWallDirection()
{
	
	for (int i = 0; i < m_SaveLocation.size(); i++)
	{
		int sum = 0;
		for (int j = 0; j < m_SaveLocation.size(); j++)
		{
			if (i != j && m_SaveLocation[i].x == m_SaveLocation[j].x)
			{
				float leng = m_SaveLocation[i].z - m_SaveLocation[j].z;
				if (abs(leng) < 7.5f)
				{
					leng > 0 ? sum+= (int)좌장애물있음 : sum += (int)우장애물있음;
				}
			}
		}
		switch (sum)
		{
		case 0:
			m_CanSeeDirection.push_back(비지않음);
		case 1:
			m_CanSeeDirection.push_back(좌장애물있음);
			break;
		case 2:
			m_CanSeeDirection.push_back(우장애물있음);
			break;
		case 3:
			m_CanSeeDirection.push_back(비지않음);
			break;
		}
	}
}

void UnitBox::FindHidingInTheWallLocationRushSoldier(int _Mobnum)
{
	D3DXVECTOR3 Save;
	for (size_t i = 0; i < m_SaveLocation.size(); i++)
	{
		Save = D3DXVECTOR3(m_SaveLocation[i].x + 4.0f, m_SaveLocation[i].y, m_SaveLocation[i].z);
		if (abs(m_SaveLocation[i].z - m_pMob[_Mobnum]->GetPosition().z) < 10)
		{
			if (i == 0)
			{
				m_pMob[_Mobnum]->SetMoveTheWall(Save, i, m_CanSeeDirection[i]);
				continue;
			}
			for (int j = 0; j < m_pMob[_Mobnum]->GetMoveTheWall().size(); j++)
			{
				if (m_pMob[_Mobnum]->GetMoveTheWall()[j].x != Save.x)
				{
					m_SameChk = false;
				}
				else
				{
					m_SameChk = true;
					m_pMob[_Mobnum]->SetTemporary(Save, i, m_CanSeeDirection[i]);
					j = m_pMob[_Mobnum]->GetMoveTheWall().size();
				}
			}
			if (m_SameChk == false)
			{
				m_pMob[_Mobnum]->SetMoveTheWall(Save, i, m_CanSeeDirection[i]);
			}
			m_SameChk = false;
		}
	}
	m_pMob[_Mobnum]->LocationSwap();
	m_pMob[_Mobnum]->TemporarySwap();
}
//내가 갈곳들 경로 저장
void UnitBox::FindHidingInTheWallLocation(int _Mobnum)
{
	D3DXVECTOR3 Save;
	for (size_t i = 0; i < m_SaveLocation.size(); i++)
	{
		Save = D3DXVECTOR3(m_SaveLocation[i].x + 6.0f, m_SaveLocation[i].y, m_SaveLocation[i].z);
		//내위치로부터 Z값±10인곳만 검색
		if (abs(m_SaveLocation[i].z - m_pMob[_Mobnum]->GetPosition().z) < 10)
		{
			if (i == 0)
			{
				m_pMob[_Mobnum]->SetMoveTheWall(Save,i, m_CanSeeDirection[i]);
				continue;
			}

			for (int j = 0; j < m_pMob[_Mobnum]->GetMoveTheWall().size(); j++)
			{
				//내가 저장한위치와 다음의 장애물위치의 x값이 같지않을때 저장 
				if (m_pMob[_Mobnum]->GetMoveTheWall()[j].x != Save.x)
				{
					m_SameChk = false;
				}
				else //내가 저장한위치와 다음의 장애물위치의 x값이 같으면 임시저장
				{
					m_SameChk = true;
					m_pMob[_Mobnum]->SetTemporary(Save,i, m_CanSeeDirection[i]);
					j = m_pMob[_Mobnum]->GetMoveTheWall().size();
				}
			}
			if (m_SameChk == false)
			{
				m_pMob[_Mobnum]->SetMoveTheWall(Save,i, m_CanSeeDirection[i]);
			}
			m_SameChk = false;
		}
	}
	//저장한위치들의 정렬(뒤로갈수록 내위치와 가까움)
	m_pMob[_Mobnum]->LocationSwap();
	//임시저장한위치들의 정렬(뒤로갈수록 시작지점과 가까움)
	m_pMob[_Mobnum]->TemporarySwap();
}

void UnitBox::MobMoveInTheWall(int _Mobnum)
{
	//엄폐물저장위치가 없으면 참호로 돌격
	if (m_pMob[_Mobnum]->GetMoveTheWall().empty() == true)
	{
		if (m_pMob[_Mobnum]->m_move == false)
		{
			//m_pMob[_Mobnum]->SetDestination(D3DXVECTOR3(5.0f + NODE_POSITSIZE, 2.67f, GSM().mobPos.z + ((_Mobnum + 1) * 20 + NODE_POSITSIZE)));
			m_pMob[_Mobnum]->SetDestination(D3DXVECTOR3(NODE_POSITSIZEX + 100.0f, 2.67f, m_pMob[_Mobnum]->GetPosition().z));
			m_pMob[_Mobnum]->m_move = true;
		}
	}
	else
	{
		//엄폐이동하는놈 && 돌격이동이어도 교전시에 엄페물숨을놈 && 제자리사격 하다가 엄폐물 숨을놈
		if (m_pMob[_Mobnum]->m_Act._moving == 몹_엄폐이동 || (m_pMob[_Mobnum]->m_Act._engage == 몹_엄폐물에숨기 && m_pMob[_Mobnum]->PlayerSearch() == true)
			|| ((m_pMob[_Mobnum]->HaveBullet() == false && m_pMob[_Mobnum]->MaxBullet() == true) && m_pMob[_Mobnum]->m_Act._engage == 몹_제자리멈춤))
		{
			if (m_pMob[_Mobnum]->m_move == false)
			{
				m_pMob[_Mobnum]->SetDestination(m_pMob[_Mobnum]->GetMoveTheWall().back());
				m_pMob[_Mobnum]->UpdatePositionToDestination();
				m_pMob[_Mobnum]->m_move = true;
			}

			if (m_pMob[_Mobnum]->m_move == true)
			{
				float Dist = D3DXVec3Length(&(m_pMob[_Mobnum]->GetMoveTheWall().back() - m_pMob[_Mobnum]->GetPosition()));
				if (Dist < 20 && m_pMob[_Mobnum]->GetDetermined() == false)
				{
					//원래길로가는것
					if (m_CanSave[m_pMob[_Mobnum]->GetLocationNum().back()] == true)
					{
						m_pMob[_Mobnum]->SetDetermined(true);
						m_CanSave[m_pMob[_Mobnum]->GetLocationNum().back()] = false;
					}
					else     //차선으로 가는것
					{
						int j = m_pMob[_Mobnum]->GetTemporary().size() - 1;
						while (j > -1)
						{
							//내위치보다 임시저장위치가 뒤에있으면 없앰
							if (m_pMob[_Mobnum]->GetMoveTheWall().back().x < m_pMob[_Mobnum]->GetTemporary()[j].x)
							{
								m_pMob[_Mobnum]->EraseTemporary();
								j = m_pMob[_Mobnum]->GetTemporary().size() - 1;
								continue;
							}
							//내가 갈위치의 X값이랑 임시저장위치의 X값이 같을때(같은길에있는거)
							if (m_pMob[_Mobnum]->GetMoveTheWall().back().x == m_pMob[_Mobnum]->GetTemporary()[j].x)
							{
								//임시저장위치가 갈수있는곳일때 내원래있는위치 지우고 임시저장위치를 집어넣음
								if (m_CanSave[m_pMob[_Mobnum]->GetTemporaryNum().back()] == true)
								{
									m_pMob[_Mobnum]->EraseWallLocation();
									m_pMob[_Mobnum]->SetMoveTheWall(m_pMob[_Mobnum]->GetTemporary().back(), m_pMob[_Mobnum]->GetTemporaryNum().back()
									,m_pMob[_Mobnum]->GetTemporaryDirection().back());
									m_pMob[_Mobnum]->EraseTemporary();
									break;
								}
								else //못가는곳일때 거기없앰
								{
									m_pMob[_Mobnum]->EraseTemporary();
									j = m_pMob[_Mobnum]->GetTemporary().size() - 1;
								}

							}
							else //같은길에 임시저장위치도 갈곳이 없으면 그라인 포기
							{
								m_pMob[_Mobnum]->EraseWallLocation();
								break;
							}
						}

						//차선이동일때 상단에 내용에서 경로재지정을하고 하단내용에서 이동과 그위치 못오게막음
						if (m_pMob[_Mobnum]->GetLocationNum().empty() == false)
						{
							m_CanSave[m_pMob[_Mobnum]->GetLocationNum().back()] = false;
							m_pMob[_Mobnum]->SetDestination(m_pMob[_Mobnum]->GetMoveTheWall().back());
							m_pMob[_Mobnum]->UpdatePositionToDestination();
							Dist = D3DXVec3Length(&(m_pMob[_Mobnum]->GetMoveTheWall().back() - m_pMob[_Mobnum]->GetPosition()));
						}
						//장애물 정했음
						m_pMob[_Mobnum]->SetDetermined(true);
					}
				}
				//다음 장애물로 가기 위한 조건문
				if (Dist < 1.0f)
				{
					m_pMob[_Mobnum]->hidingChk = true;
					if (m_pMob[_Mobnum]->PlayerSearch() == 주변적없음)
					{
						m_pMob[_Mobnum]->SetMoveSpeed(0);
						m_pMob[_Mobnum]->num++;
						if (m_pMob[_Mobnum]->num > 100)
						{
							m_pMob[_Mobnum]->SetMoveSpeed(1.0f);
							m_CanSave[m_pMob[_Mobnum]->GetLocationNum().back()] = true;
							m_pMob[_Mobnum]->SetDetermined(false);
							if(!m_pMob[_Mobnum]->GetMoveTheWall().empty())
								m_pMob[_Mobnum]->EraseWallLocation();
							m_pMob[_Mobnum]->m_move = false;
							m_pMob[_Mobnum]->num = 0;
							m_pMob[_Mobnum]->hidingChk = false;
						}
					}
				}
			}
		}
	}
}

void UnitBox::CreateMob(int num)
{
	g_pSoundManager->playMusic(1);
	g_pSoundManager->effectSound(0);

	for (int i = 0; i < num; i++)
	{
		MobNum++;
		m_pMob.resize(MobNum);
		m_pMob[MobNum - 1] = new Mob;
		m_pMob[MobNum - 1]->Init();
		m_pMob[MobNum - 1]->SetPosition(&D3DXVECTOR3(GSM().mobPos.x + (rand() % 40), 2.67f, GSM().mobPos.z + (rand() % 350)));
		if (m_pMob[MobNum - 1]->m_Act._moving == 몹_엄폐이동 || m_pMob[MobNum - 1]->m_Act._reload == 몹_장전함 || m_pMob[MobNum - 1]->m_Act._engage == 몹_엄폐물에숨기)
		{
			FindHidingInTheWallLocation(MobNum - 1);
		}
	}
}

void UnitBox::ReSetMob()
{
	for (auto p : m_pMob)
	{
		p->ResetAll();
		if (m_pMob[MobNum - 1]->m_Act._moving == 몹_엄폐이동 || m_pMob[MobNum - 1]->m_Act._reload == 몹_장전함 || m_pMob[MobNum - 1]->m_Act._engage == 몹_엄폐물에숨기)
		{
			FindHidingInTheWallLocation(MobNum - 1);
		}
	}
	MobStart = false;
}

void UnitBox::teamSummon()
{
	int num = 1;
	for (int i = 0; i < num; i++)
	{
		TeamNum++;
		m_pTeam.resize(TeamNum);
		m_pTeam[TeamNum - 1] = new TeamAI;
		m_pTeam[TeamNum - 1]->Init();
		//m_pTeam[TeamNum - 1]->SetPosition(&D3DXVECTOR3(GSM().TeamPos.x + NODE_POSITSIZE, 2.67f, GSM().TeamPos.z + ((TeamNum) * 20 + NODE_POSITSIZE)));
		m_pTeam[TeamNum - 1]->SetPosition(&D3DXVECTOR3((GSM().TeamPos.x + NODE_POSITSIZEX - 50), 2.67f, GSM().TeamPos.z + 70 + (rand() % 160)));
	}
}

vector<Mob*>* UnitBox::getPMob()
{
	
	return &m_pMob;
}

vector<TeamAI*>* UnitBox::getPTeam()
{
	return &m_pTeam;
}