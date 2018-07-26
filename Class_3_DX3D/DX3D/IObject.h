#pragma once
class IObject
{
private:
	int m_referenceCount;

public:
	IObject();
	virtual ~IObject();

	virtual void AddRef();
	virtual void Release();
};

