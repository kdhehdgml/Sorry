#include "stdafx.h"
#include "Mob.h"
#include "CubemanParts.h"
#include "Ray.h"
#include "MONSTER.h"
Mob::Mob()
{
//	m_pRootParts = NULL;
	m_MONSTER = NULL;//몬스터 클래스 추가
	m_isMoving = false;
	m_isShoot = false;

	//m_baseRotY = D3DX_PI;

	m_forward.z = -1;
	m_pos.y = 3.0f;
	m_destPos = m_pos;
	m_move = false;
	num = 0;
	m_moveSpeed = 0.4f;

	m_pSphereBody = NULL;
	m_pSphereHead = NULL;
	health = 100;
	status = 1;
	m_BeDetermined = false;
}


Mob::~Mob()
{
	//m_pRootParts->ReleaseAll();
	SAFE_RELEASE(m_MONSTER);
	SAFE_RELEASE(m_pSphereBody);
	SAFE_RELEASE(m_pSphereHead);
	SAFE_DELETE(m_pBoundingSphereBody);
	SAFE_DELETE(m_pBoundingSphereHead);
}

void Mob::Init()
{
	g_pObjMgr->AddToTagList(TAG_MOB, this);

	D3DXCreateSphere(g_pDevice, 1.5f, 10, 10, &m_pSphereHead, NULL);
	m_pBoundingSphereHead = new BoundingSphere(m_pos, 1.5f);
	D3DXCreateSphere(g_pDevice, 2.0f, 10, 10, &m_pSphereBody, NULL);
	m_pBoundingSphereBody = new BoundingSphere(m_pos, 2.0f);

	m_MONSTER = new MONSTER;
	m_MONSTER->Init();

	//CreateAllParts();
	IUnitObject::m_moveSpeed = GSM().mobSpeed;

	//m_pMob[i]->SetPosition(&D3DXVECTOR3(50.0f, 5.0f, (i + 1) * 10));
}

void Mob::Update()
{
	if (health <= 0) {
		status = 0;
	}
	if (status > 0) {
		IUnitObject::UpdateKeyboardState();
		IUnitObject::UpdatePositionToDestination();
		
		m_pBoundingSphereBody->center = m_pos;
		m_pBoundingSphereBody->center.y += 2.0f;
		m_pBoundingSphereHead->center = m_pos;
		m_pBoundingSphereHead->center.y += 5.0f;

		//m_pRootParts->SetMovingState(m_isMoving);
		//m_pRootParts->Update();
		m_MONSTER->SetPos(m_pos);
		m_MONSTER->Update();

		Debug->AddText("몹 체력:");
		Debug->AddText(health);
		Debug->EndLine();
	}
}

void Mob::Render()
{
	g_pDevice->SetRenderState(D3DRS_FOGENABLE, true);
	g_pDevice->SetRenderState(D3DRS_FOGCOLOR, 0xffbbbbbb);
	g_pDevice->SetRenderState(D3DRS_FOGDENSITY, FtoDw(0.3f)); //강도 0~1f
	//안개적용되는 최소 거리
	g_pDevice->SetRenderState(D3DRS_FOGSTART, FtoDw(GSM().fogMin));
	//안개 최대치로 적용되는 거리
	g_pDevice->SetRenderState(D3DRS_FOGEND, FtoDw(GSM().fogMax));
	g_pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	
	if (status > 0) {
		g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
		//m_pRootParts->Render();
		m_MONSTER->Render();

		D3DXMATRIXA16 matI;
		D3DXMatrixIdentity(&matI);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pDevice->SetTransform(D3DTS_WORLD, &matI);
		g_pDevice->SetFVF(VERTEX_PC::FVF);
		g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST,
			1, &Shootpos[0], sizeof(VERTEX_PC));

		D3DXMATRIXA16 mat;
		D3DXMatrixTranslation(&mat, m_pBoundingSphereBody->center.x, m_pBoundingSphereBody->center.y, m_pBoundingSphereBody->center.z);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->SetTexture(0, NULL);
		m_pSphereBody->DrawSubset(0);
		//D3DXMATRIXA16 mat2;
		D3DXMatrixIdentity(&mat);
		D3DXMatrixTranslation(&mat, m_pBoundingSphereHead->center.x, m_pBoundingSphereHead->center.y, m_pBoundingSphereHead->center.z);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->SetTexture(0, NULL);
		m_pSphereHead->DrawSubset(0);
	}
}

BoundingSphere * Mob::getBoundingSphereBody()
{
	return m_pBoundingSphereBody;
}

BoundingSphere * Mob::getBoundingSphereHead()
{
	return m_pBoundingSphereHead;
}

int Mob::getHealth()
{
	return health;
}

void Mob::setHealth(int h)
{
	health = h;
}

int Mob::getStatus()
{
	return status;
}

void Mob::setStatus(int s)
{
	status = s;
}

