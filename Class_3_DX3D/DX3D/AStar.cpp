#include "stdafx.h"
#include "AStar.h"
#include "AStarNode.h"
#include "Ray.h"
#include "Heap.h"
#include "ColorCube.h"

// 벽생성 매크로
#define WALL(X1,X2,Z1,Z2) if ((posX >= X1 && posX <= X2) && (posZ >= Z1 && posZ <= Z2))\
			{ pNode->m_nodeState = STATE_WALL;\
			Wall_location.push_back(pNode->m_location); }

#define nWALL(X1,X2,Z1,Z2) if ((posX >= X1 && posX <= X2) && (posZ >= Z1 && posZ <= Z2))\
			{ pNode->m_nodeState = STATE_NOHIDEWALL; }

//노드 구체 사이즈 조절
#define SPHERESIZE 1.0f

AStar::AStar()
{
}


AStar::~AStar()
{
	SAFE_DELETE(m_pOpenNodeHeap);
	
	SAFE_RELEASE(m_pSphere);
	for (auto p : m_vecNode)
	{
		SAFE_RELEASE(p);
	}
	SAFE_RELEASE(m_ColorCube);
}

void AStar::Init()
{
	D3DXCreateSphere(g_pDevice, SPHERESIZE, 10, 10, &m_pSphere, NULL);
	m_pOpenNodeHeap = new Heap;

	m_ColorCube = new ColorCube;
	m_ColorCube->Init();

	m_count = 0;
	
}

void AStar::Render()
{
	D3DXMATRIXA16 mat;
	m_ColorCube->Update();

	g_pDevice->SetTexture(0, NULL);
	

	

	for (auto p : m_vecNode)
	{
		switch (p->m_nodeState)
		{
		case STATE_NONE:
			g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);
			break;
		case STATE_OPEN:
			g_pDevice->SetMaterial(&DXUtil::RED_MTRL);
			break;
		case STATE_CLOSE:
			g_pDevice->SetMaterial(&DXUtil::YELLOW_MTRL);
			break;
		case STATE_USING:
			g_pDevice->SetMaterial(&DXUtil::BLUE_MTRL);
			break;
		case STATE_WALL:
			g_pDevice->SetMaterial(&DXUtil::GREEN_MTRL);
			break;
		case STATE_NOHIDEWALL:
			g_pDevice->SetMaterial(&DXUtil::BLACK_MTRL);
			break;
			//탱크노드
		case STATE_TANK:
			g_pDevice->SetMaterial(&DXUtil::BLACK_MTRL);
			break;
			//참호안
		case STATE_TRENCH:
			g_pDevice->SetMaterial(&DXUtil::SKY_MTRL);
			break;
		}

		////충돌체크!
		//D3DXVECTOR3 Distance = p->GetLocation() - m_ColorCube->GetPostion();
		////좌표위치 차이
		//float p_Distance = D3DXVec3Length(&Distance);
		////반지름합
		//float Radius = m_ColorCube->GetRADIUS() + SPHERESIZE;
		//
		////충돌된것 피하는 장애물로 변환
		////각 객체의 반지름을 합하고 두 위치 사이의 거리를 비교
		////반지름의 합보다 사이거리가 짧을경우 충돌로 판정후 실행
		//
		//if (Radius > p_Distance)
		//{
		//	//하이드월과 노 하이드월은 탱크노드로 변경하지 않는다.
		//	if (!(p->m_nodeState == STATE_NOHIDEWALL || p->m_nodeState == STATE_WALL ))
		//	{
		//		p->m_nodeState = STATE_TANK;
		//		//닿았으면 충돌 트루
		//		p->m_ClickBox = true;
		//	}
		//	//m_count++;
		//	
		//}
		//else
		//{
		//	//닿지않았다.
		//	p->m_ClickBox = false;
		//}
		//
		////탱크가 없는곳 모두 일반노드화
		//if (p->m_ClickBox == false && p->m_nodeState == STATE_TANK)
		//{
		//	p->m_nodeState = STATE_NONE;
		//}


		D3DXMatrixTranslation(&mat, p->GetLocation().x, p->GetLocation().y, p->GetLocation().z);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		m_pSphere->DrawSubset(0);

		D3DXMatrixIdentity(&mat);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST,
			p->GetVecLines().size() / 2, p->GetVecLines()[0],
			sizeof(D3DXVECTOR3));
	}

	Debug->AddText("충돌 갯수");
	Debug->AddText(m_count);
	Debug->EndLine();
}

