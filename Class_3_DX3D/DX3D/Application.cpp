#include "stdafx.h"
#include "Application.h"

float temp_rotX;
float temp_rotY;

Application::Application()
{
	//isPaused = false;
	temp_rotX = 0;
	temp_rotY = 0;
}


Application::~Application()
{
	
}

void Application::Init()
{
	g_pDeviceManager->Init();
	Mouse::Get()->SetHandle(g_hWnd);

	g_pCamera->Init();
	g_pSceneManager->Init();
	g_pFrustum->Init();

}

void Application::Destroy()
{
	Mouse::Get()->Delete();
	Keyboard::Get()->Delete();
	
	g_pFrustum->Destroy();
	g_pSceneManager->Destroy();
	g_pObjMgr->Destroy();
	g_pTextureManager->Destroy();
	g_pFontMgr->Destroy();
	Debug->Destroy();
	g_pDeviceManager->Destroy();

	
}

void Application::Update()
{
	if (!g_pCamera->isPaused)
	{
		Mouse::Get()->Update();
		Keyboard::Get()->Update();
		Debug->InitText();
		g_pTimeManager->Update();
		g_pKeyboardManager->Update();
		g_pSceneManager->Update();
		g_pCamera->Update();
		g_pFrustum->Update();
	}
	//g_pSceneManager->Update();
	if (GetAsyncKeyState('M') & 0x0001)
	{
		Debug->ShowMessageBox();
	}
	if (GetAsyncKeyState('P') & 0x0001) {
		if (g_pCamera->isPaused) {
			g_pCamera->isPaused = false;
			g_pCamera->mouseLock = true;
			ShowCursor(false);
			g_pCamera->setRotX(temp_rotX);
			g_pCamera->setRotY(temp_rotY);
		}
		else {
			g_pCamera->isPaused = true;
			g_pCamera->mouseLock = false;
			ShowCursor(true);
			temp_rotX = g_pCamera->getRotX();
			temp_rotY = g_pCamera->getRotY();
		}
	}
}

void Application::Render()
{
	if (!g_pCamera->isPaused)
	{
		g_pDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(50, 50, 50), 1.0f, 0);

		g_pDevice->BeginScene();

		g_pSceneManager->Render();
		Debug->Print();

		g_pDevice->EndScene();
		g_pDevice->Present(NULL, NULL, NULL, NULL);
	}
}

void Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//if (!isPaused)
	{
		Mouse::Get()->InputProc(message, wParam, lParam);
		g_pSceneManager->WndProc(hWnd, message, wParam, lParam);
		g_pCamera->WndProc(hWnd, message, wParam, lParam);
		//g_pFrustum
	}
}
