#include "stdafx.h"
#include "ObjRender.h"
#include "ObjRen.h"

#define CREATE_OBJ(obj_name, size, folder, objFile, TextureImage, x, y, z, rotationX, rotationY, rotationZ) obj_name = new ObjRen;\
      obj_name->Init(size, _T("resources/ObjImages/" ## #folder ##"/" ## #objFile),_T("resources/ObjImages/" ## #folder ##"/" ## #TextureImage), x, y, z, rotationX, rotationY, rotationZ);

ObjRender::ObjRender()
{
	//참호 판자
	for (int i = 0; i < 16; i++)
		m_MapTest[i] = NULL;
	for (int i = 0; i < 10; i++)
		m_MapTest1[i] = NULL;
	//철조망
	for (int i = 0; i < 53; i++)
		m_BarbedWireT[i] = NULL;
	//사격받침
	m_FireStep00 = NULL;
	//모래
	for (int i = 0; i < 30; i++)
		SaddleBag0[i] = NULL;
	for (int i = 0; i < 33; i++)
		SaddleBag1[i] = NULL;

	//나무
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
	//지푸라기
	for (int i = 0; i < 2; i++)
	   m_Straw00[i] = NULL;
	//돌
	for (int i = 0; i < 4; i++)
	   m_Stone00[i] = NULL;

	//탱크
	for (int i = 0; i < 2; i++)
	{
		m_Tank[i] = NULL;
	}
	
	//웨건
	for (int i = 0; i < 3; i++)
	{
		m_Wagon[i] = NULL;
	}
	
	//건물
	for (int i = 0; i < 3; i++)
	{
		m_Apt[i] = NULL;
	}

	//타일
	for (int i = 0; i < 15; i++)
	{
		m_Tile[i] = NULL;
	}

}


ObjRender::~ObjRender()
{
	//참호 판자
	for (int i = 0; i < 16; i++)
		m_MapTest[i]->~ObjRen();
	for (int i = 0; i < 10; i++)
		m_MapTest1[i]->~ObjRen();
	//철조망
	for (int i = 0; i < 53; i++)
		m_BarbedWireT[i]->~ObjRen();
	//사격받침
	m_FireStep00->~ObjRen();
	//모래
	for (int i = 0; i < 30; i++)
		SaddleBag0[i]->~ObjRen();
	for (int i = 0; i < 33; i++)
		SaddleBag1[i]->~ObjRen();

	//나무
	for (int i = 0; i < 10; i++)
	{
		m_Tree00[i]->~ObjRen();
		m_Tree01[i]->~ObjRen();
		m_Tree02[i]->~ObjRen();
		m_Tree03[i]->~ObjRen();
		//m_Tree04[i]->~ObjRen();
		//m_Tree05[i]->~ObjRen();
		m_Tree06[i]->~ObjRen();
	}
	//지푸라기
	for (int i = 0; i < 2; i++)
	   m_Straw00[i]->~ObjRen();
	//돌
	for (int i = 0; i < 4; i++)
	   m_Stone00[i]->~ObjRen();

	//탱크
	for (int i = 0; i < 2; i++)
	{
		m_Tank[i]->~ObjRen();
	}

	//웨건
	for (int i = 0; i < 3; i++)
	{
		m_Wagon[i]->~ObjRen();
	}

	//건물
	for (int i = 0; i < 3; i++)
	{
		m_Apt[i]->~ObjRen();
	}

	//타일
	for (int i = 0; i < 15; i++)
	{
		m_Tile[i]->~ObjRen();
	}

}


void ObjRender::Init()
{
	//참호 판자
	CREATE_OBJ(m_MapTest[0], 66.9f, WoodenBarrier, WoodenBarrierTest02.obj, woodTex.png, 363.0f, 11.5f, -537.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[1], 12.5f, WoodenBarrier, WoodenBarrierPartTest00.obj, woodTex.png, 100.5f, 5.0f, 77.8f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[2], 18.0f, WoodenBarrier, WoodenBarrierPartTest01.obj, woodTex.png, 210.6f, 7.5f, 22.8f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[3], 13.5f, WoodenBarrier, WoodenBarrierPartTest02.obj, woodTex.png, 260.6f, 7.9f, 164.8f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[4], 11.6f, WoodenBarrier, WoodenBarrierPartTest03.obj, woodTex.png, 142.0f, 7.9f, 335.6f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[5], 12.8f, WoodenBarrier, WoodenBarrierPartTest04.obj, woodTex.png, 225.0f, 0.0f, 444.3f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[6], 13.8f, WoodenBarrier, WoodenBarrierPartTest05.obj, woodTex.png, 114.5f, 7.0f, 532.8f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[7], 16.8f, WoodenBarrier, WoodenBarrierPartTest06.obj, woodTex.png, 259.0f, 19.2f, 490.6f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[8], 10.3f, WoodenBarrier, WoodenBarrierPartTest07.obj, woodTex.png, 173.0f, 5.2f, 55.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[9], 15.3f, WoodenBarrier, WoodenBarrierPartTest08.obj, woodTex.png, 80.0f, 16.3f, 470.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[10], 15.3f, WoodenBarrier, WoodenBarrierPartTest09.obj, woodTex.png, 156.0f, 15.5f, 391.5f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[11], 16.2f, WoodenBarrier, WoodenBarrierPartTest10.obj, woodTex.png, 147.0f, 14.7f, 312.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[12], 13.8f, WoodenBarrier, WoodenBarrierPartTest11.obj, woodTex.png, 172.0f, 11.7f, 273.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[13], 9.8f, WoodenBarrier, WoodenBarrierPartTest12.obj, woodTex.png, 132.0f, 12.7f, 222.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[14], 11.8f, WoodenBarrier, WoodenBarrierPartTest13.obj, woodTex.png, 176.0f, 13.6f, 145.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_MapTest[15], 9.8f, WoodenBarrier, WoodenBarrierPartTest14.obj, woodTex.png, 246.0f, 15.6f, 214.0f, 0.0f, 0.0f, 0.0f);

	CREATE_OBJ(m_MapTest1[0], 5.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 218.0f, 16.4f, 544.0f, D3DX_PI / 2 + 0.2f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_MapTest1[1], 5.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 224.0f, 16.9f, 564.0f, D3DX_PI / 2 + 0.2f, D3DX_PI / 2 - 1.9f, 0.0f);
	CREATE_OBJ(m_MapTest1[2], 5.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 202.0f, 16.9f, 564.0f, D3DX_PI / 2 - 0.2f, D3DX_PI / 2 + 1.9f, 0.0f);
	CREATE_OBJ(m_MapTest1[3], 5.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 174.0f, 16.9f, 591.0f, D3DX_PI / 2 + 0.2f, -0.9f, 0.0f);
	CREATE_OBJ(m_MapTest1[4], 5.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 153.0f, 16.9f, 585.0f, D3DX_PI / 2 - 0.2f, D3DX_PI / 2 + 1.9f, 0.0f);
	CREATE_OBJ(m_MapTest1[5], 5.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 237.0f, 16.9f, 602.0f, D3DX_PI / 2 - 0.2f, D3DX_PI / 2 + 2.1f, 0.0f);
	CREATE_OBJ(m_MapTest1[6], 5.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 246.0f, 15.6f, 214.0f, D3DX_PI / 2 + 0.2f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_MapTest1[7], 5.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 246.0f, 15.6f, 214.0f, D3DX_PI / 2 + 0.2f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_MapTest1[8], 5.8f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 246.0f, 15.6f, 214.0f, D3DX_PI / 2 + 0.2f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_MapTest1[9], 5.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 246.0f, 15.6f, 214.0f, D3DX_PI / 2 + 0.2f, D3DX_PI / 2, 0.0f);


	//철조망
	//1번 줄
	CREATE_OBJ(m_BarbedWireT[0], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 468.0f, 31.0f, 526.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[1], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 468.0f, 31.0f, 516.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[2], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 487.0f, 33.0f, 475.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[3], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 487.0f, 34.0f, 458.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[4], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 500.0f, 35.0f, 419.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[5], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 500.0f, 31.0f, 374.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[6], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 494.0f, 34.0f, 360.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[7], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 500.0f, 31.0f, 318.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[8], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 494.0f, 33.0f, 304.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[9], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 494.0f, 33.0f, 287.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[10], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 468.0f, 28.0f, 219.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[11], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 494.0f, 33.0f, 229.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	//2번 줄
	CREATE_OBJ(m_BarbedWireT[12], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 407.0f, 31.0f, 560.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[13], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 407.0f, 31.0f, 544.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[14], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 407.0f, 32.0f, 502.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[15], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 407.0f, 32.0f, 485.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[16], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 407.0f, 34.0f, 446.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[17], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 413.0f, 30.0f, 401.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[18], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 413.0f, 34.0f, 387.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[19], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 413.0f, 29.0f, 345.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[20], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 387.0f, 32.0f, 330.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[21], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 387.0f, 33.0f, 315.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[22], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 413.0f, 29.0f, 248.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[23], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 407.0f, 32.0f, 258.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[24], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 407.0f, 30.0f, 220.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[25], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 407.0f, 30.0f, 210.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	//3번 줄
	CREATE_OBJ(m_BarbedWireT[26], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 322.0f, 31.0f, 531.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[27], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 322.0f, 31.0f, 515.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[28], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 322.0f, 32.0f, 475.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[29], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 322.0f, 33.0f, 458.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[30], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 322.0f, 33.0f, 419.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[31], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 328.0f, 30.0f, 374.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[32], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 322.0f, 34.0f, 360.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[33], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 328.0f, 30.0f, 318.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[34], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 322.0f, 33.0f, 304.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[35], 3.5f, BarbedWire, BarbedWire03.obj, BarbedWireTex.png, 322.0f, 33.0f, 287.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[36], 3.5f, BarbedWire, BarbedWire04.obj, BarbedWireTex.png, 328.0f, 29.0f, 219.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[37], 3.5f, BarbedWire, BarbedWire02.obj, BarbedWireTex.png, 322.0f, 33.0f, 229.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	//입구쪽
	CREATE_OBJ(m_BarbedWireT[38], 3.5f, BarbedWire, BarbedWire01.obj, BarbedWireTex.png, 286.0f, 29.0f, 518.0f, 0.0f, D3DX_PI / 2 + D3DX_PI - 0.4f, 0.0f);
	CREATE_OBJ(m_BarbedWireT[39], 3.5f, BarbedWire, BarbedWire01.obj, BarbedWireTex.png, 289.0f, 29.0f, 490.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);
	CREATE_OBJ(m_BarbedWireT[40], 3.5f, BarbedWire, BarbedWire00.obj, BarbedWireTex.png, 280.0f, 29.0f, 463.0f, 0.0f, D3DX_PI / 2 + D3DX_PI + 0.4f, 0.0f);
	CREATE_OBJ(m_BarbedWireT[41], 3.5f, BarbedWire, BarbedWire00.obj, BarbedWireTex.png, 292.0f, 29.0f, 442.0f, 0.0f, D3DX_PI / 2 + D3DX_PI - 0.2f, 0.0f);
	CREATE_OBJ(m_BarbedWireT[42], 3.5f, BarbedWire, BarbedWire01.obj, BarbedWireTex.png, 286.0f, 29.0f, 415.0f, 0.0f, D3DX_PI / 2 + D3DX_PI - 0.4f, 0.0f);
	CREATE_OBJ(m_BarbedWireT[43], 3.5f, BarbedWire, BarbedWire00.obj, BarbedWireTex.png, 297.0f, 29.0f, 378.0f, 0.0f, D3DX_PI / 2 + D3DX_PI + 0.4f, 0.0f);
	CREATE_OBJ(m_BarbedWireT[44], 3.5f, BarbedWire, BarbedWire01.obj, BarbedWireTex.png, 278.0f, 29.0f, 344.0f, 0.0f, D3DX_PI / 2 + D3DX_PI + 0.1f, 0.0f);
	CREATE_OBJ(m_BarbedWireT[45], 3.5f, BarbedWire, BarbedWire01.obj, BarbedWireTex.png, 299.0f, 29.8f, 297.0f, 0.0f, D3DX_PI / 2 + D3DX_PI - 0.1f, 0.0f);
	CREATE_OBJ(m_BarbedWireT[46], 3.5f, BarbedWire, BarbedWire00.obj, BarbedWireTex.png, 299.0f, 29.5f, 268.0f, 0.0f, D3DX_PI / 2 + D3DX_PI - 0.2f, 0.0f);
	CREATE_OBJ(m_BarbedWireT[47], 3.5f, BarbedWire, BarbedWire00.obj, BarbedWireTex.png, 299.0f, 29.0f, 247.0f, 0.0f, D3DX_PI / 2 + D3DX_PI + 0.4f, 0.0f);

	CREATE_OBJ(m_BarbedWireT[48], 3.5f, BarbedWire, BarbedWire00.obj, BarbedWireTex.png, 300.0f, 29.0f, 354.0f, 0.0f, D3DX_PI / 2 + D3DX_PI + 0.1f, 0.0f);
	CREATE_OBJ(m_BarbedWireT[49], 3.5f, BarbedWire, BarbedWire00.obj, BarbedWireTex.png, 303.0f, 29.0f, 330.0f, 0.0f, D3DX_PI / 2 + D3DX_PI - 0.1f, 0.0f);
	CREATE_OBJ(m_BarbedWireT[50], 3.5f, BarbedWire, BarbedWire00.obj, BarbedWireTex.png, 307.0f, 29.0f, 224.0f, 0.0f, D3DX_PI / 2 + D3DX_PI - 0.4f, 0.0f);
	CREATE_OBJ(m_BarbedWireT[51], 3.5f, BarbedWire, BarbedWire00.obj, BarbedWireTex.png, 297.0f, 29.0f, 209.0f, 0.0f, D3DX_PI / 2 + D3DX_PI - 0.1f, 0.0f);
	CREATE_OBJ(m_BarbedWireT[52], 3.5f, BarbedWire, BarbedWire00.obj, BarbedWireTex.png, 286.0f, 29.0f, 189.0f, 0.0f, D3DX_PI / 2 + D3DX_PI, 0.0f);

	//사격받침
	//CREATE_OBJ(m_FireStep00, 63.0f, FireStep, FireStep00.obj, woodTex.png, 232.0f, -6.8f, 398.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_FireStep00, 63.0f, FireStep, FireStep01.obj, woodTex.png, 250.0f, -6.8f, 398.0f, 0.0f, 0.0f, 0.0f);

	//모래
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

	CREATE_OBJ(SaddleBag0[20], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 202.0f, 24.5f, 539.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag0[21], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 189.0f, 24.5f, 527.0f, 0.0f, 0.25f, 0.0f);
	CREATE_OBJ(SaddleBag0[22], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 179.0f, 24.5f, 543.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag0[23], 4.0f, SaddleBag, SaddleBag01.obj, SaddleBagTex.png, 228.0f, 24.5f, 500.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag0[24], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 216.0f, 24.5f, 479.0f, 0.0f, -0.79f, 0.0f);
	CREATE_OBJ(SaddleBag0[25], 4.0f, SaddleBag, SaddleBag01.obj, SaddleBagTex.png, 207.0f, 23.8f, 463.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag0[26], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 193.0f, 23.5f, 444.0f, 0.0f, -0.63f, 0.0f);
	CREATE_OBJ(SaddleBag0[27], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 222.0f, 23.0f, 422.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag0[28], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 228.0f, 23.0f, 402.0f, 0.0f, 0.67f, 0.0f);
	CREATE_OBJ(SaddleBag0[29], 4.0f, SaddleBag, SaddleBag01.obj, SaddleBagTex.png, 227.0f, 23.4f, 385.0f, 0.0f, -0.46f / 2, 0.0f);

	CREATE_OBJ(SaddleBag1[0], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 190.0f, 21.2f, 376.3f, 0.0f, 0.48f, 0.0f);
	CREATE_OBJ(SaddleBag1[1], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 200.0f, 21.2f, 371.3f, 0.0f, 0.48f, 0.0f);
	CREATE_OBJ(SaddleBag1[2], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 206.0f, 21.9f, 361.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag1[3], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 237.0f, 23.2f, 391.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag1[4], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 194.0f, 22.8f, 350.0f, 0.0f, -0.53f, 0.0f);
	CREATE_OBJ(SaddleBag1[5], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 222.0f, 21.9f, 329.0f, 0.0f, 0.69f, 0.0f);
	CREATE_OBJ(SaddleBag1[6], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 223.0f, 21.9f, 312.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag1[7], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 228.0f, 21.9f, 315.0f, 0.0f, -0.73f, 0.0f);
	CREATE_OBJ(SaddleBag1[8], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 214.0f, 21.9f, 299.0f, 0.0f, -0.58f, 0.0f);
	CREATE_OBJ(SaddleBag1[9], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 231.0f, 23.6f, 252.0f, 0.0f, D3DX_PI / 2, 0.0f);

	CREATE_OBJ(SaddleBag1[10], 4.0f, SaddleBag, SaddleBag01.obj, SaddleBagTex.png, 233.0f, 23.6f, 281.0f, 0.0f, 0.48f, 0.0f);
	CREATE_OBJ(SaddleBag1[11], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 236.0f, 23.8f, 268.0f, 0.0f, -0.63f, 0.0f);
	CREATE_OBJ(SaddleBag1[12], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 236.0f, 24.2f, 234.0f, 0.0f, 0.69f, 0.0f);
	CREATE_OBJ(SaddleBag1[13], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 230.0f, 24.2f, 223.0f, 0.0f, -0.48f, 0.0f);
	CREATE_OBJ(SaddleBag1[14], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 260.0f, 24.2f, 266.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag1[15], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 255.0f, 24.3f, 247.0f, 0.0f, 0.67f, 0.0f);
	CREATE_OBJ(SaddleBag1[16], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 259.0f, 24.3f, 236.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag1[17], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 259.0f, 24.3f, 221.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag1[18], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 251.0f, 23.7f, 210.0f, 0.0f, -0.95f / 2, 0.0f);
	CREATE_OBJ(SaddleBag1[19], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 233.0f, 23.4f, 200.0f, 0.0f, -0.95f / 2, 0.0f);

	CREATE_OBJ(SaddleBag1[20], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 242.0f, 23.2f, 519.0f, 0.0f, 0.57f, 0.0f);
	CREATE_OBJ(SaddleBag1[21], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 247.0f, 23.2f, 488.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag1[22], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 230.0f, 22.8f, 464.0f, 0.0f, -0.83f, 0.0f);
	CREATE_OBJ(SaddleBag1[23], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 246.0f, 23.6f, 369.0f, 0.0f, -0.16f, 0.0f);
	CREATE_OBJ(SaddleBag1[24], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 234.0f, 23.6f, 367.0f, 0.0f, -0.16f, 0.0f);
	CREATE_OBJ(SaddleBag1[25], 4.0f, SaddleBag, SaddleBag01.obj, SaddleBagTex.png, 246.0f, 23.8f, 336.0f, 0.0f, 0.67f, 0.0f);
	CREATE_OBJ(SaddleBag1[26], 4.0f, SaddleBag, SaddleBag01.obj, SaddleBagTex.png, 247.0f, 24.2f, 303.0f, 0.0f, -0.83f, 0.0f);
	CREATE_OBJ(SaddleBag1[27], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 249.0f, 24.3f, 293.0f, 0.0f, 0.69f, 0.0f);
	CREATE_OBJ(SaddleBag1[28], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 255.0f, 24.3f, 258.0f, 0.0f, -0.67f, 0.0f);
	CREATE_OBJ(SaddleBag1[29], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 243.0f, 23.4f, 205.0f, 0.0f, -0.95f / 2, 0.0f);
	CREATE_OBJ(SaddleBag1[30], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 172.0f, 24.2f, 486.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag1[31], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 168.0f, 22.3f, 408.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(SaddleBag1[32], 3.0f, SaddleBag, SaddleBag02.obj, SaddleBagTex.png, 191.0f, 24.3f, 267.0f, 0.0f, D3DX_PI / 2, 0.0f);

	//나무
	CREATE_OBJ(m_Tree00[0], 8.0f, Environment, Tree00.obj, TreeTex.png, 320.0f, 30.0f, 321.0f, 0.0f, 0.1f, 0.0f);
	CREATE_OBJ(m_Tree01[0], 6.0f, Environment, Tree01.obj, TreeTex.png, 300.0f, 30.0f, 360.0f, 0.0f, 0.1f, 0.0f);
	CREATE_OBJ(m_Tree02[0], 3.0f, Environment, Tree02.obj, TreeTex.png, 355.0f, 25.0f, 342.0f, 0.0f, 0.1f, 0.0f);
	CREATE_OBJ(m_Tree03[0], 2.0f, Environment, Tree03.obj, TreeTex.png, 360.0f, 25.0f, 300.0f, 0.0f, 0.1f, 0.0f);
	CREATE_OBJ(m_Tree06[0], 3.0f, Environment, Tree06.obj, TreeTex.png, 340.0f, 30.0f, 320.0f, 0.0f, 0.1f, 0.0f);

	CREATE_OBJ(m_Tree00[1], 8.0f, Environment, Tree00.obj, TreeTex.png, 320.0f, 30.0f, 436.0f, 0.0f, 0.4f, 0.0f);
	CREATE_OBJ(m_Tree01[1], 6.0f, Environment, Tree01.obj, TreeTex.png, 300.0f, 30.0f, 447.0f, 0.0f, 0.4f, 0.0f);
	CREATE_OBJ(m_Tree02[1], 3.0f, Environment, Tree02.obj, TreeTex.png, 355.0f, 25.0f, 467.0f, 0.0f, 0.4f, 0.0f);
	CREATE_OBJ(m_Tree03[1], 2.0f, Environment, Tree03.obj, TreeTex.png, 360.0f, 25.0f, 412.0f, 0.0f, 0.4f, 0.0f);
	CREATE_OBJ(m_Tree06[1], 3.0f, Environment, Tree06.obj, TreeTex.png, 340.0f, 30.0f, 420.0f, 0.0f, 0.4f, 0.0f);

	CREATE_OBJ(m_Tree00[2], 8.0f, Environment, Tree00.obj, TreeTex.png, 320.0f, 30.0f, 261.0f, 0.0f, 0.3f, 0.0f);
	CREATE_OBJ(m_Tree01[2], 6.0f, Environment, Tree01.obj, TreeTex.png, 300.0f, 30.0f, 247.0f, 0.0f, 0.3f, 0.0f);
	CREATE_OBJ(m_Tree02[2], 3.0f, Environment, Tree02.obj, TreeTex.png, 355.0f, 25.0f, 244.0f, 0.0f, 0.3f, 0.0f);
	CREATE_OBJ(m_Tree03[2], 2.0f, Environment, Tree03.obj, TreeTex.png, 360.0f, 25.0f, 222.0f, 0.0f, 0.3f, 0.0f);
	CREATE_OBJ(m_Tree06[2], 3.0f, Environment, Tree06.obj, TreeTex.png, 340.0f, 30.0f, 219.0f, 0.0f, 0.3f, 0.0f);

	CREATE_OBJ(m_Tree00[3], 8.0f, Environment, Tree00.obj, TreeTex.png, 320.0f, 25.0f, 480.0f, 0.0f, 0.2f, 0.0f);
	CREATE_OBJ(m_Tree01[3], 6.0f, Environment, Tree01.obj, TreeTex.png, 290.0f, 25.0f, 505.0f, 0.0f, 0.2f, 0.0f);
	CREATE_OBJ(m_Tree02[3], 3.0f, Environment, Tree02.obj, TreeTex.png, 325.0f, 20.0f, 510.0f, 0.0f, 0.2f, 0.0f);
	CREATE_OBJ(m_Tree03[3], 2.0f, Environment, Tree03.obj, TreeTex.png, 330.0f, 20.0f, 482.0f, 0.0f, 0.2f, 0.0f);
	CREATE_OBJ(m_Tree06[3], 3.0f, Environment, Tree06.obj, TreeTex.png, 310.0f, 25.0f, 470.0f, 0.0f, 0.2f, 0.0f);

	CREATE_OBJ(m_Tree00[4], 8.0f, Environment, Tree00.obj, TreeTex.png, 420.0f, 30.0f, 340.0f, 0.0f, 0.1f, 0.0f);
	CREATE_OBJ(m_Tree01[4], 6.0f, Environment, Tree01.obj, TreeTex.png, 400.0f, 30.0f, 360.0f, 0.0f, 0.1f, 0.0f);
	CREATE_OBJ(m_Tree02[4], 3.0f, Environment, Tree02.obj, TreeTex.png, 455.0f, 25.0f, 320.0f, 0.0f, 0.1f, 0.0f);
	CREATE_OBJ(m_Tree03[4], 2.0f, Environment, Tree03.obj, TreeTex.png, 460.0f, 25.0f, 355.0f, 0.0f, 0.1f, 0.0f);
	CREATE_OBJ(m_Tree06[4], 3.0f, Environment, Tree06.obj, TreeTex.png, 440.0f, 30.0f, 302.0f, 0.0f, 0.1f, 0.0f);

	CREATE_OBJ(m_Tree00[5], 8.0f, Environment, Tree00.obj, TreeTex.png, 420.0f, 30.0f, 455.0f, 0.0f, 0.4f, 0.0f);
	CREATE_OBJ(m_Tree01[5], 6.0f, Environment, Tree01.obj, TreeTex.png, 400.0f, 30.0f, 460.0f, 0.0f, 0.4f, 0.0f);
	CREATE_OBJ(m_Tree02[5], 3.0f, Environment, Tree02.obj, TreeTex.png, 455.0f, 25.0f, 440.0f, 0.0f, 0.4f, 0.0f);
	CREATE_OBJ(m_Tree03[5], 2.0f, Environment, Tree03.obj, TreeTex.png, 460.0f, 25.0f, 420.0f, 0.0f, 0.4f, 0.0f);
	CREATE_OBJ(m_Tree06[5], 3.0f, Environment, Tree06.obj, TreeTex.png, 440.0f, 30.0f, 401.0f, 0.0f, 0.4f, 0.0f);

	CREATE_OBJ(m_Tree00[6], 8.0f, Environment, Tree00.obj, TreeTex.png, 420.0f, 30.0f, 180.0f, 0.0f, 0.3f, 0.0f);
	CREATE_OBJ(m_Tree01[6], 6.0f, Environment, Tree01.obj, TreeTex.png, 400.0f, 30.0f, 260.0f, 0.0f, 0.3f, 0.0f);
	CREATE_OBJ(m_Tree02[6], 3.0f, Environment, Tree02.obj, TreeTex.png, 455.0f, 25.0f, 241.0f, 0.0f, 0.3f, 0.0f);
	CREATE_OBJ(m_Tree03[6], 2.0f, Environment, Tree03.obj, TreeTex.png, 460.0f, 25.0f, 219.0f, 0.0f, 0.3f, 0.0f);
	CREATE_OBJ(m_Tree06[6], 3.0f, Environment, Tree06.obj, TreeTex.png, 440.0f, 30.0f, 240.0f, 0.0f, 0.3f, 0.0f);

	CREATE_OBJ(m_Tree00[7], 8.0f, Environment, Tree00.obj, TreeTex.png, 520.0f, 30.0f, 355.0f, 0.0f, 0.1f, 0.0f);
	CREATE_OBJ(m_Tree01[7], 6.0f, Environment, Tree01.obj, TreeTex.png, 500.0f, 30.0f, 340.0f, 0.0f, 0.1f, 0.0f);
	CREATE_OBJ(m_Tree02[7], 3.0f, Environment, Tree02.obj, TreeTex.png, 555.0f, 25.0f, 360.0f, 0.0f, 0.1f, 0.0f);
	CREATE_OBJ(m_Tree03[7], 2.0f, Environment, Tree03.obj, TreeTex.png, 560.0f, 25.0f, 355.0f, 0.0f, 0.1f, 0.0f);
	CREATE_OBJ(m_Tree06[7], 3.0f, Environment, Tree06.obj, TreeTex.png, 540.0f, 30.0f, 320.0f, 0.0f, 0.1f, 0.0f);

	CREATE_OBJ(m_Tree00[8], 8.0f, Environment, Tree00.obj, TreeTex.png, 520.0f, 30.0f, 440.0f, 0.0f, 0.4f, 0.0f);
	CREATE_OBJ(m_Tree01[8], 6.0f, Environment, Tree01.obj, TreeTex.png, 500.0f, 30.0f, 460.0f, 0.0f, 0.4f, 0.0f);
	CREATE_OBJ(m_Tree02[8], 3.0f, Environment, Tree02.obj, TreeTex.png, 555.0f, 25.0f, 455.0f, 0.0f, 0.4f, 0.0f);
	CREATE_OBJ(m_Tree03[8], 2.0f, Environment, Tree03.obj, TreeTex.png, 560.0f, 25.0f, 400.0f, 0.0f, 0.4f, 0.0f);
	CREATE_OBJ(m_Tree06[8], 3.0f, Environment, Tree06.obj, TreeTex.png, 540.0f, 30.0f, 420.0f, 0.0f, 0.4f, 0.0f);

	CREATE_OBJ(m_Tree00[9], 8.0f, Environment, Tree00.obj, TreeTex.png, 520.0f, 30.0f, 240.0f, 0.0f, 0.3f, 0.0f);
	CREATE_OBJ(m_Tree01[9], 6.0f, Environment, Tree01.obj, TreeTex.png, 500.0f, 30.0f, 255.0f, 0.0f, 0.3f, 0.0f);
	CREATE_OBJ(m_Tree02[9], 3.0f, Environment, Tree02.obj, TreeTex.png, 555.0f, 25.0f, 240.0f, 0.0f, 0.3f, 0.0f);
	CREATE_OBJ(m_Tree03[9], 2.0f, Environment, Tree03.obj, TreeTex.png, 560.0f, 25.0f, 190.0f, 0.0f, 0.3f, 0.0f);
	CREATE_OBJ(m_Tree06[9], 3.0f, Environment, Tree06.obj, TreeTex.png, 540.0f, 30.0f, 222.0f, 0.0f, 0.3f, 0.0f);

	//지푸라기
	CREATE_OBJ(m_Straw00[0], 3.0f, Environment, Straw00.obj, StrawTex.png, 7.0f, 25.0f, 71.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_Straw00[1], 3.0f, Environment, Straw00.obj, StrawTex.png, 7.0f, 25.0f, 61.0f, 0.0f, D3DX_PI / 2, 0.0f);
	//돌
	CREATE_OBJ(m_Stone00[0], 6.0f, Environment, Stone00.obj, StoneTex.png, 440.0f, 25.0f, 424.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_Stone00[1], 2.0f, Environment, Stone00.obj, StoneTex.png, 292.0f, 22.0f, 538.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_Stone00[2], 2.0f, Environment, Stone00.obj, StoneTex.png, 332.0f, 22.0f, 210.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_Stone00[3], 3.0f, Environment, Stone00.obj, StoneTex.png, 333.0f, 22.0f, 320.0f, 0.0f, 0.0f, 0.0f);

	//탱크
	CREATE_OBJ(m_Tank[0], 8.5f, ETC, Tank00.obj, TankTex.png, 354.0f, 25.0f, 454.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_Tank[1], 8.5f, ETC, Tank00.obj, TankTex.png, 412.0f, 25.0f, 280.0f, 0.0f, -D3DX_PI / 2, -0.3f);

	//웨건
	CREATE_OBJ(m_Wagon[0], 4.5f, ETC, 105mm.obj, 105mmTex.png, 336.0f, 19.0f, 272.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_Wagon[1], 4.5f, ETC, 105mm.obj, 105mmTex.png, 400.0f, 19.0f, 451.0f, 0.0f, -D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_Wagon[2], 4.5f, ETC, 105mm.obj, 105mmTex.png, 400.0f, 19.0f, 441.0f, 0.0f, D3DX_PI / 2, -0.3f);

	//건물
	CREATE_OBJ(m_Apt[0], 9.5f, ETC, Apt00.obj, AptTex.png, -50.0f, 50.0f, 400.0f, 0.0f, D3DX_PI, 0.0f);
	CREATE_OBJ(m_Apt[1], 9.5f, ETC, Apt00.obj, AptTex.png, -50.0f, 50.0f, 300.0f, 0.0f, D3DX_PI, 0.0f);
	CREATE_OBJ(m_Apt[2], 9.5f, ETC, Apt00.obj, AptTex.png, -50.0f, 50.0f, 200.0f, 0.0f, D3DX_PI, 0.0f);

	//타일
	CREATE_OBJ(m_Tile[0], 25.0f, Ground, Tile00.obj, GroundTex.png, 224.0f, 12.2f, 483.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_Tile[1], 24.0f, Ground, Tile01.obj, GroundTex.png, 171.0f, 13.6f, 466.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_Tile[2], 25.0f, Ground, Tile02.obj, GroundTex.png, 197.0f, 13.6f, 380.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_Tile[3], 24.0f, Ground, Tile03.obj, GroundTex.png, 224.0f, 15.0f, 257.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_Tile[4], 24.0f, Ground, Tile04.obj, GroundTex.png, 166.0f, 14.0f, 242.0f, 0.0f, 0.0f, 0.0f);

	CREATE_OBJ(m_Tile[5], 6.0f, Ground, Tile05.obj, GroundTex.png, 202.0f, 14.0f, 439.0f, 0.0f, 1.0f, 0.0f);
	CREATE_OBJ(m_Tile[6], 6.0f, Ground, Tile05.obj, GroundTex.png, 204.0f, 14.0f, 378.0f, 0.0f, -1.0f, 0.0f);
	CREATE_OBJ(m_Tile[7], 6.0f, Ground, Tile05.obj, GroundTex.png, 241.0f, 14.2f, 405.0f, 0.0f, -1.0f, 0.0f);
	CREATE_OBJ(m_Tile[8], 6.0f, Ground, Tile05.obj, GroundTex.png, 246.0f, 14.5f, 384.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_Tile[9], 6.0f, Ground, Tile05.obj, GroundTex.png, 231.0f, 14.5f, 375.0f, 0.0f, 1.5f, 0.0f);
	CREATE_OBJ(m_Tile[10], 6.0f, Ground, Tile05.obj, GroundTex.png, 216.0f, 14.5f, 356.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_Tile[11], 6.0f, Ground, Tile05.obj, GroundTex.png, 202.0f, 14.0f, 342.0f, 0.0f, 0.8f, 0.0f);
	CREATE_OBJ(m_Tile[12], 8.0f, Ground, Tile05.obj, GroundTex.png, 233.0f, 15.0f, 331.0f, 0.0f, -0.3f, 0.0f);
	CREATE_OBJ(m_Tile[13], 8.0f, Ground, Tile05.obj, GroundTex.png, 248.0f, 16.0f, 270.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_Tile[14], 8.0f, Ground, Tile05.obj, GroundTex.png, 177.0f, 15.7f, 232.0f, 0.0f, 0.3f, 0.0f);

}

void ObjRender::Render()
{
	//참호 판자
	for (int i = 0; i < 16; i++)
		SAFE_RENDER(m_MapTest[i]);
	for (int i = 0; i < 10; i++)
		SAFE_RENDER(m_MapTest1[i]);
	//철조망
	for (int i = 0; i < 53; i++)
		SAFE_RENDER(m_BarbedWireT[i]);
	//사격받침
	SAFE_RENDER(m_FireStep00);
	//모래
	for (int i = 0; i < 30; i++)
		SAFE_RENDER(SaddleBag0[i]);
	for (int i = 0; i < 33; i++)
		SAFE_RENDER(SaddleBag1[i]);

	//나무
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
	//지푸라기
	for (int i = 0; i < 2; i++)
	   SAFE_RENDER(m_Straw00[i]);
	//돌
	for (int i = 0; i < 4; i++)
	   SAFE_RENDER(m_Stone00[i]);

	//탱크
	for (int i = 0; i < 2; i++)
	{
		SAFE_RENDER(m_Tank[i]);
	}

	//웨건
	for (int i = 0; i < 3; i++)
	{
		SAFE_RENDER(m_Wagon[i]);
	}

	//건물
	for (int i = 0; i < 3; i++)
	{
		SAFE_RENDER(m_Apt[i]);
	}

	//타일
	for (int i = 0; i < 15; i++)
	{
		SAFE_RENDER(m_Tile[i]);
	}
}