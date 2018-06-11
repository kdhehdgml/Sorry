#include "stdafx.h"
#include "GSM.h"

/*
	[ 키보드 설정 ]

	WASD : 걷기
	Shift: 달리기

	V : 프리카메라 On/Off
	R : 상승 (프리카메라)
	F : 하강 (프리카메라)

	Tab : AStar 노드 렌더 On/Off
	H : 노드 바꾸는 큐브 렌더 On/Off

	0 : 배경음악 On/Off

	4 : 카메라 디버그 텍스트 On/Off

	P : 게임 일시정지

	F1 ~ F4 : 적군 소환
	F5 ~ F6 : 아군 소환
	F7 : 아군 전진

	M : 디버그 팝업창
*/


GSM::GSM()
{
	// 시작 씬
	StartScene = SCENE_HEIGHTMAP;
	// SCENE_LOADING       // 복붙용
	// SCENE_HEIGHTMAP     //
	// SCENE_GRID          //
	// SCENE_OBJMAP        //
	// SCENE_TEST          //
	// SCENE_XFILE         //
	// SCENE_BATTLEFIELD   //

	// 맵 크기
	mapSize = 500.0f;

	// 안개 거리
	fogMin = mapSize / 5;
	fogMax = mapSize;

	// 카메라 초기 위치
	camPos.x = 100.0f;
	camPos.z = 250.0f;
	camPos.y = -10.0f;

	// 몹 초기 위치
	mobPos.x = mapSize - 200.0f;
	mobPos.z = 100.0f;

	// 아군 초기 위치
	TeamPos.x = mapSize - 450.0f;
	TeamPos.z = 100.0f;

	// 몹 속도
	mobSpeed = 2.0f;
}


GSM::~GSM()
{
}
