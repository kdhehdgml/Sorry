#pragma once
#include "IDisplayObject.h"
class Walls :
	public IDisplayObject
{
private:
	vector<VERTEX_PN> m_vecFloor;
	vector<VERTEX_PN> m_vecWalls;
	vector<VERTEX_PN> m_vecWall0;
	vector<VERTEX_PN> m_vecWall1;
	vector<VERTEX_PN> m_vecWall2;

public:
	Walls();
	~Walls();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void MakePlane(vector<VERTEX_PN> &vecOut, vector<D3DXVECTOR3> &vecPos, D3DXMATRIXA16 &mat);
	void MakePlaneGroup(vector<VERTEX_PN> &vecOut, vector<D3DXVECTOR3> vecWall);
};

