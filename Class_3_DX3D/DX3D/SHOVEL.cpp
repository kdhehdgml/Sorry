#include "stdafx.h"
#include "SHOVEL.h"
#include "AllocateHierarchy.h"



// ��Ų ������ ����
#define SCALE 300.0f
//#define SCALE 10000.0f

SHOVEL::SHOVEL()
{
	m_baseRotY = D3DX_PI;

	m_pRootFrame = NULL;
	m_pAnimController = NULL;
	m_fBlendTime = 0.3f;
	m_fPassedBlendTime = 0.0f;
	m_AnimaTionIndex = 0;
	m_bWireFrame = false;
	m_bDrawFrame = true;
	m_bDrawSkeleton = false;

	m_animationSTATE = true;

	pCurrAnimSet = NULL;
	pNextAnimSet = NULL;
}


SHOVEL::~SHOVEL()
{
	SAFE_RELEASE(m_pSphereMesh);
	AllocateHierarchy alloc;
	D3DXFrameDestroy(m_pRootFrame, &alloc);

	SAFE_RELEASE(m_pAnimController);
}

void SHOVEL::Init()
{

	//D3DXCreateSphere(g_pDevice, 0.5f, 10, 10, &m_pSphereMesh, NULL);

	//Load(ASSET_PATH + _T("zealot/"), _T("zealot.X"));
	//CString path = "resources/xFile/";
	CString path = "resources/xFile/weapons/melee/";
	CString filename = "shovel.X";
	Load(path, filename);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_Hand_mat);
	D3DXMatrixScaling(&matS, SCALE, SCALE, SCALE);

	/*m_angleX = 0.64f;
	m_angleY = 1.1699f;
	m_angleZ = 5.33f;
	x = -0.f;
	y = 10.f;
	z = 0.f;*/
	x = 0;
	y = -0.f; 
	z = 0;

	m_angleX = 1.58f;
	m_angleY = 1.01f;
	m_angleZ = 0.0f;

	

	//m_pos.y = 10.f;
	//ó�������� �⺻����
	m_pAnimController->GetAnimationSet(m_AnimaTionIndex, &pNextAnimSet);
	m_pAnimController->GetTrackDesc(0, &track);
	m_pAnimController->GetAnimationSet(0, &pCurrAnimSet);
}

void SHOVEL::Update()
{
	/*if (Keyboard::Get()->KeyPress('R'))
	{
		m_angleX += 0.01f;
	}
	if (Keyboard::Get()->KeyPress('T'))
	{
		m_angleX -= 0.01f;
	}

	if (Keyboard::Get()->KeyPress('F'))
	{
		m_angleY += 0.01f;
	}
	if (Keyboard::Get()->KeyPress('G'))
	{
		m_angleY -= 0.01f;
	}

	if (Keyboard::Get()->KeyPress('V'))
	{
		m_angleZ += 0.01f;
	}
	if (Keyboard::Get()->KeyPress('B'))
	{
		m_angleZ -= 0.01f;
	}

	if (Keyboard::Get()->KeyPress(VK_UP))
	{
		z += 1.f;
	}
	if (Keyboard::Get()->KeyPress(VK_DOWN))
	{
		z -= 1.f;
	}
	if (Keyboard::Get()->KeyPress(VK_LEFT))
	{
		x += 1.f;
	}
	if (Keyboard::Get()->KeyPress(VK_RIGHT))
	{
		x -= 1.f;
	}
	if (Keyboard::Get()->KeyPress(VK_NUMPAD0))
	{
		y += 1.f;
	}
	if (Keyboard::Get()->KeyPress(VK_NUMPAD2))
	{
		y -= 1.f;
	}
	Debug->AddText("�� ������ǥ: ");
	Debug->AddText(m_pos);
	Debug->EndLine();
	Debug->AddText("�� ������ǥ: ");
	Debug->AddText(D3DXVECTOR3( x ,  y,  z));
	Debug->EndLine();
	Debug->AddText("�� ����X: ");
	Debug->AddText(m_angleX);
	Debug->EndLine();
	Debug->AddText("�� ����Y: ");
	Debug->AddText(m_angleY);
	Debug->EndLine();
	Debug->AddText("�� ����Z: ");
	Debug->AddText(m_angleZ);
	Debug->EndLine();*/
	//D3DXMatrixTranslation(&matT, 0, 200.f, 0);

	UpdateAnim();
	UpdateFrameMatrices(m_pRootFrame, NULL);


	D3DXMatrixTranslation(&matT, m_pos.x + x, m_pos.y + y, m_pos.z + z);

	D3DXMatrixRotationX(&matRx, m_angleX);
	D3DXMatrixRotationY(&matRy, m_angleY);
	D3DXMatrixRotationZ(&matRz, m_angleZ);
	D3DXMATRIXA16 matR;
	matR = matRx * matRy * matRz * m_matR;
	//matR = matR * m_matR;
	m_matWorld = matS * matR*  matT;


	//D3DXMatrixIdentity(&m_matWorld);
	//m_matWorld = m_matWorld * m_Hand_mat;


	m_pAnimController->GetTrackDesc(m_AnimaTionIndex, &track);
	m_pAnimController->GetAnimationSet(m_AnimaTionIndex, &pCurrAnimSet);


	SetAnimationIndex(m_AnimaTionIndex, true);
}

