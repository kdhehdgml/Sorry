#include "stdafx.h"
#include "ObjManager.h"


ObjManager::ObjManager()
{
}


ObjManager::~ObjManager()
{
}

void ObjManager::AddObject(BaseObject * pObj)
{
	m_setObject.insert(pObj);
}

void ObjManager::RemoveObject(BaseObject * pObj)
{
	m_setObject.erase(pObj);
}

void ObjManager::Destroy()
{
//	assert(m_setObject.empty() && "생성된 객체 중 삭제되지 않은 객체가 있습니다.");
}

void ObjManager::AddToTagList(WORD _tag, IUnitObject * _pObj)
{
	m_tagList[_tag].push_back(_pObj);
}

void ObjManager::RemoveFromTagList(WORD _tag, IUnitObject * _pObj)
{
	m_tagList[_tag].clear();
}

IUnitObject * ObjManager::FindObjectByTag(WORD _tag)
{
	if (m_tagList[_tag].empty() == true) 
		return NULL;

	return m_tagList[_tag].front();
}

vector<IUnitObject*> ObjManager::FindObjectsByTag(WORD _tag)
{
	return m_tagList[_tag];
}
