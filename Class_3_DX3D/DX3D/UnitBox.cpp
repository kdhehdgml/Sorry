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
	m_pMob.resize(5);

	for (size_t i = 0; i < m_pMob.size(); i++)
	{
		m_pMob[i] = new Mob;
		m_pMob[i]->Init();
		m_pMob[i]->SetPosition(&D3DXVECTOR3(GSM().mobPos.x + NODE_POSITSIZE, 2.67f, GSM().mobPos.z + ((i + 1) * 20 + NODE_POSITSIZE)));
		FindHidingInTheWallLocation(i);
	}
}

void UnitBox::Update()
{
	SAFE_UPDATE(m_pCubeman);
	
	for (size_t i = 0; i < m_pMob.size(); i++)
	{
		SAFE_UPDATE(m_pMob[i]);
	}
	//타겟을따라서 움직이는 내용
	/*if (m_pMob[0]->PlayerSearch(m_pCubeman->GetPosition(), m_pMob[0]) == true)
	{
		m_pMob[0]->SetDestination(m_pCubeman->GetPosition());
		m_pMob[0]->UpdatePositionToDestination();
	}
	if (m_pMob[1]->PlayerSearch(m_pCubeman->GetPosition(), m_pMob[1]) == true)
	{
		m_pMob[1]->SetDestination(m_pCubeman->GetPosition());
		m_pMob[1]->UpdatePositionToDestination();
	}
	if (m_pMob[2]->PlayerSearch(m_pCubeman->GetPosition(), m_pMob[2]) == true)
	{
		m_pMob[2]->SetDestination(m_pCubeman->GetPosition());
		m_pMob[2]->UpdatePositionToDestination();
	}
	if (m_pMob[3]->PlayerSearch(m_pCubeman->GetPosition(), m_pMob[3]) == true)
	{
		m_pMob[3]->SetDestination(m_pCubeman->GetPosition());
		m_pMob[3]->UpdatePositionToDestination();
	}
	if (m_pMob[4]->PlayerSearch(m_pCubeman->GetPosition(), m_pMob[4]) == true)
	{
		m_pMob[4]->SetDestination(m_pCubeman->GetPosition());
		m_pMob[4]->UpdatePositionToDestination();
	}*/
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
	for (int i = 0; i < SaveLocation.size(); i++)
	{
		if (abs(SaveLocation[i].z - m_pMob[_Mobnum]->GetPosition().z) < 7)
		{
			D3DXVECTOR3 Save;
			Save = { SaveLocation[i].x + 1.0f, SaveLocation[i].y, SaveLocation[i].z };
			m_pMob[_Mobnum]->GetMoveTheWall(Save);
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
				//m_pMob[i]->SetDestination(D3DXVECTOR3(5.0f + NODE_POSITSIZE, 2.67f, (i + 1) * 20 + NODE_POSITSIZE));
				m_pMob[i]->SetDestination(D3DXVECTOR3(GSM().mobDestLine , 2.67f, GSM().mobPos.z + ((i + 1) * 20 + NODE_POSITSIZE)));
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
