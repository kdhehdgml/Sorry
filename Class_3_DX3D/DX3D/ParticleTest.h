#pragma once
#include "IDisplayObject.h"

struct Attribute
{
	D3DXVECTOR3 _position;
	D3DXVECTOR3 _velocity;
	D3DXCOLOR	_color;
	float		_delay;
	float		_age;

	Attribute() :_delay(0.0f), _age(0.0f) {}
};

class ParticleTest : public IDisplayObject
{
public:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DTEXTURE9		m_pTex;
	vector<Attribute*>		m_vecAtt;

	ParticleTest();
	~ParticleTest();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

