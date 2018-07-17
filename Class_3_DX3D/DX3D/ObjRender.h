#pragma once

class ObjRen;

class ObjRender
{
public:
	ObjRender();
	~ObjRender();

	//참호 판자
	ObjRen*			m_MapTest[16];

	//ObjRen*			m_MapTest1[25];
	ObjRen*			m_MapTest1;
	ObjRen*			m_MapTest00[75];;

	float size;
	float x;
	float y;
	float z;
	float rotationX;
	float rotationY;
	float rotationZ;

	//철조망
	ObjRen*			m_BarbedWireT[53];
	//ObjRen*			m_BarbedWireT1[20];
	//ObjRen*			m_BarbedWireT2[20];


	//사격받침
	ObjRen*			m_FireStep00[6];

	//주머니
	ObjRen*			SaddleBag0[30];
	ObjRen*			SaddleBag1[116];

	//나무
	ObjRen*			m_Tree00[10];
	ObjRen*			m_Tree01[10];
	ObjRen*			m_Tree02[10];
	ObjRen*			m_Tree03[10];
	//ObjRen*			m_Tree04[10];
	//ObjRen*			m_Tree05[10];
	ObjRen*			m_Tree06[10];

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

	//타일
	ObjRen*			m_Tile[15];

	void Init();
	void Render();
	void Update();
};

