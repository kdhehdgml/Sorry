#pragma once
#include "IUnitObject.h"
class Cubeman;
class Mob;
class AStar;
class UnitBox : public IUnitObject
{
private:
	Cubeman *		m_pCubeman;
	AStar *			m_pAstar;
	vector<Mob*>	m_pMob;
	vector<D3DXVECTOR3> SaveLocation;

public:
	UnitBox();
	~UnitBox();

	virtual void SetLocation(vector<D3DXVECTOR3> _location) { SaveLocation = _location; }
	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

};

