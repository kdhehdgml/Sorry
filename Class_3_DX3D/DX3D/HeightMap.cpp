#include "stdafx.h"
#include "HeightMap.h"
#include "Ray.h"
#include "AStar.h"
#include "AStarNode.h"

HeightMap::HeightMap()
{
	m_pMesh = NULL;
	m_pMtlTex = NULL;
	AStarNodeRenderOn = false;
	TabKeyDownCheck = false;
}


HeightMap::~HeightMap()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMtlTex);
	SAFE_RELEASE(m_pAStar);
}

void HeightMap::Load(const char * fullPath, D3DXMATRIXA16 * pMat)
{
	vector<VERTEX_PNT> vecVertex;
	vecVertex.resize(m_dimension * m_dimension);
	m_vecVertex.resize(m_dimension * m_dimension);

	std::ifstream fin(fullPath, std::ios::binary);

	for (int z = 0; z < m_dimension; z++)
	{
		for (int x = 0; x < m_dimension; x++)
		{
			int index = z * m_dimension + x;
			int y = fin.get();
			vecVertex[index].p = D3DXVECTOR3(x, y, z);
			vecVertex[index].n = D3DXVECTOR3(0, 1, 0);
			vecVertex[index].t = 
				D3DXVECTOR2(x / (float)m_numTile, 
					1 - (z / (float)m_numTile));

			if (pMat != NULL)
			{
				D3DXVec3TransformCoord(&vecVertex[index].p, 
					&vecVertex[index].p, pMat);
			}

			m_vecVertex[index] = vecVertex[index].p;
		}
	}

	fin.close();

	if (pMat != NULL)
	{
		m_scale.x = pMat->_11;
		m_scale.z = pMat->_33;
	}
	m_size.x = m_numTile * m_scale.x;
	m_size.z = m_numTile * m_scale.z;

	//set index
	vector<DWORD> vecIndex;
	vecIndex.reserve(m_numTile * m_numTile * 3 * 2);

	for (int z = 0; z < m_numTile; z++)
	{
		for (int x = 0; x < m_numTile; x++)
		{
			// 1--3
			// 0--2
			int _0 = (z + 0) * m_dimension + x + 0;
			int _1 = (z + 1) * m_dimension + x + 0;
			int _2 = (z + 0) * m_dimension + x + 1;
			int _3 = (z + 1) * m_dimension + x + 1;

			vecIndex.push_back(_0);
			vecIndex.push_back(_1);
			vecIndex.push_back(_2);
			vecIndex.push_back(_2);
			vecIndex.push_back(_1);
			vecIndex.push_back(_3);
		}
	}
	//set normal
	for (int z = 1; z < m_numTile; z++)
	{
		for (int x = 1; x < m_numTile; x++)
		{
			//--u--
			//l-n-r
			//--d--
			int index = z * m_dimension + x;

			int l = index - 1;
			int r = index + 1;
			int u = index + m_dimension;
			int d = index - m_dimension;

			D3DXVECTOR3 du = m_vecVertex[u] - m_vecVertex[d];
			D3DXVECTOR3 lr = m_vecVertex[r] - m_vecVertex[l];
			D3DXVECTOR3 n;
			D3DXVec3Cross(&n, &du, &lr);
			D3DXVec3Normalize(&n, &n);

			vecVertex[index].n = n;
		}
	}

	D3DXCreateMeshFVF(vecIndex.size() / 3, vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT, VERTEX_PNT::FVF,
		g_pDevice, &m_pMesh);

	VERTEX_PNT* pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(VERTEX_PNT));
	m_pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
	m_pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	m_pMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, (vecIndex.size() / 3) * sizeof(DWORD));
	m_pMesh->UnlockAttributeBuffer();

	vector<DWORD> vecAdjBuffer(m_pMesh->GetNumFaces() * 3);
	m_pMesh->GenerateAdjacency(FLT_EPSILON, &vecAdjBuffer[0]);
	m_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
		&vecAdjBuffer[0], 0, 0, 0);
}

void HeightMap::SetMtlTex(D3DMATERIAL9 & mtl, LPDIRECT3DTEXTURE9 pTex)
{
	m_pMtlTex = new MTLTEX;
	m_pMtlTex->SetMaterial(mtl);
	m_pMtlTex->SetTexture(pTex);
}

void HeightMap::Init()
{
	m_pAStar = new AStar(); m_pAStar->Init(); m_pAStar->InitNodes(this);
	SetSurface();
	//SetObstacle();
	//m_pAStar->SetObstacle(m_vecObstacleVertex);
	GetWall(m_pAStar->GetWallLocation());
}

