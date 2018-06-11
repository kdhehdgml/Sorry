#include "stdafx.h"
#include "Monster.h"
#include "AllocateHierarchy.h"



Monster::Monster()
{
	m_baseRotY = D3DX_PI;

	m_pRootFrame = NULL;
	m_pAnimController = NULL;
	m_fBlendTime = 0.3f;
	m_fPassedBlendTime = 0.0f;
	m_animIndex = 0;
	m_bWireFrame = false;
	m_bDrawFrame = true;
	m_bDrawSkeleton = false;


}


Monster::~Monster()
{
	SAFE_RELEASE(m_pSphereMesh);
	AllocateHierarchy alloc;
	D3DXFrameDestroy(m_pRootFrame, &alloc);

	SAFE_RELEASE(m_pAnimController);
}

void Monster::Init()
{
}

void Monster::Update()
{
}

void Monster::Render()
{
}

void Monster::Load(LPCTSTR path, LPCTSTR filename)
{
}

void Monster::SetupBoneMatrixPointers(LPD3DXFRAME pFrame)
{
}

void Monster::SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase)
{
}

void Monster::UpdateAnim()
{
}

void Monster::UpdateFrameMatrices(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
}

void Monster::DrawFrame(LPD3DXFRAME pFrame)
{
}

void Monster::DrawMeshContainer(LPD3DXFRAME pFrame)
{
}

void Monster::DrawSkeleton(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
}

void Monster::SetAnimationIndex(int nIndex, bool isBlend)
{
}
