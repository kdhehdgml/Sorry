#pragma once
#include "IUnitObject.h"

class MoveOBJ;

class MARK : public IUnitObject
{
public:
	MARK();
	~MARK();

	MoveOBJ*	m_mark;

	float x, y, z, xR, yR, zR;

	// IUnitObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};



