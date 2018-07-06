#pragma once

class ObjRen;

class ObjRender
{
public:
	ObjRender();
	~ObjRender();

	//참호 판자
	ObjRen*			m_MapTest[16];

	//철조망
	ObjRen*			m_BarbedWireT[48];

	//사격받침
	ObjRen*			m_FireStep00;

	//주머니
	ObjRen*			SaddleBag0[30];
	ObjRen*			SaddleBag1[30];

	//나무
	ObjRen*			m_Tree00[20];
	ObjRen*			m_Tree01[20];
	ObjRen*			m_Tree02[20];
	ObjRen*			m_Tree03[20];
	//ObjRen*			m_Tree04[10];
	//ObjRen*			m_Tree05[10];
	ObjRen*			m_Tree06[20];

	//지푸라기
	ObjRen*			m_Straw00[2];

	//돌
	ObjRen*			m_Stone00[4];

	//탱크
	ObjRen*			m_Tank[2];

	//웨건
	ObjRen*			m_Wagon[3];

	//건물
	ObjRen*			m_Apt[3];


	void Init();
	void Render();
};

