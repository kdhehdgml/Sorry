#include "stdafx.h"
#include "MONSTER.h"
#include "AllocateHierarchy.h"

//적군 스킨 사이즈 조절
#define SCALE 0.02f
//#define SCALE 0.002f


MONSTER::MONSTER()
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
	m_pos = D3DXVECTOR3(0,0,0);

	m_animationSTATE = true;

	pCurrAnimSet = NULL;
	pNextAnimSet = NULL;

	STATE = true;
}


MONSTER::~MONSTER()
{
	SAFE_RELEASE(m_pSphereMesh);
	AllocateHierarchy alloc;
	D3DXFrameDestroy(m_pRootFrame, &alloc);

	SAFE_RELEASE(m_pAnimController);
}

void MONSTER::Init()
{

	D3DXCreateSphere(g_pDevice, 0.01f, 10, 10, &m_pSphereMesh, NULL);

	//Load(ASSET_PATH + _T("zealot/"), _T("zealot.X"));
	//CString path = "resources/xFile/";
	CString path = "resources/xFile/MONSTER_AI/";
	CString filename = "MOB_ANI_ALL2.X";
	Load(path, filename);
	D3DXMatrixIdentity(&m_matWorld);

	//m_angle = D3DX_PI / 2;

	
	D3DXMatrixScaling(&matS, SCALE, SCALE, SCALE);

	//처음생성시 기본설정
	m_pAnimController->GetAnimationSet(m_AnimaTionIndex, &pNextAnimSet);
	m_pAnimController->GetTrackDesc(0, &track);
	m_pAnimController->GetAnimationSet(0, &pCurrAnimSet);

	RotSpeed = 2.0f;
}

void MONSTER::Update()
{

	if (STATE)
	{

		D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);

		UpdateAnim();
		UpdateFrameMatrices(m_pRootFrame, NULL);
		//
		//Debug->AddText("매트릭스 각도 : ");
		//Debug->AddText(m_angle);
		//Debug->EndLine();
		
		/*Debug->AddText("매트릭스 각도 : ");
		Debug->AddText(m_angle);
		Debug->EndLine();*/

		D3DXMatrixRotationY(&matR, m_angle);
		m_matWorld = matS * matR * matT;

		m_pAnimController->GetTrackDesc(m_AnimaTionIndex, &track);
		m_pAnimController->GetAnimationSet(m_AnimaTionIndex, &pCurrAnimSet);

		//Debug->AddText("애니 인덱스 : ");
		//Debug->AddText(m_AnimaTionIndex);
		//Debug->EndLine();

		//if (Keyboard::Get()->KeyDown('F7'))
		//{
		//	m_AnimaTionIndex++;

		//	if (m_AnimaTionIndex > 9)
		//		m_AnimaTionIndex = 0;
		//}

		//if (pCurrAnimSet->GetPeriod() <= pCurrAnimSet->GetPeriodicPosition(track.Position) + 0.1f &&
		//	m_AnimaTionIndex == 4)
		//{

		//	//트랙속도 감소!
		//	m_pAnimController->SetTrackSpeed(0, 0);
		//	
		//}
		//나중에 다시 불러올떄 1로 다시해주면 속도가 돌아온다
		//m_pAnimController->SetTrackSpeed(0, 1);

		//
		//Debug->AddText("애니메이션 On/Off : ");
		//Debug->AddText(m_animationSTATE);
		//Debug->EndLine();


		/*디버그모드
		
		
		
		*/
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

		if (m_AnimaTionIndex == 몹_달리다가죽기 || m_AnimaTionIndex == 몹_죽음)
		{
			if (pCurrAnimSet->GetPeriod() <= pCurrAnimSet->GetPeriodicPosition(track.Position) + 0.1f)
			{
				//트랙속도 감소!
				m_pAnimController->SetTrackSpeed(0, 0);
			}
		}
		else
		{
			m_pAnimController->SetTrackSpeed(0, 1);
		}

	SetAnimationIndex(m_AnimaTionIndex, true);


	}

}

void MONSTER::Render()
{

	m_numFrame = 0;
	m_numMesh = 0;

	if (m_bDrawFrame && STATE)DrawFrame(m_pRootFrame);
//	if (m_bDrawSkeleton)DrawSkeleton(m_pRootFrame, NULL);
}

void MONSTER::Load(LPCTSTR path, LPCTSTR filename)
{
	AllocateHierarchy alloc(path);

	CString fullPath(path);
	fullPath.Append(filename);

	D3DXLoadMeshHierarchyFromX(fullPath, D3DXMESH_MANAGED, g_pDevice,
		&alloc, NULL, &m_pRootFrame, &m_pAnimController);

	SetupBoneMatrixPointers(m_pRootFrame);
}

void MONSTER::SetupBoneMatrixPointers(LPD3DXFRAME pFrame)
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

void MONSTER::SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase)
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

void MONSTER::UpdateAnim()
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

