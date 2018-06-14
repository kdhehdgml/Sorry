#pragma once

#define g_pObjMgr ObjManager::GetInstance()

class BaseObject;
class IUnitObject;

class ObjManager
{
	SINGLETON(ObjManager)
private:
	set<BaseObject*> m_setObject;
	map<WORD, vector<IUnitObject*>> m_tagList;

public:
	void AddObject(BaseObject* pObj);
	void RemoveObject(BaseObject* pObj);
	void Destroy();

	void AddToTagList(WORD _tag, IUnitObject* _pObj);
	void RemoveFromTagList(WORD _tag, IUnitObject* _pObj);
	IUnitObject* FindObjectByTag(WORD _tag);
	vector<IUnitObject*> FindObjectsByTag(WORD _tag);

};

