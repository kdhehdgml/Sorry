#include "stdafx.h"
#include "GSM.h"

/*
	[ 키보드 설정 ]

	F2 : 적 병사 초기생성 (1번만 실행 됨)
	F3 : 시퀀스 매니저 업데이트 On

	R : 재장전

	WASD : 걷기
	Shift: 달리기

	V : 프리카메라 On/Off

	Tab : AStar 노드 렌더 On/Off
	H : 아군 병사 렌더 On/Off

	4 : 카메라 디버그 텍스트 On/Off

	P : 게임 일시정지

	F5 : 아군 소환 및 배치
	F6 : 아군 제거

	I, K : 사운드 볼륨 조절

	M : 디버그 팝업창

	E : 아군AI와 상호작용

	키패드 1~4 : 플레이어 체력 조절
*/


GSM::GSM()
{
	Debug_Mode_On = false;

	//(프로세스 시작 직후의)시작 씬
	InitScene = SCENE_LOADING;
	// (로딩 끝난 후의)시작 씬
	StartScene = SCENE_HEIGHTMAP;
	// SCENE_LOADING       // 복붙용
	// SCENE_HEIGHTMAP     //
	// SCENE_GRID          //
	// SCENE_OBJMAP        //
	// SCENE_TEST          //
	// SCENE_XFILE         //
	// SCENE_MAIN          //

	// 맵 크기
	mapSize = 750.0f;

	playerHeight = 8.5f;

	// 안개 거리
	fogMin = mapSize / 5;
	fogMax = mapSize;

	// 카메라 초기 위치
	camPos.x = 152.0f;
	camPos.z = 331.0f;
	camPos.y = 22.0f;

	// 몹 초기 위치
	// mobPos.x = mapSize - 50.0f;
	mobPos.x = NODE_POSITSIZEX + 460; // 테스트용
	mobPos.z = NODE_POSITSIZEZ;

	// 몹 속도
	mobSpeed = 0.2f;

	// 사운드 초기 볼륨
	volume_music_init = 5.0f;

	// 장전 속도
	//reload_one = 105;
	//reload_all = 180;
	reload_one = 1750;
	reload_all = 3000;
}


GSM::~GSM()
{
}
