#include "stdafx.h"
#include "SceneGrid.h"
#include "ColorCube.h"
#include "Grid.h"
#include "Cubeman.h"
#include "Walls.h"
#include "ActionCube.h"
#include "Hexagon.h"
#include "WireSphere.h"

SceneGrid::SceneGrid()
{
	m_pColorCube = NULL;
	m_pGrid = NULL;
	m_pCubeman = NULL;
	m_pWalls = NULL;
	m_pActionCube = NULL;
	m_pHexagon = NULL;
}


SceneGrid::~SceneGrid()
{
	SAFE_RELEASE(m_pColorCube);
	SAFE_RELEASE(m_pGrid);
	SAFE_RELEASE(m_pCubeman);
	SAFE_RELEASE(m_pWalls);
	SAFE_RELEASE(m_pActionCube);
	SAFE_RELEASE(m_pHexagon);
	SAFE_RELEASE(m_pWireSphere);
}

void SceneGrid::Init()
{
	//m_pColorCube = new ColorCube(); m_pColorCube->Init();
	m_pGrid = new Grid(); m_pGrid->Init();
	//m_pCubeman = new Cubeman(); m_pCubeman->Init();
	//m_pWalls = new Walls(); m_pWalls->Init();
	m_pActionCube = new ActionCube(); m_pActionCube->Init();
	m_pHexagon = new Hexagon(); m_pHexagon->Init();
	m_pWireSphere = new WireSphere(); m_pWireSphere->Init();
	D3DXVECTOR3 camPos(-30.0f, 22.0f, 0.0f);
	g_pCamera->setPos(camPos);
}

void SceneGrid::Update()
{
	SAFE_UPDATE(m_pColorCube);
	SAFE_UPDATE(m_pCubeman);
	SAFE_UPDATE(m_pActionCube);
	SAFE_UPDATE(m_pWireSphere);
}

void SceneGrid::Render()
{
	SAFE_RENDER(m_pColorCube);
	SAFE_RENDER(m_pGrid);
	SAFE_RENDER(m_pCubeman);
	SAFE_RENDER(m_pWalls);
	SAFE_RENDER(m_pActionCube);
	SAFE_RENDER(m_pHexagon);
	SAFE_RENDER(m_pWireSphere);
}

void SceneGrid::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
