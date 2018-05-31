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
		m_pMob[i]->SetPosition(&D3DXVECTOR3(50.0f, 5.0f, (i + 1) * 10));
	}
	/*for (size_t i = 0; i < m_pAstar->GetNodes().size(); i++)
	{
		if (m_pAstar->GetNodes()[i]->m_nodeState == STATE_WALL)
		{
			SaveLocation.push_back(m_pAstar->GetNodes()[i]->GetLocation());
		}
	}*/
}

void UnitBox::Update()
{
	SAFE_UPDATE(m_pCubeman);
	
	for (size_t i = 0; i < m_pMob.size(); i++)
	{
		SAFE_UPDATE(m_pMob[i]);
	}
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
	}
	m_pMob[0]->ShootVertex(m_pCubeman->GetPosition(), m_pMob[0]);
	m_pMob[1]->ShootVertex(m_pCubeman->GetPosition(), m_pMob[1]);
	m_pMob[2]->ShootVertex(m_pCubeman->GetPosition(), m_pMob[2]);
	m_pMob[3]->ShootVertex(m_pCubeman->GetPosition(), m_pMob[3]);
	m_pMob[4]->ShootVertex(m_pCubeman->GetPosition(), m_pMob[4]);		*/
	
	for (size_t i = 0; i < m_pMob.size(); i++)
	{
		for (size_t j = 0; j < SaveLocation.size(); j++)
		{
			float Dist = D3DXVec3Length(&(SaveLocation[j] - m_pMob[i]->GetPosition()));
			if (Dist <= 5)
			{
				
				if (m_pMob[i]->m_move == false)
				{
					if (SaveLocation.empty() == false)
					{
						SaveLocation[j].x += 1.0f;
						m_pMob[i]->SetDestination(SaveLocation[j]);
						m_pMob[i]->m_move = true;
						SaveLocation.erase(SaveLocation.begin() + j);
					}
					else
					{
						m_pMob[i]->SetDestination(D3DXVECTOR3(5.0f, 5.0f, (i + 1) * 10));
					}
				}
				else
				{
					m_pMob[i]->num++;
					if (m_pMob[i]->num > 100)
					{
						m_pMob[i]->m_move = false;
					}
				}
				m_pMob[i]->UpdatePositionToDestination();
			}
			else if (m_pMob[i]->m_move == false)
			{

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
	SAFE_RENDER(m_pCubeman);
}
