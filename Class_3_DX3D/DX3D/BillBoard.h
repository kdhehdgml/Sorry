#pragma once
class BillBoard
{
public:
	BillBoard();
	~BillBoard();

	LPDIRECT3DTEXTURE9		g_pTexBillboard;
	D3DXMATRIXA16 m_matWorld;

	//float xP, yP, zP;
	bool	check;

	void Init();
	void Update();
	void Render(float xP, float yP, float zP);
};

