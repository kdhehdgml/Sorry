#pragma once
class BillBoard
{
public:
	BillBoard();
	~BillBoard();

	LPDIRECT3DTEXTURE9		g_pTexBillboard;
	D3DXMATRIXA16 m_matWorld;

	void Init();
	void Update();
	void Render();
};