void AStar::InitNodes(IMap * pMap)
{
	temp_Imap = pMap;
	int nodeDim = 100;// 노드 한 줄 갯수
					 //간격
	//이 수치 
	float interval = ((pMap->GetSize().x - NODE_POSITSIZEZ * 2)-20) / (float)(nodeDim - 0.99);

	for (int posZ = 0; posZ < nodeDim; posZ++)
	{
		for (int posX = 0; posX < nodeDim; posX++)
		{
			//여길건드리면 시작점이다름
			D3DXVECTOR3 location(NODE_POSITSIZEX + posX * interval, 0, NODE_POSITSIZEZ + posZ * interval);

			pMap->GetHeight(location.y, location);

			//0부터시작해서 ??
			AStarNode* pNode = new AStarNode(location, m_vecNode.size());

			m_vecNode.push_back(pNode);

			//if (posX == 25 && (posZ > 40 && posZ < 42))
			//{ pNode->m_nodeState = STATE_WALL;
			//	Wall_location.push_back(pNode->m_location);	/*m_pUnit->SetLocation(pNode->m_location);*/ }
			
			// 벽생성 (매크로 사용)
			bool lineodd = true;
			int lineNum = 0;
			for (int x = 35; x < 100; x += 4)
			{
				for (int z = 4; z < 96; z += 5)
				{
					if (lineodd)
					{
						if (lineNum % 3 != 1)
						{
							WALL(x, x, z, z + 2);
						}
						else
						{
							nWALL(x, x, z, z + 2);
						}
						lineodd = false;
					}
					else
					{
						if (lineNum % 3 != 1)
						{
							WALL(x, x, z + 2, z + 4);
						}
						else
						{
							nWALL(x, x, z + 2, z + 4);
						}
						lineodd = true;
					}	
				}
				lineNum++;
			}

		}
	}
	//위에 노드까는코드

	for (size_t i = 0; i < m_vecNode.size(); i++)
	{
		//제일 우측열ㅇ르 제외하고 자신의 우측노드와 서로 Edge등ㅇ록
		if (i % nodeDim != nodeDim - 1)//가장오른쪽인애 오른쪽은 더없기떄문에 -1 해준다.
		{
			m_vecNode[i]->AddEdge(m_vecNode[i + 1]);
			m_vecNode[i + 1]->AddEdge(m_vecNode[i]);
		}
		//제일 윗 횡을 제외하고 자신의 윗 노드와 서로 edge등록
		if (i < m_vecNode.size() - nodeDim)
		{
			m_vecNode[i]->AddEdge(m_vecNode[i + nodeDim]);
			m_vecNode[i + nodeDim]->AddEdge(m_vecNode[i]);
		}
	}
}

