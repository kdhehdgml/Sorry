#include "stdafx.h"
#include "UnitBox.h"
#include "Cubeman.h"
#include "Mob.h"
#include "Ray.h"

UnitBox::UnitBox()
{
	for (size_t i = 0; i < m_pMob.size(); i++)
	{
		m_pMob[i] = NULL;
	}
	m_pCubeman = NULL;
	m_SameChk = false;
	num = 0;
}


UnitBox::~UnitBox()
{
	for (size_t i = 0; i < m_pMob.size(); i++)
	{
		SAFE_RELEASE(m_pMob[i]);
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
		num++;
		m_pMob.resize(num);
		m_pMob[num-1] = new Mob;
		m_pMob[num-1]->Init();
		m_pMob[num-1]->SetPosition(&D3DXVECTOR3(GSM().mobPos.x + NODE_POSITSIZE, 2.67f, GSM().mobPos.z + 150));
		//(num * 20 + NODE_POSITSIZE)
		FindHidingInTheWallLocation(num-1);
	}
	for (size_t i = 0; i < m_pMob.size(); i++)
	{
		SAFE_UPDATE(m_pMob[i]);
	}
	//타겟을따라서 움직이는 내용
	if (m_pMob.size() > 0)
	{
		for (int i = 0; i < m_pMob.size(); i++)
		{
			if (m_pMob[i]->PlayerSearch(m_pCubeman->GetPosition(), m_pMob[i]) == true)
			{
				//m_pMob[i]->SetDestination(m_pCubeman->GetPosition());
				m_pMob[i]->GetTargetPostion(m_pCubeman->GetPosition());
				m_pMob[i]->UpdatePositionToDestination();
			}
			m_pMob[i]->ShootVertex(m_pCubeman->GetPosition(), m_pMob[i]);
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
				m_pMob[i]->SetDestination(D3DXVECTOR3(5.0f + NODE_POSITSIZE, 2.67f, GSM().mobPos.z + 150));
				//((i + 1) * 20 + NODE_POSITSIZE)
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

			if (m_pMob[i]->m_move == true)
			{
				float Dist = D3DXVec3Length(&(m_pMob[i]->SetMoveTheWall().back() - m_pMob[i]->GetPosition()));
				if (Dist < 5)
				{
					if (m_CanSave[m_pMob[i]->SetLocationNum().back()] == true&& m_pMob[i]->SetDetermined() == false)
					{
						m_pMob[i]->GetDetermined(true);
						//1은 원래길로가는것
						MoveType = 1;
						m_CanSave[m_pMob[i]->SetLocationNum().back()] = false;
					}
					else if(m_pMob[i]->SetDetermined() == false)
					{
						//2는 차선으로 가는것
						MoveType = 2;
						int j = m_pMob[i]->SetTemporary().size() - 1;
						while (j > -1)
						{
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
						m_CanSave[m_pMob[i]->SetLocationNum().back()] = false;
						m_pMob[i]->SetDestination(m_pMob[i]->SetMoveTheWall().back());
						m_pMob[i]->UpdatePositionToDestination();
						Dist = D3DXVec3Length(&(m_pMob[i]->SetMoveTheWall().back() - m_pMob[i]->GetPosition()));
						m_pMob[i]->GetDetermined(true);
					}
				}
				
				if (Dist < 0.3f)
				{
					m_pMob[i]->num++;
					if (m_pMob[i]->num > 100)
					{
						m_pMob[i]->GetDetermined(false);
						m_pMob[i]->EraseWallLocation();
						m_pMob[i]->m_move = false;
						m_pMob[i]->num = 0;
						m_CanSave[m_pMob[i]->SetLocationNum().back()] = true;
					}
				}
			}
		}
	}
}
void UnitBox::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
			}
		}
	}
	break;
	default:
		break;
	}
}