void MONSTER::UpdateFrameMatrices(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	FRAME_EX* pFrameEx = (FRAME_EX*)pFrame;

	pFrameEx->CombinedTM = pFrameEx->CombinedTM * m_matWorld;
	
	if (pFrame->Name != NULL && strcmp(pFrame->Name, "mixamorig_LeftHandMiddle1") == 0)
	{
		/*pFrameEx->CombinedTM  =  pFrameEx->CombinedTM */
		m_L_mat = pFrameEx->CombinedTM * m_matWorld;
		m_L_pos = D3DXVECTOR3(pFrameEx->CombinedTM._41, pFrameEx->CombinedTM._42, pFrameEx->CombinedTM._43);
	}
	else if (pFrame->Name != NULL && strcmp(pFrame->Name, "mixamorig_RightHandMiddle1") == 0)
	{
		//D3DXMATRIXA16 matT;
		//D3DXMatrixTranslation(&matT,0.f,100.f,0.f);
		//m_R_mat 순수 행렬
		m_R_mat = pFrameEx->CombinedTM  * m_matWorld;
		//m_R_pos 행렬의 좌표값(이동값) 즉 matT
		m_R_pos = D3DXVECTOR3(pFrameEx->CombinedTM._41, pFrameEx->CombinedTM._42, pFrameEx->CombinedTM._43);

		//D3DXQUATERNION				m_quat;
		//m_scaleMat = matS;
		D3DXMatrixIdentity(&m_rotMat);
		GetScaleAndRotation(m_R_mat, &m_scaleMat, m_rotMat);
		

		//D3DXVec3TransformCoord(&vDirAxis, &vDirAxis, &m_rotMat); //위에서 구한 회전행렬 * 임의의축(vDirAxis)을 해서 최종 축을 구한다

		//D3DXQuaternionNormalize(&m_quat, &m_quat);        //노멀라이징

		//D3DXMatrixRotationQuaternion(&m_rotMat, &m_quat);   //최종구한 쿼터니안 만큼 회전 행렬을 구한다

		//m_rotMat = 회전행렬값 즉 matR

	}
	//else if (pFrame->Name != NULL && strcmp(pFrame->Name, "Bip01_R_Hand") == 0)
	//{
	//	m_R_mat = pFrameEx->CombinedTM * m_matWorld;
	//	m_R_pos = D3DXVECTOR3(pFrameEx->CombinedTM._41, pFrameEx->CombinedTM._42, pFrameEx->CombinedTM._43);
	//}
	else if (pFrame->Name != NULL && strcmp(pFrame->Name, "mixamorig_Head") == 0)
	{
		m_head_mat = pFrameEx->CombinedTM * m_matWorld;
		//m_R_pos = D3DXVECTOR3(pFrameEx->CombinedTM._41, pFrameEx->CombinedTM._42, pFrameEx->CombinedTM._43);
	}
	else if (pFrame->Name != NULL && strcmp(pFrame->Name, "mixamorig_RightPinky3") == 0)
	{
		m_head_mat2 = pFrameEx->CombinedTM * m_matWorld;
		//m_R_pos = D3DXVECTOR3(pFrameEx->CombinedTM._41, pFrameEx->CombinedTM._42, pFrameEx->CombinedTM._43);
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

void MONSTER::DrawFrame(LPD3DXFRAME pFrame)
{
	m_numFrame++;
	//디버그모드
	//if (m_numFrame % 5 == 0)
	//{
	//	Debug->EndLine();
	//}
	//if (pFrame->Name == NULL)
	//	Debug->AddText(_T("NULL"));
	//else
	//	Debug->AddText(pFrame->Name);

	LPD3DXMESHCONTAINER pMeshContainer = pFrame->pMeshContainer;
	while (pMeshContainer != NULL)
	{
		m_numMesh++;
		//디버그모드
		//Debug->AddText(_T("(MESH)"));
		DrawMeshContainer(pFrame);
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}
	//디버그모드
	//Debug->AddText(_T(" / "));
	if (pFrame->pFrameSibling != NULL)
	{
		DrawFrame(pFrame->pFrameSibling);
	}

	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawFrame(pFrame->pFrameFirstChild);
	}
}

void MONSTER::DrawMeshContainer(LPD3DXFRAME pFrame)
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

void MONSTER::DrawSkeleton(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
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
//
//void MONSTER::GetScaleAndRotation(const D3DXMATRIX & val, D3DXVECTOR3 * OutScale, D3DXQUATERNION * OutRotation)
//{
//	const D3DXVECTOR3 s(
//		D3DXVec3Length(&D3DXVECTOR3(val._11, val._12, val._13)),
//		D3DXVec3Length(&D3DXVECTOR3(val._21, val._22, val._23)),
//		D3DXVec3Length(&D3DXVECTOR3(val._31, val._32, val._33)));
//
//	if (OutScale)
//		*OutScale = s;
//
//	if (OutRotation)
//	{
//		D3DXQuaternionRotationMatrix(
//			OutRotation,
//			&D3DXMATRIX(
//				val._11 / s.x, val._12 / s.x, val._13 / s.x, 0.0f,
//				val._21 / s.y, val._22 / s.y, val._23 / s.y, 0.0f,
//				val._31 / s.z, val._32 / s.z, val._33 / s.z, 0.0f,
//				0.0f, 0.0f, 0.0f, 1.0f));
//	}
//
//}

void MONSTER::SetAnimationIndex(int nIndex, bool isBlend)
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


		//Debug->AddText("전체시간 :");
		//Debug->AddText(pCurrAnimSet->GetPeriod());
		//Debug->EndLine();

		//Debug->AddText("현재시간 :");
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
