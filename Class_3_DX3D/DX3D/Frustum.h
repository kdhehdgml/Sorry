#pragma once
#include "IDisplayObject.h"

class UnitBox;
class TeamAI;
class Mob;

#define g_pFrustum Frustum::GetInstance()

class Frustum
{
	SINGLETON(Frustum);

private:

	vector<D3DXVECTOR3> m_vecProjVtx;
	vector<D3DXVECTOR3> m_vecWorldVtx;
	vector<D3DXPLANE>	m_vecPlane;
	//vector<BoundingSphere*> m_vecpBoundary;
	LPD3DXMESH		m_pMesh;

	


public:
	/*Frustum();
	~Frustum();*/

	// IDisplayObject을(를) 통해 상속됨
	void Init();
	void Update();
	void Render();
	void Destroy();


	void UpdateFrustum();
	bool IsSphereInsideFrustum(BoundingSphere* pSphere);
	bool IsTeamAIFrustum(TeamAI* Unit);
	bool IsMobAIFrustum(Mob* Unit);
};

