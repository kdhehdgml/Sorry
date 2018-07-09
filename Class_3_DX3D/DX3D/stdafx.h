// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>	
#include <assert.h>
#include <time.h>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>
#include <fstream>
#include <atlstr.h>
#include <fmod.h>
#include <windows.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//#ifdef _DEBUG
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#endif 

using std::string;

using std::vector;
using std::map;
using std::set;
using std::list;
using std::to_string;

extern HWND g_hWnd;

extern const int SCREEN_X = 1280;
extern const int SCREEN_Y = 720;

#include "GSM.h" // Global Setting

#include "Mouse.h"
#include "Keyboard.h"	
#include "Application.h"
#include "DeviceManager.h"
#include "D3DUtility.h"
#include "BaseObject.h"
#include "GlobalDefinition.h"
#include "IMap.h"
//셰이더 
#include "IShader.h"
//
#include "IUnitObject.h"
#include "IAction.h"
#include "Debug.h"
#include "ObjManager.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Frustum.h"
#include "MapManager.h"
#include "KeyboardManager.h"
#include "SoundManager.h"
#include "seqManager.h"

//셰이더 
#include "Shaders.h"
#include "Objects.h"
//