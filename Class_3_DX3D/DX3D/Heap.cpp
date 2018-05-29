#include "stdafx.h"
#include "Heap.h"
#include "AStarNode.h"

Heap::Heap()
{
}


Heap::~Heap()
{
}

void Heap::Insert(AStarNode * pNode)
{
	//�������� �� ��� �߰�
	//�θ�� ���ذ��� ������ ����
	m_vecNode.push_back(pNode);
	Upheap(m_vecNode.size() - 1);
}

AStarNode * Heap::ExtractMin()
{
	//��Ʈ�� ����
	//���� ������ ��带 ��Ʈ �ڸ��� �ø���
	//�ڽ� ���� ū ���̸� ����

	if (m_vecNode.empty())
		return NULL;

	AStarNode* minFNode = m_vecNode.front();
	Swap(0, m_vecNode.size() - 1);
	m_vecNode.pop_back();
	DownHeap(0);

	return minFNode;
}

void Heap::Clear()
{
	m_vecNode.clear();
}

void Heap::Upheap(int targetIdx)
{
	if (targetIdx == 0)
		return;

	int parentIdx = (targetIdx - 1) / 2;

	if (m_vecNode[parentIdx]->m_f > m_vecNode[targetIdx]->m_f)
	{
		Swap(targetIdx, parentIdx);
		Upheap(parentIdx);
	}
}

void Heap::DownHeap(int targetIdx)
{
	int LChildIdx = targetIdx * 2 + 1;

	if (LChildIdx >= m_vecNode.size())
		return;

	int minChildIdx = LChildIdx;
	int RChildIdx = LChildIdx + 1;

	//2 ���� child �� �� ���� ���� ã�´�
	if (RChildIdx < m_vecNode.size())
	{
		if (m_vecNode[RChildIdx]->m_f < m_vecNode[LChildIdx]->m_f)
			minChildIdx = RChildIdx;
	}
	//target �� ���� �� ũ�� �ش� child �� swap
	if (m_vecNode[targetIdx]->m_f > m_vecNode[minChildIdx]->m_f)
	{
		Swap(targetIdx, minChildIdx);
		DownHeap(minChildIdx);
	}
}

void Heap::Swap(int idx1, int idx2)
{
	AStarNode* pTemp = m_vecNode[idx2];
	m_vecNode[idx2] = m_vecNode[idx1];
	m_vecNode[idx1] = pTemp;
}
