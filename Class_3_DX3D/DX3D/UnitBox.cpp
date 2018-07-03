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
	//�Ʊ�AI����
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
	//�Ĺ� ���� ��ȯ
	if (GetAsyncKeyState(VK_F5) & 0x0001)
	{
		teamSummon();
	}
	//�Ĺ� ���� ����
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

	////���� ���������� ��ֹ� ��������ġ ����
	//for (auto p : m_pMob)
	//{
	//	if(p->m_Act._moving==��_�����̵�)
	//		p->EraseLocationSoldier();
	//}
	//�Ʊ�Ai�� ��Ai�ν��ϴ� ����
	if (m_pTeam.size() > 0)
	{
		for (size_t i = 0; i < m_pTeam.size(); i++)
		{
			SAFE_UPDATE(m_pTeam[i]);
		}
	}
	if (MobStart)
	{
		//Ÿ�������� �����̴� ����
		if (m_pMob.size() > 0)
		{
			for (size_t i = 0; i < m_pMob.size(); i++)
			{
				SAFE_UPDATE(m_pMob[i]);
				//��ֹ��ڿ� ����
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
					leng > 0 ? sum+= (int)����ֹ����� : sum += (int)����ֹ�����;
				}
			}
		}
		switch (sum)
		{
		case 0:
			m_CanSeeDirection.push_back(��������);
		case 1:
			m_CanSeeDirection.push_back(����ֹ�����);
			break;
		case 2:
			m_CanSeeDirection.push_back(����ֹ�����);
			break;
		case 3:
			m_CanSeeDirection.push_back(��������);
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
//���� ������ ��� ����
void UnitBox::FindHidingInTheWallLocation(int _Mobnum)
{
	D3DXVECTOR3 Save;
	for (size_t i = 0; i < m_SaveLocation.size(); i++)
	{
		Save = D3DXVECTOR3(m_SaveLocation[i].x + 6.0f, m_SaveLocation[i].y, m_SaveLocation[i].z);
		//����ġ�κ��� Z����10�ΰ��� �˻�
		if (abs(m_SaveLocation[i].z - m_pMob[_Mobnum]->GetPosition().z) < 10)
		{
			if (i == 0)
			{
				m_pMob[_Mobnum]->SetMoveTheWall(Save,i, m_CanSeeDirection[i]);
				continue;
			}

			for (int j = 0; j < m_pMob[_Mobnum]->GetMoveTheWall().size(); j++)
			{
				//���� ��������ġ�� ������ ��ֹ���ġ�� x���� ���������� ���� 
				if (m_pMob[_Mobnum]->GetMoveTheWall()[j].x != Save.x)
				{
					m_SameChk = false;
				}
				else //���� ��������ġ�� ������ ��ֹ���ġ�� x���� ������ �ӽ�����
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
	//��������ġ���� ����(�ڷΰ����� ����ġ�� �����)
	m_pMob[_Mobnum]->LocationSwap();
	//�ӽ���������ġ���� ����(�ڷΰ����� ���������� �����)
	m_pMob[_Mobnum]->TemporarySwap();
}

void UnitBox::MobMoveInTheWall(int _Mobnum)
{
	//����������ġ�� ������ ��ȣ�� ����
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
		//�����̵��ϴ³� && �����̵��̾ �����ÿ� ���买������ && ���ڸ���� �ϴٰ� ���� ������
		if (m_pMob[_Mobnum]->m_Act._moving == ��_�����̵� || (m_pMob[_Mobnum]->m_Act._engage == ��_���󹰿����� && m_pMob[_Mobnum]->PlayerSearch() == true)
			|| ((m_pMob[_Mobnum]->HaveBullet() == false && m_pMob[_Mobnum]->MaxBullet() == true) && m_pMob[_Mobnum]->m_Act._engage == ��_���ڸ�����))
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
					//������ΰ��°�
					if (m_CanSave[m_pMob[_Mobnum]->GetLocationNum().back()] == true)
					{
						m_pMob[_Mobnum]->SetDetermined(true);
						m_CanSave[m_pMob[_Mobnum]->GetLocationNum().back()] = false;
					}
					else     //�������� ���°�
					{
						int j = m_pMob[_Mobnum]->GetTemporary().size() - 1;
						while (j > -1)
						{
							//����ġ���� �ӽ�������ġ�� �ڿ������� ����
							if (m_pMob[_Mobnum]->GetMoveTheWall().back().x < m_pMob[_Mobnum]->GetTemporary()[j].x)
							{
								m_pMob[_Mobnum]->EraseTemporary();
								j = m_pMob[_Mobnum]->GetTemporary().size() - 1;
								continue;
							}
							//���� ����ġ�� X���̶� �ӽ�������ġ�� X���� ������(�����濡�ִ°�)
							if (m_pMob[_Mobnum]->GetMoveTheWall().back().x == m_pMob[_Mobnum]->GetTemporary()[j].x)
							{
								//�ӽ�������ġ�� �����ִ°��϶� �������ִ���ġ ����� �ӽ�������ġ�� �������
								if (m_CanSave[m_pMob[_Mobnum]->GetTemporaryNum().back()] == true)
								{
									m_pMob[_Mobnum]->EraseWallLocation();
									m_pMob[_Mobnum]->SetMoveTheWall(m_pMob[_Mobnum]->GetTemporary().back(), m_pMob[_Mobnum]->GetTemporaryNum().back()
									,m_pMob[_Mobnum]->GetTemporaryDirection().back());
									m_pMob[_Mobnum]->EraseTemporary();
									break;
								}
								else //�����°��϶� �ű����
								{
									m_pMob[_Mobnum]->EraseTemporary();
									j = m_pMob[_Mobnum]->GetTemporary().size() - 1;
								}

							}
							else //�����濡 �ӽ�������ġ�� ������ ������ �׶��� ����
							{
								m_pMob[_Mobnum]->EraseWallLocation();
								break;
							}
						}

						//�����̵��϶� ��ܿ� ���뿡�� ������������ϰ� �ϴܳ��뿡�� �̵��� ����ġ �����Ը���
						if (m_pMob[_Mobnum]->GetLocationNum().empty() == false)
						{
							m_CanSave[m_pMob[_Mobnum]->GetLocationNum().back()] = false;
							m_pMob[_Mobnum]->SetDestination(m_pMob[_Mobnum]->GetMoveTheWall().back());
							m_pMob[_Mobnum]->UpdatePositionToDestination();
							Dist = D3DXVec3Length(&(m_pMob[_Mobnum]->GetMoveTheWall().back() - m_pMob[_Mobnum]->GetPosition()));
						}
						//��ֹ� ������
						m_pMob[_Mobnum]->SetDetermined(true);
					}
				}
				//���� ��ֹ��� ���� ���� ���ǹ�
				if (Dist < 1.0f)
				{
					m_pMob[_Mobnum]->hidingChk = true;
					if (m_pMob[_Mobnum]->PlayerSearch() == �ֺ�������)
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
		if (m_pMob[MobNum - 1]->m_Act._moving == ��_�����̵� || m_pMob[MobNum - 1]->m_Act._reload == ��_������ || m_pMob[MobNum - 1]->m_Act._engage == ��_���󹰿�����)
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
		if (m_pMob[MobNum - 1]->m_Act._moving == ��_�����̵� || m_pMob[MobNum - 1]->m_Act._reload == ��_������ || m_pMob[MobNum - 1]->m_Act._engage == ��_���󹰿�����)
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