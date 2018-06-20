#include "stdafx.h"
#include "Frustum.h"
#include "TeamAI.h"
#include "Mob.h"



Frustum::Frustum()
{
	m_pMesh = NULL;
	
}


Frustum::~Frustum()
{
	
	
}

void Frustum::Destroy()
{
	SAFE_RELEASE(m_pMesh);

}

void Frustum::Init()
{
	m_vecProjVtx.push_back(D3DXVECTOR3(-1, 1, 1));	//�»���
	m_vecProjVtx.push_back(D3DXVECTOR3(1, 1, 1));	//�����
	m_vecProjVtx.push_back(D3DXVECTOR3(-1, 1, 0));	//�»���
	m_vecProjVtx.push_back(D3DXVECTOR3(1, 1, 0));	//�����
	m_vecProjVtx.push_back(D3DXVECTOR3(-1, -1, 1));	//������
	m_vecProjVtx.push_back(D3DXVECTOR3(1, -1, 1));	//������
	m_vecProjVtx.push_back(D3DXVECTOR3(-1, -1, 0));	//������
	m_vecProjVtx.push_back(D3DXVECTOR3(1, -1, 0));	//������

	m_vecWorldVtx.resize(8);
	m_vecPlane.resize(6);

	/*m_Unit = new UnitBox;
	m_Unit->Init();
*/
	////��ü �׷��ֱ� dim * dim * dim
	//int dim = 6;
	//float offset = 4;
	//float half = (dim - 1) * offset / 2.0f;
	//float radius = 0.6f;
	//D3DXCreateSphere(g_pDevice, radius, 10, 10, &m_pMesh, NULL);

	//m_vecpBoundary.reserve(dim * dim * dim);
	//for (int i = 0; i < dim; i++)
	//{
	//	for (int j = 0; j < dim; j++)
	//	{
	//		for (int k = 0; k < dim; k++)
	//		{
	//			BoundingSphere* s = new BoundingSphere(D3DXVECTOR3(
	//				i * offset - half, j * offset - half, k * offset - half), radius);
	//			m_vecpBoundary.push_back(s);
	//		}
	//	}
	//}

	UpdateFrustum();
}

void Frustum::Update()
{
	//m_Unit->Update();

	UpdateFrustum();

}

void Frustum::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetMaterial(&DXUtil::BLUE_MTRL);
	g_pDevice->SetTexture(0, NULL);
	
	/*for (auto p : *m_Unit->getPTeam())
	{
		if (IsTeamAIFrustum(p) == true)
		{
			p->Render();
		}
	}


	for (auto p : *m_Unit->getPMob())
	{
		if (IsMobAIFrustum(p) == true)
		{
			p->Render();
		}
	}*/
}

void Frustum::UpdateFrustum()
{
	D3DXMATRIXA16 matProj, matView;
	g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pDevice->GetTransform(D3DTS_VIEW, &matView);

	for (size_t i = 0; i < m_vecWorldVtx.size(); i++)
	{
		D3DXVec3Unproject(&m_vecWorldVtx[i], &m_vecProjVtx[i],
			NULL, &matProj, &matView, NULL);
	}
	//�����	//�»���//�����//������
	D3DXPlaneFromPoints(&m_vecPlane[0],
		&m_vecWorldVtx[2], &m_vecWorldVtx[3], &m_vecWorldVtx[6]);
	//�����	//�����//�»���//������
	D3DXPlaneFromPoints(&m_vecPlane[1],
		&m_vecWorldVtx[1], &m_vecWorldVtx[0], &m_vecWorldVtx[5]);
	//�����
	D3DXPlaneFromPoints(&m_vecPlane[2],
		&m_vecWorldVtx[0], &m_vecWorldVtx[2], &m_vecWorldVtx[4]);
	//�����
	D3DXPlaneFromPoints(&m_vecPlane[3],
		&m_vecWorldVtx[3], &m_vecWorldVtx[1], &m_vecWorldVtx[7]);
	//�����
	D3DXPlaneFromPoints(&m_vecPlane[4],
		&m_vecWorldVtx[0], &m_vecWorldVtx[1], &m_vecWorldVtx[2]);
	//�����
	D3DXPlaneFromPoints(&m_vecPlane[5],
		&m_vecWorldVtx[6], &m_vecWorldVtx[7], &m_vecWorldVtx[4]);
}

bool Frustum::IsSphereInsideFrustum(BoundingSphere * pSphere)
{
	for (auto p : m_vecPlane)
	{
		
		if (D3DXPlaneDotCoord(&p, &pSphere->center) > pSphere->radius)
		{
			//center �� ���� ���ʿ� ��ġ�ϰ� 
			//center �� ���� �Ÿ��� radius ���� ũ��
			return false;
		}
	}
	return true;
}

bool Frustum::IsTeamAIFrustum(TeamAI* Team)
{
	for (auto p : m_vecPlane)
	{
		//�Ʊ� �浹����
		//3.0f
		if (D3DXPlaneDotCoord(&p, &Team->GetPosition()) > 3.0f)
		{
			//center �� ���� ���ʿ� ��ġ�ϰ� 
			//center �� ���� �Ÿ��� radius ���� ũ��
			return false;
		}
	}
	return true;
}

bool Frustum::IsMobAIFrustum(Mob * mob)
{
	for (auto p : m_vecPlane)
	{
		//�� �浹����
		//2.0f
		if (D3DXPlaneDotCoord(&p, &mob->GetPosition()) > 2.0f)
		{
			//center �� ���� ���ʿ� ��ġ�ϰ� 
			//center �� ���� �Ÿ��� radius ���� ũ��
			return false;
		}
	}
	return true;
}
