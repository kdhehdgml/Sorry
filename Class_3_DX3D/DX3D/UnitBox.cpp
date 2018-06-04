#include "stdafx.h"
#include "UnitBox.h"
#include "Cubeman.h"
#include "Mob.h"

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
	
}

void UnitBox::Update()
{
	SAFE_UPDATE(m_pCubeman);
	
	if (GetAsyncKeyState(VK_F1) & 0x0001)
	{
		num++;
		m_pMob.resize(num);
		m_pMob[num-1] = new Mob;
		m_pMob[num-1]->Init();
		m_pMob[num-1]->SetPosition(&D3DXVECTOR3(GSM().mobPos.x + NODE_POSITSIZE, 2.67f, GSM().mobPos.z + ((num) * 20 + NODE_POSITSIZE)));
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
				/*m_pMob[i]->SetDestination(m_pCubeman->GetPosition());
				m_pMob[i]->UpdatePositionToDestination();*/
				m_pMob[i]->ShootVertex(m_pCubeman->GetPosition(), m_pMob[i]);
			}
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
	for (size_t i = 0; i < SaveLocation.size(); i++)
	{
		Save = D3DXVECTOR3(SaveLocation[i].x + 1.0f, SaveLocation[i].y, SaveLocation[i].z);
		if (abs(SaveLocation[i].z - m_pMob[_Mobnum]->GetPosition().z) < 30)
		{
			if (i == 0)
			{
				m_pMob[_Mobnum]->GetMoveTheWall(Save);
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
					j = m_pMob[_Mobnum]->SetMoveTheWall().size();
				}
				
			}
			if (m_SameChk == false)
			{
				m_pMob[_Mobnum]->GetMoveTheWall(Save);
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
	
}

void UnitBox::MobMoveInTheWall()
{
	for (size_t i = 0; i < m_pMob.size(); i++)
	{
		float Dist = 0;
		if (m_pMob[i]->SetMoveTheWall().empty() == true)
		{
			if (m_pMob[i]->m_move == false)
			{
				m_pMob[i]->SetDestination(D3DXVECTOR3(5.0f + NODE_POSITSIZE, 2.67f, GSM().mobPos.z + ((i + 1) * 20 + NODE_POSITSIZE)));
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
				Dist = D3DXVec3Length(&(m_pMob[i]->SetMoveTheWall().back() - m_pMob[i]->GetPosition()));

				if (Dist < 0.3f)
				{
					m_pMob[i]->num++;
					if (m_pMob[i]->num > 100)
					{

						m_pMob[i]->EraseWallLocation();
						m_pMob[i]->m_move = false;
						m_pMob[i]->num = 0;
					}
				}
			}
		}
	}
}

