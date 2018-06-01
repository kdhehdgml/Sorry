#include "stdafx.h"
#include "GSM.h"


GSM::GSM()
{
	// 맵 크기
	mapSize = 500.0f;

	// 안개 거리
	fogMin = mapSize * 2;
	fogMax = mapSize * 2;

	// 카메라 초기 위치
	camPos.x = 100.0f;
	camPos.z = 250.0f;
	camPos.y = -10.0f;

	// 몹 초기 위치
	mobPos.x = mapSize - 200.0f;
	mobPos.z = 100.0f;
}


GSM::~GSM()
{
}
