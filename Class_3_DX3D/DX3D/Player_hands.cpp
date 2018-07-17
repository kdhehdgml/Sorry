#include "stdafx.h"
#include "Player_hands.h"
#include "AllocateHierarchy.h"
#include "Camera.h"

//플레이어 스케일조정
#define SCALE 1.0f
//애니메이션 후딜레이
#define ANI_DELAY 350

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
	health = 4;
	m_pRootFrame = NULL;
	m_pAnimController = NULL;
	m_fBlendTime = 0.3f;
	m_fPassedBlendTime = 0.0f;
	m_AnimaTionIndex = 0;
	m_bWireFrame = false;
	m_bDrawFrame = true;
	m_bDrawSkeleton = false;
	m_def = 1;
	angleX = 0;
	angleY = 0;

	m_Reload = false;
	m_Render = false;
	m_zooming = false;
	CanFight = true;
	count = 0;

	pCurrAnimSet = NULL;
	pNextAnimSet = NULL;
	
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
	g_pObjMgr->AddToTagList(TAG_TEAM, this);
	m_renderMode = RenderMode::RenderMode_Lighting;
	Shaders::Get()->AddList(this, m_renderMode);

	g_pCamera->SetTarget(&m_pos);
	g_pKeyboardManager->SetMovingTarget(&m_keyState);

	D3DXCreateSphere(g_pDevice, 0.01f, 10, 10, &m_pSphereMesh, NULL);

	//Load(ASSET_PATH + _T("zealot/"), _T("zealot.X"));
	//CString path = "resources/xFile/";
	CString path = "resources/xFile/player_test/";
	CString filename = "test_player2.X";
	Load(path, filename);
	D3DXMatrixIdentity(&m_matWorld);

	
	D3DXMatrixScaling(&matS, SCALE, SCALE, SCALE);


	m_AnimaTionIndex = 기본상태;

	//처음생성시 기본설정
	m_pAnimController->GetAnimationSet(m_AnimaTionIndex, &pNextAnimSet);
	m_pAnimController->GetTrackDesc(0, &track);
	m_pAnimController->GetAnimationSet(0, &pCurrAnimSet);
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

	////액션 처음으로 초기화
	if (m_AnimaTionIndex != 달리는중 
		&& m_AnimaTionIndex != 전탄장전
		&& m_Reload == false )
		m_pAnimController->SetTrackPosition(0, 0);

	Debug->AddText("플레이어 체력: ");
	Debug->AddText(health);
	Debug->EndLine();
	//렌더 껏다키기
	if (Keyboard::Get()->KeyDown('V'))
	{
		m_Render = !m_Render;
	}

	//프리모드 아닐경우만 발동
	if (m_Render)
	{

		//상태값들
		if (Keyboard::Get()->KeyPress(VK_SHIFT))
		{
			m_AnimaTionIndex = 달리는중;
		}
		else
		{
			m_AnimaTionIndex = 기본상태;
		}

		/*Debug->AddText("시간 : ");
		Debug->AddText(GetTickCount());
		Debug->AddText("  / ");
		Debug->AddText("쿨타임 : ");
		Debug->AddText(g_pCamera->getCooldown());
		Debug->AddText("  / ");
		Debug->AddText("각도 : ");
		Debug->AddText(g_pCamera->getRecoil());
		Debug->AddText("  / ");
		Debug->AddText("재장전 상태 (0은 재장전x) : ");
		Debug->AddText(m_Reload);
		Debug->EndLine();*/

		


		//쿨타임 초기화떄, 화면각도 초기화떄
		if (g_pCamera->getCooldown() > GetTickCount()
			&& g_pCamera->getRecoil() == 0 && m_AnimaTionIndex != 달리는중)
		{
			//전탄장전할떄
			if (g_pCamera->getMagazine() == 5)
			{
				m_AnimaTionIndex = 전탄장전;
			}
			//단발일떄
			else
			{
				if(m_Reload == true)
					m_AnimaTionIndex = 볼트액션;
			}
		}

		////전탄장전
		//if (g_pCamera->getMagazine() == 5 &&
		//	g_pCamera->getRecoil() == 0)
		//{
		//	if(g_pCamera->getCooldown() > GetTickCount() )
		//			m_AnimaTionIndex = 전탄장전;
		//	
		//}
		//
		////볼트액션
		//if (g_pCamera->getCooldown() > GetTickCount() &&
		//	g_pCamera->getRecoil() == 0 &&
		//	/*m_Reload == true && */
		//	m_AnimaTionIndex != 전탄장전)
		//{
		//	m_AnimaTionIndex = 볼트액션;
		//}

	
		//업데이트 안해주면 처음값만 계속불러온다 그래서 업데이트에서 설정
		//애니메이션 컨테이너 설정
		m_pAnimController->GetTrackDesc(m_AnimaTionIndex, &track);
		m_pAnimController->GetAnimationSet(m_AnimaTionIndex, &pCurrAnimSet);

		Debug->AddText("전체시간 :");
		Debug->AddText(pCurrAnimSet->GetPeriod());
		Debug->EndLine();

		Debug->AddText("현재시간 :");
		Debug->AddText(pCurrAnimSet->GetPeriodicPosition(track.Position));
		Debug->EndLine();

		//훈회형이말한 타임 아무래도 애니메이션 전체의 타임인것같다.
		/*float total = pCurrAnimSet->GetPeriod() * pCurrAnimSet->GetNumAnimations();

		Debug->AddText("시간 :");
		Debug->AddText(total);
		Debug->EndLine();
		Debug->AddText("gettickCount :");
		Debug->AddText(GetTickCount());
		Debug->EndLine();
*/


		//현재 애니메이션의 전체타임과  현재 애니메이션 타임의 비교연산
		//현재 애니메이션 타임이 더 커지면 애니메이션 끄기
		if (pCurrAnimSet->GetPeriod() <= pCurrAnimSet->GetPeriodicPosition(track.Position) + 0.2f 
			&& m_Reload == true)
		{
			m_Reload = false;

			//SetTrackAnimationTime
			//m_pAnimController->SetTrackAnimationSet(pCurrAnimSet->GetPeriod(), pCurrAnimSet);
		}

		//Debug->AddText("잔탄 : ");
		//Debug->AddText(g_pCamera->getMagazine());
		//Debug->EndLine();

		//m_magazine = 5  최대 잔탄수
		//m_cooldown = 150 최대 쿨타임

		if (!m_Reload && m_zooming && m_AnimaTionIndex == 기본상태 
			/*&& (m_AnimaTionIndex!= 볼트액션 || m_AnimaTionIndex != 전탄장전)*/ )
		{
			//if (g_pCamera->getRecoil() == 0)
				m_AnimaTionIndex = 줌_모드;
		}

		
		SetAnimationIndex(m_AnimaTionIndex, true);
		

		SetPosToCamera();
	}
}

