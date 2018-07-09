#pragma once
#include "IUnitObject.h"

#define TeamSize 10
#define TeamPositSize 14
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
struct GameWave
{
	int		NumOfWave;
	int		StartAmount;
	int		IncreaseAmount;
	int		MinLifeMob;
	GameWave() {}
	GameWave(int _wave, int _start, int _increase, int _minmob)
		:NumOfWave(_wave), StartAmount(_start), IncreaseAmount(_increase), MinLifeMob(_minmob)
	{}
};
class UnitBox : public IUnitObject
{
private:
	Cubeman *		m_pCubeman;
	GameWave		m_game;
	vector<TeamAI*>	m_pTeam;
	vector<D3DXVECTOR3> m_SaveLocation;
	vector<D3DXVECTOR3> m_nWallLocation;
	vector<vector<D3DXVECTOR3>> m_LocationList;
	vector<EmptyWall> m_CanSeeDirection;
	vector<bool>		m_CanSave;
	vector<D3DXVECTOR3> m_TeamPosition;
	vector<int> posit;
	int				MobNum;
	int				TeamNum;
	int				NOL_Mob;
	int				NOL_Team;
	bool			m_SameChk;
	bool			MobStart;
public:
	UnitBox();
	~UnitBox();
	vector<Mob*>	m_pMob;
	void SetLocation(vector<vector<D3DXVECTOR3>> _location) 
	{	m_SaveLocation = _location[0]; 
		m_nWallLocation = _location[1]; }
	
	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	void FindEmptyWallDirection();
	void FindHidingInTheWallLocationRushSoldier(int _Mobnum);
	void FindHidingInTheWallLocation(Mob* _mob);
	void MobMoveInTheWall(int _Mobnum);
	void TeamPosition();
	void RandomSelectPosition();
	void RegenTeam();
	void CreateMob(int num);
	void ReSetMob();
	void CheckNumberOfLivingAI();
	void LocationSharing();
	void GameWaveSetting(int _wave, int _start, int _increase, int _minmob);
	//void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	vector<Mob*>* getPMob();
	vector<TeamAI*>* getPTeam();

};

