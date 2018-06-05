#include "stdafx.h"
#include "CreateSmog.h"
#include "IDisplayObject.h"

#define SMOGSIZE 1.f

CreateSmog::CreateSmog()
	:m_IndexCount(0),
	m_MaxIndex(10)
{
}


CreateSmog::~CreateSmog()
{
	m_pVB->Release();
}

void CreateSmog::Init()
{
	m_pTex = g_pTextureManager->GetTexture(L"resources/images/smog.png");

	//m_pTex->GetSurfaceLevel();

	D3DXMATRIXA16 matS,matR,matT;

	D3DXMatrixIdentity(&m_matWorld);
	//
	//D3DXMatrixScaling(&matS, SMOGSIZE, SMOGSIZE, SMOGSIZE);
	//m_matWorld =  matS;

	g_pDevice->CreateVertexBuffer(m_MaxIndex * sizeof(VERTEX_PC),
		D3DUSAGE_POINTS | D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, VERTEX_PC::FVF,
		D3DPOOL_DEFAULT, &m_pVB, 0);
}



void CreateSmog::Update()
{
	for (size_t i = 0; i < m_vecAtt.size(); i++)
	{
		//m_vecAtt[i]->_position.x = 10.0f;
		m_vecAtt[i]->_position.y = 5.0f;
		m_vecAtt[i]->_position.z += 0.1f;

	//	m_vecAtt[i]->_position.x += 0.01f;
	//�Ȱ� ����
		m_vecAtt[i]->_color.a = 0.6f;//1���� 0���� ����
		Debug->AddText(m_vecAtt[i]->_position);
		Debug->EndLine();

	}
	

	VERTEX_PC* v;
	//�������ۿ� �������� ���� �����ϰڴ�
	m_pVB->Lock(0, 0, (LPVOID*)&v, D3DLOCK_DISCARD);

	for (auto p : m_vecAtt)
	{
		v->p = p->_position;
		v->c = p->_color;
		v++;//�ƹ����� ++ �̵Ǹ� ���� �ּҷ� ��������
	}
}

void CreateSmog::Render()
{
	//z���� �����Ѵٴ��ǹ�
	//�ؽ����� �ܰ��� ����
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	//����Ʈ �ϳ��� ��������Ʈ �ϳ��� ������ ���ڵ��� �ǹ�
	g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);

	//���� ũ�⸦ �����Ҽ� �ְ��ϰڵ�.
	g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);

	//g_pDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(0.5f));

	g_pDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(SMOGSIZE));



	//D3DTOP_SELECTARG1�� ���İ��� ���ͼ� ������
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

	g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
}

void CreateSmog::Insert(D3DXVECTOR3 pos)
{
	
	//���� �Ȱ������� �ִ�ġ�� 0���� �ʱ�ȭ!
	if (m_IndexCount == m_MaxIndex)
		m_IndexCount = 0;

	
	m_IndexCount++;


	m_numParticle = m_IndexCount;

	m_vecAtt.resize(m_numParticle);

	
	SMOG2* att = new SMOG2;
	att->_position = //D3DXVECTOR3(25.0f, 0, 25.0f);
		D3DXVECTOR3(pos.x,5.0f, pos.z);

	//att->_color = 0xffffffff * GetRandomFloat(0, 1);
	att->_color = 0xffffffff;
	//att->_color.a = 0.6f;
	m_vecAtt[m_IndexCount-1] = att;

	


}

