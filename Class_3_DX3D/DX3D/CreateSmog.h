#pragma once

struct SMOG2
{
	D3DXVECTOR3		_position;
	D3DXCOLOR		_color;
};
 

class CreateSmog
{


private:
	LPDIRECT3DVERTEXBUFFER9   m_pVB;
	LPDIRECT3DTEXTURE9      m_pTex;



	D3DXMATRIXA16   matWorld;//만약 상태값 변화할꺼면 사용할 매트릭스

	int m_IndexCount;
	int m_MaxIndex;
	size_t m_numParticle;

public:
	vector<SMOG2*>      m_vecAtt;

	CreateSmog();
	~CreateSmog();

	void Init();
	void Update();
	void Render();
	void Insert(D3DXVECTOR3 pos);

	void Relese() 
	{
   		m_pVB->Release(); 
		m_vecAtt.clear(); 
	}
};

