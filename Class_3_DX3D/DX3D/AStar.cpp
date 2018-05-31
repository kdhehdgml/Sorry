#include "stdafx.h"
#include "AStar.h"
#include "AStarNode.h"
#include "Ray.h"
#include "Heap.h"

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
}

void AStar::Init()
{
	D3DXCreateSphere(g_pDevice, 0.2f, 10, 10, &m_pSphere, NULL);
	m_pOpenNodeHeap = new Heap;
}

void AStar::Render()
{
	D3DXMATRIXA16 mat;

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
		}

		D3DXMatrixTranslation(&mat, p->GetLocation().x, p->GetLocation().y, p->GetLocation().z);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		m_pSphere->DrawSubset(0);

		D3DXMatrixIdentity(&mat);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST,
			p->GetVecLines().size() / 2, p->GetVecLines()[0],
			sizeof(D3DXVECTOR3));
	}
}

void AStar::InitNodes(IMap * pMap)
{
	int nodeDim = 30;//30x30

					 //����
	//�� ��ġ 
	float interval = (pMap->GetSize().x - NODE_POSITSIZE*2) / (float)(nodeDim - 0.99);



	for (int posZ = 0; posZ < nodeDim; posZ++)
	{
		for (int posX = 0; posX < nodeDim; posX++)
		{
			//����ǵ帮�� �������̴ٸ�
			D3DXVECTOR3 location(NODE_POSITSIZE + posX * interval, 0, NODE_POSITSIZE + posZ * interval);

			pMap->GetHeight(location.y, location);

			//0���ͽ����ؼ� ??
			AStarNode* pNode = new AStarNode(location, m_vecNode.size());

			m_vecNode.push_back(pNode);

			if (posX == 5 && posZ < 9)
			{
				pNode->m_nodeState = STATE_WALL;
				Wall_location.push_back(pNode->m_location);
				//m_pUnit->SetLocation(pNode->m_location);
			}
			if (posX == 13 && (posZ > 4 && posZ < 26))
			{
				pNode->m_nodeState = STATE_WALL;
				Wall_location.push_back(pNode->m_location);
				//m_pUnit->SetLocation(pNode->m_location);
			}
			if (posX == 15 && (posZ > 3 && posZ < 26))
			{
				pNode->m_nodeState = STATE_NOHIDEWALL;
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
		if (m_vecNode[i]->m_nodeState != STATE_WALL )
			m_vecNode[i]->m_nodeState = STATE_NONE;

		/*if(m_vecNode[i]->m_nodeState != STATE_NOHIDEWALL)
			m_vecNode[i]->m_nodeState = STATE_NONE;*/
	}
}

int AStar::FindClosestNode(const D3DXVECTOR3 & pos)
{
	//���̶� ���� �����
	float minDist = FLT_MAX;
	int closestNodeIndex = -1;

	for (int i = 0; i < m_vecNode.size(); i++)
	{
		if (m_vecNode[i]->m_nodeState == STATE_WALL || m_vecNode[i]->m_nodeState == STATE_NOHIDEWALL)
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
				(m_vecNode[i]->m_nodeState == STATE_NOHIDEWALL && a + 0.3 < nodeDist))
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
