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
	//마지막에 새 노드 추가
	//부모와 비교해가며 작으면 스왑
	m_vecNode.push_back(pNode);
	Upheap(m_vecNode.size() - 1);
}

AStarNode * Heap::ExtractMin()
{
	//루트를 추출
	//제일 마지막 노드를 루트 자리로 올린후
	//자식 보다 큰 값이면 스왑

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

	//2 개의 child 중 더 작은 쪽을 찾는다
	if (RChildIdx < m_vecNode.size())
	{
		if (m_vecNode[RChildIdx]->m_f < m_vecNode[LChildIdx]->m_f)
			minChildIdx = RChildIdx;
	}
	//target 의 값이 더 크면 해당 child 와 swap
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
