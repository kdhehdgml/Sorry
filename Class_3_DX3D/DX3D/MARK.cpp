#include "stdafx.h"
#include "MARK.h"
#include "MoveOBJ.h"

#define CREATE_OBJ(obj_name, size, folder, objFile, TextureImage, x, y, z, rotationX, rotationY, rotationZ) obj_name = new MoveOBJ;\
      obj_name->Init(size, _T("resources/ObjImages/" ## #folder ##"/" ## #objFile),_T("resources/ObjImages/" ## #folder ##"/" ## #TextureImage), x, y, z, rotationX, rotationY, rotationZ);

MARK::MARK()
{
	m_mark = NULL;
	x = 743.0f;
	y = 29.0f;
	z = 369.0f;
	/*x = 0;
	y = 0;
	z = 0;*/
	xR = 0.0f;
	yR = D3DX_PI / 2;
	zR = 0.0f;


}


MARK::~MARK()
{
	m_mark->~MoveOBJ();
	SAFE_DELETE(m_pBoundingSphere);
	SAFE_RELEASE(m_pSphere);
}

void MARK::Init()
{

	MaxHP = 100;
	HP = 100;
	MoveSpeed = 0.1f;
	ATK = 3;
	DEF = 1;
	state = 0;
	size = 5.0f;


	D3DXCreateSphere(g_pDevice, size, 10, 10, &m_pSphere, NULL);
	m_pBoundingSphere = new BoundingSphere(m_pos, size);


	CREATE_OBJ(m_mark, 10.0f, Mark, BOSS_Mark00.obj, BOSSTEX.png, x, y, z, xR, yR, zR);
}

void MARK::Update()
{
	Debug->AddText("��ũ ��ǥ :");
	Debug->AddText(m_mark->m_pos);
	Debug->EndLine();

	
	

	//����������� �۵�
	if (HP > 0)
	{
	//	IUnitObject::UpdatePositionToDestination();

		m_pBoundingSphere->center = m_mark->m_pos;

		if (Keyboard::Get()->KeyPress(VK_NUMPAD2))
		{
			state = ���̵�;
		}
		else if (Keyboard::Get()->KeyPress(VK_NUMPAD5))
		{
			state = ���̵�;
		}
		if (Keyboard::Get()->KeyPress(VK_NUMPAD1))
		{
			state = ���̵�;
			m_mark->SetRot(0.1f);
		}
		else if (Keyboard::Get()->KeyPress(VK_NUMPAD3))
		{
			state = ���̵�;
		}
		else if (Keyboard::Get()->KeyPress(VK_NUMPAD4))
		{
			state = ����;
		}
		//��ũ ���°�
		switch (state)
		{
		case ���̵�:
			m_mark->m_pos.z = m_mark->m_pos.z + MoveSpeed;
			break;
		case ���̵�:
			m_mark->m_pos.z = m_mark->m_pos.z - MoveSpeed;
			break;

		case ���̵�:
			m_mark->m_pos.x = m_mark->m_pos.x + MoveSpeed;
			break;
		case ���̵�:
			m_mark->m_pos.x = m_mark->m_pos.x - MoveSpeed;
			break;

			//�������� �׽�Ʈ��
		case �̵�:
			break;
		case ����Ѱ���:
			break;
		case ��ȣ�μ���:
			break;
		}

		m_mark->Update();
	}

}

void MARK::Render()
{
	//����������� ����
	if (HP > 0)
	{
		SAFE_RENDER(m_mark);

		D3DXMATRIXA16 mat;
		D3DXMatrixTranslation(&mat, m_pBoundingSphere->center.x, m_pBoundingSphere->center.y, m_pBoundingSphere->center.z);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->SetTexture(0, NULL);
		m_pSphere->DrawSubset(0);
	}


}

