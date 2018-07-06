#include "stdafx.h"
#include "ObjRender.h"
#include "ObjRen.h"

#define CREATE_OBJ(obj_name, size, folder, objFile, TextureImage, x, y, z, rotationX, rotationY, rotationZ) obj_name = new ObjRen;\
      obj_name->Init(size, _T("resources/ObjImages/" ## #folder ##"/" ## #objFile),_T("resources/ObjImages/" ## #folder ##"/" ## #TextureImage), x, y, z, rotationX, rotationY, rotationZ);

ObjRender::ObjRender()
{
	//��ȣ ����
	for (int i = 0; i < 8; i++)
		m_MapTest[i] = NULL;
	//ö����
	for (int i = 0; i < 38; i++)
		m_BarbedWireT[i] = NULL;
	//��ݹ�ħ
	m_FireStep00 = NULL;
	//��
	for (int i = 0; i < 30; i++)
		SaddleBag0[i] = NULL;
	//����
	for (int i = 0; i < 10; i++)
	{
		m_Tree00[i] = NULL;
		m_Tree01[i] = NULL;
		m_Tree02[i] = NULL;
		m_Tree03[i] = NULL;
		//m_Tree04[i] = NULL;
		//m_Tree05[i] = NULL;
		m_Tree06[i] = NULL;
	}
	//   //��Ǫ���
	//   for (int i = 0; i < 6; i++)
	//      m_Straw00[i] = NULL;
	//   //��
	//   for (int i = 0; i < 20; i++)
	//      m_Stone00[i] = NULL;
}


ObjRender::~ObjRender()
{
	//��ȣ ����
	for (int i = 0; i < 8; i++) {
		//m_MapTest[i]->~ObjRen();
		SAFE_DELETE(m_MapTest[i]);
	}
	//ö����
	for (int i = 0; i < 38; i++) {
		//m_BarbedWireT[i]->~ObjRen();
		SAFE_DELETE(m_BarbedWireT[i]);
	}
	//��ݹ�ħ
	//m_FireStep00->~ObjRen();
	SAFE_DELETE(m_FireStep00);
	//��
	for (int i = 0; i < 30; i++) {
		//SaddleBag0[i]->~ObjRen();
		SAFE_DELETE(SaddleBag0[i]);
	}
	//����
	for (int i = 0; i < 10; i++)
	{
		SAFE_DELETE(m_Tree00[i]);
		SAFE_DELETE(m_Tree01[i]);
		SAFE_DELETE(m_Tree02[i]);
		SAFE_DELETE(m_Tree03[i]);
		SAFE_DELETE(m_Tree06[i]);
		//m_Tree00[i]->~ObjRen();
		//m_Tree01[i]->~ObjRen();
		//m_Tree02[i]->~ObjRen();
		//m_Tree03[i]->~ObjRen();
		//m_Tree04[i]->~ObjRen();
		//m_Tree05[i]->~ObjRen();
		//m_Tree06[i]->~ObjRen();
	}
	////��Ǫ���
	//for (int i = 0; i < 6; i++)
	//   m_Straw00[i]->~ObjRen();
	////��
	//for (int i = 0; i < 20; i++)
	//   m_Stone00[i]->~ObjRen();
}


void ObjRender::Init()
{
	//��ȣ ����
	CREATE_OBJ(m_MapTest[0], 66.9f, WoodenBarrier, WoodenBarrierTest02.obj, woodTex.png, 363.0f, 11.5f, -537.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[1], 12.5f, WoodenBarrier, WoodenBarrierPartTest00.obj, woodTex.png, 100.5f, 5.0f, 77.8f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[2], 18.0f, WoodenBarrier, WoodenBarrierPartTest01.obj, woodTex.png, 210.6f, 7.5f, 22.8f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[3], 13.5f, WoodenBarrier, WoodenBarrierPartTest02.obj, woodTex.png, 260.6f, 7.9f, 164.8f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[4], 11.6f, WoodenBarrier, WoodenBarrierPartTest03.obj, woodTex.png, 142.0f, 7.9f, 335.6f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[5], 12.8f, WoodenBarrier, WoodenBarrierPartTest04.obj, woodTex.png, 225.0f, 0.0f, 444.3f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[6], 13.8f, WoodenBarrier, WoodenBarrierPartTest05.obj, woodTex.png, 114.5f, 7.0f, 532.8f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[7], 16.8f, WoodenBarrier, WoodenBarrierPartTest06.obj, woodTex.png, 259.0f, 19.2f, 490.6f, 0.0f, 0.0f, 0.0f);

	//ö����
	//1�� ��
	CREATE_OBJ(m_BarbedWireT[0], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 494.0f, 31.0f, 531.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[1], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 494.0f, 31.0f, 515.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[2], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 494.0f, 33.0f, 475.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[3], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 494.0f, 34.0f, 458.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[4], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 494.0f, 35.0f, 419.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[5], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 500.0f, 31.0f, 374.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[6], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 494.0f, 34.0f, 360.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[7], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 500.0f, 31.0f, 318.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[8], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 494.0f, 33.0f, 304.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[9], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 494.0f, 33.0f, 287.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[10], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 500.0f, 30.0f, 219.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[11], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 494.0f, 33.0f, 229.0f, 0.0f, D3DX_PI / 2, 0.0f);
	//2�� ��
	CREATE_OBJ(m_BarbedWireT[12], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 407.0f, 31.0f, 560.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[13], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 407.0f, 31.0f, 544.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[14], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 407.0f, 32.0f, 502.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[15], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 407.0f, 32.0f, 485.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[16], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 407.0f, 34.0f, 446.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[17], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 413.0f, 30.0f, 401.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[18], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 407.0f, 34.0f, 387.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[19], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 413.0f, 29.0f, 345.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[20], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 407.0f, 32.0f, 330.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[21], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 407.0f, 33.0f, 315.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[22], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 413.0f, 29.0f, 248.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[23], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 407.0f, 32.0f, 258.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[24], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 407.0f, 30.0f, 220.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[25], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 407.0f, 30.0f, 210.0f, 0.0f, D3DX_PI / 2, 0.0f);
	//3�� ��
	CREATE_OBJ(m_BarbedWireT[26], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 322.0f, 31.0f, 531.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[27], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 322.0f, 31.0f, 515.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[28], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 322.0f, 32.0f, 475.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[29], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 322.0f, 33.0f, 458.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[30], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 322.0f, 33.0f, 419.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[31], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 328.0f, 30.0f, 374.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[32], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 322.0f, 34.0f, 360.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[33], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 328.0f, 30.0f, 318.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[34], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 322.0f, 33.0f, 304.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[35], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 322.0f, 33.0f, 287.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[36], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 328.0f, 29.0f, 219.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_BarbedWireT[37], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 322.0f, 33.0f, 229.0f, 0.0f, D3DX_PI / 2, 0.0f);

	//��ݹ�ħ
	//CREATE_OBJ(m_FireStep00, 63.0f, FireStep, FireStep00.obj, woodTex.png, 232.0f, -6.8f, 398.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_FireStep00, 63.0f, FireStep, FireStep01.obj, woodTex.png, 250.0f, -6.8f, 398.0f, 0.0f, 0.0f, 0.0f);

	//��
	CREATE_OBJ(SaddleBag0[0], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 228.0f, 23.2f, 528.3f, 0.0f, 0.57f, 0.0f);
	CREATE_OBJ(SaddleBag0[1], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 238.0f, 23.2f, 522.0f, 0.0f, 0.57f, 0.0f);
	CREATE_OBJ(SaddleBag0[2], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 247.0f, 23.2f, 509.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag0[3], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 247.0f, 23.2f, 494.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag0[4], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 238.0f, 22.8f, 473.0f, 0.0f, -0.83f, 0.0f);
	CREATE_OBJ(SaddleBag0[5], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 235.0f, 22.8f, 451.0f, 0.0f, 0.79f, 0.0f);
	CREATE_OBJ(SaddleBag0[6], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 243.0f, 23.6f, 430.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag0[7], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 251.0f, 23.6f, 409.0f, 0.0f, 0.79f, 0.0f);
	CREATE_OBJ(SaddleBag0[8], 4.0f, SaddleBag, SaddleBag01.obj, SaddleBagTex.png, 260.0f, 23.6f, 396.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag0[9], 4.0f, SaddleBag, SaddleBag01.obj, SaddleBagTex.png, 260.0f, 23.6f, 381.0f, 0.0f, D3DX_PI / 2, 0.0f);

	CREATE_OBJ(SaddleBag0[10], 4.0f, SaddleBag, SaddleBag01.obj, SaddleBagTex.png, 229.0f, 23.6f, 361.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag0[11], 4.0f, SaddleBag, SaddleBag01.obj, SaddleBagTex.png, 234.0f, 23.8f, 346.0f, 0.0f, 0.67f, 0.0f);
	CREATE_OBJ(SaddleBag0[12], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 250.0f, 24.2f, 318.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag0[13], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 260.0f, 24.2f, 281.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag0[14], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 260.0f, 24.2f, 266.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag0[15], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 255.0f, 24.3f, 247.0f, 0.0f, 0.67f, 0.0f);
	CREATE_OBJ(SaddleBag0[16], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 259.0f, 24.3f, 236.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag0[17], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 259.0f, 24.3f, 221.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag0[18], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 251.0f, 23.7f, 210.0f, 0.0f, -0.95f / 2, 0.0f);
	CREATE_OBJ(SaddleBag0[19], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 233.0f, 23.4f, 200.0f, 0.0f, -0.95f / 2, 0.0f);

	CREATE_OBJ(SaddleBag0[20], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 242.0f, 23.2f, 519.0f, 0.0f, 0.57f, 0.0f);
	CREATE_OBJ(SaddleBag0[21], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 247.0f, 23.2f, 488.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag0[22], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 230.0f, 22.8f, 464.0f, 0.0f, -0.83f, 0.0f);
	CREATE_OBJ(SaddleBag0[23], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 246.0f, 23.6f, 369.0f, 0.0f, -0.16f, 0.0f);
	CREATE_OBJ(SaddleBag0[24], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 234.0f, 23.6f, 367.0f, 0.0f, -0.16f, 0.0f);
	CREATE_OBJ(SaddleBag0[25], 4.0f, SaddleBag, SaddleBag01.obj, SaddleBagTex.png, 246.0f, 23.8f, 336.0f, 0.0f, 0.67f, 0.0f);
	CREATE_OBJ(SaddleBag0[26], 4.0f, SaddleBag, SaddleBag01.obj, SaddleBagTex.png, 247.0f, 24.2f, 303.0f, 0.0f, -0.83f, 0.0f);
	CREATE_OBJ(SaddleBag0[27], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 249.0f, 24.3f, 293.0f, 0.0f, 0.69f, 0.0f);
	CREATE_OBJ(SaddleBag0[28], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 255.0f, 24.3f, 258.0f, 0.0f, -0.67f, 0.0f);
	CREATE_OBJ(SaddleBag0[29], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 243.0f, 23.4f, 205.0f, 0.0f, -0.95f / 2, 0.0f);

	//����
	for (int i = 0; i < 10; i++)
	{
		int x = rand() % 200 + 240;
		int y = rand() % 300 + 180;
		int plus0 = rand() % 100;
		int plus1 = rand() % 100;
		int plus2 = rand() % 100;
		int plus3 = rand() % 100;
		int plus4 = rand() % 100;
		int plus5 = rand() % 100;
		int plus6 = rand() % 100;
		CREATE_OBJ(m_Tree00[i], 8.0f, Environment, Tree00.obj, TreeTex.png, x + plus0, 30.0f, y + plus0, 0.0f, plus0 % 99, 0.0f);
		CREATE_OBJ(m_Tree01[i], 6.0f, Environment, Tree01.obj, TreeTex.png, x + plus1, 30.0f, y + plus1, 0.0f, plus1 % 99, 0.0f);
		CREATE_OBJ(m_Tree02[i], 3.0f, Environment, Tree02.obj, TreeTex.png, x + plus2, 25.0f, y + plus2, 0.0f, plus2 % 99, 0.0f);
		CREATE_OBJ(m_Tree03[i], 2.0f, Environment, Tree03.obj, TreeTex.png, x + plus3, 25.0f, y + plus3, 0.0f, plus3 % 99, 0.0f);
		//CREATE_OBJ(m_Tree04[i], 5.0f, Environment, Tree04.obj, Tree04Tex.png, x + plus4, 30.0f, y + plus4, 0.0f, plus4 % 99, 0.0f);
		//CREATE_OBJ(m_Tree05[i], 6.0f, Environment, Tree05.obj, Tree05Tex.png, x + plus5, 30.0f, y + plus5, 0.0f, plus5 % 99, 0.0f);
		CREATE_OBJ(m_Tree06[i], 3.0f, Environment, Tree06.obj, TreeTex.png, x + plus6, 30.0f, y + plus6, 0.0f, plus6 % 99, 0.0f);
	}

	////��Ǫ���
	//for (int i = 0; i < 6; i++)
	//{
	//   int x = rand() % 200 + 240;
	//   int y = rand() % 300 + 180;
	//   int plus0 = rand() % 100;
	//   CREATE_OBJ(m_Straw00[i], 2.0f, Environment, Straw00.obj, StrawTex.png, x + plus0, 25.0f, y + plus0, 0.0f, 0.0f, 0.0f);
	//}
	////��
	//for (int i = 0; i < 20; i++)
	//{
	//   int x = rand() % 200 + 240;
	//   int y = rand() % 300 + 180;
	//   int plus0 = rand() % 100;
	//   CREATE_OBJ(m_Stone00[i], 1.0f, Environment, Stone00.obj, StoneTex.png, x + plus0, 22.0f, y + plus0, 0.0f, 0.0f, 0.0f);
	//}
}
//400400200200
void ObjRender::Render()
{
	//��ȣ ����
	for (int i = 0; i < 8; i++)
		SAFE_RENDER(m_MapTest[i]);
	//ö����
	for (int i = 0; i < 38; i++)
		SAFE_RENDER(m_BarbedWireT[i]);
	//��ݹ�ħ
	SAFE_RENDER(m_FireStep00);
	//��
	for (int i = 0; i < 30; i++)
		SAFE_RENDER(SaddleBag0[i]);

	//����
	for (int i = 0; i < 10; i++)
	{
		SAFE_RENDER(m_Tree00[i]);
		SAFE_RENDER(m_Tree01[i]);
		SAFE_RENDER(m_Tree02[i]);
		SAFE_RENDER(m_Tree03[i]);
		//SAFE_RENDER(m_Tree04[i]);
		//SAFE_RENDER(m_Tree05[i]);
		SAFE_RENDER(m_Tree06[i]);
	}
	////��Ǫ���
	//for (int i = 0; i < 6; i++)
	//   SAFE_RENDER(m_Straw00[i]);
	////��
	//for (int i = 0; i < 20; i++)
	//   SAFE_RENDER(m_Stone00[i]);
}