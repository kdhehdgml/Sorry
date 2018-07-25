#include "stdafx.h"
#include "IObject.h"
#include "Objects.h"

IObject::IObject()
	: m_referenceCount(1)
{
	Objects::AddObject(this);
}

IObject::~IObject()
{
	Objects::RemoveObject(this);
	assert(m_referenceCount <= 0 && "Use Release Method");
}

void IObject::AddRef()
{
	m_referenceCount++;
}

void IObject::Release()
{
	m_referenceCount--;

	if (m_referenceCount <= 0)
	{
		delete this;
	}
}
