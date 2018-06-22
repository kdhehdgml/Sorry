#include "stdafx.h"
#include "ObjRender.h"
#include "ObjRen.h"

#define CREATE_OBJ(obj_name, size, folder, objFile, TextureImage, x, y, z, rotation) obj_name = new ObjRen;\
		obj_name->Init(size, _T("resources/ObjImages/" ## #folder ##"/" ## #objFile),_T("resources/ObjImages/" ## #folder ##"/" ## #TextureImage), x, y, z, rotation);

ObjRender::ObjRender()
{
	//ÂüÈ£ ÆÇÀÚ
	m_MapTest = NULL;
	m_MapTest0 = NULL;
	m_MapTest1 = NULL;
	m_MapTest2 = NULL;
	m_MapTest3 = NULL;
	m_MapTest4 = NULL;
	m_MapTest5 = NULL;
	m_MapTest6 = NULL;
	//Ã¶Á¶¸Á
	m_BarbedWire00 = NULL;
	m_BarbedWire01 = NULL;
	m_BarbedWire02 = NULL;
	m_BarbedWire03 = NULL;
	m_BarbedWire04 = NULL;
	//¸ÇÀ­ÁÙ Ã¶Á¶¸Á
	m_BarbedWireT00 = NULL;
	m_BarbedWireT01 = NULL;
	m_BarbedWireT02 = NULL;
	m_BarbedWireT03 = NULL;
	m_BarbedWireT04 = NULL;
	m_BarbedWireT05 = NULL;
	m_BarbedWireT06 = NULL;
	m_BarbedWireT07 = NULL;
	m_BarbedWireT08 = NULL;
	m_BarbedWireT09 = NULL;
	m_BarbedWireT10 = NULL;
	m_BarbedWireT11 = NULL;

	//³ª¹«
	m_Tree00 = NULL;
	m_Tree01 = NULL;
	m_Tree02 = NULL;
	m_Tree03 = NULL;
	m_Tree04 = NULL;
	m_Tree05 = NULL;
	m_Tree06 = NULL;
	//ÁöÇª¶ó±â
	m_Straw00 = NULL;
	//µ¹
	m_Stone00 = NULL;
}


ObjRender::~ObjRender()
{
	//ÂüÈ£ ÆÇÀÚ
	m_MapTest->~ObjRen();
	m_MapTest0->~ObjRen();
	m_MapTest1->~ObjRen();
	m_MapTest2->~ObjRen();
	m_MapTest3->~ObjRen();
	m_MapTest4->~ObjRen();
	m_MapTest5->~ObjRen();
	m_MapTest6->~ObjRen();
	//Ã¶Á¶¸Á
	m_BarbedWire00->~ObjRen();
	m_BarbedWire01->~ObjRen();
	m_BarbedWire02->~ObjRen();
	m_BarbedWire03->~ObjRen();
	m_BarbedWire04->~ObjRen();
	m_BarbedWireT00->~ObjRen();
	m_BarbedWireT01->~ObjRen();
	m_BarbedWireT02->~ObjRen();
	m_BarbedWireT03->~ObjRen();
	m_BarbedWireT04->~ObjRen();
	m_BarbedWireT05->~ObjRen();
	m_BarbedWireT06->~ObjRen();
	m_BarbedWireT07->~ObjRen();
	m_BarbedWireT08->~ObjRen();
	m_BarbedWireT09->~ObjRen();
	m_BarbedWireT10->~ObjRen();
	m_BarbedWireT11->~ObjRen();
	//³ª¹«
	m_Tree00->~ObjRen();
	m_Tree01->~ObjRen();
	m_Tree02->~ObjRen();
	m_Tree03->~ObjRen();
	m_Tree04->~ObjRen();
	m_Tree05->~ObjRen();
	m_Tree06->~ObjRen();
	//ÁöÇª¶ó±â
	m_Straw00->~ObjRen();
	//µ¹
	m_Stone00->~ObjRen();
}


void ObjRender::Init()
{
	//ÂüÈ£ ÆÇÀÚ
	CREATE_OBJ(m_MapTest, 66.9f, WoodenBarrier, WoodenBarrierTest02.obj, images.png, 363.0f, 11.5f, -537.0f, 0.0f);
	CREATE_OBJ(m_MapTest0, 12.5f, WoodenBarrier, WoodenBarrierPartTest00.obj, images.png, 100.5f, 5.0f, 77.8f, 0.0f);
	CREATE_OBJ(m_MapTest1, 18.0f, WoodenBarrier, WoodenBarrierPartTest01.obj, images.png, 210.6f, 7.5f, 22.8f, 0.0f);
	CREATE_OBJ(m_MapTest2, 13.5f, WoodenBarrier, WoodenBarrierPartTest02.obj, images.png, 260.6f, 7.9f, 164.8f, 0.0f);
	CREATE_OBJ(m_MapTest3, 11.6f, WoodenBarrier, WoodenBarrierPartTest03.obj, images.png, 142.0f, 7.9f, 335.6f, 0.0f);
	CREATE_OBJ(m_MapTest4, 12.8f, WoodenBarrier, WoodenBarrierPartTest04.obj, images.png, 225.0f, 0.0f, 444.3f, 0.0f);
	CREATE_OBJ(m_MapTest5, 13.8f, WoodenBarrier, WoodenBarrierPartTest05.obj, images.png, 114.5f, 7.0f, 532.8f, 0.0f);
	CREATE_OBJ(m_MapTest6, 16.8f, WoodenBarrier, WoodenBarrierPartTest06.obj, images.png, 259.0f, 19.2f, 490.6f, 0.0f);
	
	//Ã¶Á¶¸Á
	CREATE_OBJ(m_BarbedWire00, 1.0f, BarbedWire, BarbedWire00.obj, BarbedWireTex.png, 0.0f, 40.0f, 0.0f, 0.0f);
	m_BarbedWire01 = new ObjRen; m_BarbedWire01->Init(1.0f, _T("resources/ObjImages/BarbedWire/BarbedWire01.obj"), _T("resources/ObjImages/BarbedWire/BarbedWireTex.png"), 0.0f, 40.0f, 0.0f, 0.0f);
	m_BarbedWire02 = new ObjRen; m_BarbedWire02->Init(3.5f, _T("resources/ObjImages/BarbedWire/BarbedWire02.obj"), _T("resources/ObjImages/BarbedWire/BarbedWireTex.png"), 0.0f, 34.0f, 0.0f, D3DX_PI/2);
	m_BarbedWire03 = new ObjRen; m_BarbedWire03->Init(1.0f, _T("resources/ObjImages/BarbedWire/BarbedWire03.obj"), _T("resources/ObjImages/BarbedWire/BarbedWireTex.png"), 0.0f, 40.0f, 0.0f, 0.0f);
	m_BarbedWire04 = new ObjRen; m_BarbedWire04->Init(1.0f, _T("resources/ObjImages/BarbedWire/BarbedWire04.obj"), _T("resources/ObjImages/BarbedWire/BarbedWireTex.png"), 0.0f, 40.0f, 0.0f, 0.0f);

	m_BarbedWireT00 = new ObjRen; m_BarbedWireT00->Init(3.5f, _T("resources/ObjImages/BarbedWire/BarbedWire02.obj"), _T("resources/ObjImages/BarbedWire/BarbedWireTex.png"), 494.0f, 31.0f, 531.0f, D3DX_PI/2);
	m_BarbedWireT01 = new ObjRen; m_BarbedWireT01->Init(3.5f, _T("resources/ObjImages/BarbedWire/BarbedWire02.obj"), _T("resources/ObjImages/BarbedWire/BarbedWireTex.png"), 494.0f, 31.0f, 515.0f, D3DX_PI/2);
	m_BarbedWireT02 = new ObjRen; m_BarbedWireT02->Init(3.5f, _T("resources/ObjImages/BarbedWire/BarbedWire03.obj"), _T("resources/ObjImages/BarbedWire/BarbedWireTex.png"), 494.0f, 32.0f, 475.0f, D3DX_PI/2);
	m_BarbedWireT03 = new ObjRen; m_BarbedWireT03->Init(3.5f, _T("resources/ObjImages/BarbedWire/BarbedWire03.obj"), _T("resources/ObjImages/BarbedWire/BarbedWireTex.png"), 494.0f, 33.0f, 458.0f, D3DX_PI/2);
	m_BarbedWireT04 = new ObjRen; m_BarbedWireT04->Init(3.5f, _T("resources/ObjImages/BarbedWire/BarbedWire02.obj"), _T("resources/ObjImages/BarbedWire/BarbedWireTex.png"), 494.0f, 33.0f, 419.0f, D3DX_PI/2);
	m_BarbedWireT05 = new ObjRen; m_BarbedWireT05->Init(3.5f, _T("resources/ObjImages/BarbedWire/BarbedWire04.obj"), _T("resources/ObjImages/BarbedWire/BarbedWireTex.png"), 500.0f, 31.0f, 374.0f, D3DX_PI/2);//
	m_BarbedWireT06 = new ObjRen; m_BarbedWireT06->Init(3.5f, _T("resources/ObjImages/BarbedWire/BarbedWire03.obj"), _T("resources/ObjImages/BarbedWire/BarbedWireTex.png"), 494.0f, 31.0f, 370.0f, D3DX_PI/2);
	m_BarbedWireT07 = new ObjRen; m_BarbedWireT07->Init(3.5f, _T("resources/ObjImages/BarbedWire/BarbedWire04.obj"), _T("resources/ObjImages/BarbedWire/BarbedWireTex.png"), 494.0f, 31.0f, 355.0f, D3DX_PI/2);
	m_BarbedWireT08 = new ObjRen; m_BarbedWireT08->Init(3.5f, _T("resources/ObjImages/BarbedWire/BarbedWire02.obj"), _T("resources/ObjImages/BarbedWire/BarbedWireTex.png"), 494.0f, 31.0f, 315.0f, D3DX_PI/2);
	m_BarbedWireT09 = new ObjRen; m_BarbedWireT09->Init(3.5f, _T("resources/ObjImages/BarbedWire/BarbedWire03.obj"), _T("resources/ObjImages/BarbedWire/BarbedWireTex.png"), 494.0f, 31.0f, 300.0f, D3DX_PI/2);
	m_BarbedWireT10 = new ObjRen; m_BarbedWireT10->Init(3.5f, _T("resources/ObjImages/BarbedWire/BarbedWire04.obj"), _T("resources/ObjImages/BarbedWire/BarbedWireTex.png"), 494.0f, 31.0f, 260.0f, D3DX_PI/2);
	m_BarbedWireT11 = new ObjRen; m_BarbedWireT11->Init(3.5f, _T("resources/ObjImages/BarbedWire/BarbedWire02.obj"), _T("resources/ObjImages/BarbedWire/BarbedWireTex.png"), 494.0f, 31.0f, 245.0f, D3DX_PI/2);
	
	//³ª¹«
	m_Tree00 = new ObjRen; m_Tree00->Init(1.0f, _T("resources/ObjImages/Environment/Tree00.obj"), _T("resources/ObjImages/Environment/TreeTex.png"), 0.0f, 40.0f, 0.0f, 0.0f);
	m_Tree01 = new ObjRen; m_Tree01->Init(1.0f, _T("resources/ObjImages/Environment/Tree01.obj"), _T("resources/ObjImages/Environment/TreeTex.png"), 0.0f, 40.0f, 0.0f, 0.0f);
	m_Tree02 = new ObjRen; m_Tree02->Init(1.0f, _T("resources/ObjImages/Environment/Tree02.obj"), _T("resources/ObjImages/Environment/TreeTex.png"), 0.0f, 40.0f, 0.0f, 0.0f);
	m_Tree03 = new ObjRen; m_Tree03->Init(1.0f, _T("resources/ObjImages/Environment/Tree03.obj"), _T("resources/ObjImages/Environment/TreeTex.png"), 0.0f, 40.0f, 0.0f, 0.0f);
	m_Tree04 = new ObjRen; m_Tree04->Init(1.0f, _T("resources/ObjImages/Environment/Tree04.obj"), _T("resources/ObjImages/Environment/Tree04Tex.png"), 0.0f, 40.0f, 0.0f, 0.0f);
	m_Tree05 = new ObjRen; m_Tree05->Init(1.0f, _T("resources/ObjImages/Environment/Tree05.obj"), _T("resources/ObjImages/Environment/Tree05Tex.png"), 0.0f, 40.0f, 0.0f, 0.0f);
	m_Tree06 = new ObjRen; m_Tree06->Init(1.0f, _T("resources/ObjImages/Environment/Tree06.obj"), _T("resources/ObjImages/Environment/TreeTex.png"), 0.0f, 40.0f, 0.0f, 0.0f);
	//ÁöÇª¶ó±â
	m_Straw00 = new ObjRen; m_Straw00->Init(1.0f, _T("resources/ObjImages/Environment/Straw00.obj"), _T("resources/ObjImages/Environment/StrawTex.png"), 0.0f, 40.0f, 0.0f, 0.0f);
	//µ¹
	m_Stone00 = new ObjRen; m_Stone00->Init(1.0f, _T("resources/ObjImages/Environment/Stone00.obj"), _T("resources/ObjImages/Environment/StoneTex.png"), 0.0f, 40.0f, 0.0f, 0.0f);
}

void ObjRender::Render()
{
	//ÂüÈ£ ÆÇÀÚ
	SAFE_RENDER(m_MapTest);
	SAFE_RENDER(m_MapTest0);
	SAFE_RENDER(m_MapTest1);
	SAFE_RENDER(m_MapTest2);
	SAFE_RENDER(m_MapTest3);
	SAFE_RENDER(m_MapTest4);
	SAFE_RENDER(m_MapTest5);
	SAFE_RENDER(m_MapTest6);
	//Ã¶Á¶¸Á
	SAFE_RENDER(m_BarbedWire00);
	SAFE_RENDER(m_BarbedWire01);
	SAFE_RENDER(m_BarbedWire02);
	SAFE_RENDER(m_BarbedWire03);
	SAFE_RENDER(m_BarbedWire04);
	SAFE_RENDER(m_BarbedWireT00);
	SAFE_RENDER(m_BarbedWireT01);
	SAFE_RENDER(m_BarbedWireT02);
	SAFE_RENDER(m_BarbedWireT03);
	SAFE_RENDER(m_BarbedWireT04);
	SAFE_RENDER(m_BarbedWireT05);
	SAFE_RENDER(m_BarbedWireT06);
	SAFE_RENDER(m_BarbedWireT07);
	SAFE_RENDER(m_BarbedWireT08);
	SAFE_RENDER(m_BarbedWireT09);
	SAFE_RENDER(m_BarbedWireT10);
	SAFE_RENDER(m_BarbedWireT11);
	//³ª¹«
	SAFE_RENDER(m_Tree00);
	SAFE_RENDER(m_Tree01);
	SAFE_RENDER(m_Tree02);
	SAFE_RENDER(m_Tree03);
	SAFE_RENDER(m_Tree04);
	SAFE_RENDER(m_Tree05);
	SAFE_RENDER(m_Tree06);
	//ÁöÇª¶ó±â
	SAFE_RENDER(m_Straw00);
	//µ¹
	SAFE_RENDER(m_Stone00);
}
