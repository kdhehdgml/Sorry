#pragma once
#include "IUnitObject.h"

class MoveOBJ;


class FR_HEADGEAR : public IUnitObject
{
public:
	FR_HEADGEAR();
	~FR_HEADGEAR();

	MoveOBJ*		m_Skin;
	D3DXMATRIXA16	matS, matR, matT;
	D3DXMATRIXA16	m_Hand_mat;


	BoundingSphere* m_pBoundingSphere;
	LPD3DXMESH		m_pSphere;


	void SetPos(D3DXVECTOR3* pos) { m_pos = *pos; };
	void SetMat(D3DXMATRIXA16 *mat) { m_Hand_mat = (*mat); }

	// IUnitObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

