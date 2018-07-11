#pragma once
#include "IDisplayObject.h"
class BulletUI :
	public IDisplayObject
{
public:
	BulletUI();
	~BulletUI();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

