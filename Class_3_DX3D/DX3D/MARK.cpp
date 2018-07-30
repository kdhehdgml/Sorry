#include "stdafx.h"
#include "MARK.h"
#include "MoveOBJ.h"

#define CREATE_OBJ(obj_name, size, folder, objFile, TextureImage, x, y, z, rotationX, rotationY, rotationZ) obj_name = new MoveOBJ;\
      obj_name->Init(size, _T("resources/ObjImages/" ## #folder ##"/" ## #objFile),_T("resources/ObjImages/" ## #folder ##"/" ## #TextureImage), x, y, z, rotationX, rotationY, rotationZ);



MARK::MARK()
{
	m_mark_main = NULL;
	m_mark_sponson = NULL;
	m_mark_tire = NULL;

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
	m_mark_main->~MoveOBJ();
	m_mark_sponson->~MoveOBJ();
	m_mark_tire->~MoveOBJ();
	SAFE_DELETE(m_pHead);
	SAFE_DELETE(m_pBody);
	SAFE_RELEASE(m_pSphere);
	
	if (g_pMeshMaterials != NULL)
	{
		delete[] g_pMeshMaterials;
	}

	if (g_pMeshTexture)
	{
		for (DWORD i = 0; i < g_dwNumMaterials; i++)
		{
			if (g_pMeshTexture[i])
			{
				g_pMeshTexture[i]->Release();
			}
		}
		delete[] g_pMeshTexture;
	}
}

void MARK::Init()
{
	MoveNum = 0;
	MaxHP = 100;
	HP = 100;
	MoveSpeed = 0.1f;
	ATK = 3;
	DEF = 1;
	state = 0;
	size = 10.0f;
	m_pos = { 743.0f ,29.0f,369.0f };
	m_finalDestPos = m_pos;
	m_moveSpeed = 0.6f;
	m_vecMovePosit.push_back(D3DXVECTOR3(324.0f, 0, 367.0f));
	m_vecMovePosit.push_back(D3DXVECTOR3(252.0f, 0, 523.0f));
	m_vecMovePosit.push_back(D3DXVECTOR3(252.0f, 0, 426.0f));
	m_vecMovePosit.push_back(D3DXVECTOR3(264.0f, 0, 408.0f));
	m_vecMovePosit.push_back(D3DXVECTOR3(264.0f, 0, 372.0f));
	m_vecMovePosit.push_back(D3DXVECTOR3(248.0f, 0, 355.0f));
	m_vecMovePosit.push_back(D3DXVECTOR3(260.0f, 0, 335.0f));
	m_vecMovePosit.push_back(D3DXVECTOR3(264.0f, 0, 301.0f));
	m_vecMovePosit.push_back(D3DXVECTOR3(264.0f, 0, 230.0f));
	m_vecMovePosit.push_back(D3DXVECTOR3(280.0f, 0, 230.0f));

	D3DXCreateSphere(g_pDevice, size, 10, 10, &m_pSphere, NULL);
	m_pHead = new BoundingSphere(m_pos, size);
	m_pBody = new BoundingSphere(m_pos, size);

	//g_pMesh = Load("resources/xFile/boss/Mark.X");
	//CREATE_OBJ(m_mark_main, 10.0f, Boss, BOSS_Mark00.obj, level_vehicle_mark_IV_hull.png, x, y, z, xR, yR, zR);
	CREATE_OBJ(m_mark_main, 10.0f, boss3, mark.obj, level_vehicle_mark_IV_hull.png, x, y, z, xR, yR, zR);
	CREATE_OBJ(m_mark_sponson, 6.0f, boss3, sponson.obj, level_vehicle_mark_IV_sponson.png, x, y, z, xR, yR, zR);
	CREATE_OBJ(m_mark_tire, 10.0f, boss3, tire.obj, level_vehicle_mark_IV_tracks.png, x, y, z, xR, yR, zR);
}

void MARK::Update()
{
	Debug->AddText("��ũ ��ǥ :");
	Debug->AddText(m_mark_main->m_pos);
	Debug->EndLine();

	if (m_finalDestPos.x == m_pos.x && m_finalDestPos.z == m_pos.z)
	{
		SetFinalPos(m_vecMovePosit[MoveNum]);
	}
	UpdatePosition();
	m_mark_main->m_pos = m_pos;
	m_mark_main->SetRot(SaveRot);

	m_mark_sponson->m_pos = m_pos;
	m_mark_sponson->SetRot(SaveRot);

	m_mark_tire->m_pos = m_pos;
	m_mark_tire->SetRot(SaveRot);


	Debug->AddText(SaveRot);
	Debug->EndLine();



	//����������� �۵�
	if (HP > 0)
	{
	//	IUnitObject::UpdatePositionToDestination();

		m_pHead->center = m_mark_main->m_pos;
		m_pBody->center = m_mark_main->m_pos;

		//if (Keyboard::Get()->KeyPress(VK_NUMPAD2))
		//{
		//	state = ���̵�;
		//}
		//else if (Keyboard::Get()->KeyPress(VK_NUMPAD5))
		//{
		//	state = ���̵�;
		//}
		//if (Keyboard::Get()->KeyPress(VK_NUMPAD1))
		//{
		//	//state = ���̵�;
		//	m_mark_main->SetRot(0.1f);
		//}
		//else if (Keyboard::Get()->KeyPress(VK_NUMPAD3))
		//{
		//	state = ���̵�;
		//}
		//else if (Keyboard::Get()->KeyPress(VK_NUMPAD4))
		//{
		//	state = ����;
		//}
		////��ũ ���°�
		//switch (state)
		//{
		//case ���̵�:
		//	m_mark_main->m_pos.z = m_mark_main->m_pos.z + MoveSpeed;
		//	break;
		//case ���̵�:
		//	m_mark_main->m_pos.z = m_mark_main->m_pos.z - MoveSpeed;
		//	break;
		//case ���̵�:
		//	m_mark_main->m_pos.x = m_mark_main->m_pos.x + MoveSpeed;
		//	break;
		//case ���̵�:
		//	m_mark_main->m_pos.x = m_mark_main->m_pos.x - MoveSpeed;
		//	break;
		//	//�������� �׽�Ʈ��
		//case �̵�:
		//	break;
		//case ����Ѱ���:
		//	break;
		//case ��ȣ�μ���:
		//	break;
		//}

		m_mark_main->Update();
		m_mark_sponson->Update();
		m_mark_tire->Update();

		if (m_finalDestPos.x == m_pos.x && m_finalDestPos.z == m_pos.z)
			MoveNum++;
		if (MoveNum > 9)
			MoveNum = 1;

	}

}

void MARK::Skin_render()
{
	// ���� ���
	D3DXMatrixIdentity(&m_matWorld); // ��������� ������ķ� ����

	// ���� ���
	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	//S
	//R
	//T
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	m_matWorld = matS * matR * matT;

	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld); // ��������� ����̽��� ����

	for (DWORD i = 0; i < g_dwNumMaterials; i++)
	{
		//	�κ����� �޽��� ������ �ؽ�ó ����
		g_pDevice->SetMaterial(&g_pMeshMaterials[i]);
		g_pDevice->SetTexture(0, g_pMeshTexture[i]);
		//	�κ����� �޽� ���
		g_pMesh->DrawSubset(i);
	}


}

void MARK::Render()
{
	//����������� ����
	if (HP > 0)
	{
		SAFE_RENDER(m_mark_main);
		SAFE_RENDER(m_mark_sponson);
		SAFE_RENDER(m_mark_tire);

		//Skin_render();
		D3DXMATRIXA16 mat;
		D3DXMatrixTranslation(&mat, m_pHead->center.x, m_pHead->center.y, m_pHead->center.z);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->SetTexture(0, NULL);
		m_pSphere->DrawSubset(0);

		D3DXMatrixTranslation(&mat, m_pBody->center.x, m_pBody->center.y, m_pBody->center.z);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->SetTexture(0, NULL);
		m_pSphere->DrawSubset(0);
	}
	//	�޽ô� ������ �ٸ� �޽ú��� �κ������� �̷�� �Ӥ���.
	//	�̵��� ������ �����ؼ� ��� �׷��ش�.
}

void MARK::SetFinalPos(const D3DXVECTOR3 & pos)
{
	m_finalDestPos = pos;
}

void MARK::UpdatePosition()
{
	D3DXVECTOR3 forward = D3DXVECTOR3(m_finalDestPos.x - m_pos.x, 0, m_finalDestPos.z - m_pos.z);
	D3DXVECTOR3 forwardNormalized = forward;
	if (D3DXVec3LengthSq(&forward) > 0)
	{
		D3DXVec3Normalize(&forwardNormalized, &forwardNormalized);
		m_forward = forwardNormalized;//m_forward�� ��������� ����
		if (forward.x <= 0)
		{
			if ((D3DXVec3Dot(&forwardNormalized, &D3DXVECTOR3(0, 0, 1))) - D3DX_PI / 2.0f > -0.6f)
				SaveRot = (D3DXVec3Dot(&forwardNormalized, &D3DXVECTOR3(0, 0, 1))) * 1.5f - D3DX_PI / 2.0f;
			else if((D3DXVec3Dot(&forwardNormalized, &D3DXVECTOR3(0, 0, 1))) - D3DX_PI / 2 > -0.7f)
				SaveRot = (D3DXVec3Dot(&forwardNormalized, &D3DXVECTOR3(0, 0, 1))) * 1.3f - D3DX_PI / 2.0f;
			else
				SaveRot = (D3DXVec3Dot(&forwardNormalized, &D3DXVECTOR3(0, 0, 1))) * 1.6f - D3DX_PI / 2.0f;
		}
			
		else
		{
			if(D3DXVec3Dot(&forwardNormalized, &D3DXVECTOR3(0, 0, 1)) >= -0.1f && D3DXVec3Dot(&forwardNormalized, &D3DXVECTOR3(0, 0, 1)) <= 0.1f)
				SaveRot = D3DXVec3Dot(&forwardNormalized, &D3DXVECTOR3(0, 0, 1)) - D3DX_PI / 2.1f;
			if (D3DXVec3Dot(&forwardNormalized, &D3DXVECTOR3(0, 0, 1)) > - 1.0f && D3DXVec3Dot(&forwardNormalized, &D3DXVECTOR3(0, 0, 1)) < -0.98f)
				SaveRot = D3DXVec3Dot(&forwardNormalized, &D3DXVECTOR3(0, 0, 1)) + D3DX_PI * 1.3f;
			else
				SaveRot = D3DXVec3Dot(&forwardNormalized, &D3DXVECTOR3(0, 0, 1)) + D3DX_PI * 1.1f;
		}
			

		if (D3DXVec3Length(&forward) >= m_moveSpeed * m_currMoveSpeedRate)
		{
			m_pos += forwardNormalized * m_moveSpeed * m_currMoveSpeedRate;
		}
		else
		{
			m_pos.x = m_finalDestPos.x;
			m_pos.z = m_finalDestPos.z;
		}
	}
	else
	{
		m_pos = m_finalDestPos;
	}

}

LPD3DXMESH MARK::Load(const char * szFileName)
{
	//�Žð�ü
	LPD3DXMESH mesh = NULL;
	//	������ �ӽ÷� ������ ���� ����
	LPD3DXBUFFER	pD3DXMtrlBuffer;

	if (FAILED(D3DXLoadMeshFromX((LPCWSTR)szFileName, D3DXMESH_SYSTEMMEM, g_pDevice, NULL, &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials, &mesh)))
	{
		MessageBox(g_hWnd, L"�� �ε� ���� ", L"����", MB_OK);
	}

	//	���� ������ �ؽ�ó ������ ���� �̾Ƴ���.
	D3DXMATERIAL*	d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];//	������ ������ŭ ���� ����ü �迭 ����
	g_pMeshTexture = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];//	���� ������ŭ �ؽ�ó �迭 ����

	for (DWORD i = 0; i < g_dwNumMaterials; i++)
	{
		//	���� ���� ����
		g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

		//	�ֺ� ���� ������ diffuse ������
		g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;

		g_pMeshTexture[i] = NULL;

		if (d3dxMaterials[i].pTextureFilename != NULL &&

			lstrlen((LPCWSTR)(d3dxMaterials[i].pTextureFilename)) > 0)
		{
			//	�ؽ�ó�� ���Ͽ��� �ε��Ѵ�.
			if (FAILED(D3DXCreateTextureFromFile(g_pDevice, (LPCWSTR)d3dxMaterials[i].pTextureFilename,&g_pMeshTexture[i])))
			{
				//	�ؽ�ó�� ���� ������ ������ �������� �˻�
				const	TCHAR* strPrefix = TEXT("..\\");
				const	int	lenPrefix = lstrlen(strPrefix);
				TCHAR	strTexture[MAX_PATH];

				lstrcpyn(strTexture, strPrefix, MAX_PATH);
				lstrcpyn(strTexture + lenPrefix,(LPCWSTR)d3dxMaterials[i].pTextureFilename, MAX_PATH - lenPrefix);

				if (FAILED(D3DXCreateTextureFromFile(g_pDevice, strTexture,&g_pMeshTexture[i])))
				{
					MessageBox(NULL, (LPCWSTR)"Could not Find Texture map", (LPCWSTR)"Meshes.exe", MB_OK);
				}
			}
		}
	}

	//	�ӽ÷� ������ ���� ���� �Ұ�
	pD3DXMtrlBuffer->Release();

	return mesh;
}