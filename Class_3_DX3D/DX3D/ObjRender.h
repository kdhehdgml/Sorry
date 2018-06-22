#pragma once

class ObjRen;

class ObjRender
{
public:
	ObjRender();
	~ObjRender();

	//ÂüÈ£ ÆÇÀÚ
	ObjRen*			m_MapTest;
	ObjRen*			m_MapTest0;
	ObjRen*			m_MapTest1;
	ObjRen*			m_MapTest2;
	ObjRen*			m_MapTest3;
	ObjRen*			m_MapTest4;
	ObjRen*			m_MapTest5;
	ObjRen*			m_MapTest6;

	//Ã¶Á¶¸Á
	ObjRen*			m_BarbedWire00;
	ObjRen*			m_BarbedWire01;
	ObjRen*			m_BarbedWire02;
	ObjRen*			m_BarbedWire03;
	ObjRen*			m_BarbedWire04;
	//¸Ç À­ÁÙ
	ObjRen*			m_BarbedWireT00;
	ObjRen*			m_BarbedWireT01;
	ObjRen*			m_BarbedWireT02;
	ObjRen*			m_BarbedWireT03;
	ObjRen*			m_BarbedWireT04;
	ObjRen*			m_BarbedWireT05;
	ObjRen*			m_BarbedWireT06;
	ObjRen*			m_BarbedWireT07;
	ObjRen*			m_BarbedWireT08;
	ObjRen*			m_BarbedWireT09;
	ObjRen*			m_BarbedWireT10;
	ObjRen*			m_BarbedWireT11;

	//³ª¹«
	ObjRen*			m_Tree00;
	ObjRen*			m_Tree01;
	ObjRen*			m_Tree02;
	ObjRen*			m_Tree03;
	ObjRen*			m_Tree04;
	ObjRen*			m_Tree05;
	ObjRen*			m_Tree06;

	//ÁöÇª¶ó±â
	ObjRen*			m_Straw00;

	//µ¹
	ObjRen*			m_Stone00;

	void Init();
	void Render();
};

