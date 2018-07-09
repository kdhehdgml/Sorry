#pragma once
#include "stdafx.h"

class Objects
{
public:
	static Objects*	Get();
	static void		Delete();
private:
	static Objects*	instance;
	Objects();
	~Objects();

	/////All Objects/////
	static set<BaseObject*> m_pObjectList;
public:
	static void AddObject(BaseObject* pObject);
	static void RemoveObject(BaseObject* pObject);
	/////All Objects/////

	/////TagList/////
private:
	static map<WORD, list<IDisplayObject*>> m_tagList;
public:
	static void AddToTagList(WORD _tag, IDisplayObject* _pObject);
	static void RemoveFromTagList(WORD _tag, IDisplayObject* _pObject);
	static IDisplayObject* FindObjectByTag(WORD _tag);
	static list<IDisplayObject*> FindObjectsByTag(WORD _tag);
	/////TagList/////

	/////Map/////
private:
	static IMap * m_pCurrentMap;
public:
	static void SetCurrentMap(LPCTSTR name);
	static IMap* GetCurrentMap();
	/////Map/////

};