void AStar::FindPath(D3DXVECTOR3 startPos, D3DXVECTOR3 destPos, OUT vector<int>& vecIndex)
{
	//인덱스의 위치를 가져갈수이씅니까 그 노드의 위치를 따라가는것임
	RestNodes();

	int startNodeIdx = FindClosestNode(startPos);
	int destNodeIdx = FindClosestNode(destPos);

	//값이 없으면 끝!
	if (startNodeIdx == -1 || destNodeIdx == -1)
	{
		return;
	}

	//출발지 노드를 초기화해주고 열림상태로 만든다.
	float g = 0.0f;
	float h = GetManHattanDistance(startNodeIdx, destNodeIdx);
	float f = g + h;

	m_vecNode[startNodeIdx]->SetValues(STATE_OPEN, g, h, f, startNodeIdx);
	//m_pOpenNodeList.push_back(m_vecNode[startNodeIdx]);
	m_pOpenNodeHeap->Insert(m_vecNode[startNodeIdx]);

	//목적지 노드가 닫힘 상태가 될 떄까지 출발지 노드부터 확장해 간다
	//확장을 완료한 노드는 닫힘 상태로 만든다.


	//클로즈되면종료
	while (m_vecNode[destNodeIdx]->m_nodeState != STATE_CLOSE)
	{
		int currIndex = GetMinFNodeIndex();
		if (currIndex == -1)return;

		Extend(currIndex, destNodeIdx);
		m_vecNode[currIndex]->m_nodeState = STATE_CLOSE;
	}//끝나면 길을 찾은상태

	 //목적지 노드부터 출발지 노드 이전까지 경유 노드들의 인덱스를
	 //path 목록에 추가, 목록에 추가한 노드들은 사용 상태로 만든다

	int currIndex = destNodeIdx;
	while (currIndex != startNodeIdx)
	{
		m_vecNode[currIndex]->m_nodeState = STATE_USING;
		vecIndex.push_back(currIndex);
		currIndex = m_vecNode[currIndex]->m_via;
	}

	//출발지 노드의 인덱스도 Path 목록에 추가하고 사용 상태로 만든다
	m_vecNode[currIndex]->m_nodeState = STATE_USING;
	vecIndex.push_back(currIndex);
	//목적지 - > 경유지... ->출발지 인덱스 목록 완성


	//m_pOpenNodeList.clear();
	m_pOpenNodeHeap->Clear();
}

void AStar::RestNodes()
{
	for (int i = 0; i < m_vecNode.size(); i++)
	{
		if (m_vecNode[i]->m_nodeState != STATE_WALL && m_vecNode[i]->m_nodeState != STATE_NOHIDEWALL && m_vecNode[i]->m_nodeState != STATE_TANK)
			m_vecNode[i]->m_nodeState = STATE_NONE;
	}
}

int AStar::FindClosestNode(const D3DXVECTOR3 & pos)
{
	//레이랑 과정 비슷함
	float minDist = FLT_MAX;
	int closestNodeIndex = -1;

	for (int i = 0; i < m_vecNode.size(); i++)
	{
		if (m_vecNode[i]->m_nodeState == STATE_WALL || m_vecNode[i]->m_nodeState == STATE_NOHIDEWALL || m_vecNode[i]->m_nodeState == STATE_TANK)
		{
			continue;
		}

		D3DXVECTOR3 subtract = pos - m_vecNode[i]->GetLocation();

		float  dist = D3DXVec3Length(&subtract);


		if (dist < minDist)
		{
			minDist = dist;
			closestNodeIndex = i;
		}

	}
	return closestNodeIndex;//가장가까운 노드의 인덱스반환
}

float AStar::GetManHattanDistance(int from, int to)
{
	float offsetX = fabs(m_vecNode[from]->GetLocation().x - m_vecNode[to]->GetLocation().x);
	float offsetZ = fabs(m_vecNode[from]->GetLocation().z - m_vecNode[to]->GetLocation().z);

	return offsetX + offsetZ;
}

int AStar::GetMinFNodeIndex()
{
	//f 값이 제일 작은애를 찾을거임

	AStarNode* node = NULL;

	/*
	float minValue = FLT_MAX;

	for (auto p : m_pOpenNodeList)
	{
	if (p->m_f < minValue)
	{
	minValue = p->m_f;
	node = p;
	//가장작은애 찾는거

	}
	}
	if (node == NULL)return -1;

	m_pOpenNodeList.remove(node);
	*/

	node = m_pOpenNodeHeap->ExtractMin();
	if (node == NULL) return -1;


	return node->m_index;
}

