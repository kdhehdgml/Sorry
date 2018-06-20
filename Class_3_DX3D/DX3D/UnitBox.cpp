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

	if (GetAsyncKeyState(VK_F1) & 0x0001)
	{
		g_pSoundManager->playMusic(1);
		g_pSoundManager->effectSound(0);

		int GroupNum = 1;
		for (int i = 0; i < GroupNum; i++)
		{
			MobNum++;
			m_pMob.resize(MobNum);
			m_pMob[MobNum - 1] = new Mob;
			m_pMob[MobNum - 1]->Init();

			//m_pMob[MobNum - 1]->SetPosition(&D3DXVECTOR3(GSM().mobPos.x + NODE_POSITSIZE, 2.67f, GSM().mobPos.z + ((MobNum) * 20 + NODE_POSITSIZE)));
			m_pMob[MobNum - 1]->SetPosition(&D3DXVECTOR3(GSM().mobPos.x + (rand() % 40), 2.67f, GSM().mobPos.z + (rand() % 350)));
			if (m_pMob[MobNum - 1]->m_Act._moving == 1)
				FindHidingInTheWallLocation(MobNum - 1);
			else if(m_pMob[MobNum - 1]->m_Act._engage != ��_�����ϰ���)
				FindHidingInTheWallLocationRushSoldier(MobNum - 1);
		}
	}
	//�Ĺ� ���� ��ȯ
	if (GetAsyncKeyState(VK_F5) & 0x0001)
	{
		int Num = 10;
		for (int i = 0; i < Num; i++)
		{
			TeamNum++;
			m_pTeam.resize(TeamNum);
			m_pTeam[TeamNum - 1] = new TeamAI;
			m_pTeam[TeamNum - 1]->Init();
			//m_pTeam[TeamNum - 1]->SetPosition(&D3DXVECTOR3(GSM().TeamPos.x + NODE_POSITSIZE, 2.67f, GSM().TeamPos.z + ((TeamNum) * 20 + NODE_POSITSIZE)));
			m_pTeam[TeamNum - 1]->SetPosition(&D3DXVECTOR3((GSM().TeamPos.x + NODE_POSITSIZEX - 50), 2.67f, GSM().TeamPos.z + 70 + (rand() % 160)));
		}
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

	//���� ���������� ��ֹ� ��������ġ ����
	for (auto p : m_pMob)
	{
		if(p->m_Act._moving==0)
			p->EraseLocationSoldier();
	}

	//Ÿ�������� �����̴� ����
	if (m_pMob.size() > 0)
	{
		for (size_t i = 0; i < m_pMob.size(); i++)
		{
			SAFE_UPDATE(m_pMob[i]);
		}

		for (int i = 0; i < m_pMob.size(); i++)
		{
			if (m_pMob[i]->PlayerSearch() == true)
			{
				if (m_pMob[i]->m_Act._engage == ��_���ڸ�����)
				{
					m_pMob[i]->SetMoveSpeed(0.1f);
				}
				
				/*m_pMob[i]->SetTargetPostion(m_pCubeman->GetPosition());
				m_pMob[i]->UpdatePositionToDestination();*/
			}
			else if (m_pMob[i]->m_Act._engage == ��_���ڸ�����)
			{
				m_pMob[i]->SetMoveSpeed(2.0f);
			}
			m_pMob[i]->ShootVertex();
		}
	}
	//�Ʊ�Ai�� ��Ai�ν��ϴ� ����
	if (m_pTeam.size() > 0)
	{
		for (size_t i = 0; i < m_pTeam.size(); i++)
		{
			SAFE_UPDATE(m_pTeam[i]);
		}
		for (int i = 0; i < m_pTeam.size(); i++)
		{
			if (m_pTeam[i]->MobSearch() == true)
			{
				//	//m_pTeam[i]->SetDestination(m_pCubeman->GetPosition());
				//	//m_pTeam[i]->UpdatePositionToDestination();
			}
			//m_pTeam[i]->ShootVertex();
		}
	}
	//��ֹ��ڿ� ����
	MobMoveInTheWall();
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
				m_pMob[_Mobnum]->SetMoveTheWall(Save, i);
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
					m_pMob[_Mobnum]->SetTemporary(Save, i);
					j = m_pMob[_Mobnum]->GetMoveTheWall().size();
				}
			}
			if (m_SameChk == false)
			{
				m_pMob[_Mobnum]->SetMoveTheWall(Save, i);
			}
			m_SameChk = false;
		}
	}
	if (m_pMob[_Mobnum]->GetMoveTheWall().size() > 1)
	{
		for (int i = 0; i < m_pMob[_Mobnum]->GetMoveTheWall().size() - 1; i++)
		{
			for (int j = 0; j < m_pMob[_Mobnum]->GetMoveTheWall().size() - 1; j++)
			{
				if (m_pMob[_Mobnum]->GetMoveTheWall()[j].x > m_pMob[_Mobnum]->GetMoveTheWall()[j + 1].x)
				{
					m_pMob[_Mobnum]->LocationSwap(j, j + 1);
				}
			}
		}
	}
	if (m_pMob[_Mobnum]->GetTemporary().size() > 1)
	{
		for (int i = 0; i < m_pMob[_Mobnum]->GetTemporary().size() - 1; i++)
		{
			for (int j = 0; j < m_pMob[_Mobnum]->GetTemporary().size() - 1; j++)
			{
				if (m_pMob[_Mobnum]->GetTemporary()[j].x > m_pMob[_Mobnum]->GetTemporary()[j + 1].x)
				{
					m_pMob[_Mobnum]->TemporarySwap(j, j + 1);
				}
			}
		}
	}
}
//���� ������ ��� ����
void UnitBox::FindHidingInTheWallLocation(int _Mobnum)
{
	D3DXVECTOR3 Save;
	for (size_t i = 0; i < m_SaveLocation.size(); i++)
	{
		Save = D3DXVECTOR3(m_SaveLocation[i].x + 4.0f, m_SaveLocation[i].y, m_SaveLocation[i].z);
		//����ġ�κ��� Z����10�ΰ��� �˻�
		if (abs(m_SaveLocation[i].z - m_pMob[_Mobnum]->GetPosition().z) < 10)
		{
			if (i == 0)
			{
				m_pMob[_Mobnum]->SetMoveTheWall(Save,i);
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
					m_pMob[_Mobnum]->SetTemporary(Save,i);
					j = m_pMob[_Mobnum]->GetMoveTheWall().size();
				}
			}
			if (m_SameChk == false)
			{
				m_pMob[_Mobnum]->SetMoveTheWall(Save,i);
			}
			m_SameChk = false;
		}
	}
	//��������ġ���� ����(�ڷΰ����� ����ġ�� �����)
	if ( m_pMob[_Mobnum]->GetMoveTheWall().size() > 1)
	{
		for (int i = 0; i < m_pMob[_Mobnum]->GetMoveTheWall().size() - 1; i++)
		{
			for (int j = 0; j < m_pMob[_Mobnum]->GetMoveTheWall().size() - 1; j++)
			{
				if (m_pMob[_Mobnum]->GetMoveTheWall()[j].x > m_pMob[_Mobnum]->GetMoveTheWall()[j + 1].x)
				{
					m_pMob[_Mobnum]->LocationSwap(j, j + 1);
				}
			}
		}
	}
	//�ӽ���������ġ���� ����(�ڷΰ����� ���������� �����)
	if (m_pMob[_Mobnum]->GetTemporary().size() > 1)
	{
		for (int i = 0; i < m_pMob[_Mobnum]->GetTemporary().size() - 1; i++)
		{
			for (int j = 0; j < m_pMob[_Mobnum]->GetTemporary().size() - 1; j++)
			{
				if (m_pMob[_Mobnum]->GetTemporary()[j].x > m_pMob[_Mobnum]->GetTemporary()[j + 1].x)
				{
					m_pMob[_Mobnum]->TemporarySwap(j, j + 1);
				}
			}
		}
	}
}

