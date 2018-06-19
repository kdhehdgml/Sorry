﻿#include "stdafx.h"
#include "Player_hands.h"
#include "AllocateHierarchy.h"
#include "Camera.h"

#define SCALE 5.0f

/*

	D3DXTRACK_DESC track;
	m_pAnimController->GetTrackDesc(0, &track);
	LPD3DXANIMATIONSET pCurrAnimSet = NULL;
	m_pAnimController->GetAnimationSet(0, &pCurrAnimSet);

	//전체 시간
	pCurrAnimSet->GetPeriod(); 

	//현재 시간
	pCurrAnimSet->GetPeriodicPosition(track.Position); 
	pCurrAnimSet->Release();
*/

Player_hands::Player_hands()
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

	angleX = 0;
	angleY = 0;

	m_Reload = false;
	m_Render = false;
	m_zooming = false;

	count = 0;
}


Player_hands::~Player_hands()
{
	SAFE_RELEASE(m_pSphereMesh);
	AllocateHierarchy alloc;
	D3DXFrameDestroy(m_pRootFrame, &alloc);

	SAFE_RELEASE(m_pAnimController);
}

void Player_hands::Init()
{
	g_pCamera->SetTarget(&m_pos);
	g_pKeyboardManager->SetMovingTarget(&m_keyState);

	D3DXCreateSphere(g_pDevice, 0.01f, 10, 10, &m_pSphereMesh, NULL);

	//Load(ASSET_PATH + _T("zealot/"), _T("zealot.X"));
	//CString path = "resources/xFile/";
	CString path = "resources/xFile/player_ani/";
	CString filename = "player_hands_ani.X";
	Load(path, filename);
	D3DXMatrixIdentity(&m_matWorld);

	
	D3DXMatrixScaling(&matS, SCALE, SCALE, SCALE);

	m_AnimaTionIndex = 6;

}


void Player_hands::Load(LPCTSTR path, LPCTSTR filename)
{
	AllocateHierarchy alloc(path);

	CString fullPath(path);
	fullPath.Append(filename);

	D3DXLoadMeshHierarchyFromX(fullPath, D3DXMESH_MANAGED, g_pDevice,
		&alloc, NULL, &m_pRootFrame, &m_pAnimController);

	SetupBoneMatrixPointers(m_pRootFrame);
}


void Player_hands::Update()
{
	//렌더 껏다키기
	if (Keyboard::Get()->KeyDown('V'))
	{
		m_Render = !m_Render;
	}

	//프리모드 아닐경우만 발동
	if (m_Render)
	{

		//상태값들
		if (Keyboard::Get()->KeyDown(VK_SHIFT))
		{
			m_AnimaTionIndex = 달리기준비;
		}
		else if (Keyboard::Get()->KeyPress(VK_SHIFT))
		{
			m_AnimaTionIndex = 달리는중;
		}
		else if (Keyboard::Get()->KeyUp(VK_SHIFT))
		{
			m_AnimaTionIndex = 달리기해제;
		}
		else
		{
			if(!m_Reload)
				m_AnimaTionIndex = 기본상태;
		}

		if (m_Reload)
		{
			count++;
			Debug->AddText("재장전시간 : ");
			Debug->AddText(count);
			Debug->EndLine();

			if (count == 75)
				m_Reload = false;
		}
		else
		{
			count = 0;
		}

		if (!m_Reload && m_zooming)
			m_AnimaTionIndex = 줌_모드;


	/*	Debug->AddText("줌인 상태");
		Debug->AddText(m_zooming);
		Debug->EndLine();*/



		SetAnimationIndex(m_AnimaTionIndex, true);

		SetPosToCamera();
	}
}

void Player_hands::Render()
{
	if (m_Render)
	{
		m_numFrame = 0;
		m_numMesh = 0;



		if (m_bDrawFrame)DrawFrame(m_pRootFrame);
		//if (m_bDrawSkeleton)DrawSkeleton(m_pRootFrame, NULL);
	}
}

void Player_hands::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_Reload = true;
		m_AnimaTionIndex = 볼트액션;
		//액션 처음으로 초기화
		m_pAnimController->SetTrackPosition(0, 0);
	}
	break;
	case WM_LBUTTONUP:
	{
		
	}
	break;
	case WM_RBUTTONDOWN:
		
		m_zooming = true;
		break;
	case WM_RBUTTONUP:
		
		m_zooming = false;
		break;
	case WM_MOUSEMOVE:
	{


	}break;
	case WM_MOUSEWHEEL:

		break;
	}
}

void Player_hands::SetupBoneMatrixPointers(LPD3DXFRAME pFrame)
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

void Player_hands::SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase)
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

