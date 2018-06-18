#include "stdafx.h"
#include "AStar.h"
#include "AStarNode.h"
#include "Ray.h"
#include "Heap.h"
#include "ColorCube.h"

// ������ ��ũ��
#define WALL(X1,X2,Z1,Z2) if ((posX >= X1 && posX <= X2) && (posZ >= Z1 && posZ <= Z2))\
			{ pNode->m_nodeState = STATE_WALL;\
			Wall_location.push_back(pNode->m_location); }

#define nWALL(X1,X2,Z1,Z2) if ((posX >= X1 && posX <= X2) && (posZ >= Z1 && posZ <= Z2))\
			{ pNode->m_nodeState = STATE_NOHIDEWALL; }

//��� ��ü ������ ����
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
			//��ũ���
		case STATE_TANK:
			g_pDevice->SetMaterial(&DXUtil::BLACK_MTRL);
			break;
			//��ȣ��
		case STATE_TRENCH:
			g_pDevice->SetMaterial(&DXUtil::SKY_MTRL);
			break;
		}

		////�浹üũ!
		//D3DXVECTOR3 Distance = p->GetLocation() - m_ColorCube->GetPostion();
		////��ǥ��ġ ����
		//float p_Distance = D3DXVec3Length(&Distance);
		////��������
		//float Radius = m_ColorCube->GetRADIUS() + SPHERESIZE;
		//
		////�浹�Ȱ� ���ϴ� ��ֹ��� ��ȯ
		////�� ��ü�� �������� ���ϰ� �� ��ġ ������ �Ÿ��� ��
		////�������� �պ��� ���̰Ÿ��� ª����� �浹�� ������ ����
		//
		//if (Radius > p_Distance)
		//{
		//	//���̵���� �� ���̵���� ��ũ���� �������� �ʴ´�.
		//	if (!(p->m_nodeState == STATE_NOHIDEWALL || p->m_nodeState == STATE_WALL ))
		//	{
		//		p->m_nodeState = STATE_TANK;
		//		//������� �浹 Ʈ��
		//		p->m_ClickBox = true;
		//	}
		//	//m_count++;
		//	
		//}
		//else
		//{
		//	//�����ʾҴ�.
		//	p->m_ClickBox = false;
		//}
		//
		////��ũ�� ���°� ��� �Ϲݳ��ȭ
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

	Debug->AddText("�浹 ����");
	Debug->AddText(m_count);
	Debug->EndLine();
}

