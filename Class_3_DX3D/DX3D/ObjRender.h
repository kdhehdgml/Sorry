#pragma once

class ObjRen;

class ObjRender
{
public:
	ObjRender();
	~ObjRender();

	//��ȣ ����
	ObjRen*			m_MapTest[8];

	//ö����
	ObjRen*			m_BarbedWireT[38];

	//��ݹ�ħ
	ObjRen*			m_FireStep00;

	//�ָӴ�
	ObjRen*			SaddleBag0[30];

	//����
	ObjRen*			m_Tree00[10];
	ObjRen*			m_Tree01[10];
	ObjRen*			m_Tree02[10];
	ObjRen*			m_Tree03[10];
	//ObjRen*			m_Tree04[10];
	//ObjRen*			m_Tree05[10];
	ObjRen*			m_Tree06[10];

	////��Ǫ���
	//ObjRen*			m_Straw00[6];

	////��
	//ObjRen*			m_Stone00[20];

	void Init();
	void Render();
};

