#include "stdafx.h"
#include "GSM.h"

/*
	[ 키보드 설정 ]

	V : 총 이랑 손 렌더 껏다키기
	R : 장전 모션 한번더 누르면 취소
	F : 재장전

	WASD : 걷기
	Shift: 달리기

	V : 프리카메라 On/Off

	Tab : AStar 노드 렌더 On/Off
	H : 노드 바꾸는 큐브 렌더 On/Off

	0 : 배경음악 On/Off

	4 : 카메라 디버그 텍스트 On/Off

	P : 게임 일시정지

	F1 ~ F4 : 적군 소환
	F5 : 아군 소환
	F6 : 아군 전진

	I, K : 배경음악 볼륨 조절

	M : 디버그 팝업창

	E : 아군AI와 상호작용
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
	mapSize = 750.0f;

	// 안개 거리
	fogMin = mapSize / 5;
	fogMax = mapSize;

	// 카메라 초기 위치
	camPos.x = 160.0f;
	camPos.z = 375.0f;
	camPos.y = -10.0f;

	// 몹 초기 위치
	// mobPos.x = mapSize - 50.0f;
	mobPos.x = NODE_POSITSIZEX + 360; // 테스트용
	mobPos.z = NODE_POSITSIZEZ;

	// 아군 초기 위치
	TeamPos.x = mapSize / 10.0f;
	TeamPos.z = NODE_POSITSIZEZ + 20.0f;

	// 몹 속도
	mobSpeed = 0.5f;

	// 사운드 초기 볼륨
	volume_music_init = 5.0f;
}


GSM::~GSM()
{
}