void HeightMap::Update()
{
	// TAB 키 누르면 AStarNode 렌더 ON / OFF
	if ((GetKeyState(VK_TAB) & 0x8000))
	{
		if (!TabKeyDownCheck)
		{
			TabKeyDownCheck = true;

			if (!AStarNodeRenderOn)
				AStarNodeRenderOn = true;
			else
				AStarNodeRenderOn = false;
		}
	}
	else if (TabKeyDownCheck)
		TabKeyDownCheck = false;	
}

void HeightMap::Render()
{

	g_pDevice->SetRenderState(D3DRS_FOGENABLE, true);
	g_pDevice->SetRenderState(D3DRS_FOGCOLOR, 0xffbbbbbb);
	g_pDevice->SetRenderState(D3DRS_FOGDENSITY, FtoDw(0.1f)); //강도 0~1f
	//안개적용되는 최소 거리
	g_pDevice->SetRenderState(D3DRS_FOGSTART, FtoDw(20.0f));
	//안개 최대치로 적용되는 거리
	g_pDevice->SetRenderState(D3DRS_FOGEND, FtoDw(40.0f));
	g_pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);

	//g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetMaterial(&m_pMtlTex->GetMaterial());
	g_pDevice->SetTexture(0, m_pMtlTex->GetTexture());
	m_pMesh->DrawSubset(0);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	
	// AStarNode 렌더
	if(AStarNodeRenderOn)
		SAFE_RENDER(m_pAStar);

	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	D3DMATERIAL9 mtl = DXUtil::BLUE_MTRL;
	mtl.Diffuse.a = 0.3f;
	g_pDevice->SetMaterial(&mtl);
	
	//g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
	//	m_vecSurfaceVertex.size() / 3,
	//	&m_vecSurfaceVertex[0], sizeof(D3DXVECTOR3));
		
	/*g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecObstacleVertex.size() / 3, &m_vecObstacleVertex[0],
		sizeof(D3DXVECTOR3));*/

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pDevice->SetRenderState(D3DRS_FOGENABLE, false);
}

bool HeightMap::GetHeight(OUT float & height, const D3DXVECTOR3 & pos)
{
	if (pos.x < 0 || pos.z < 0 ||
		pos.x > m_size.x || pos.z > m_size.z)
	{
		height = 0;
		return false;
	}
	// 1--3
	// |  |
	// 0--2
	int nX = (int)(pos.x / m_scale.x);
	int nZ = (int)(pos.z / m_scale.z);
	float deltaX = (pos.x / m_scale.x) - nX;
	float deltaZ = (pos.z / m_scale.z) - nZ;

	int _0 = (nZ + 0) * m_dimension + nX + 0;
	int _1 = (nZ + 1) * m_dimension + nX + 0;
	int _2 = (nZ + 0) * m_dimension + nX + 1;
	int _3 = (nZ + 1) * m_dimension + nX + 1;

	if (deltaX + deltaZ < 1.0f)
	{
		float zY = m_vecVertex[_1].y - m_vecVertex[_0].y;
		float xY = m_vecVertex[_2].y - m_vecVertex[_0].y;

		height = m_vecVertex[_0].y + zY * deltaZ + xY * deltaX;
	}
	else
	{
		deltaX = 1 - deltaX;
		deltaZ = 1 - deltaZ;

		float zY = m_vecVertex[_1].y - m_vecVertex[_3].y;
		float xY = m_vecVertex[_2].y - m_vecVertex[_3].y;

		height = m_vecVertex[_3].y + zY * deltaZ + xY * deltaX;
	}

	return true;
}

bool HeightMap::CalcPickedPosition(D3DXVECTOR3 & vOut, WORD screenX, WORD screenY)
{
	Ray ray = Ray::RayAtWorldSpace(screenX, screenY);
	float minDist = FLT_MAX;
	float intersectionDist;
	bool bIntersect = false;

	for (int i = 0; i < m_vecSurfaceVertex.size(); i += 3)
	{
		if (ray.CalcIntersectTri(
			&m_vecSurfaceVertex[i], &intersectionDist))
		{
			if (intersectionDist < minDist)
			{
				bIntersect = true;
				minDist = intersectionDist;
				vOut = ray.m_pos + ray.m_dir * intersectionDist;
			}
		}
	}

	return bIntersect;
}