void Player_hands::Render()
{
	if (m_renderMode != RenderMode_Default) return;
	{
		if (m_Render)
		{
			m_numFrame = 0;
			m_numMesh = 0;
			//팔짤리는거 방지용으로 컬모즈를 잠시 제거함
			g_pDevice->SetRenderState(D3DRS_CULLMODE, false);

			if (m_bDrawFrame)DrawFrame(m_pRootFrame);
			//if (m_bDrawSkeleton)DrawSkeleton(m_pRootFrame, NULL);

			//컬모드 원래대로 돌려주는것
			g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		}
	}

}

void Player_hands::RenderUseShader_0()
{
	if (m_bDrawFrame)DrawFrame(m_pRootFrame);

}

void Player_hands::RenderUseShader_1()
{
	if (m_bDrawFrame)DrawFrame(m_pRootFrame);//if (m_pSubRootFrame) if (m_bDrawFrame)DrawFrame(m_pSubRootFrame);
}

void Player_hands::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		if (!m_Reload && g_pCamera->getCooldown() < GetTickCount())
		{
			m_Reload = true;
		}
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
	// AdvanceTime  메쉬를 애니메이션화하고 전역 애니메이션 시간을 지정된 양만큼 전진시킵니다.
	//전역 애니메이션 시간을 앞당길 양 (초). TimeDelta 값은 음수가 아니거나 0이어야합니다.
	m_pAnimController->AdvanceTime(fDeltaTime, NULL);


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

	if (m_renderMode == RenderMode::RenderMode_Default)
	{
		g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
		//g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

		for (size_t i = 0; i < pMeshContainerEx->vecMtlTex.size(); ++i)
		{
			g_pDevice->SetMaterial(&pMeshContainerEx->vecMtlTex[i]->GetMaterial());
			g_pDevice->SetTexture(0, pMeshContainerEx->vecMtlTex[i]->GetTexture());
			pMeshContainerEx->pWorkMesh->DrawSubset(i);
		}
	}
	else if (m_renderMode == RenderMode::RenderMode_Lighting)
	{
		for (size_t i = 0; i < pMeshContainerEx->vecMtlTex.size(); ++i)
		{
			Shaders::Get()->GetCurrentShader()->SetWorldMatrix(&m_matWorld);
			Shaders::Get()->GetCurrentShader()->SetTexture(pMeshContainerEx->vecMtlTex[i]->pTexture);
			Shaders::Get()->GetCurrentShader()->SetMaterial(&pMeshContainerEx->vecMtlTex[i]->material);
			Shaders::Get()->GetCurrentShader()->Commit();
			pMeshContainerEx->pWorkMesh->DrawSubset(i);
		}
	}
	else if (m_renderMode == RenderMode::RenderMode_ShadowMapping)
	{
		for (size_t i = 0; i < pMeshContainerEx->vecMtlTex.size(); ++i)
		{
			Shaders::Get()->GetCurrentShader()->SetWorldMatrix(&m_matWorld);
			Shaders::Get()->GetCurrentShader()->SetTexture(pMeshContainerEx->vecMtlTex[i]->pTexture);
			Shaders::Get()->GetCurrentShader()->SetMaterial(&pMeshContainerEx->vecMtlTex[i]->material);
			Shaders::Get()->GetCurrentShader()->Commit();
			pMeshContainerEx->pWorkMesh->DrawSubset(i);
		}
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
	//m_pos.z += 3.5f;
	//m_pos.y -= 1.5f;

	D3DXVECTOR3 dir = g_pCamera->getDir();

	angleX = atan(dir.y); //카메라 방향벡터의 역함수를 구함
	angleY = asin(dir.x) * -1;

	if (dir.z > 0) { //90~270도 사이일때
		angleY = D3DX_PI - angleY; //역방향을 취함
	} //역삼각함수가 단사함수가 아니기 때문에 해야 하는 연산들

	//IUnitObject::UpdateKeyboardState();
	//IUnitObject::UpdatePositionToDestination();

	D3DXMATRIXA16 matR_X, matR_Y;

	D3DXMatrixRotationX(&matR_X, angleX);
	D3DXMatrixRotationY(&matR_Y, angleY);

	matR = matR_X * matR_Y;


	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixScaling(&matS, SCALE, SCALE, SCALE);
	UpdateAnim();
	UpdateFrameMatrices(m_pRootFrame, NULL);

	m_matWorld = matS * matR * matT;
}

void Player_hands::SetAnimationIndex(int nIndex, bool isBlend)
{
	//LPD3DXANIMATIONSET pNextAnimSet = NULL;
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
		/*D3DXTRACK_DESC track;
		
		LPD3DXANIMATIONSET pCurrAnimSet = NULL;
		*/
		m_pAnimController->GetTrackDesc(0, &track);
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



	/*	if (pCurrAnimSet->GetPeriod() <= pCurrAnimSet->GetPeriodicPosition(track.Position) )
		{
			isBlend = false;
			m_pAnimController->SetTrackPosition(0, 0);
		}*/
			
		pCurrAnimSet->Release();

		m_fPassedBlendTime = 0.0f;
		
	}

	
	m_pAnimController->SetTrackAnimationSet(0, pNextAnimSet);
	//SetTrackPosition
	m_pAnimController->ResetTime();

	SAFE_RELEASE(pNextAnimSet);
}