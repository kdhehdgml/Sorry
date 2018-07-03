#include "stdafx.h"
#include "IUnitObject.h"
#include "AStar.h"
#include "AStarNode.h"

IUnitObject::IUnitObject()
{
	m_isMoving = false;
	m_moveSpeed = 0.2f;
	m_currMoveSpeedRate = 1.0f;
	m_rotationSpeed = 0.1f;
	m_start = true;
	m_isJumping = false;
	m_jumpPower = 1.0f;
	m_gravity = 0.05f;
	m_currGravity = 0.0f;
	m_colision = false;
	m_maxStepHeight = 2.0f;
}


IUnitObject::~IUnitObject()
{
}

void IUnitObject::SetTargetPostion(const D3DXVECTOR3 & pos)
{
	m_destPos = m_pos;// 현재포지션으로 초기화 
	m_finalDestPos = pos;
}

void IUnitObject::SetDestination(const D3DXVECTOR3 & pos)
{

	//m_destPos = pos;

	//마우스 찍을떄마다 갱신

	m_vecAStarIndex.clear();
	m_destPos = m_pos;// 현재포지션으로 초기화 
	m_finalDestPos = pos;
	g_pCurrentMap->GetAStar()->FindPath(m_pos, pos, m_vecAStarIndex);
	g_pCurrentMap->GetAStar()->MakeDirectPath(m_pos, pos, m_vecAStarIndex);
}

void IUnitObject::UpdateKeyboardState()
{
	if (m_isJumping == false) m_isJumping = m_keyState.bJump;
	m_deltaPos.z = m_keyState.deltaPos.z;
	m_deltaRot.y = m_keyState.deltaRot.y;

	if (m_deltaPos.z == 0 && m_deltaRot.y == 0)
		return;

	D3DXMATRIXA16 matRY;
	D3DXMatrixRotationY(&matRY, m_deltaRot.y * m_rotationSpeed);
	D3DXVec3TransformNormal(&m_forward, &m_forward, &matRY);

	m_destPos = (D3DXVECTOR3(m_pos + m_forward * m_deltaPos.z*m_moveSpeed*m_currMoveSpeedRate));

	m_finalDestPos = m_destPos;
	m_vecAStarIndex.clear();
}

void IUnitObject::UpdatePositionToDestination()
{
	D3DXVECTOR3 targetPos = m_pos;

	UpdateTargetPosition(targetPos);
	ApplyTargetPosition(targetPos);
	
	D3DXMATRIXA16 m_matRotY;
	D3DXMatrixLookAtLH(&m_matRotY, &D3DXVECTOR3(0, 0, 0), &m_forward, &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&m_matRotY, &m_matRotY);
	D3DXMATRIXA16 matBaseR;
	D3DXMatrixRotationY(&matBaseR, m_baseRotY);
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	m_matWorld = m_matRotY * matBaseR * matT;

	/*if (D3DXVec3LengthSq(&m_deltaPos) > 0 || D3DXVec3LengthSq(&m_deltaRot) > 0)
		m_isMoving = true;
	else
		m_isMoving = false;*/

}

void IUnitObject::UpdateTargetPosition(OUT D3DXVECTOR3 & targetPos)
{
	D3DXVECTOR3 forward = D3DXVECTOR3(m_destPos.x - m_pos.x, 0, m_destPos.z - m_pos.z);
	if (g_pObjMgr->FindObjectByTag(TAG_MOB) || g_pObjMgr->FindObjectByTag(TAG_TEAM))
	{
		if (m_start)
		{
			m_finalDestPos = m_pos;
			m_destPos = m_pos;
			m_start = false;
		}
	}
	
	D3DXVECTOR3 forwardNormalized = forward;
	if (D3DXVec3LengthSq(&forward) > 0)
	{
		D3DXVec3Normalize(&forwardNormalized, &forwardNormalized);
		m_forward = forwardNormalized;//m_forward는 정면방향을 뜻함

		if (m_deltaPos.z == 1)
		{
			//W 키로 이동할 때
			m_currMoveSpeedRate = 1.0f;
		}
		else if (m_deltaPos.z == -1)
		{
			//S 키로 이동할 때
			m_currMoveSpeedRate = 0.5f;
			m_forward *= -1;
		}
		else
		{
			//클릭으로 이동할 때
			m_currMoveSpeedRate = 1.0f;
			m_deltaPos.z = 1;
		}
		
		if (D3DXVec3Length(&forward) >= m_moveSpeed * m_currMoveSpeedRate)
		{
			if (g_pObjMgr->FindObjectByTag(TAG_MOB) == false)
			{
				targetPos = m_pos + forwardNormalized * m_moveSpeed * m_currMoveSpeedRate;
			}
			else
			{
				
				for (int i = 0; i < g_pObjMgr->FindObjectsByTag(TAG_MOB).size(); i++)
				{
					if (targetPos != g_pObjMgr->FindObjectsByTag(TAG_MOB)[i]->GetPosition())
					{
						if (D3DXVec3Length(&((m_pos + forwardNormalized * m_moveSpeed * m_currMoveSpeedRate) -
							g_pObjMgr->FindObjectsByTag(TAG_MOB)[i]->GetPosition())) < 4.0f)
						{
							m_colision = true;
							break;
						}
						else
						{
							m_colision = false;
						}
					}
				}
				if (m_colision == false)
				{
					targetPos = m_pos + forwardNormalized * m_moveSpeed * m_currMoveSpeedRate;
				}
			}
		}
		else
		{
			targetPos.x = m_destPos.x;
			targetPos.z = m_destPos.z;
		}
	}
	else if (m_vecAStarIndex.empty() == false)
	{
		//목적지 도달후 Astar 노드가 남아있을 시 목적지 재설정
		m_destPos = g_pCurrentMap->GetAStar()->
			GetNodes()[m_vecAStarIndex.back()]->GetLocation();

		m_vecAStarIndex.pop_back();
		//뒤에서부터 가져오고 뻄.
	}
	else
	{
		m_destPos = m_finalDestPos;
	}
}

