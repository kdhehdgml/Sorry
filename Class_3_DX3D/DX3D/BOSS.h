#pragma once

#include "IUnitObject.h"


class BOSS : public IUnitObject
{
public:
	BOSS();
	~BOSS();

	// IUnitObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:

	LPD3DXMESH Load(const char* szFileName);
	LPD3DXEFFECT LoadShader(const char* szFileName);


};

