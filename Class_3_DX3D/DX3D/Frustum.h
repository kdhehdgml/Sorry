#pragma once
#include "IDisplayObject.h"

class UnitBox;
class TeamAI;
class Mob;

class Frustum : public IDisplayObject
{
	vector<D3DXVECTOR3> m_vecProjVtx;
	vector<D3DXVECTOR3> m_vecWorldVtx;
	vector<D3DXPLANE>	m_vecPlane;
	vector<BoundingSphere*> m_vecpBoundary;
	LPD3DXMESH		m_pMesh;

	//���⼭ �������ְ� �������ٲ���
	UnitBox*		m_Unit;
	


public:
	Frustum();
	~Frustum();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void UpdateFrustum();
	bool IsSphereInsideFrustum(BoundingSphere* pSphere);
	bool IsTeamAIFrustum(TeamAI* Unit);
	bool IsMobAIFrustum(Mob* Unit);
};

