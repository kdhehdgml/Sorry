#pragma once

class ObjRen;

class ObjRender
{
public:
	ObjRender();
	~ObjRender();

	//��ȣ ����
	ObjRen*			m_MapTest[16];
	ObjRen*			m_MapTest00[75];;

	//ö����
	ObjRen*			m_BarbedWireT[47];

	//��ݹ�ħ
	ObjRen*			m_FireStep00[6];

	//�ָӴ�
	ObjRen*			SaddleBag0[30];
	ObjRen*			SaddleBag1[86];

	//����
	ObjRen*			m_Tree00[5];
	ObjRen*			m_Tree01[5];

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

