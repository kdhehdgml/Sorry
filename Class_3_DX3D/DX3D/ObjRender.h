#pragma once

class ObjRen;

class ObjRender
{
public:
	ObjRender();
	~ObjRender();

	//��ȣ ����
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

	//ö����
	ObjRen*			m_BarbedWireT[53];
	//ObjRen*			m_BarbedWireT1[20];
	//ObjRen*			m_BarbedWireT2[20];


	//��ݹ�ħ
	ObjRen*			m_FireStep00[6];

	//�ָӴ�
	ObjRen*			SaddleBag0[30];
	ObjRen*			SaddleBag1[116];

	//����
	ObjRen*			m_Tree00[10];
	ObjRen*			m_Tree01[10];
	ObjRen*			m_Tree02[10];
	ObjRen*			m_Tree03[10];
	//ObjRen*			m_Tree04[10];
	//ObjRen*			m_Tree05[10];
	ObjRen*			m_Tree06[10];

	//��Ǫ���
	ObjRen*			m_Straw00[2];

	//��
	ObjRen*			m_Stone00[4];

	//��ũ
	ObjRen*			m_Tank[2];

	//����
	ObjRen*			m_Wagon[3];

	//�ǹ�
	ObjRen*			m_Apt[3];

	//Ÿ��
	ObjRen*			m_Tile[15];

	void Init();
	void Render();
	void Update();
};