void IUnitObject::ApplyTargetPosition(D3DXVECTOR3 & targetPos)
{
	bool   isIntersected = true;
	float   height = 0;

	if (m_isJumping == true)
	{
		m_currMoveSpeedRate = 0.7f;
		//targetPos = m_pos + m_forward * m_deltaPos.z
		//	* m_moveSpeed * m_currMoveSpeedRate;

		targetPos.y += m_jumpPower - m_currGravity;
		m_currGravity += m_gravity;

		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
		}

		if (isIntersected == false)
		{
			if (g_pCurrentMap != NULL)
			{
				isIntersected = g_pCurrentMap->GetHeight(height, m_pos);
			}
			m_pos.y = targetPos.y;
		}
		else
		{
			m_pos = targetPos;
		}

		if (m_pos.y <= height && m_jumpPower < m_currGravity)
		{
			m_pos.y = height;
			m_isJumping = false;
			m_currGravity = 0;
			m_currMoveSpeedRate = 1.0f;
		}
		//m_pos = targetPos;
	}
	else //m_isJumping == false
	{
		//targetPos = m_pos + m_forward * m_deltaPos.z
		//	* m_moveSpeed * m_currMoveSpeedRate;

		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
			int tmp = 0;
			if (isIntersected == false || fabs(height - m_pos.y) > m_maxStepHeight)
			{
				m_pos.y = height;
			}
			else
			{
				targetPos.y = height;
				m_pos = targetPos;
			}
		}
		else
		{
			m_pos = targetPos;
		}

		//m_pos = targetPos;
	}

}

void IUnitObject::UpdatePosition()
{
	if (g_pObjMgr->FindObjectByTag(TAG_MOB) || g_pObjMgr->FindObjectByTag(TAG_TEAM))
	{
		if (m_start)
		{
			m_finalDestPos = m_pos;
			m_destPos = m_pos;
			m_start = false;
		}
	}

	m_rot += m_deltaRot * m_rotationSpeed;

	D3DXMATRIXA16 matRotY;
	D3DXMatrixRotationY(&matRotY, m_rot.y);
	D3DXVec3TransformNormal(&m_forward,
		&D3DXVECTOR3(0, 0, 1), &matRotY);

	D3DXVECTOR3 targetPos;
	float basePosY = 0;
	bool   isIntersected = true;
	float   height = 0;

	if (m_isJumping == true)
	{
		m_currMoveSpeedRate = 0.7f;
		targetPos = m_pos + m_forward * m_deltaPos.z
			* m_moveSpeed * m_currMoveSpeedRate;

		targetPos.y += m_jumpPower - m_currGravity;
		m_currGravity += m_gravity;

		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
		}

		if (isIntersected == false)
		{
			if (g_pCurrentMap != NULL)
			{
				isIntersected = g_pCurrentMap->GetHeight(height, m_pos);
			}
			m_pos.y = targetPos.y;
		}
		else
		{
			m_pos = targetPos;
		}

		if (m_pos.y <= height && m_jumpPower < m_currGravity)
		{
			m_pos.y = height;
			m_isJumping = false;
			m_currGravity = 0;
			m_currMoveSpeedRate = 1.0f;
		}
		//m_pos = targetPos;
	}
	else //m_isJumping == false
	{
		targetPos = m_pos + m_forward * m_deltaPos.z
			* m_moveSpeed * m_currMoveSpeedRate;

		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
			int tmp = 0;
			if (isIntersected == false || fabs(height - m_pos.y) > m_maxStepHeight)
			{

			}
			else
			{
				targetPos.y = height;
				m_pos = targetPos;
			}
		}
		else
		{

			m_pos = targetPos;
		}

		//m_pos = targetPos;
	}

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixRotationY(&matRotY, m_rot.y + m_baseRotY);
	m_matWorld = matRotY * matT;

	if (D3DXVec3LengthSq(&m_deltaRot) > D3DX_16F_EPSILON ||
		D3DXVec3LengthSq(&m_deltaPos) > D3DX_16F_EPSILON)
		m_isMoving = true;
	else
		m_isMoving = false;
}

void IUnitObject::DecreaseHealth(int h)
{
	if (m_def > 0)
		health -= 1;
	else
		health -= h;
	
}
