#include "stdafx.h"
#include "MARK.h"
#include "MoveOBJ.h"

#define CREATE_OBJ(obj_name, size, folder, objFile, TextureImage, x, y, z, rotationX, rotationY, rotationZ) obj_name = new MoveOBJ;\
      obj_name->Init(size, _T("resources/ObjImages/" ## #folder ##"/" ## #objFile),_T("resources/ObjImages/" ## #folder ##"/" ## #TextureImage), x, y, z, rotationX, rotationY, rotationZ);

MARK::MARK()
{
	m_mark = NULL;
	//x = 512.0f;
	//y = 30.0f;
	//z = 374.0f;
	x = 0;
	y = 0;
	z = 0;
	xR = 0.0f;
	yR = D3DX_PI / 2;
	zR = 0.0f;
}


MARK::~MARK()
{
	m_mark->~MoveOBJ();
}

void MARK::Init()
{
	CREATE_OBJ(m_mark, 10.0f, Mark, BOSS_Mark00.obj, BOSSTEX.png, x, y, z, xR, yR, zR);
}

void MARK::Update()
{
	Debug->AddText("ÅÊÅ© ÁÂÇ¥ :");
	Debug->AddText(m_mark->m_pos);
	Debug->EndLine();
	
	m_mark->m_pos.x = m_mark->m_pos.x - 0.1f;
	m_mark->Update();
}

void MARK::Render()
{
	SAFE_RENDER(m_mark);
}

