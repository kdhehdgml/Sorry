#include "stdafx.h"
#include "SkinnedMesh.h"
#include "AllocateHierarchy.h"

#define SCALE 0.1f

SkinnedMesh::SkinnedMesh()
{
	//m_Brot.y = ;
	m_baseRotY = D3DX_PI;

	m_pRootFrame = NULL;
	m_pAnimController = NULL;
	m_fBlendTime = 0.3f;
	m_fPassedBlendTime = 0.0f;
	m_AnimaTionIndex = 0;
	m_bWireFrame = false;
	m_bDrawFrame = true;
	m_bDrawSkeleton = false;
	m_pos = D3DXVECTOR3(0,0,0);
	m_angle = NULL;
}

SkinnedMesh::~SkinnedMesh()
{
	SAFE_RELEASE(m_pSphereMesh);
	AllocateHierarchy alloc;
	D3DXFrameDestroy(m_pRootFrame, &alloc);

	SAFE_RELEASE(m_pAnimController);
}

void SkinnedMesh::Init()
{
	g_pCamera->SetTarget(&m_pos);
	g_pKeyboardManager->SetMovingTarget(&m_keyState);

	D3DXCreateSphere(g_pDevice, 0.01f, 10, 10, &m_pSphereMesh, NULL);

	//Load(ASSET_PATH + _T("zealot/"), _T("zealot.X"));
	//CString path = "resources/xFile/";
	CString path = "resources/xFile/test_team/test/";
	CString filename = "TEAM_melee.X";
	Load(path, filename);
	D3DXMatrixIdentity(&m_matWorld);
}

void SkinnedMesh::Load(LPCTSTR path, LPCTSTR filename)
{
	AllocateHierarchy alloc(path);

	CString fullPath(path);
	fullPath.Append(filename);

	D3DXLoadMeshHierarchyFromX(fullPath, D3DXMESH_MANAGED, g_pDevice,
		&alloc, NULL, &m_pRootFrame, &m_pAnimController);

	SetupBoneMatrixPointers(m_pRootFrame);
}

// 각 프레임의 매시 컨테이너에 있는 pSkinInfo를 이용하여 
// 현재 매쉬에 영향을 주는 프레임들의 월드행렬 포인터를 연결 
//Called to setup the pointers for a given bone to its transformation matrix
void SkinnedMesh::SetupBoneMatrixPointers(LPD3DXFRAME pFrame)
{
	if (pFrame->pMeshContainer != NULL)
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

void SkinnedMesh::SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase)
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


void SkinnedMesh::Update()
{
	Debug->AddText(_T("Anim Index = "));
	Debug->AddText((int)m_AnimaTionIndex + 1);
	Debug->AddText(_T(" / "));
	Debug->AddText((int)m_pAnimController->GetMaxNumAnimationSets());
	Debug->EndLine();
	D3DXMATRIXA16 matR;



	if (Keyboard::Get()->KeyDown('1'))
	//if (GetAsyncKeyState('1') & 0x8000)
	{
		if (m_AnimaTionIndex < m_pAnimController->GetMaxNumAnimationSets() - 1)
			m_AnimaTionIndex++;

		SetAnimationIndex(m_AnimaTionIndex, true);
	}
	else if (Keyboard::Get()->KeyDown('2'))
	//if (GetAsyncKeyState('2') & 0x8000)
	{
		if (m_AnimaTionIndex > 0)
			m_AnimaTionIndex--;

		SetAnimationIndex(m_AnimaTionIndex, true);
	}
	else if (Keyboard::Get()->KeyDown(VK_F1))
	//if (GetAsyncKeyState(VK_F1) & 0x8000)
	{
		m_bDrawFrame = !m_bDrawFrame;
	}
	else if (Keyboard::Get()->KeyDown(VK_F2))
	//if (GetAsyncKeyState(VK_F2) & 0x8000)
	{
		m_bDrawSkeleton = !m_bDrawSkeleton;
	}
	else if (Keyboard::Get()->KeyDown(VK_F3))
	//if (GetAsyncKeyState(VK_F3) & 0x8000)
	{
		m_bWireFrame = !m_bWireFrame;
	}

	Debug->AddText(m_gun_pos);
	Debug->EndLine();

	//IUnitObject::UpdateKeyboardState();
	//IUnitObject::UpdatePositionToDestination();
	

	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixScaling(&matS, SCALE, SCALE, SCALE);
	UpdateAnim();
	UpdateFrameMatrices(m_pRootFrame, NULL);

	m_matWorld = matT * matS;
}


void SkinnedMesh::UpdateAnim()
{
	float fDeltaTime = g_pTimeManager->GetDeltaTime();
	// AdvanceTime 함수가 호출된 간격으로 Anim 키프레임 계산
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

void SkinnedMesh::UpdateFrameMatrices(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	FRAME_EX* pFrameEx = (FRAME_EX*)pFrame;

	if (pFrame->Name != NULL &&  strcmp( pFrame->Name, "Bip01_L_Hand") == 0)
	{
		pFrameEx->CombinedTM  =  pFrameEx->CombinedTM * m_matWorld;
		m_gun_pos = D3DXVECTOR3(pFrameEx->CombinedTM._41, pFrameEx->CombinedTM._42, pFrameEx->CombinedTM._43);
	}

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


void SkinnedMesh::Render()
{
	m_numFrame = 0;
	m_numMesh = 0;
	Debug->AddText(_T("=====DrawFrame====="));
	Debug->EndLine();
	if (m_bDrawFrame)DrawFrame(m_pRootFrame);
	Debug->EndLine();
	Debug->AddText(_T("numFrame = "));
	Debug->AddText(m_numFrame);
	Debug->EndLine();
	Debug->AddText(_T("numMesh = "));
	Debug->AddText(m_numMesh);
	Debug->EndLine();
	if (m_bDrawSkeleton)DrawSkeleton(m_pRootFrame, NULL);
}

// Desc: Called to render a frame in the hierarchy
void SkinnedMesh::DrawFrame(LPD3DXFRAME pFrame)
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

void SkinnedMesh::DrawMeshContainer(LPD3DXFRAME pFrame)
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

void SkinnedMesh::DrawSkeleton(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
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


void SkinnedMesh::SetAnimationIndex(int nIndex, bool isBlend)
{
	LPD3DXANIMATIONSET pNextAnimSet = NULL;
	m_pAnimController->GetAnimationSet(nIndex, &pNextAnimSet);
	//isBlend = false;
	if (isBlend)
	{
		m_fPassedBlendTime = 0.0f;

		LPD3DXANIMATIONSET pPrevAnimSet = NULL;

		m_pAnimController->GetTrackAnimationSet(0, &pPrevAnimSet);
		m_pAnimController->SetTrackAnimationSet(1, pPrevAnimSet);

		D3DXTRACK_DESC trackDesc;
		m_pAnimController->GetTrackDesc(0, &trackDesc);
		m_pAnimController->SetTrackDesc(1, &trackDesc);

		m_pAnimController->SetTrackWeight(0, 0.0f);
		m_pAnimController->SetTrackWeight(1, 1.0f);

		SAFE_RELEASE(pPrevAnimSet);

		m_fPassedBlendTime = 0.0f;
	}

	m_pAnimController->SetTrackAnimationSet(0, pNextAnimSet);
	m_pAnimController->ResetTime();

	SAFE_RELEASE(pNextAnimSet);
}
