#include "stdafx.h"
#include "CreateSmog.h"
#include "IDisplayObject.h"



CreateSmog::CreateSmog()
	:m_IndexCount(0),
	m_MaxIndex(10)
{
	//스모그 사이즈조절
	m_SmogSize = 1.5f;
	//스모그 종류
	m_Smog_index = 0;

}


CreateSmog::~CreateSmog()
{
	m_pVB->Release();
}

void CreateSmog::Init()
{
	//스모그 종류 초기화
	m_pTex.push_back(g_pTextureManager->GetTexture(L"resources/images/smog.png"));
	m_pTex.push_back(g_pTextureManager->GetTexture(L"resources/images/smoke.png"));
	m_pTex.push_back(g_pTextureManager->GetTexture(L"resources/images/smoke2.png"));
	m_pTex.push_back(g_pTextureManager->GetTexture(L"resources/images/smoketest2.png"));

	//m_pTex->GetSurfaceLevel();

	//srand(time(NULL));

	D3DXMatrixIdentity(&m_matWorld);
	//
	
	for (size_t i = 0; i < m_vecAtt.size(); i++)
	{
		m_vecAtt[i]->_state = true;
	}


	g_pDevice->CreateVertexBuffer(m_MaxIndex * sizeof(VERTEX_PC),
		D3DUSAGE_POINTS | D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, VERTEX_PC::FVF,
		D3DPOOL_DEFAULT, &m_pVB, 0);
}



void CreateSmog::Update()
{
	D3DXMATRIXA16 matS, matR, matT;
	//Debug->AddText("0번 : ");
	//Debug->AddText(m_vecAtt[0]->_state);
	//Debug->AddText("//1번 : ");
	//Debug->AddText(m_vecAtt[1]->_state);
	//Debug->AddText("//2번 : ");
	//Debug->AddText(m_vecAtt[2]->_state);
	//Debug->AddText("//3번 : ");
	//Debug->AddText(m_vecAtt[3]->_state);
	//Debug->AddText("//4번 : ");
	//Debug->AddText(m_vecAtt[4]->_state);
	//Debug->EndLine();

	for (size_t i = 0; i < m_vecAtt.size(); i++)
	{
		m_vecAtt[i]->_position.y = 5.0f;
		
		//안개 투명도
		//0에수렴했을때 반전
		if (m_vecAtt[i]->_color.a <= 0)
		{
			m_vecAtt[i]->_state = false;
		}
		//맥스에 수렴했을때 반전
		else if (m_vecAtt[i]->_color.a >= m_vecAtt[i]->_MaxTransparency)
		{
			m_vecAtt[i]->_state = true;
		}

		if (m_vecAtt[i]->_state)
			m_vecAtt[i]->_color.a -= 0.001f;//1부터 0으로 수렴
		else
		{
			m_vecAtt[i]->_color.a += 0.001f;
			//			m_Smog_index = rand() % 4; //안개 이미지 생성시 랜덤하게 하기 도전중
		}
		//Debug->AddText(m_vecAtt[i]->_position);
		//Debug->EndLine();

	}
	

	VERTEX_PC* v;
	//기존버퍼에 쓰여졌던 값은 무시하겠다
	m_pVB->Lock(0, 0, (LPVOID*)&v, D3DLOCK_DISCARD);

	for (auto p : m_vecAtt)
	{
		v->p = p->_position;
		v->c = p->_color;
		v++;//아무래도 ++ 이되면 다음 주소로 가나보다
	}

	//마우스 우클릭후 확대하면 스모그가 작아지니까 그만큼 크게해줌
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		m_SmogSize = 4.0f;
	}
	else
	{
		m_SmogSize = 1.5f;
	}


	
	
}

void CreateSmog::Render()
{
	//z값을 제외한다는의미
	//텍스쳐의 외각을 꺼줌
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	//포인트 하나에 스프라이트 하나를 입혀서 쓰겠따는 의미
	g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);

	//점의 크기를 조절할수 있게하겠따.
	g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);

	//g_pDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(0.5f));

	g_pDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(m_SmogSize));



	//D3DTOP_SELECTARG1의 알파값을 빼와서 쓸것임
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetTexture(0, m_pTex[m_Smog_index]);
	g_pDevice->SetFVF(VERTEX_PC::FVF);
	g_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX_PC));
	g_pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, m_vecAtt.size());

	g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
}
//transparency=  투명도
void CreateSmog::Insert(D3DXVECTOR3 pos ,float transparency,int index)
{
	
	//지금 안개갯수가 최대치면 0으로 초기화!
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
	att->_MaxTransparency = transparency;
	att->_color.a = transparency;
	m_vecAtt[m_IndexCount-1] = att;

	
	m_Smog_index = index;

}