void AStar::InitNodes(IMap * pMap)
{
	temp_Imap = pMap;
	int nodeDim = 100;// ��� �� �� ����
					 //����
	//�� ��ġ 
	float interval = ((pMap->GetSize().x - NODE_POSITSIZEZ * 2)-20) / (float)(nodeDim - 0.99);

	for (int posZ = 0; posZ < nodeDim; posZ++)
	{
		for (int posX = 0; posX < nodeDim; posX++)
		{
			//����ǵ帮�� �������̴ٸ�
			D3DXVECTOR3 location(NODE_POSITSIZEX + posX * interval, 0, NODE_POSITSIZEZ + posZ * interval);

			pMap->GetHeight(location.y, location);

			//0���ͽ����ؼ� ??
			AStarNode* pNode = new AStarNode(location, m_vecNode.size());

			m_vecNode.push_back(pNode);

			//if (posX == 25 && (posZ > 40 && posZ < 42))
			//{ pNode->m_nodeState = STATE_WALL;
			//	Wall_location.push_back(pNode->m_location);	/*m_pUnit->SetLocation(pNode->m_location);*/ }
			
			// ������ (��ũ�� ���)
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
	//���� ������ڵ�

	for (size_t i = 0; i < m_vecNode.size(); i++)
	{
		//���� ���������� �����ϰ� �ڽ��� �������� ���� Edge���
		if (i % nodeDim != nodeDim - 1)//����������ξ� �������� �����⋚���� -1 ���ش�.
		{
			m_vecNode[i]->AddEdge(m_vecNode[i + 1]);
			m_vecNode[i + 1]->AddEdge(m_vecNode[i]);
		}
		//���� �� Ⱦ�� �����ϰ� �ڽ��� �� ���� ���� edge���
		if (i < m_vecNode.size() - nodeDim)
		{
			m_vecNode[i]->AddEdge(m_vecNode[i + nodeDim]);
			m_vecNode[i + nodeDim]->AddEdge(m_vecNode[i]);
		}
	}
}

void AStar::FindPath(D3DXVECTOR3 startPos, D3DXVECTOR3 destPos, OUT vector<int>& vecIndex)
{
	//�ε����� ��ġ�� ���������̝��ϱ� �� ����� ��ġ�� ���󰡴°���
	RestNodes();

	int startNodeIdx = FindClosestNode(startPos);
	int destNodeIdx = FindClosestNode(destPos);

	//���� ������ ��!
	if (startNodeIdx == -1 || destNodeIdx == -1)
	{
		return;
	}

	//����� ��带 �ʱ�ȭ���ְ� �������·� �����.
	float g = 0.0f;
	float h = GetManHattanDistance(startNodeIdx, destNodeIdx);
	float f = g + h;

	m_vecNode[startNodeIdx]->SetValues(STATE_OPEN, g, h, f, startNodeIdx);
	//m_pOpenNodeList.push_back(m_vecNode[startNodeIdx]);
	m_pOpenNodeHeap->Insert(m_vecNode[startNodeIdx]);

	//������ ��尡 ���� ���°� �� ������ ����� ������ Ȯ���� ����
	//Ȯ���� �Ϸ��� ���� ���� ���·� �����.


	//Ŭ����Ǹ�����
	while (m_vecNode[destNodeIdx]->m_nodeState != STATE_CLOSE)
	{
		int currIndex = GetMinFNodeIndex();
		if (currIndex == -1)return;

		Extend(currIndex, destNodeIdx);
		m_vecNode[currIndex]->m_nodeState = STATE_CLOSE;
	}//������ ���� ã������

	 //������ ������ ����� ��� �������� ���� ������ �ε�����
	 //path ��Ͽ� �߰�, ��Ͽ� �߰��� ������ ��� ���·� �����

	int currIndex = destNodeIdx;
	while (currIndex != startNodeIdx)
	{
		m_vecNode[currIndex]->m_nodeState = STATE_USING;
		vecIndex.push_back(currIndex);
		currIndex = m_vecNode[currIndex]->m_via;
	}

	//����� ����� �ε����� Path ��Ͽ� �߰��ϰ� ��� ���·� �����
	m_vecNode[currIndex]->m_nodeState = STATE_USING;
	vecIndex.push_back(currIndex);
	//������ - > ������... ->����� �ε��� ��� �ϼ�


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
	//���̶� ���� �����
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
	return closestNodeIndex;//���尡��� ����� �ε�����ȯ
}

float AStar::GetManHattanDistance(int from, int to)
{
	float offsetX = fabs(m_vecNode[from]->GetLocation().x - m_vecNode[to]->GetLocation().x);
	float offsetZ = fabs(m_vecNode[from]->GetLocation().z - m_vecNode[to]->GetLocation().z);

	return offsetX + offsetZ;
}

int AStar::GetMinFNodeIndex()
{
	//f ���� ���� �����ָ� ã������

	AStarNode* node = NULL;

	/*
	float minValue = FLT_MAX;

	for (auto p : m_pOpenNodeList)
	{
	if (p->m_f < minValue)
	{
	minValue = p->m_f;
	node = p;
	//���������� ã�°�

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
	//�������� ������ �޾ƿ�(�ε���)
	//���۳���� ��� ���� ��带 �޾Ƽ� Ȯ���ϴ°���
	vector<EDGE_INFO*> vecEdge = m_vecNode[targetIdx]->GetEdgeInfos();

	for (int i = 0; i < vecEdge.size(); i++)
	{
		int index = vecEdge[i]->index;
		AStarNode* currNode = m_vecNode[index];

		if (currNode->m_nodeState == STATE_CLOSE) continue;//����������?
		if (currNode->m_nodeState == STATE_WALL) continue;//��?
		if (currNode->m_nodeState == STATE_NOHIDEWALL) continue;
		if (currNode->m_nodeState == STATE_TANK) continue;
														  //������������ �ڽ�Ʈ(����Ÿ������� �ʿ��� ���)
		float G = m_vecNode[targetIdx]->m_g + vecEdge[i]->edgeCost;//Ȯ���Ϸ��� �������� ���µ� �ʿ��� �� g ��

		float H = GetManHattanDistance(index, destIdx);//�ʿ��� ����� ������
		float F = G + H;

		if (currNode->m_nodeState == STATE_OPEN &&
			G >= currNode->m_g) continue; // �����ʿ��� �ѱ�

		currNode->SetValues(STATE_OPEN, G, H, F, targetIdx);//���������� ������ ���� ���

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
			//��������ġ���� �� ��ġ�� ����
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
		//�浹������
		if (isIntersected == true)
		{
			numEraseNode--;//�ڱ������� �ڸ�
			break;
		}
		//�浹��������
		else
		{
			numEraseNode++;//�ڱ����ĸ� �ڸ�
		}
	}
}

void AStar::MakeDirectPath(const D3DXVECTOR3 & startPos,
	const D3DXVECTOR3 & destPos, OUT vector<int>& vecIndex)
{

	//if (m_vecObstacle.empty() == true)
	//{
	//	//��ֹ� ������ �����̵�
	//	vecIndex.clear();
	//}
	//else
	//{
	int numNodeToErase = 0;
	//������������ üũ�ϰ� ���� ���� �������� ��� ����
	CalcEraseCount(startPos, vecIndex, true, numNodeToErase);
	//�ڿ������� ����?
	if (numNodeToErase > 0)
		vecIndex.erase(vecIndex.end() - numNodeToErase, vecIndex.end());



	//������������ üũ�ϰ� ���� ���� �������� ��� ����
	CalcEraseCount(destPos, vecIndex, true, numNodeToErase);

	if (numNodeToErase == vecIndex.size()) numNodeToErase--;

	if (numNodeToErase > 0)
		vecIndex.erase(vecIndex.begin(), vecIndex.begin() + numNodeToErase);

	//}
}