void SHOVEL::Render()
{
	m_numFrame = 0;
	m_numMesh = 0;
	if (m_bDrawFrame)DrawFrame(m_pRootFrame);
	Debug->AddText(_T("=====DrawFrame====="));
	Debug->EndLine();
	//if (m_bDrawFrame)DrawFrame(m_pRootFrame);
	Debug->EndLine();
	Debug->AddText(_T("numFrame = "));
	Debug->AddText(m_numFrame);
	Debug->EndLine();
	Debug->AddText(_T("numMesh = "));
	Debug->AddText(m_numMesh);
	Debug->EndLine();

	//D3DXMATRIXA16 mat;
	//D3DXMatrixTranslation(&mat, m_pos.x + x, m_pos.y + y, m_pos.z + z);
	////D3DXMatrixTranslation(&mat, -2.0f,4.0f,0.f);

	//g_pDevice->SetTransform(D3DTS_WORLD, &mat);
	//g_pDevice->SetTexture(0, NULL);
	//m_pSphereMesh->DrawSubset(0);
}


void SHOVEL::Load(LPCTSTR path, LPCTSTR filename)
{
	AllocateHierarchy alloc(path);

	CString fullPath(path);
	fullPath.Append(filename);

	D3DXLoadMeshHierarchyFromX(fullPath, D3DXMESH_MANAGED, g_pDevice,
		&alloc, NULL, &m_pRootFrame, &m_pAnimController);

	SetupBoneMatrixPointers(m_pRootFrame);
}

void SHOVEL::SetupBoneMatrixPointers(LPD3DXFRAME pFrame)
{


	;	if (pFrame->pMeshContainer != NULL)
	{
		SetupBoneMatrixPointersOnMesh(pFrame->pMeshContainer);
	}

	if (pFrame->pFrameSibling != NULL)
	{
		SetupBoneMatrixPointers(pFrame->pFrameSibling);
	}

	if (pFrame->pFrameFirstChild != NULL)
	{
		SetupBoneMatrixPointers(pFrame->pFrameFirstChild);
	}
}

void SHOVEL::SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	DWORD numBones;
	FRAME_EX* pFrameExInfluence;
	MESHCONTAINER_EX* pMeshContainerEx = (MESHCONTAINER_EX*)pMeshContainerBase;

	if (pMeshContainerEx->pSkinInfo != NULL)
	{
		numBones = pMeshContainerEx->pSkinInfo->GetNumBones();

		for (DWORD i = 0; i < numBones; ++i)
		{
			pFrameExInfluence = (FRAME_EX*)D3DXFrameFind(m_pRootFrame,
				pMeshContainerEx->pSkinInfo->GetBoneName(i));

			pMeshContainerEx->ppBoneMatrixPtrs[i] = &pFrameExInfluence->CombinedTM;
		}
	}
}