void Mob::CreateAllParts()
{
	CubemanParts* pParts;
	//몸통
	m_pRootParts = new CubemanParts();
	CreateParts(m_pRootParts, this, D3DXVECTOR3(0.0f, 3.0f, 0.0f),
		D3DXVECTOR3(1.0f, 1.0f, 0.5f), D3DXVECTOR3(0, 0, 0), uvBody);
	//머리
	pParts = new CubemanParts();
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(0.0f, 1.6f, 0.0f),
		D3DXVECTOR3(0.8f, 0.8f, 0.8f), D3DXVECTOR3(0, 0, 0), uvHead);
	//왼팔
	pParts = new CubemanParts(0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-1.5f, 1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLArm);
	//오른팔
	pParts = new CubemanParts(-0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(1.5f, 1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvRArm);
	//왼다리
	pParts = new CubemanParts(-0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-0.5f, -1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLLeg);
	//오른다리
	pParts = new CubemanParts(0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(0.5f, -1.0f, 0.0f),
		D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvRLeg);
}

void Mob::CreateParts(CubemanParts *& pParts,
	IDisplayObject * pParent, D3DXVECTOR3 pos,
	D3DXVECTOR3 scale, D3DXVECTOR3 trans,
	vector<vector<int>> &vecUV)
{
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&matT, trans.x, trans.y, trans.z);
	mat = matS * matT;
	pParts->Init(&mat, vecUV);
	pParts->SetPosition(&pos);
	pParent->AddChild(pParts);
}

bool Mob::PlayerSearch(Mob* mob)
{

	if (mob->m_pos.x < 164.5f)
	{
		D3DXVECTOR3 move_forward;
		move_forward = D3DXVECTOR3(mob->m_destPos.x - mob->m_pos.x, 0, mob->m_destPos.z - mob->m_pos.z);
		if (D3DXVec3LengthSq(&move_forward) > 0)
		{
			mob->forward = D3DXVECTOR3(mob->m_destPos.x - mob->m_pos.x, 0, mob->m_destPos.z - mob->m_pos.z);
		}

		D3DXVECTOR3 DirectPM;
		D3DXVECTOR3 MobPos;
		DirectPM = (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetPosition() - mob->m_pos;
		DirectPM.y = 0;
		D3DXVECTOR3 DirectPMnormal = DirectPM;
		D3DXVec3Normalize(&DirectPMnormal, &DirectPMnormal);
		D3DXVec3Normalize(&mob->forward, &mob->forward);
		float Length = abs((g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetPosition().x - mob->m_pos.x
			+ (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetPosition().z - mob->m_pos.z);
		float DotPM = D3DXVec3Dot(&DirectPMnormal, &mob->forward);
		float direct = 1.0f / 2.0f;
		
		if ((Length < 15 && DotPM >= direct))
		{
			m_isShoot = true;
			return true;
		}

		m_isShoot = false;
		return false;
	}
	else
	{
		return false;
	}
}

void Mob::ShootVertex(Mob* mob)
{
	Ray * ray;
	ray = new Ray();

	D3DXVECTOR3 move_forward;
	move_forward = D3DXVECTOR3(mob->m_destPos.x - mob->m_pos.x, 0, mob->m_destPos.z - mob->m_pos.z);
	if (D3DXVec3LengthSq(&move_forward) > 0)
	{
		mob->forward = D3DXVECTOR3(mob->m_destPos.x - mob->m_pos.x, 0, mob->m_destPos.z - mob->m_pos.z);
	}

	D3DCOLOR c = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR d = D3DCOLOR_XRGB(0, 255, 0);
	//D3DXVECTOR3 directPMnor = Ppos - mob->m_pos;
	ray->m_pos = { mob->m_pos.x,  mob->m_pos.y + 4.0f, mob->m_pos.z };

	ray->m_dir = { (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetPosition().x , 
		(g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetPosition().y + 4.0f,
		(g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetPosition().z };
	if (m_isShoot == true)
	{
		Shootpos[0] = (VERTEX_PC(ray->m_pos, c));
		Shootpos[1] = (VERTEX_PC(ray->m_dir, c));
	}
	else
	{
		Shootpos[0] = (VERTEX_PC(ray->m_pos, d));
		Shootpos[1] = (VERTEX_PC(ray->m_dir, d));
	}

	/*if(ray.CalcIntersectTri(&m_vecObstacle[i], &intersectionDist))
	{
	}*/


}

void Mob::InsertAction(int _first, int _second)
{
	m_Action.resize(2);
	m_Action[0] = _first;
	m_Action[1] = _second;
}

void Mob::LocationSwap(int _v1, int _v2)
{
	D3DXVECTOR3 temp;
	temp = moveLocation[_v1];
	moveLocation[_v1] = moveLocation[_v2];
	moveLocation[_v2] = temp;

	int Itemp;
	Itemp = SaveLocationNum[_v1];
	SaveLocationNum[_v1] = SaveLocationNum[_v2];
	SaveLocationNum[_v2] = Itemp;
}

void Mob::TemporarySwap(int _v1, int _v2)
{
	D3DXVECTOR3 temp;
	temp = Temporary_Storage[_v1];
	Temporary_Storage[_v1] = Temporary_Storage[_v2];
	Temporary_Storage[_v2] = temp;

	int Itemp;
	Itemp = m_SaveTempNum[_v1];
	m_SaveTempNum[_v1] = m_SaveTempNum[_v2];
	m_SaveTempNum[_v2] = Itemp;
}