#include "stdafx.h"
#include "Objects.h"
#include "x/SkinnedMeshHLSL.h"

set<IObject*> Objects::m_pObjectList;
map<WORD, list<IDisplayObject*>> Objects::m_tagList;
IMap* Objects::m_pCurrentMap = NULL;
map<CString, SkinnedMeshHLSL*> Objects::m_pSkinnedMeshList;

Objects* Objects::instance = NULL;


//선생님 이걸로 전부 삭제하는걸 만드신거같은데 왜 새로운 오브젝트에는 따로따로 하셨나요?
Objects * Objects::Get()
{
	if (instance == NULL)
		instance = new Objects();

	return instance;
}

void Objects::Delete()
{
	/*


	for (auto p : m_tagList[TAG_PARTICLE])
	{
		SAFE_RELEASE(p);
	}

	for (auto p : m_pSkinnedMeshList)
	{
		p.second->Delete();
		p.second->Release();
	}
	m_pSkinnedMeshList.clear();
	
	*/
	assert(m_pObjectList.empty() && "생성된 객체 중 삭제되지 않은 객체가 있습니다.");

	SAFE_DELETE(instance);

}


Objects::Objects()
{
}

Objects::~Objects()
{
	
}

void Objects::AddObject(IObject* pObject)
{
	m_pObjectList.insert(pObject);
}

void Objects::RemoveObject(IObject* pObject)
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

	/*
	if (name == NULL)
	{
		m_pCurrentMap = NULL;
		return;
	}
	
	*/
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


SkinnedMeshHLSL* Objects::GetSkinnedMesh(LPCTSTR path, LPCTSTR filename)
{
	CString fullPath(path);
	fullPath.Append(filename);

	if (m_pSkinnedMeshList.find(fullPath) == m_pSkinnedMeshList.end())
	{
		SkinnedMeshHLSL *pMesh = new SkinnedMeshHLSL();
		pMesh->Load(path, filename);
		m_pSkinnedMeshList[fullPath] = pMesh;
	}
	return m_pSkinnedMeshList[fullPath];
}
