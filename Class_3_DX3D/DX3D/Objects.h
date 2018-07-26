#pragma once
#include "stdafx.h"
class SkinnedMeshHLSL;


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
	static set<IObject*> m_pObjectList;
public:
	static void AddObject(IObject* pObject);
	static void RemoveObject(IObject* pObject);
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

	/////Player/////
public:
	static IUnitObject* GetPlyer();
	/////Player/////


	/////Map/////
private:
	static IMap * m_pCurrentMap;
public:
	static void SetCurrentMap(LPCTSTR name);
	static IMap* GetCurrentMap();
	/////Map/////

	/////SkinnedMesh/////
private:
	static map<CString, SkinnedMeshHLSL*> m_pSkinnedMeshList;
public:
	static SkinnedMeshHLSL* GetSkinnedMesh(LPCTSTR path, LPCTSTR filename);
	/////SkinnedMesh/////
};

