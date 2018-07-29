#include "stdafx.h"
#include "MoveOBJ.h"

#include "FR_HEADGEAR.h"

#define CREATE_OBJ(obj_name, size, folder, objFile, TextureImage, x, y, z, rotationX, rotationY, rotationZ) obj_name = new MoveOBJ;\
      obj_name->Init(size, _T("resources/ObjImages/" ## #folder ##"/" ## #objFile),_T("resources/ObjImages/" ## #folder ##"/" ## #TextureImage), x, y, z, rotationX, rotationY, rotationZ);
#define SCALE 0.3f

FR_HEADGEAR::FR_HEADGEAR()
{
	m_Skin = NULL;
}


FR_HEADGEAR::~FR_HEADGEAR()
{
	SAFE_DELETE(m_pBoundingSphere);
	SAFE_RELEASE(m_pSphere);


	m_Skin->~MoveOBJ();
}

void FR_HEADGEAR::Init()
{
	CREATE_OBJ(m_Skin, SCALE, eq_head/fr_headgear, fr_headgear.obj,
		character_fr_headgear_adrian_clr.png, m_pos.x, m_pos.y, m_pos.z, 0,0,0);
}

void FR_HEADGEAR::Update()
{
	m_Skin->m_pos = m_pos;
	m_Skin->SetMatRot(&m_Hand_mat,1);
	//m_Skin->SetRot(m_angle);
	m_Skin->Update();

	
}

void FR_HEADGEAR::Render()
{
	SAFE_RENDER(m_Skin);
}
