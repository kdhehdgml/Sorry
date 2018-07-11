#pragma once
#include "IMap.h"

class HeightMap : public IMap
{
protected:
	MTLTEX*		m_pMtlTex;
	LPD3DXMESH	m_pMesh;
	bool		AStarNodeRenderOn;
	bool		TabKeyDownCheck;

	vector<D3DXVECTOR3> m_vecSurfaceVertex;
	vector<D3DXVECTOR3> m_vecObstacleVertex;
	vector<vector<D3DXVECTOR3>> m_wall;
public:
	HeightMap();
	virtual ~HeightMap();

	void Load(const char* fullPath, D3DXMATRIXA16* pMat = NULL);
	void SetMtlTex(D3DMATERIAL9 &mtl, LPDIRECT3DTEXTURE9 pTex);

	// IMap을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void RenderUseShader_0() override;
	virtual void RenderUseShader_1() override;
	virtual bool GetHeight(OUT float & height, const D3DXVECTOR3 & pos) override;
	virtual bool CalcPickedPosition(D3DXVECTOR3 &vOut,
		WORD screenX, WORD screenY) override;
	void SetSurface();
	void SetObstacle();
	vector<vector<D3DXVECTOR3>> SetWall(vector<vector<D3DXVECTOR3>> wall) { return m_wall = wall; }
	vector<vector<D3DXVECTOR3>> GetWall() { return m_wall; }
	METHOD_WNDPROC(WndProc);
};