void SHOVEL::UpdateAnim()
{
	float fDeltaTime = g_pTimeManager->GetDeltaTime();
	// AdvanceTime �Լ��� ȣ��� �������� Anim Ű������ ���
	m_pAnimController->AdvanceTime(fDeltaTime, NULL);

	if (m_fPassedBlendTime <= m_fBlendTime)
	{
		m_fPassedBlendTime += fDeltaTime;

		if (m_fPassedBlendTime < m_fBlendTime)
		{
			float fWeight = m_fPassedBlendTime / m_fBlendTime;

			m_pAnimController->SetTrackWeight(0, fWeight);
			m_pAnimController->SetTrackWeight(1, 1.0f - fWeight);
		}
		else
		{
			m_pAnimController->SetTrackWeight(0, 1);
			m_pAnimController->SetTrackWeight(1, 0);
			m_pAnimController->SetTrackEnable(1, false);
		}
	}

}

void SHOVEL::UpdateFrameMatrices(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	FRAME_EX* pFrameEx = (FRAME_EX*)pFrame;

	if (pParent != NULL)
	{
		pFrameEx->CombinedTM = pFrameEx->TransformationMatrix * ((FRAME_EX*)pParent)->CombinedTM;
	}
	else
	{
		pFrameEx->CombinedTM = pFrameEx->TransformationMatrix;
	}

	if (pFrameEx->pFrameSibling != NULL)
	{
		UpdateFrameMatrices(pFrameEx->pFrameSibling, pParent);
	}

	if (pFrameEx->pFrameFirstChild != NULL)
	{
		UpdateFrameMatrices(pFrameEx->pFrameFirstChild, pFrameEx);
	}
}

void SHOVEL::DrawFrame(LPD3DXFRAME pFrame)
{
	m_numFrame++;
	if (m_numFrame % 5 == 0)
	{
		Debug->EndLine();
	}
	if (pFrame->Name == NULL)
		Debug->AddText(_T("NULL"));
	else
		Debug->AddText(pFrame->Name);

	LPD3DXMESHCONTAINER pMeshContainer = pFrame->pMeshContainer;
	while (pMeshContainer != NULL)
	{
		m_numMesh++;
		Debug->AddText(_T("(MESH)"));
		DrawMeshContainer(pFrame);
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}
	Debug->AddText(_T(" / "));

	if (pFrame->pFrameSibling != NULL)
	{
		DrawFrame(pFrame->pFrameSibling);
	}

	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawFrame(pFrame->pFrameFirstChild);
	}
}

void SHOVEL::DrawMeshContainer(LPD3DXFRAME pFrame)
{
	if (pFrame->pMeshContainer->pSkinInfo == NULL)
		return;

	FRAME_EX* pFrameEx = (FRAME_EX*)pFrame;
	MESHCONTAINER_EX* pMeshContainerEx = (MESHCONTAINER_EX*)pFrameEx->pMeshContainer;
	DWORD numBones = pMeshContainerEx->pSkinInfo->GetNumBones();

	for (DWORD i = 0; i < numBones; ++i)
	{
		pMeshContainerEx->pFinalBoneMatrices[i] =
			pMeshContainerEx->pBoneOffsetMatrices[i] * *(pMeshContainerEx->ppBoneMatrixPtrs[i]);
	}

	PBYTE pVerticesSrc = NULL;
	PBYTE pVerticesDest = NULL;

	pMeshContainerEx->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pVerticesSrc);
	pMeshContainerEx->pWorkMesh->LockVertexBuffer(0, (LPVOID*)&pVerticesDest);

	// generate skinned mesh
	pMeshContainerEx->pSkinInfo->UpdateSkinnedMesh(
		pMeshContainerEx->pFinalBoneMatrices, NULL, pVerticesSrc, pVerticesDest);

	pMeshContainerEx->pWorkMesh->UnlockVertexBuffer();
	pMeshContainerEx->pOrigMesh->UnlockVertexBuffer();

	//g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	if (m_bWireFrame)
		g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//D3DXMatrixIdentity(&m_matWorld);
	//D3DXMatrixScaling(&m_matWorld, 5.0f, 5.0f, 5.0f);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	for (size_t i = 0; i < pMeshContainerEx->vecMtlTex.size(); ++i)
	{
		g_pDevice->SetMaterial(&pMeshContainerEx->vecMtlTex[i]->GetMaterial());
		g_pDevice->SetTexture(0, pMeshContainerEx->vecMtlTex[i]->GetTexture());
		pMeshContainerEx->pWorkMesh->DrawSubset(i);
	}

	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

}

