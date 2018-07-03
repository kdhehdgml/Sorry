#pragma once
#include "IUnitObject.h"

#define TeamSize 10
#define TeamPositSize 17
using std::pair;
class Cubeman;
class Mob;
class TeamAI;
enum EmptyWall 
{
	��������,
	����ֹ�����,
	����ֹ�����
};
class UnitBox : public IUnitObject
{
private:
	Cubeman *		m_pCubeman;
	vector<Mob*>	m_pMob;
	vector<TeamAI*>	m_pTeam;
	vector<D3DXVECTOR3> m_SaveLocation;
	vector<EmptyWall> m_CanSeeDirection;
	vector<bool>		m_CanSave;
	vector<D3DXVECTOR3> m_TeamPosition;
	vector<int> posit;
	int				MobNum;
	int				TeamNum;
	bool			m_SameChk;
	bool			MobStart;
public:
	UnitBox();
	~UnitBox();

	virtual void SetLocation(vector<D3DXVECTOR3> _location) { m_SaveLocation = _location; }
	
	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	void FindEmptyWallDirection();
	void FindHidingInTheWallLocationRushSoldier(int _Mobnum);
	void FindHidingInTheWallLocation(int _Mobnum);
	void MobMoveInTheWall(int _Mobnum);
	void TeamPosition();
	void RandomSelectPosition();
	void RegenTeam();
	void CreateMob(int num);
	void ReSetMob();
	void teamSummon();
	//void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	vector<Mob*>* getPMob();
	vector<TeamAI*>* getPTeam();

};

