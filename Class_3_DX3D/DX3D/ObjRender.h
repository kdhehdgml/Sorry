#pragma once

class ObjRen;

class ObjRender
{
public:
	ObjRender();
	~ObjRender();

	//��ȣ ����
	ObjRen*			m_MapTest[16];

	//ö����
	ObjRen*			m_BarbedWireT[48];

	//��ݹ�ħ
	ObjRen*			m_FireStep00;

	//�ָӴ�
	ObjRen*			SaddleBag0[30];
	ObjRen*			SaddleBag1[30];

	//����
	ObjRen*			m_Tree00[20];
	ObjRen*			m_Tree01[20];
	ObjRen*			m_Tree02[20];
	ObjRen*			m_Tree03[20];
	//ObjRen*			m_Tree04[10];
	//ObjRen*			m_Tree05[10];
	ObjRen*			m_Tree06[20];

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


	void Init();
	void Render();
};