void HeightMap::SetSurface()
{
	vector<D3DXVECTOR3> vecPos;
	vector<DWORD>		vecIndex;

	int surfaceDim = 5;
	int numSurfaceTile = surfaceDim - 1;

	vecPos.reserve(surfaceDim * surfaceDim);
	for (size_t z = 0; z < surfaceDim; z++)
	{
		for (size_t x = 0; x < surfaceDim; x++)
		{
			DWORD index = z / (float)numSurfaceTile *
				m_numTile * m_dimension
				+ x / (float)numSurfaceTile * m_numTile;
			vecPos.push_back(m_vecVertex[index]);
		}
	}

	vecIndex.reserve(numSurfaceTile * numSurfaceTile * 2 * 3);
	for (size_t z = 0; z < numSurfaceTile; z++)
	{
		for (size_t x = 0; x < numSurfaceTile; x++)
		{
			//1--3
			//|--|
			//0--2
			DWORD _0 = (z + 0) * surfaceDim + x + 0;
			DWORD _1 = (z + 1) * surfaceDim + x + 0;
			DWORD _2 = (z + 0) * surfaceDim + x + 1;
			DWORD _3 = (z + 1) * surfaceDim + x + 1;

			vecIndex.push_back(_0);
			vecIndex.push_back(_1);
			vecIndex.push_back(_2);
			vecIndex.push_back(_2);
			vecIndex.push_back(_1);
			vecIndex.push_back(_3);
		}
	}

	for (size_t i = 0; i < vecIndex.size(); i++)
	{
		m_vecSurfaceVertex.push_back(vecPos[vecIndex[i]]);
	}
}

void HeightMap::SetObstacle()
{
	float posX = m_pAStar->GetNodes()[2]->GetLocation().x - 0.7f;
	float posZ = m_pAStar->GetNodes()[30 * 4 + 2]
		->GetLocation().z + 0.9f;
	float height = 6;

	m_vecObstacleVertex.push_back(D3DXVECTOR3(posX, 3, posZ));
	m_vecObstacleVertex.push_back(D3DXVECTOR3(posX, height, 0));
	m_vecObstacleVertex.push_back(D3DXVECTOR3(posX, 3, 0));

	m_vecObstacleVertex.push_back(D3DXVECTOR3(posX, 3, posZ));
	m_vecObstacleVertex.push_back(D3DXVECTOR3(posX, height, posZ));
	m_vecObstacleVertex.push_back(D3DXVECTOR3(posX, height, 0));

	posX += 1.4f;
	m_vecObstacleVertex.push_back(D3DXVECTOR3(posX, 3, posZ));
	m_vecObstacleVertex.push_back(D3DXVECTOR3(posX, height, 0));
	m_vecObstacleVertex.push_back(D3DXVECTOR3(posX, 3, 0));

	m_vecObstacleVertex.push_back(D3DXVECTOR3(posX, 3, posZ));
	m_vecObstacleVertex.push_back(D3DXVECTOR3(posX, height, posZ));
	m_vecObstacleVertex.push_back(D3DXVECTOR3(posX, height, 0));
}

void HeightMap::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_RBUTTONUP:
	{
		//D3DXVECTOR3 pos;
		//if (CalcPickedPosition(pos, SCREEN_POINT(lParam)) == true)
		//{
		//	//케릭터 pos 로 이동하게 하기
		//	GetHeight(pos.y, pos);
		//	static_cast<IUnitObject*>
		//		(g_pObjMgr->FindObjectByTag(TAG_PLAYER))
		//		->SetDestination(pos);
		//}
		vector<D3DXVECTOR3> Mobpos;
		Mobpos.resize((g_pObjMgr->FindObjectsByTag(TAG_MOB).size()));
		for (size_t i = 0; i < Mobpos.size(); i++)
		{
			GetHeight(Mobpos[i].y, Mobpos[i]);
			Mobpos[i].x = 5;
			Mobpos[i].z = (i + 1) * 10;
		}
		int a = 0;
		for (auto p : (g_pObjMgr->FindObjectsByTag(TAG_MOB)))
		{

			static_cast<IUnitObject*>
				(p)->SetDestination(Mobpos[a]);
			/*Mob::PlayerSearch(g_pObjMgr->FindObjectByTag(TAG_PLAYER))
			->GetPosition(), p)*/
			/*p->PlayerSearch(static_cast<IUnitObject*>
			(g_pObjMgr->FindObjectByTag(TAG_PLAYER))
			->GetPosition(), p);*/

			a++;
		}
		D3DXVECTOR3 pos;
		if (CalcPickedPosition(pos, SCREEN_POINT(lParam)) == true)
		{

			//케릭터 pos 로 이동하게 하기
			GetHeight(pos.y, pos);
			//static_cast<IUnitObject*>
			//	(g_pObjMgr->FindObjectByTag(TAG_PLAYER))
			//	->SetPosition(&pos);
			static_cast<IUnitObject*>
				(g_pObjMgr->FindObjectByTag(TAG_PLAYER))
				->SetDestination(pos);
		}

	}
	break;
	}
}
