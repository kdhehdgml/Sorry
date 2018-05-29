#include "stdafx.h"
#include "ParticleTest.h"


ParticleTest::ParticleTest()
{
}


ParticleTest::~ParticleTest()
{
	SAFE_RELEASE(m_pVB);
}

void ParticleTest::Init()
{
	m_pTex = g_pTextureManager->GetTexture(
		(L"../../_Assets/sprites/particle/snow.png"));

	size_t  numParticle = 5000;
	m_vecAtt.resize(numParticle);
	for (int i = 0; i < numParticle; i++)
	{
		Attribute* att = new Attribute();
		att->_position = D3DXVECTOR3(GetRandomFloat(-0.1f, 0.1f), GetRandomFloat(-0.01f, 0.01f),
			GetRandomFloat(-0.1f, 0.1f));
		att->_color = 0xffff3300 * GetRandomFloat(0, 1);
		//att->_color = 0xffffffff;
		att->_delay = -i * 2;
		m_vecAtt[i] = att;
	}

	g_pDevice->CreateVertexBuffer(numParticle * sizeof(VERTEX_PC),
		D3DUSAGE_POINTS | D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
		VERTEX_PC::FVF, D3DPOOL_DEFAULT, &m_pVB, 0);
}

void ParticleTest::Update()
{
	for (size_t i = 0; i < m_vecAtt.size(); i++)
	{
		m_vecAtt[i]->_delay += 1;

		if (m_vecAtt[i]->_delay < 0) continue;

		m_vecAtt[i]->_age += g_pTimeManager->GetDeltaTime();
		//m_vecAtt[i]->_velocity.x += cosf(m_vecAtt[i]->_age * 2.0f) * 0.002f;
		//m_vecAtt[i]->_velocity.y += m_vecAtt[i]->_age * 0.01f;
		//m_vecAtt[i]->_velocity.z += sinf(m_vecAtt[i]->_age * 2.0f) * 0.002f;
		m_vecAtt[i]->_velocity.x = cosf(m_vecAtt[i]->_age * 4.0f) * 0.2f;
		m_vecAtt[i]->_velocity.z = sinf(m_vecAtt[i]->_age * 4.0f) * 0.2f;
		m_vecAtt[i]->_velocity.y = m_vecAtt[i]->_age * 0.15f;

		m_vecAtt[i]->_position = m_vecAtt[i]->_velocity
			+ g_pObjMgr->FindObjectByTag(TAG_PLAYER)->GetPosition();
		m_vecAtt[i]->_color.a -= 0.002f;
	}
	Debug->AddText(m_vecAtt[0]->_velocity.y);

	VERTEX_PC* v;
	m_pVB->Lock(0, 0, (LPVOID*)&v, D3DLOCK_DISCARD);
	for (auto p : m_vecAtt)
	{
		v->p = p->_position;
		v->c = p->_color;
		v++;
	}
}

void ParticleTest::Render()
{
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	g_pDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(0.4f));
	g_pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));
	
	g_pDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	g_pDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
	g_pDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));
	
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetTexture(0, m_pTex);
	g_pDevice->SetFVF(VERTEX_PC::FVF);
	g_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX_PC));
	g_pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, m_vecAtt.size());


	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