void UnitBox::MobMoveInTheWall()
{
	for (size_t i = 0; i < m_pMob.size(); i++)
	{
		//����������ġ�� ������ ��ȣ�� ����
		if (m_pMob[i]->GetMoveTheWall().empty() == true)
		{
			if (m_pMob[i]->m_move == false)
			{
				//m_pMob[i]->SetDestination(D3DXVECTOR3(5.0f + NODE_POSITSIZE, 2.67f, GSM().mobPos.z + ((i + 1) * 20 + NODE_POSITSIZE)));
				m_pMob[i]->SetDestination(D3DXVECTOR3(GSM().mobPos.x - 340.0f, 2.67f, m_pMob[i]->GetPosition().z));
				m_pMob[i]->m_move = true;
			}
		}
		else
		{
			//�����̵��ϴ³� && �����̵��̾ �����ÿ� ���买������ && ���ڸ���� �ϴٰ� ���� ������
			if (m_pMob[i]->m_Act._moving == ��_�����̵� || (m_pMob[i]->m_Act._engage == ��_���󹰿����� && m_pMob[i]->PlayerSearch() == true)
				|| (m_pMob[i]->GetBullet() <=0 && m_pMob[i]->m_Act._engage == ��_���ڸ�����))
			{
				if (m_pMob[i]->m_move == false)
				{
					m_pMob[i]->SetDestination(m_pMob[i]->GetMoveTheWall().back());
					m_pMob[i]->UpdatePositionToDestination();
					m_pMob[i]->m_move = true;
				}

				if (m_pMob[i]->m_move == true)
				{
					float Dist = D3DXVec3Length(&(m_pMob[i]->GetMoveTheWall().back() - m_pMob[i]->GetPosition()));
					if (Dist < 20 && m_pMob[i]->GetDetermined() == false)
					{
						//1�� ������ΰ��°�
						if (m_CanSave[m_pMob[i]->GetLocationNum().back()] == true)
						{
							m_pMob[i]->SetDetermined(true);
							m_CanSave[m_pMob[i]->GetLocationNum().back()] = false;
						}
						else     //�������� ���°�
						{
							int j = m_pMob[i]->GetTemporary().size() - 1;
							while (j > -1)
							{
								//����ġ���� �ӽ�������ġ�� �ڿ������� ����
								if (m_pMob[i]->GetMoveTheWall().back().x < m_pMob[i]->GetTemporary()[j].x)
								{
									m_pMob[i]->EraseTemporary();
									j = m_pMob[i]->GetTemporary().size() - 1;
									continue;
								}
								//���� ����ġ�� X���̶� �ӽ�������ġ�� X���� ������(�����濡�ִ°�)
								if (m_pMob[i]->GetMoveTheWall().back().x == m_pMob[i]->GetTemporary()[j].x)
								{
									//�ӽ�������ġ�� �����ִ°��϶� �������ִ���ġ ����� �ӽ�������ġ�� �������
									if (m_CanSave[m_pMob[i]->GetTemporaryNum().back()] == true)
									{
										m_pMob[i]->EraseWallLocation();
										m_pMob[i]->SetMoveTheWall(m_pMob[i]->GetTemporary().back(), m_pMob[i]->GetTemporaryNum().back());
										m_pMob[i]->EraseTemporary();
										break;
									}
									else //�����°��϶� �ű����
									{
										m_pMob[i]->EraseTemporary();
										j = m_pMob[i]->GetTemporary().size() - 1;
									}

								}
								else //�����濡 �ӽ�������ġ�� ������ ������ �׶��� ����
								{
									m_pMob[i]->EraseWallLocation();
									break;
								}
							}

							//�����̵��϶� ��ܿ� ���뿡�� ������������ϰ� �ϴܳ��뿡�� �̵��� ����ġ �����Ը���
							if (m_pMob[i]->GetLocationNum().empty() == false)
							{
								m_CanSave[m_pMob[i]->GetLocationNum().back()] = false;
								m_pMob[i]->SetDestination(m_pMob[i]->GetMoveTheWall().back());
								m_pMob[i]->UpdatePositionToDestination();
								Dist = D3DXVec3Length(&(m_pMob[i]->GetMoveTheWall().back() - m_pMob[i]->GetPosition()));
							}
							//��ֹ� ������
							m_pMob[i]->SetDetermined(true);
						}
					}
					//���� ��ֹ��� ���� ���� ���ǹ�
					if (Dist < 1.0f)
					{
						m_pMob[i]->num++;
						if (m_pMob[i]->num > 100)
						{
							m_CanSave[m_pMob[i]->GetLocationNum().back()] = true;
							m_pMob[i]->SetDetermined(false);
							m_pMob[i]->EraseWallLocation();
							m_pMob[i]->m_move = false;
							m_pMob[i]->num = 0;

						}
					}
				}
			}
		}
	}
}
/*void UnitBox::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		Ray r = Ray::RayAtWorldSpace(SCREEN_POINT(lParam));
		for (auto p : m_pMob)
		{
			bool getHit = false;
			getHit = r.CalcIntersectSphere(p->getBoundingSphere());
			if (getHit) {
				p->setHealth(p->getHealth() - 100);
				break;
			}
		}
	}
	break;
	default:
		break;
	}
}*/

vector<Mob*>* UnitBox::getPMob()
{
	
	return &m_pMob;
}

vector<TeamAI*>* UnitBox::getPTeam()
{
	return &m_pTeam;
}