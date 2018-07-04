#pragma once
#include "BaseObject.h"

class ColorCube;
class AStarNode;
class Heap;


class AStar : public BaseObject
{
private:
	vector<AStarNode*>	m_vecNode;
	list<AStarNode*>	m_pOpenNodeList;
	Heap*				m_pOpenNodeHeap;
	LPD3DXMESH			m_pSphere;
	vector<D3DXVECTOR3> m_vecObstacle;
	vector<D3DXVECTOR3> Wall_location;
	
	ColorCube *			m_ColorCube;
	D3DXVECTOR3			m_CubePos;
	int					m_count;
	
	//이닛노드의 map 정보를 임시적으로 받아줄 변수
	IMap*				temp_Imap;

public:
	AStar();
	virtual ~AStar();
	void Init();
	void Render();
	void InitNodes(IMap* pMap);
	const vector<AStarNode*>& GetNodes() { return m_vecNode; }
	void SetObstacle(const vector<D3DXVECTOR3> &vecObstacle)
	{
		m_vecObstacle = vecObstacle;
	}
	vector<D3DXVECTOR3> GetWallLocation() { return Wall_location; }
	void FindPath(D3DXVECTOR3 startPos, D3DXVECTOR3 destPos,
		OUT vector<int>& vecIndex);
private:
	void RestNodes();
	int FindClosestNode(const D3DXVECTOR3 &pos);
	float GetManHattanDistance(int from, int to);
	int GetMinFNodeIndex();
	void Extend(int targetIdx, int destIdx);

public:
	void MakeDirectPath(const D3DXVECTOR3 &startPos,
		const D3DXVECTOR3 &destPos, OUT vector<int>& vecIndex);
private:
	void CalcEraseCount(const D3DXVECTOR3& pos,
		const vector<int>& vecIndex, bool bByStartPos,
		OUT int &numEraseNode);

public:
	void MakeWall(int posX, int posZ, AStarNode * pNode);
	void ReviseAstarNode();
};

