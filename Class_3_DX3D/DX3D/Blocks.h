#pragma once
#include "BaseObject.h"
#include "IDisplayObject.h"


class Blocks : public IDisplayObject
{
private:
	D3DXMATRIXA16			m_matWorld;
	LPDIRECT3DTEXTURE9		m_tex;

	vector<VERTEX_PT>		m_vecPTVertex;

public:
	Blocks();
	~Blocks();


	void InitTT(D3DXMATRIXA16* pMat, vector<vector<int>> &vecUV);
	void SetPTVertexTT(vector<VERTEX_PT>& vecOut, vector<D3DXVECTOR3>& vecVertex, vector<vector<int>>& uv);
	void MakeUVListTT(vector<D3DXVECTOR2>& out, vector<vector<int>>& uv);


	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;

	virtual void Update() override;

	virtual void Render() override;

};

