#pragma once
#include "IDisplayObject.h"
class BulletUI :
	public IDisplayObject
{
public:
	BulletUI();
	~BulletUI();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

