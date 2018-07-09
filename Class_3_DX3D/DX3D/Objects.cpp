#include "stdafx.h"
#include "Objects.h"


Objects* Objects::instance = NULL;
set<BaseObject*> Objects::m_pObjectList;
map<WORD, list<IDisplayObject*>> Objects::m_tagList;
IMap* Objects::m_pCurrentMap = NULL;

Objects * Objects::Get()
{
	if (instance == NULL)
		instance = new Objects();

	return instance;
}

void Objects::Delete()
{
	//for (auto p : m_tagList[TAG_PARTICLE])
	//{
	//	SAFE_RELEASE(p);
	//}

	assert(m_pObjectList.empty() && "생성된 객체 중 삭제되지 않은 객체가 있습니다.");

	SAFE_DELETE(instance);

}


Objects::Objects()
{
}

Objects::~Objects()
{
	
}

void Objects::AddObject(BaseObject* pObject)
{
	m_pObjectList.insert(pObject);
}

void Objects::RemoveObject(BaseObject* pObject)
{
	m_pObjectList.erase(pObject);
}

void Objects::AddToTagList(WORD _tag, IDisplayObject * _object)
{
	m_tagList[_tag].push_back(_object);
}

void Objects::RemoveFromTagList(WORD _tag, IDisplayObject* _pObject)
{
	m_tagList[_tag].remove(_pObject);
}

IDisplayObject * Objects::FindObjectByTag(WORD _tag)
{
	if (m_tagList[_tag].empty() == true) return NULL;

	return m_tagList[_tag].front();
}

list<IDisplayObject*> Objects::FindObjectsByTag(WORD _tag)
{
	return m_tagList[_tag];
}


void Objects::SetCurrentMap(LPCTSTR name)
{
	//for (auto p : m_tagList[TAG_MAP])
	//{
	//	if (name == p->GetName())
	//	{
	//		m_pCurrentMap = (IMap*)p;
	//		break;
	//	}
	//}
}

IMap * Objects::GetCurrentMap()
{
	return m_pCurrentMap;
}