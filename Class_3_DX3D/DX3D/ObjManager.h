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

	bool IntersectSphereBox(BoundingSphere* pSphere, BoundingBox* pBox) {
		float rr = pSphere->radius * pSphere->radius;
		float dmin = 0;
		if (pSphere->center.x < pBox->aa.x) {
			dmin += sqrt(pSphere->center.x - pBox->aa.x);
		}
		else if (pSphere->center.x > pBox->bb.x) {
			dmin += sqrt(pSphere->center.x - pBox->bb.x);
		}

		if (pSphere->center.y < pBox->aa.y) {
			dmin += sqrt(pSphere->center.y - pBox->aa.y);
		}
		else if (pSphere->center.y > pBox->bb.y) {
			dmin += sqrt(pSphere->center.y - pBox->bb.y);
		}

		if (pSphere->center.z < pBox->aa.z) {
			dmin += sqrt(pSphere->center.z - pBox->aa.z);
		}
		else if (pSphere->center.z > pBox->bb.z) {
			dmin += sqrt(pSphere->center.z - pBox->bb.z);
		}
		if (dmin <= rr) {
			return true;
		}
		return false;
	}
};

