#include "stdafx.h"
#include "DeviceManager.h"


void DeviceManager::ToggleFullscreen(float width, float height)
{
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	m_pFullscreen = !m_pFullscreen;
	d3dpp.Windowed = !m_pFullscreen;
	HRESULT result = m_pD3DDevice->Reset(&d3dpp);
}

DeviceManager::DeviceManager()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
	m_pFullscreen = false;
}


DeviceManager::~DeviceManager()
{
}

HRESULT DeviceManager::Init()
{
	//���� ������ ���� IDirect3D9 Interface �� ������ ȹ��
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL) return E_FAIL;

	D3DCAPS9	caps; 
	int			vp;

	//�� �׷���ī���� ������ D3DCAPS9 �� �޾ƿ´�.
	if (FAILED(m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, &caps)))
		return E_FAIL;

	//�ϵ��� ����ó���� �����ϴ��� Ȯ��
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	//D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true; //���⸦ �����ϸ� ��ü ȭ��
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_X;
	d3dpp.BackBufferHeight = SCREEN_Y;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //�̰ɷ� �ϸ� FPS ������ �����
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	if (FAILED(m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		g_hWnd, vp | D3DCREATE_MULTITHREADED, &d3dpp, &m_pD3DDevice)))
	{
		return E_FAIL;
	}
}

LPDIRECT3DDEVICE9 DeviceManager::GetDevice()
{
	return m_pD3DDevice;
}

void DeviceManager::Destroy()
{
	if (m_pD3DDevice)
	{
		ULONG ul = m_pD3DDevice->Release();
		assert(ul == 0 && 
			"����̽��� �̿��ؼ� ������ ��ü �� �Ҹ���� ���� ��ü�� �ֽ��ϴ�.");
	}

	if (m_pD3D) m_pD3D->Release();
}
