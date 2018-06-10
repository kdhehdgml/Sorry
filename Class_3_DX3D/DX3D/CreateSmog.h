#pragma once

struct SMOG2
{
	LPDIRECT3DTEXTURE9 _pTex;
	D3DXVECTOR3		_position;
	D3DXCOLOR		_color;
	float			_MaxTransparency;
};
 

class CreateSmog :public IDisplayObject
{


private:
	LPDIRECT3DVERTEXBUFFER9   m_pVB;
	vector<LPDIRECT3DTEXTURE9>      m_pTex;

	float					m_SmogSize;
	int						m_Smog_index;


	D3DXMATRIXA16   matWorld;//���� ���°� ��ȭ�Ҳ��� ����� ��Ʈ����

	int m_IndexCount;
	int m_MaxIndex;
	size_t m_numParticle;

public:
	vector<SMOG2*>      m_vecAtt;

	CreateSmog();
	~CreateSmog();

	//void Init();
	//void Update();
	//void Render();
	void Insert(D3DXVECTOR3 pos, float transparency);



	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