void AStar::Extend(int targetIdx, int destIdx)
{
	//시작점과 목적지 받아옴(인덱스)
	//시작노드의 사방 엣지 노드를 받아서 확장하는거임
	vector<EDGE_INFO*> vecEdge = m_vecNode[targetIdx]->GetEdgeInfos();

	for (int i = 0; i < vecEdge.size(); i++)
	{
		int index = vecEdge[i]->index;
		AStarNode* currNode = m_vecNode[index];

		if (currNode->m_nodeState == STATE_CLOSE) continue;//못가는지역?
		if (currNode->m_nodeState == STATE_WALL) continue;//벽?
		if (currNode->m_nodeState == STATE_NOHIDEWALL) continue;
		if (currNode->m_nodeState == STATE_TANK) continue;
														  //시작점까지의 코스트(현재거리까지의 필요한 비용)
		float G = m_vecNode[targetIdx]->m_g + vecEdge[i]->edgeCost;//확장하려는 인저노드로 가는데 필요한 총 g 값

		float H = GetManHattanDistance(index, destIdx);//필요한 비용의 수정값
		float F = G + H;

		if (currNode->m_nodeState == STATE_OPEN &&
			G >= currNode->m_g) continue; // 비교할필요없어서 넘김

		currNode->SetValues(STATE_OPEN, G, H, F, targetIdx);//마지막인자 내꺼의 이전 노드

															//m_pOpenNodeList.push_back(currNode);
		m_pOpenNodeHeap->Insert(currNode);


	}
}

void AStar::CalcEraseCount(const D3DXVECTOR3 & pos, const vector<int>& vecIndex, bool bByStartPos, OUT int & numEraseNode)
{
	numEraseNode = 0;
	Ray ray;

	ray.m_pos = pos;

	ray.m_pos.y += 0.3f;

	for (size_t index = 0; index < vecIndex.size(); index++)
	{
		if (bByStartPos == true)
		{
			//마지막위치에서 내 위치를 뺴줌
			ray.m_dir = m_vecNode[vecIndex[vecIndex.size() - 1 - index]]->GetLocation() - pos;
		}
		else
		{
			ray.m_dir = m_vecNode[vecIndex[index]]->GetLocation() - pos;
		}

		float nodeDist = D3DXVec3Length(&ray.m_dir);
		D3DXVec3Normalize(&ray.m_dir, &ray.m_dir);
		float intersectionDist;
		bool isIntersected = false;

		for (size_t i = 0; i < m_vecNode.size(); i++)
		{
			float a = D3DXVec3Length(&(m_vecNode[i]->m_location - ray.m_pos));
			if ((m_vecNode[i]->m_nodeState == STATE_WALL && a + 0.3 < nodeDist) ||
				(m_vecNode[i]->m_nodeState == STATE_NOHIDEWALL && a + 0.3 < nodeDist) ||
				(m_vecNode[i]->m_nodeState == STATE_TANK && a + 0.3 < nodeDist))
			{
				isIntersected = true;
				break;
			}
		}

		/*for (size_t i = 0; i < m_vecObstacle.size(); i += 3)
		{
		if (ray.CalcIntersectTri(&m_vecObstacle[i], &intersectionDist))
		{
		if (intersectionDist < nodeDist)
		{
		isIntersected = true;
		break;
		}
		}
		}*/
		//충돌했을떄
		if (isIntersected == true)
		{
			numEraseNode--;//자기이전을 자름
			break;
		}
		//충돌안했을떄
		else
		{
			numEraseNode++;//자기이후를 자름
		}
	}
}

void AStar::MakeDirectPath(const D3DXVECTOR3 & startPos,
	const D3DXVECTOR3 & destPos, OUT vector<int>& vecIndex)
{

	//if (m_vecObstacle.empty() == true)
	//{
	//	//장애물 없으면 직선이동
	//	vecIndex.clear();
	//}
	//else
	//{
	int numNodeToErase = 0;
	//시작지점부터 체크하고 교차 이전 지점까지 노드 삭제
	CalcEraseCount(startPos, vecIndex, true, numNodeToErase);
	//뒤에서부터 제거?
	if (numNodeToErase > 0)
		vecIndex.erase(vecIndex.end() - numNodeToErase, vecIndex.end());



	//마지막점부터 체크하고 교차 이전 지점까지 노드 삭제
	CalcEraseCount(destPos, vecIndex, true, numNodeToErase);

	if (numNodeToErase == vecIndex.size()) numNodeToErase--;

	if (numNodeToErase > 0)
		vecIndex.erase(vecIndex.begin(), vecIndex.begin() + numNodeToErase);

	//}
}
