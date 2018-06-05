#pragma once
#include "IUnitObject.h"
class Cubeman;
class Mob;
class UnitBox : public IUnitObject
{
private:
	Cubeman *		m_pCubeman;
	vector<Mob*>	m_pMob;
	vector<D3DXVECTOR3> SaveLocation;
	int				num;
	bool			m_SameChk;

public:
	UnitBox();
	~UnitBox();

	virtual void SetLocation(vector<D3DXVECTOR3> _location) { SaveLocation = _location; }
	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	void FindHidingInTheWallLocation(int _Mobnum);
	void MobMoveInTheWall();
	//void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	vector<Mob*>* getPMob();
};

