#include "stdafx.h"
#include "IDisplayObject.h"


IDisplayObject::IDisplayObject()
	:m_scale(1, 1, 1), m_tag(-1), m_pParent(NULL), m_pFrameMatrix(NULL), m_renderMode(RenderMode_Default)
{
//	m_pParent = NULL;
	D3DXMatrixIdentity(&m_localMatrix);
	D3DXMatrixIdentity(&m_matWorld);
	//D3DXMatrixIdentity(&m_worldMatrix);
	D3DXMatrixIdentity(&m_combinedMatrix);
}


IDisplayObject::~IDisplayObject()
{
}



void IDisplayObject::AddChild(IDisplayObject * pChild)
{
	if (pChild == NULL) return;
	m_vecPChild.push_back(pChild);
	pChild->m_pParent = this;
}

void IDisplayObject::ReleaseAll()
{
	for (LPDisplayObject child : m_vecPChild)
		if (child) child->ReleaseAll();

	m_vecPChild.clear();
	BaseObject::Release();
}

IDisplayObject * IDisplayObject::FindChildByName(LPCTSTR name)
{
	if (m_name == name)
		return this;

	for (auto p : m_vecPChild)
	{
		LPDisplayObject pChild = p->FindChildByName(name);

		if (pChild)
			return pChild;
	}
	return NULL;
}
