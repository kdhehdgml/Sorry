#pragma once
class ObjRen;


class FR_HEADGEAR
{
public:
	FR_HEADGEAR();
	~FR_HEADGEAR();

	ObjRen*		m_Skin;

	D3DXVECTOR3	m_pos;
	void init();
	void update();
	void render();

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };
};

