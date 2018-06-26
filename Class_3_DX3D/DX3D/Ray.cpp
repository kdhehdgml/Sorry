#include "stdafx.h"
#include "Ray.h"


Ray::Ray()
	:m_pos(0, 0, 0)
	,m_dir(0, 0, 1)
{
}


Ray::~Ray()
{
}

Ray Ray::RayAtViewSpace(int x, int y)
{
	D3DVIEWPORT9 vp;
	g_pDevice->GetViewport(&vp);

	D3DXMATRIXA16 matProj;
	g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	Ray ray;
	ray.m_dir.x = ((x * 2.0f) / vp.Width - 1.0f) / matProj._11;
	ray.m_dir.y = ((-y * 2.0f) / vp.Height + 1.0f) / matProj._22;

	return ray;
}

Ray Ray::RayAtWorldSpace(int x, int y)
{
	//스크린 x, y 좌표로 View 에 있는 Ray 구함
	Ray ray = Ray::RayAtViewSpace(x, y);

	//View 에 있는 ray 를 World 로 변환
	D3DXMATRIXA16 matView, matInvView;
	g_pDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvView, NULL, &matView);

	D3DXVec3TransformCoord(&ray.m_pos, &ray.m_pos, &matInvView);
	D3DXVec3TransformNormal(&ray.m_dir, &ray.m_dir, &matInvView);
	D3DXVec3Normalize(&ray.m_dir, &ray.m_dir);

	return ray;
}

bool Ray::CalcIntersectSphere(BoundingSphere * pSphere)
{
	//계산하기 전에 구의 위치를 원점으로 보정
	D3DXVECTOR3 localPos = m_pos - pSphere->center;

	float qv = D3DXVec3Dot(&localPos, &m_dir);
	//float vv = D3DXVec3Dot(&m_dir, &m_dir);
	float qq = D3DXVec3Dot(&localPos, &localPos);
	float rr = pSphere->radius * pSphere->radius;
	
	//qv * qv - vv * (qq - rr) >= 0;
	return qv * qv - (qq - rr) >= 0;
}

bool Ray::CalcIntersectBox(BoundingBox * pBox)
{
	float x_min = (pBox->aa.x - m_pos.x) / m_dir.x;
	float x_max = (pBox->bb.x - m_pos.x) / m_dir.x;

	if (x_min > x_max) {
		float temp;
		temp = x_min;
		x_min = x_max;
		x_max = temp;
	}
	float y_min = (pBox->aa.y - m_pos.y) / m_dir.y;
	float y_max = (pBox->bb.y - m_pos.y) / m_dir.y;

	if (y_min > y_max) {
		float temp;
		temp = y_min;
		y_min = y_max;
		y_max = temp;
	}

	if ((x_min > y_max) || (y_min > x_max)) return false;
	if (y_min > x_min) x_min = y_min;
	if (y_max < x_max) x_max = y_max;

	float z_min = (pBox->aa.z - m_pos.z) / m_dir.z;
	float z_max = (pBox->bb.z - m_pos.z) / m_dir.z;

	if (z_min > z_max) {
		float temp;
		temp = z_min;
		z_min = z_max;
		z_max = temp;
	}
	if ((x_min > z_max) || (z_min > x_max)) return false;
	if (z_min > x_min) x_min = z_min;
	if (z_max < x_max) x_max = z_max;

	return true;
}

bool Ray::CalcIntersectTri(D3DXVECTOR3 * pStart, float * distance)
{
	return D3DXIntersectTri(pStart, pStart + 1, pStart + 2, &m_pos, &m_dir,
		NULL, NULL, distance);
}

D3DXVECTOR3 Ray::getPos()
{
	return m_pos;
}

D3DXVECTOR3 Ray::getDir()
{
	return m_dir;
}
