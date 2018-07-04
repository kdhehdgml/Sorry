#pragma once

class ObjRen;

class ObjRender
{
public:
	ObjRender();
	~ObjRender();

	//참호 판자
	ObjRen*			m_MapTest[8];

	//철조망
	ObjRen*			m_BarbedWireT[38];

	//사격받침
	ObjRen*			m_FireStep00;

	//주머니
	ObjRen*			SaddleBag0[30];

	//나무
	ObjRen*			m_Tree00[10];
	ObjRen*			m_Tree01[10];
	ObjRen*			m_Tree02[10];
	ObjRen*			m_Tree03[10];
	//ObjRen*			m_Tree04[10];
	//ObjRen*			m_Tree05[10];
	ObjRen*			m_Tree06[10];

	////지푸라기
	//ObjRen*			m_Straw00[6];

	////돌
	//ObjRen*			m_Stone00[20];

	void Init();
	void Render();
};