void Player_hands::UpdateAnim()
{
	float fDeltaTime = g_pTimeManager->GetDeltaTime();
	// AdvanceTime 
	m_pAnimController->AdvanceTime(fDeltaTime, NULL);
	//Debug->AddText("델타 타임: ");
	//Debug->AddText(fDeltaTime);
	//Debug->EndLine();
	//printf("델타 타임 : %f \n", fDeltaTime);

	if (m_fPassedBlendTime <= m_fBlendTime)
	{
		m_fPassedBlendTime += fDeltaTime;

		if (m_fPassedBlendTime < m_fBlendTime)
		{
			float fWeight = m_fPassedBlendTime / m_fBlendTime;

			//fWeight = 애니메이션 셋 트랙 두개를 보간해주는 가중치
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

void Player_hands::UpdateFrameMatrices(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
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

void Player_hands::DrawFrame(LPD3DXFRAME pFrame)
{
	m_numFrame++;


	LPD3DXMESHCONTAINER pMeshContainer = pFrame->pMeshContainer;
	while (pMeshContainer != NULL)
	{
		m_numMesh++;

		DrawMeshContainer(pFrame);
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}


	if (pFrame->pFrameSibling != NULL)
	{
		DrawFrame(pFrame->pFrameSibling);
	}

	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawFrame(pFrame->pFrameFirstChild);
	}
}

void Player_hands::DrawMeshContainer(LPD3DXFRAME pFrame)
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

void Player_hands::DrawSkeleton(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
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

void Player_hands::SetPosToCamera()
{
	m_pos = Camera::GetInstance()->getPos();
	//m_pos.x -= 0.1f;
	m_pos.y -= 3.5f;
	angleX = (Camera::GetInstance()->getAngleX());
	angleY = (Camera::GetInstance()->getAngleY()) - D3DX_PI;


	//IUnitObject::UpdateKeyboardState();
	//IUnitObject::UpdatePositionToDestination();
	D3DXMATRIXA16 matR_X, matR_Y;

	D3DXMatrixRotationX(&matR_X, angleX);
	D3DXMatrixRotationY(&matR_Y, angleY);

	matR = matR_X * matR_Y;


	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	//D3DXMatrixScaling(&matS, SCALE, SCALE, SCALE);
	UpdateAnim();
	UpdateFrameMatrices(m_pRootFrame, NULL);

	m_matWorld = matS * matR * matT;
}

void Player_hands::SetAnimationIndex(int nIndex, bool isBlend)
{
	LPD3DXANIMATIONSET pNextAnimSet = NULL;
	m_pAnimController->GetAnimationSet(nIndex, &pNextAnimSet);

	//애니메이션 이름으로 호출가능. ㅠㅠ
	//stand_idle
	//m_pAnimController->GetAnimationSetByName("stand_idle",&pNextAnimSet)

	//Debug->AddText("애니메이션 이름 : ");
	//Debug->AddText();
	//Debug->EndLine();

	//isBlend = false;
	if (isBlend)
	{
		//애니메이션 시간으로 지정!
	//	m_pAnimController->SetTrackPosition(0, count);

	//Debug->AddText("애니메이션 시간? : ");
	//Debug->AddText(m_pAnimController->GetTime());
	//Debug->EndLine();
		
	//m_pAnimController->SetTrackPosition(0, count);

		m_fPassedBlendTime = 0.0f;

		LPD3DXANIMATIONSET pPrevAnimSet = NULL;

		m_pAnimController->GetTrackAnimationSet(0, &pPrevAnimSet);
		m_pAnimController->SetTrackAnimationSet(1, pPrevAnimSet);

		D3DXTRACK_DESC trackDesc;
		m_pAnimController->GetTrackDesc(0, &trackDesc);
		m_pAnimController->SetTrackDesc(1, &trackDesc);
		
	/*	Debug->AddText("트랙데스트 :");
		Debug->AddText(trackDesc.Position);
		Debug->EndLine();*/


		//시간 재기용
		D3DXTRACK_DESC track;
		m_pAnimController->GetTrackDesc(0, &track);
		LPD3DXANIMATIONSET pCurrAnimSet = NULL;
		m_pAnimController->GetAnimationSet(0, &pCurrAnimSet);

		////전체 시간
		//
		//pCurrAnimSet->GetPeriod();

		////현재 시간
		//pCurrAnimSet->GetPeriodicPosition(track.Position);
		//

		m_pAnimController->SetTrackWeight(0, 0.0f);
		m_pAnimController->SetTrackWeight(1, 1.0f);

		SAFE_RELEASE(pPrevAnimSet);

		Debug->AddText("전체시간 :");
		Debug->AddText(pCurrAnimSet->GetPeriod());
		Debug->EndLine();

		Debug->AddText("현재시간 :");
		Debug->AddText(pCurrAnimSet->GetPeriodicPosition(track.Position));
		Debug->EndLine();


		if (pCurrAnimSet->GetPeriod() <= pCurrAnimSet->GetPeriodicPosition(track.Position) + 0.1f)
		{
			m_pAnimController->SetTrackPosition(0, 0);
		}
			
		pCurrAnimSet->Release();

		m_fPassedBlendTime = 0.0f;
		
	}

	
	m_pAnimController->SetTrackAnimationSet(0, pNextAnimSet);
	//SetTrackPosition
	m_pAnimController->ResetTime();

	SAFE_RELEASE(pNextAnimSet);
}