void SHOVEL::DrawSkeleton(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	FRAME_EX* pFrameEx = (FRAME_EX*)pFrame;
	FRAME_EX* pParentFrameEx = (FRAME_EX*)pParent;

	g_pDevice->SetTransform(D3DTS_WORLD, &(pFrameEx->CombinedTM));
	//g_pDevice->SetTransform(D3DTS_WORLD, &(pFrameEx->CombinedTM * m_matWorld));

	g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);
	g_pDevice->SetTexture(0, NULL);
	m_pSphereMesh->DrawSubset(0);

	if (pParent != NULL && pFrame->Name != NULL && pParent->Name != NULL)
	{
		D3DXMATRIXA16 matThis = pFrameEx->CombinedTM;
		D3DXMATRIXA16 matParent = pParentFrameEx->CombinedTM;

		D3DXVECTOR3 posThis(matThis(3, 0), matThis(3, 1), matThis(3, 2));
		D3DXVECTOR3 posParent(matParent(3, 0), matParent(3, 1), matParent(3, 2));

		vector<VERTEX_PC> line{ VERTEX_PC(posThis, BLUE), VERTEX_PC(posParent, YELLOW) };
		g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pDevice->SetFVF(VERTEX_PC::FVF);
		D3DXMATRIXA16 mat;
		D3DXMatrixIdentity(&mat);

		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, &line[0], sizeof(VERTEX_PC));
		g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	}

	if (pFrame->pFrameSibling != NULL)
	{
		DrawSkeleton(pFrame->pFrameSibling, pParent);
	}

	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawSkeleton(pFrame->pFrameFirstChild, pFrame);
	}
}

void SHOVEL::SetAnimationIndex(int nIndex, bool isBlend)
{
	//LPD3DXANIMATIONSET pNextAnimSet = NULL;
	m_pAnimController->GetAnimationSet(nIndex, &pNextAnimSet);
	//isBlend = false;



	if (isBlend)
	{
		//D3DXTRACK_DESC track;
		//LPD3DXANIMATIONSET pCurrAnimSet = NULL;


		m_fPassedBlendTime = 0.0f;

		LPD3DXANIMATIONSET pPrevAnimSet = NULL;

		m_pAnimController->GetTrackAnimationSet(0, &pPrevAnimSet);
		m_pAnimController->SetTrackAnimationSet(1, pPrevAnimSet);

		D3DXTRACK_DESC trackDesc;
		m_pAnimController->GetTrackDesc(0, &trackDesc);
		m_pAnimController->SetTrackDesc(1, &trackDesc);

		m_pAnimController->GetTrackDesc(0, &track);
		m_pAnimController->GetAnimationSet(0, &pCurrAnimSet);


		//Debug->AddText("��ü�ð� :");
		//Debug->AddText(pCurrAnimSet->GetPeriod());
		//Debug->EndLine();

		//Debug->AddText("����ð� :");
		//Debug->AddText(pCurrAnimSet->GetPeriodicPosition(track.Position));
		//Debug->EndLine();



		m_pAnimController->SetTrackWeight(0, 0.0f);
		m_pAnimController->SetTrackWeight(1, 1.0f);

		SAFE_RELEASE(pPrevAnimSet);

		m_fPassedBlendTime = 0.0f;
	}

	m_pAnimController->SetTrackAnimationSet(0, pNextAnimSet);
	m_pAnimController->ResetTime();

	SAFE_RELEASE(pNextAnimSet);
}
