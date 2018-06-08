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
	TeamNum = 0;
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
}

void UnitBox::Update()
{
	SAFE_UPDATE(m_pCubeman);
	
	/*for (auto p : m_pMob) {
		if (p->getStatus() == 0) {
			SAFE_RELEASE(p);
		}
	}*/

	if (GetAsyncKeyState(VK_F1) & 0x0001)
	{
		int GroupNum = 1;
		for (int i = 0; i < GroupNum; i++)
		{
			MobNum++;
			m_pMob.resize(MobNum);
			m_pMob[MobNum - 1] = new Mob;
			m_pMob[MobNum - 1]->Init();
			//m_pMob[MobNum - 1]->SetPosition(&D3DXVECTOR3(GSM().mobPos.x + NODE_POSITSIZE, 2.67f, GSM().mobPos.z + ((MobNum) * 20 + NODE_POSITSIZE)));
			m_pMob[MobNum - 1]->SetPosition(&D3DXVECTOR3((GSM().mobPos.x + NODE_POSITSIZE) + (rand() % 100), 2.67f, GSM().mobPos.z + 70 + (rand() % 160)));
			FindHidingInTheWallLocation(MobNum - 1);
		}
	}
	if (GetAsyncKeyState(VK_F2) & 0x0001)
	{
		int GroupNum = 5;
		for (int i = 0; i < GroupNum; i++)
		{
			MobNum++;
			m_pMob.resize(MobNum);
			m_pMob[MobNum - 1] = new Mob;
			m_pMob[MobNum - 1]->Init();
			//m_pMob[MobNum - 1]->SetPosition(&D3DXVECTOR3(GSM().mobPos.x + NODE_POSITSIZE, 2.67f, GSM().mobPos.z + ((MobNum) * 20 + NODE_POSITSIZE)));
			m_pMob[MobNum - 1]->SetPosition(&D3DXVECTOR3((GSM().mobPos.x + NODE_POSITSIZE) + (rand() % 100), 2.67f, GSM().mobPos.z + 70 + (rand() % 160)));
			FindHidingInTheWallLocation(MobNum - 1);
		}
	}
	if (GetAsyncKeyState(VK_F3) & 0x0001)
	{
		int GroupNum = 10;
		for (int i = 0; i < GroupNum; i++)
		{
			MobNum++;
			m_pMob.resize(MobNum);
			m_pMob[MobNum - 1] = new Mob;
			m_pMob[MobNum - 1]->Init();
			//m_pMob[MobNum - 1]->SetPosition(&D3DXVECTOR3(GSM().mobPos.x + NODE_POSITSIZE, 2.67f, GSM().mobPos.z + ((MobNum) * 20 + NODE_POSITSIZE)));
			m_pMob[MobNum - 1]->SetPosition(&D3DXVECTOR3((GSM().mobPos.x + NODE_POSITSIZE) + (rand() % 100), 2.67f, GSM().mobPos.z + 70 + (rand() % 160)));

			FindHidingInTheWallLocation(MobNum - 1);
		}
	}
	if (GetAsyncKeyState(VK_F4) & 0x0001)
	{
		int GroupNum = 20;
		for (int i = 0; i < GroupNum; i++)
		{
			MobNum++;
			m_pMob.resize(MobNum);
			m_pMob[MobNum - 1] = new Mob;
			m_pMob[MobNum - 1]->Init();
			//m_pMob[MobNum - 1]->SetPosition(&D3DXVECTOR3(GSM().mobPos.x + NODE_POSITSIZE, 2.67f, GSM().mobPos.z + ((MobNum) * 20 + NODE_POSITSIZE)));
			m_pMob[MobNum - 1]->SetPosition(&D3DXVECTOR3((GSM().mobPos.x + NODE_POSITSIZE) + (rand() % 100), 2.67f, GSM().mobPos.z + 70 + (rand() % 160)));
			FindHidingInTheWallLocation(MobNum - 1);
		}
	}
	if (GetAsyncKeyState(VK_F5) & 0x0001)
	{
		TeamNum++;
		m_pTeam.resize(TeamNum);
		m_pTeam[TeamNum - 1] = new TeamAI;
		m_pTeam[TeamNum - 1]->Init();
		//m_pTeam[TeamNum - 1]->SetPosition(&D3DXVECTOR3(GSM().TeamPos.x + NODE_POSITSIZE, 2.67f, GSM().TeamPos.z + ((TeamNum) * 20 + NODE_POSITSIZE)));
		m_pTeam[TeamNum - 1]->SetPosition(&D3DXVECTOR3((GSM().TeamPos.x + NODE_POSITSIZE), 2.67f, GSM().TeamPos.z + 70 + (rand() % 160)));
	}

	if (GetAsyncKeyState(VK_F6) & 0x0001)
	{
		TeamNum++;
		m_pTeam.resize(TeamNum);
		m_pTeam[TeamNum - 1] = new TeamAI;
		m_pTeam[TeamNum - 1]->Init();
		//m_pTeam[TeamNum - 1]->SetPosition(&D3DXVECTOR3(GSM().TeamPos.x + NODE_POSITSIZE, 2.67f, GSM().TeamPos.z + ((TeamNum) * 20 + NODE_POSITSIZE)));
		m_pTeam[TeamNum - 1]->SetPosition(&D3DXVECTOR3((GSM().TeamPos.x + NODE_POSITSIZE - 50), 2.67f, GSM().TeamPos.z + 70 + (rand() % 160)));
	}
	if (GetAsyncKeyState(VK_F7) & 0x0001)
	{
		for (int i = 0; i < m_pTeam.size(); i++)
		{
			m_pTeam[i]->GetTargetPostion(D3DXVECTOR3((GSM().TeamPos.x + NODE_POSITSIZE), 2.67f, m_pTeam[i]->GetPosition().z));
			m_pTeam[i]->UpdatePositionToDestination();
		}
	}
	for (size_t i = 0; i < m_pMob.size(); i++)
	{
		SAFE_UPDATE(m_pMob[i]);
	}
	for (size_t i = 0; i < m_pTeam.size(); i++)
	{
		SAFE_UPDATE(m_pTeam[i]);
	}
	//타겟을따라서 움직이는 내용
	if (m_pMob.size() > 0)
	{
		for (int i = 0; i < m_pMob.size(); i++)
		{
			if (m_pMob[i]->PlayerSearch(m_pMob[i]) == true)
			{
				//m_pMob[i]->SetDestination(m_pCubeman->GetPosition());
				m_pMob[i]->GetTargetPostion(m_pCubeman->GetPosition());
				m_pMob[i]->UpdatePositionToDestination();
			}
			m_pMob[i]->ShootVertex(m_pMob[i]);
		}
	}
	//아군Ai가 적Ai인식하는 내용
	if (m_pTeam.size() > 0)
	{
		for (int i = 0; i < m_pTeam.size(); i++)
		{
			if (m_pTeam[i]->MobSearch(m_pTeam[i]) == true)
			{
				//m_pTeam[i]->SetDestination(m_pCubeman->GetPosition());
				//m_pTeam[i]->UpdatePositionToDestination();
			}
			m_pTeam[i]->ShootVertex(m_pTeam[i]);
		}
	}
	
	
	
	//타겟과 플레이어를 이어주는 선긋기
	/*m_pMob[0]->ShootVertex(m_pCubeman->GetPosition(), m_pMob[0]);
	m_pMob[1]->ShootVertex(m_pCubeman->GetPosition(), m_pMob[1]);
	m_pMob[2]->ShootVertex(m_pCubeman->GetPosition(), m_pMob[2]);
	m_pMob[3]->ShootVertex(m_pCubeman->GetPosition(), m_pMob[3]);
	m_pMob[4]->ShootVertex(m_pCubeman->GetPosition(), m_pMob[4]);*/
	
	//장애물뒤에 숨기
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

void UnitBox::FindHidingInTheWallLocation(int _Mobnum)
{
	D3DXVECTOR3 Save;
	for (size_t i = 0; i < m_SaveLocation.size(); i++)
	{
		Save = D3DXVECTOR3(m_SaveLocation[i].x + 1.0f, m_SaveLocation[i].y, m_SaveLocation[i].z);
		if (abs(m_SaveLocation[i].z - m_pMob[_Mobnum]->GetPosition().z) < 10)
		{
			if (i == 0)
			{
				m_pMob[_Mobnum]->GetMoveTheWall(Save,i);
				continue;
			}
			for (int j = 0; j < m_pMob[_Mobnum]->SetMoveTheWall().size(); j++)
			{
				if (m_pMob[_Mobnum]->SetMoveTheWall()[j].x != Save.x)
				{
					m_SameChk = false;
				}
				else
				{
					m_SameChk = true;
					m_pMob[_Mobnum]->GetTemporary(Save,i);
					j = m_pMob[_Mobnum]->SetMoveTheWall().size();
				}
			}
			if (m_SameChk == false)
			{
				m_pMob[_Mobnum]->GetMoveTheWall(Save,i);
			}
			m_SameChk = false;
		}
	}
	if ( m_pMob[_Mobnum]->SetMoveTheWall().size() > 1)
	{
		for (int i = 0; i < m_pMob[_Mobnum]->SetMoveTheWall().size() - 1; i++)
		{
			for (int j = 0; j < m_pMob[_Mobnum]->SetMoveTheWall().size() - 1; j++)
			{
				if (m_pMob[_Mobnum]->SetMoveTheWall()[j].x > m_pMob[_Mobnum]->SetMoveTheWall()[j + 1].x)
				{
					m_pMob[_Mobnum]->LocationSwap(j, j + 1);
				}
			}
		}
	}
	if (m_pMob[_Mobnum]->SetTemporary().size() > 1)
	{
		for (int i = 0; i < m_pMob[_Mobnum]->SetTemporary().size() - 1; i++)
		{
			for (int j = 0; j < m_pMob[_Mobnum]->SetTemporary().size() - 1; j++)
			{
				if (m_pMob[_Mobnum]->SetTemporary()[j].x > m_pMob[_Mobnum]->SetTemporary()[j + 1].x)
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
		int MoveType = 0;
		if (m_pMob[i]->SetMoveTheWall().empty() == true)
		{
			if (m_pMob[i]->m_move == false)
			{
				//m_pMob[i]->SetDestination(D3DXVECTOR3(5.0f + NODE_POSITSIZE, 2.67f, GSM().mobPos.z + ((i + 1) * 20 + NODE_POSITSIZE)));
				m_pMob[i]->SetDestination(D3DXVECTOR3(GSM().mobPos.x - GSM().mapSize / 3, 2.67f, m_pMob[i]->GetPosition().z));
				m_pMob[i]->m_move = true;
			}
		}
		else
		{
			if (m_pMob[i]->m_move == false)
			{
				m_pMob[i]->SetDestination(m_pMob[i]->SetMoveTheWall().back());
				m_pMob[i]->UpdatePositionToDestination();
				m_pMob[i]->m_move = true;
			}

			if(m_pMob[i]->m_move == true)
			{
				float Dist = D3DXVec3Length(&(m_pMob[i]->SetMoveTheWall().back() - m_pMob[i]->GetPosition()));
				if (Dist < 5 && m_pMob[i]->SetDetermined() == false)
				{
					if (m_CanSave[m_pMob[i]->SetLocationNum().back()] == true)
					{
						m_pMob[i]->GetDetermined(true);
						//1은 원래길로가는것
						MoveType = 1;
						m_CanSave[m_pMob[i]->SetLocationNum().back()] = false;
					}
					else
					{
						//2는 차선으로 가는것
						MoveType = 2;
						int j = m_pMob[i]->SetTemporary().size() - 1;
						while (j > -1)
						{
							if (m_pMob[i]->SetMoveTheWall().back().x < m_pMob[i]->SetTemporary()[j].x)
							{
								m_pMob[i]->EraseTemporary();
								j = m_pMob[i]->SetTemporary().size() - 1;
								continue;
							}

							if (m_pMob[i]->SetMoveTheWall().back().x == m_pMob[i]->SetTemporary()[j].x)
							{
								if (m_CanSave[m_pMob[i]->SetTemporaryNum().back()] == true)
								{
									m_pMob[i]->EraseWallLocation();
									m_pMob[i]->GetMoveTheWall(m_pMob[i]->SetTemporary().back(), m_pMob[i]->SetTemporaryNum().back());
									m_pMob[i]->EraseTemporary();
									break;
								}
								else
								{
									m_pMob[i]->EraseTemporary();
									j = m_pMob[i]->SetTemporary().size() - 1;
								}
								
							}
							else
							{
								m_pMob[i]->EraseWallLocation();
								break;
							}
						}
						if (m_pMob[i]->SetLocationNum().empty() == false)
						{
							m_CanSave[m_pMob[i]->SetLocationNum().back()] = false;
							m_pMob[i]->SetDestination(m_pMob[i]->SetMoveTheWall().back());
							m_pMob[i]->UpdatePositionToDestination();
							Dist = D3DXVec3Length(&(m_pMob[i]->SetMoveTheWall().back() - m_pMob[i]->GetPosition()));

						}
						m_pMob[i]->GetDetermined(true);
					}
				}

				if (Dist < 1.0f)
				{
					m_pMob[i]->num++;
					if (m_pMob[i]->num > 100)
					{
						m_CanSave[m_pMob[i]->SetLocationNum().back()] = true;
						m_pMob[i]->GetDetermined(false);
						m_pMob[i]->EraseWallLocation();
						m_pMob[i]->m_move = false;
						m_pMob[i]->num = 0;
						
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
