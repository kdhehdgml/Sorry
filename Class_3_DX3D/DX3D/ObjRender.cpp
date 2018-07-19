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
	//m_MapTest1 = NULL;
	for (int i = 0; i < 75; i++)
	{
		m_MapTest00[i] = NULL;
	}
	//철조망
	for (int i = 0; i < 53; i++)
		m_BarbedWireT[i] = NULL;
	//사격받침
	for (int i = 0; i < 6; i++)
		m_FireStep00[i] = NULL;
	//모래
	for (int i = 0; i < 30; i++)
		SaddleBag0[i] = NULL;
	for (int i = 0; i < 86; i++)
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
	//m_MapTest1->~ObjRen();
	for (int i = 0; i < 75; i++)
	{
		m_MapTest00[i]->~ObjRen();
	}
	//철조망
	for (int i = 0; i < 53; i++)
		m_BarbedWireT[i]->~ObjRen();
	
	//사격받침
	for (int i = 0; i < 6; i++)
		m_FireStep00[i]->~ObjRen();
	//모래
	for (int i = 0; i < 30; i++)
		SaddleBag0[i]->~ObjRen();
	for (int i = 0; i < 86; i++)
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
	int vertexSize = 15;
	int currentVertex = 0;
	//참호 판자
	currentVertex++;
	g_pSceneManager->calcLoadingExtra(currentVertex, vertexSize);
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
	//m_MapTest00
	currentVertex++;
	g_pSceneManager->calcLoadingExtra(currentVertex, vertexSize);
	CREATE_OBJ(m_MapTest00[0], 8.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 255.0f, 8.0f, 721.0f, -0.39f, 1.55f, 0.919f);
	CREATE_OBJ(m_MapTest00[1], 6.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 254.0f, 13.0f, 650.0f, -0.25f, 1.52f, 1.1f);
	CREATE_OBJ(m_MapTest00[2], 6.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 250.0f, 15.0f, 578.0f, -0.33f, 1.62f, 1.01f);
	CREATE_OBJ(m_MapTest00[3], 4.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 219.0f, 18.0f, 540.0f, -0.29f, 1.52f, 1.1f);
	CREATE_OBJ(m_MapTest00[4], 7.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 235.0f, 15.0f, 557.0f, -1.28f, 2.78f, 0.01f);
	CREATE_OBJ(m_MapTest00[5], 5.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 240.0f, 18.0f, 600.0f, -1.31f, 0.56f, -0.06f);
	CREATE_OBJ(m_MapTest00[6], 3.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 229.0f, 22.0f, 616.0f, -1.35f, 1.55f, 0.0f);
	CREATE_OBJ(m_MapTest00[7], 5.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 242.0f, 16.0f, 630.0f, -1.33f, 2.77f, 0.0f);
	CREATE_OBJ(m_MapTest00[8], 5.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 242.0f, 13.0f, 670.0f, -1.9f, 3.4f, -0.02f);
	CREATE_OBJ(m_MapTest00[9], 3.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 227.0f, 18.0f, 681.0f, -1.73f, 4.71f, -0.2f);
	CREATE_OBJ(m_MapTest00[10], 7.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 243.0f, 11.0f, 695.0f, -1.37, 2.72f, -0.08f);
	CREATE_OBJ(m_MapTest00[11], 5.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 231.0f, 13.0f, 703.0f, -1.78f, 2.76f, -0.04f);
	CREATE_OBJ(m_MapTest00[12], 4.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 212.0f, 15.0f, 705.0f, -1.74f, 3.88f, -0.03f);
	CREATE_OBJ(m_MapTest00[13], 3.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 207.0f, 18.0f, 717.0f, -1.78f, 4.71f, -0.03f);
	CREATE_OBJ(m_MapTest00[14], 2.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 202.0f, 18.0f, 726.0f, -1.33f, 0.36f, 0.0f);
	CREATE_OBJ(m_MapTest00[15], 9.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 169.0f, 7.0f, 699.0f, -1.46f, -0.28f, 0.05f);
	CREATE_OBJ(m_MapTest00[16], 6.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 175.0f, 12.0f, 672.0f, -1.1f, 0.2f, 0.0f);
	CREATE_OBJ(m_MapTest00[17], 8.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 185.0f, 9.0f, 653.0f, -1.78f, -1.58f, 0.0f);
	CREATE_OBJ(m_MapTest00[18], 4.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 192.0f, 15.0f, 625.0f, -1.72f, -2.09f, 0.0f);
	CREATE_OBJ(m_MapTest00[19], 3.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 205.0f, 18.0f, 615.0f, -1.76f, -2.94f, 0.0f);
	CREATE_OBJ(m_MapTest00[20], 6.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 227.0f, 13.0f, 637.0f, -1.76f, -3.51f, 0.0f);
	CREATE_OBJ(m_MapTest00[21], 6.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 156.0f, 10.0f, 649.0f, -1.22f, 0.03f, 0.0f);
	CREATE_OBJ(m_MapTest00[22], 5.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 226.0f, 17.0f, 566.0f, -1.25f, -0.36f, 0.0f);
	CREATE_OBJ(m_MapTest00[23], 7.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 197.0f, 15.0f, 568.0f, -1.23f, 0.48f, 0.0f);
	CREATE_OBJ(m_MapTest00[24], 7.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 177.0f, 12.0f, 597.0f, -1.28f, -1.03f, -0.08f);
	CREATE_OBJ(m_MapTest00[25], 3.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 160.0f, 19.0f, 583.0f, -1.43f, 0.19f, 0.0f);
	CREATE_OBJ(m_MapTest00[26], 10.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 99.0f, 9.0f, 512.0f, -1.28f, 0.42f, 0.0f);
	CREATE_OBJ(m_MapTest00[27], 10.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 67.0f, 7.0f, 535.0f, -1.39f, -1.47f, 0.0f);
	CREATE_OBJ(m_MapTest00[28], 6.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 80.0f, 14.0f, 508.0f, -1.28f, -2.75f, 0.0f);
	CREATE_OBJ(m_MapTest00[29], 6.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 78.0f, 13.0f, 340.0f, -1.32f, -2.83f, 0.0f);
	CREATE_OBJ(m_MapTest00[30], 6.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 114.0f, 15.0f, 351.0f, -1.68f, -3.6f, 0.0f);
	CREATE_OBJ(m_MapTest00[31], 7.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 61.0f, 12.0f, 362.0f, -1.7f, -4.77f, 0.0f);
	CREATE_OBJ(m_MapTest00[32], 5.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 94.0f, 16.0f, 321.0f, -1.7f, -4.71f, 0.0f);

	CREATE_OBJ(m_MapTest00[33], 8.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 111.0f, 12.0f, 422.0f, -1.38f, -0.41f, 0.03f);
	CREATE_OBJ(m_MapTest00[34], 8.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 123.0f, 13.0f, 414.0f, -1.73f, -0.32f, 0.0f);
	CREATE_OBJ(m_MapTest00[35], 3.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 84.0f, 21.0f, 396.0f, -1.34f, -1.61f, 0.0f);
	CREATE_OBJ(m_MapTest00[36], 6.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 68.0f, 15.0f, 409.0f, -1.37f, -2.78f, 0.0f);
	CREATE_OBJ(m_MapTest00[37], 6.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 57.0f, 16.0f, 427.0f, -1.33f, -1.41f, 0.0f);
	CREATE_OBJ(m_MapTest00[38], 5.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 117.0f, 14.0f, 295.0f, -1.37f, -2.68f, 0.0f);
	CREATE_OBJ(m_MapTest00[39], 6.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 82.0f, 14.0f, 298.0f, -1.9f, -3.7f, 0.0f);
	CREATE_OBJ(m_MapTest00[40], 9.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 71.0f, 10.0f, 271.0f, -1.31f, -1.55f, 0.0f);
	CREATE_OBJ(m_MapTest00[41], 7.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 84.0f, 10.0f, 241.0f, -1.29f, -2.42f, 0.0f);
	CREATE_OBJ(m_MapTest00[42], 5.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 95.0f, 13.0f, 215.0f, -1.27f, -1.53f, 0.0f);
	CREATE_OBJ(m_MapTest00[43], 5.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 114.0f, 13.0f, 243.0f, -1.38f, -0.24f, 0.0f);
	CREATE_OBJ(m_MapTest00[44], 3.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 118.0f, 18.0f, 231.0f, -1.74f, -0.24f, 0.0f);
	CREATE_OBJ(m_MapTest00[45], 4.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 95.0f, 14.0f, 217.0f, -1.69f, 1.56f, 0.0f);
	CREATE_OBJ(m_MapTest00[46], 8.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 74.0f, 11.0f, 197.0f, -1.73f, 2.84f, -0.11f);
	CREATE_OBJ(m_MapTest00[47], 7.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 58.0f, 16.0f, 177.0f, -1.83f, 1.5f, 0.0f);
	CREATE_OBJ(m_MapTest00[48], 7.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 73.0f, 15.0f, 157.0f, -1.83f, 0.48f, 0.0f);
	CREATE_OBJ(m_MapTest00[49], 6.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 85.0f, 13.0f, 188.0f, 1.36f, -0.27f, 0.0f);
	CREATE_OBJ(m_MapTest00[50], 15.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 127.0f, 1.0f, 169.0f, 1.11f, 0.83f, 0.0f);
	CREATE_OBJ(m_MapTest00[51], 5.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 161.0f, 16.0f, 173.0f, 1.36f, 0.83f, 0.0f);
	CREATE_OBJ(m_MapTest00[52], 3.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 178.0f, 17.0f, 165.0f, 1.69f, 1.58f, 0.0f);
	CREATE_OBJ(m_MapTest00[53], 7.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 187.0f, 12.0f, 143.0f, 1.75f, 3.33f, 0.0f);
	CREATE_OBJ(m_MapTest00[54], 3.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 165.0f, 16.0f, 142.0f, 1.75f, 2.68f, 0.0f);
	CREATE_OBJ(m_MapTest00[55], 3.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 145.0f, 16.0f, 133.0f, 1.24f, 1.5f, 0.0f);
	CREATE_OBJ(m_MapTest00[56], 3.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 89.0f, 19.0f, 142.0f, 1.24f, 1.5f, 0.0f);
	CREATE_OBJ(m_MapTest00[57], 5.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 87.0f, 14.0f, 121.0f, 1.24f, -0.24f, 0.0f);
	CREATE_OBJ(m_MapTest00[58], 5.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 65.0f, 14.0f, 109.0f, 1.23f, 1.49f, 0.0f);
	CREATE_OBJ(m_MapTest00[59], 8.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 82.0f, 9.0f, 87.0f, 1.38f, 0.46f, 0.0f);
	CREATE_OBJ(m_MapTest00[60], 4.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 100.0f, 17.0f, 69.0f, 1.38f, 1.62f, 0.0f);
	CREATE_OBJ(m_MapTest00[61], 4.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 98.0f, 17.0f, 44.0f, 1.38f, -0.22f, 0.0f);
	CREATE_OBJ(m_MapTest00[62], 8.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 75.0f, 14.0f, 30.0f, 1.17f, 1.58f, 0.0f);
	CREATE_OBJ(m_MapTest00[63], 5.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 83.0f, 20.0f, 5.0f, 1.17f, 0.51f, 0.0f);
	CREATE_OBJ(m_MapTest00[64], 4.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 222.0f, 17.0f, 189.0f, 1.35f, -1.52f, 0.0f);
	CREATE_OBJ(m_MapTest00[65], 7.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 223.0f, 14.0f, 173.0f, 1.35f, 0.52f, 0.0f);
	CREATE_OBJ(m_MapTest00[66], 7.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 237.0f, 15.0f, 178.0f, 1.82f, 0.34f, 0.0f);
	CREATE_OBJ(m_MapTest00[67], 6.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 251.0f, 16.0f, 161.0f, 1.82f, 1.58f, 0.0f);
	CREATE_OBJ(m_MapTest00[68], 7.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 236.0f, 14.0f, 144.0f, 1.82f, 2.91f, 0.0f);
	CREATE_OBJ(m_MapTest00[69], 4.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 219.0f, 17.0f, 129.0f, 1.73f, 1.67f, -0.01f);
	CREATE_OBJ(m_MapTest00[70], 4.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 206.0f, 16.0f, 129.0f, 1.31f, 1.5f, 0.0f);
	CREATE_OBJ(m_MapTest00[71], 8.0f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 202.0f, 10.0f, 90.0f, 1.48f, -0.92f, 0.0f);
	CREATE_OBJ(m_MapTest00[72], 5.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 252.0f, 13.0f, 72.0f, 1.48f, -0.92f, 0.0f);
	CREATE_OBJ(m_MapTest00[73], 5.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 247.0f, 15.0f, 17.0f, 1.48f, -0.58f, 0.0f);
	CREATE_OBJ(m_MapTest00[74], 5.5f, WoodenBarrier, WoodenBarrier.obj, woodTex.png, 210.0f, 15.0f, 16.0f, 1.48f, 0.24f, 0.06f);



	//철조망
	//1번 줄
	currentVertex++;
	g_pSceneManager->calcLoadingExtra(currentVertex, vertexSize);
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
	currentVertex++;
	g_pSceneManager->calcLoadingExtra(currentVertex, vertexSize);
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
	currentVertex++;
	g_pSceneManager->calcLoadingExtra(currentVertex, vertexSize);
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
	currentVertex++;
	g_pSceneManager->calcLoadingExtra(currentVertex, vertexSize);
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
	currentVertex++;
	g_pSceneManager->calcLoadingExtra(currentVertex, vertexSize);
	CREATE_OBJ(m_FireStep00[0], 7.5f, FireStep, FireStep00.obj, woodTex.png, 240.0f, 23.0f, 500.5f, -0.02f, 0.0f, -0.14f);
	CREATE_OBJ(m_FireStep00[1], 7.5f, FireStep, FireStep00.obj, woodTex.png, 237.0f, 22.5f, 436.0f, 0.0f, 0.0f, -0.15f);
	CREATE_OBJ(m_FireStep00[2], 7.5f, FireStep, FireStep00.obj, woodTex.png, 253.0f, 22.7f, 391.0f, 0.01f, 0.0f, 0.04f);
	CREATE_OBJ(m_FireStep00[3], 7.5f, FireStep, FireStep00.obj, woodTex.png, 245.0f, 23.2f, 319.0f, 0.01f, 0.0f, -0.08f);
	CREATE_OBJ(m_FireStep00[4], 7.5f, FireStep, FireStep00.obj, woodTex.png, 256.0f, 24.0f, 272.5f, 0.01f, 0.0f, -0.14f);
	CREATE_OBJ(m_FireStep00[5], 7.5f, FireStep, FireStep00.obj, woodTex.png, 254.0f, 23.5f, 234.0f, -0.01f, -0.01f, -0.32f);


	//모래
	currentVertex++;
	g_pSceneManager->calcLoadingExtra(currentVertex, vertexSize);
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
	CREATE_OBJ(SaddleBag1[33], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 214.0f, 25.0f, 264.0f, 0.0f, -1.469f, 0.0f);
	CREATE_OBJ(SaddleBag1[34], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 203.0f, 25.0f, 241.0f, 0.0f, -0.62f, 0.00f);
	CREATE_OBJ(SaddleBag1[35], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 159.0f, 24.0f, 269.0f, 0.0f, -1.559f, 0.00f);
	CREATE_OBJ(SaddleBag1[36], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 138.0f, 22.0f, 266.0f, 0.0f, -1.579f, 0.00f);
	CREATE_OBJ(SaddleBag1[37], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 154.0f, 23.0f, 224.0f, 0.0f, 0.78f, 0.00f);
	CREATE_OBJ(SaddleBag1[38], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 154.0f, 23.0f, 208.0f, 0.0f, 2.32f, 0.00f);
	CREATE_OBJ(SaddleBag1[39], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 149.0f, 23.0f, 192.0f, 0.0f, 1.54f, 0.00f);
	CREATE_OBJ(SaddleBag1[40], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 157.0f, 24.0f, 171.0f, 0.0f, 0.82f, 0.00f);
	CREATE_OBJ(SaddleBag1[41], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 191.0f, 24.0f, 201.0f, 0.0f, 0.36f, 0.00f);
	CREATE_OBJ(SaddleBag1[42], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 205.0f, 25.0f, 186.0f, 0.0f, 1.56f, 0.00f);
	CREATE_OBJ(SaddleBag1[43], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 215.0f, 24.0f, 173.0f, 0.0f, 0.54f, 0.00f);
	CREATE_OBJ(SaddleBag1[44], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 236.0f, 24.0f, 184.0f, 0.0f, 0.36f, 0.00f);
	CREATE_OBJ(SaddleBag1[45], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 256.0f, 25.0f, 162.0f, 0.0f, 1.579f, 0.00f);
	CREATE_OBJ(SaddleBag1[46], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 242.0f, 24.0f, 139.0f, 0.0f, -0.25f, 0.00f);
	CREATE_OBJ(SaddleBag1[47], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 186.0f, 23.0f, 138.0f, 0.0f, 0.19f, 0.00f);
	CREATE_OBJ(SaddleBag1[48], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 105.0f, 21.0f, 176.0f, 0.0f, 0.81f, 0.00f);
	CREATE_OBJ(SaddleBag1[49], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 123.0f, 21.0f, 155.0f, 0.0f, 0.81f, 0.00f);
	CREATE_OBJ(SaddleBag1[50], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 69.0f, 25.0f, 35.0f, 0.0f, -1.52f, 0.00f);
	CREATE_OBJ(SaddleBag1[51], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 96.0f, 24.0f, 69.0f, 0.0f, -1.52f, 0.00f);
	CREATE_OBJ(SaddleBag1[52], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 85.0f, 24.0f, 85.0f, 0.0f, -2.65f, 0.00f);
	CREATE_OBJ(SaddleBag1[53], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 60.0f, 23.0f, 112.0f, 0.0f, -1.69f, 0.00f);
	CREATE_OBJ(SaddleBag1[54], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 72.0f, 26.0f, 153.0f, 0.0f, 0.49f, 0.00f);
	CREATE_OBJ(SaddleBag1[55], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 54.0f, 27.0f, 174.0f, 0.0f, 1.45f, 0.00f);
	CREATE_OBJ(SaddleBag1[56], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 131.0f, 23.0f, 231.0f, 0.0f, -0.2f, 0.00f);
	CREATE_OBJ(SaddleBag1[57], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 125.0f, 22.0f, 250.0f, 0.0f, -0.27f, 0.00f);
	CREATE_OBJ(SaddleBag1[58], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 90.0f, 21.0f, 217.0f, 0.0f, 1.55f, 0.00f);
	CREATE_OBJ(SaddleBag1[59], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 81.0f, 21.0f, 236.0f, 0.0f, 0.7f, 0.00f);
	CREATE_OBJ(SaddleBag1[60], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 61.0f, 22.0f, 266.0f, 0.0f, 1.56f, 0.00f);
	CREATE_OBJ(SaddleBag1[61], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 128.0f, 22.0f, 284.0f, 0.0f, 0.52f, 0.00f);
	CREATE_OBJ(SaddleBag1[62], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 87.0f, 22.0f, 320.0f, 0.0f, 1.52f, 0.00f);
	CREATE_OBJ(SaddleBag1[63], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 179.0f, 24.0f, 281.0f, 0.0f, 0.52f, 0.00f);
	CREATE_OBJ(SaddleBag1[64], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 164.0f, 22.0f, 316.0f, 0.0f, 1.92f, 0.00f);
	CREATE_OBJ(SaddleBag1[65], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 140.0f, 22.0f, 302.0f, 0.0f, 0.42f, 0.00f);
	CREATE_OBJ(SaddleBag1[66], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 137.0f, 22.0f, 344.0f, 0.0f, -0.43f, 0.00f);
	CREATE_OBJ(SaddleBag1[67], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 153.0f, 24.0f, 391.0f, 0.0f, -0.42f, 0.00f);
	CREATE_OBJ(SaddleBag1[68], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 129.0f, 25.0f, 363.0f, 0.0f, -0.48f, 0.00f);
	CREATE_OBJ(SaddleBag1[69], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 150.0f, 24.0f, 421.0f, 0.0f, -0.43f, 0.00f);
	CREATE_OBJ(SaddleBag1[70], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 145.0f, 24.0f, 441.0f, 0.0f, -0.36f, 0.00f);
	CREATE_OBJ(SaddleBag1[71], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 119.0f, 24.0f, 431.0f, 0.0f, -0.36f, 0.00f);
	CREATE_OBJ(SaddleBag1[72], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 118.0f, 25.0f, 407.0f, 0.0f, -0.35f, 0.00f);
	CREATE_OBJ(SaddleBag1[73], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 144.0f, 25.0f, 456.0f, 0.0f, 0.48f, 0.00f);
	CREATE_OBJ(SaddleBag1[74], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 129.0f, 25.0f, 481.0f, 0.0f, -2.63f, 0.00f);
	CREATE_OBJ(SaddleBag1[75], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 132.0f, 24.0f, 503.0f, 0.0f, -2.63f, 0.00f);
	CREATE_OBJ(SaddleBag1[76], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 110.0f, 24.0f, 516.0f, 0.0f, -2.63f, 0.00f);
	CREATE_OBJ(SaddleBag1[77], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 146.0f, 25.0f, 512.0f, 0.0f, -1.55f, 0.00f);
	CREATE_OBJ(SaddleBag1[78], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 159.0f, 25.0f, 544.0f, 0.0f, -1.55f, 0.00f);
	CREATE_OBJ(SaddleBag1[79], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 171.0f, 23.0f, 594.0f, 0.0f, -1.02f, 0.00f);
	CREATE_OBJ(SaddleBag1[80], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 224.0f, 25.0f, 571.0f, 0.0f, -0.41f, 0.00f);
	CREATE_OBJ(SaddleBag1[81], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 202.0f, 25.0f, 571.0f, 0.0f, 0.46f, 0.00f);
	CREATE_OBJ(SaddleBag1[82], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 232.0f, 24.0f, 551.0f, 0.0f, 2.68f, 0.00f);
	CREATE_OBJ(SaddleBag1[83], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 255.0f, 24.0f, 574.0f, 0.0f, 1.59f, 0.00f);
	CREATE_OBJ(SaddleBag1[84], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 243.0f, 26.0f, 603.0f, 0.0f, 0.56f, 0.00f);
	CREATE_OBJ(SaddleBag1[85], 5.0f, SaddleBag, SaddleBag00.obj, SaddleBagTex.png, 259.0f, 24.0f, 650.0f, 0.0f, 1.53f, 0.00f);


	//나무
	currentVertex++;
	g_pSceneManager->calcLoadingExtra(currentVertex, vertexSize);
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
	currentVertex++;
	g_pSceneManager->calcLoadingExtra(currentVertex, vertexSize);
	CREATE_OBJ(m_Straw00[0], 3.0f, Environment, Straw00.obj, StrawTex.png, 7.0f, 25.0f, 71.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_Straw00[1], 3.0f, Environment, Straw00.obj, StrawTex.png, 7.0f, 25.0f, 61.0f, 0.0f, D3DX_PI / 2, 0.0f);
	//돌
	currentVertex++;
	g_pSceneManager->calcLoadingExtra(currentVertex, vertexSize);
	CREATE_OBJ(m_Stone00[0], 6.0f, Environment, Stone00.obj, StoneTex.png, 440.0f, 25.0f, 424.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_Stone00[1], 2.0f, Environment, Stone00.obj, StoneTex.png, 292.0f, 22.0f, 538.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_Stone00[2], 2.0f, Environment, Stone00.obj, StoneTex.png, 332.0f, 22.0f, 210.0f, 0.0f, 0.0f, 0.0f);
	CREATE_OBJ(m_Stone00[3], 3.0f, Environment, Stone00.obj, StoneTex.png, 333.0f, 22.0f, 320.0f, 0.0f, 0.0f, 0.0f);

	//탱크
	currentVertex++;
	g_pSceneManager->calcLoadingExtra(currentVertex, vertexSize);
	CREATE_OBJ(m_Tank[0], 8.5f, ETC, Tank00.obj, TankTex.png, 354.0f, 25.0f, 454.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_Tank[1], 8.5f, ETC, Tank00.obj, TankTex.png, 412.0f, 25.0f, 280.0f, 0.0f, -D3DX_PI / 2, -0.3f);

	//웨건
	currentVertex++;
	g_pSceneManager->calcLoadingExtra(currentVertex, vertexSize);
	CREATE_OBJ(m_Wagon[0], 4.5f, ETC, 105mm.obj, 105mmTex.png, 336.0f, 19.0f, 272.0f, 0.0f, D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_Wagon[1], 4.5f, ETC, 105mm.obj, 105mmTex.png, 400.0f, 19.0f, 451.0f, 0.0f, -D3DX_PI / 2, 0.0f);
	CREATE_OBJ(m_Wagon[2], 4.5f, ETC, 105mm.obj, 105mmTex.png, 400.0f, 19.0f, 441.0f, 0.0f, D3DX_PI / 2, -0.3f);

	//건물
	currentVertex++;
	g_pSceneManager->calcLoadingExtra(currentVertex, vertexSize);
	CREATE_OBJ(m_Apt[0], 9.5f, ETC, Apt00.obj, AptTex.png, -50.0f, 50.0f, 400.0f, 0.0f, D3DX_PI, 0.0f);
	CREATE_OBJ(m_Apt[1], 9.5f, ETC, Apt00.obj, AptTex.png, -50.0f, 50.0f, 300.0f, 0.0f, D3DX_PI, 0.0f);
	CREATE_OBJ(m_Apt[2], 9.5f, ETC, Apt00.obj, AptTex.png, -50.0f, 50.0f, 200.0f, 0.0f, D3DX_PI, 0.0f);

	//타일
	currentVertex++;
	g_pSceneManager->calcLoadingExtra(currentVertex, vertexSize);
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
	
	g_pSceneManager->m_pLoadingStringExtra.Empty();
}

void ObjRender::Render()
{
	//참호 판자
	for (int i = 0; i < 16; i++)
		SAFE_RENDER(m_MapTest[i]);
	//SAFE_RENDER(m_MapTest1);
	for (int i = 0; i < 75; i++)
		SAFE_RENDER(m_MapTest00[i]);
	//철조망
	for (int i = 0; i < 53; i++)
		SAFE_RENDER(m_BarbedWireT[i]);
	//사격받침
	for (int i = 0; i < 6; i++)
		SAFE_RENDER(m_FireStep00[i]);
	//모래
	for (int i = 0; i < 30; i++)
		SAFE_RENDER(SaddleBag0[i]);
	for (int i = 0; i < 86; i++)
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

void ObjRender::Update()
{

}
