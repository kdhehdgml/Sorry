#pragma once
#include "IUnitObject.h"
class Cubeman;
class Mob;
class TeamAI;
class UnitBox : public IUnitObject
{
private:
	Cubeman *		m_pCubeman;
	vector<Mob*>	m_pMob;
	vector<TeamAI*>	m_pTeam;
	vector<D3DXVECTOR3> m_SaveLocation;
	vector<bool>		m_CanSave;
	int				MobNum;
	int				TeamNum;
	bool			m_SameChk;

public:
	UnitBox();
	~UnitBox();

	virtual void SetLocation(vector<D3DXVECTOR3> _location) { m_SaveLocation = _location; }
	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	void FindHidingInTheWallLocationRushSoldier(int _Mobnum);
	void FindHidingInTheWallLocation(int _Mobnum);
	void MobMoveInTheWall(int _Mobnum);
	void mobSummon(int num);
	void teamSummon();
	//void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	vector<Mob*>* getPMob();
	vector<TeamAI*>* getPTeam();

};

