#pragma once
#include "IDisplayObject.h"

class Hexagon : public IDisplayObject
{
private:
	vector<VERTEX_PC>	m_vecVertex;
	WORD				m_radius;

public:
	Hexagon(WORD radius = 8);
	~Hexagon();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

