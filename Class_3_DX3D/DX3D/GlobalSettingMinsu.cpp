#include "stdafx.h"
#include "GlobalSettingMinsu.h"


GlobalSettingMinsu::GlobalSettingMinsu()
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
}


GlobalSettingMinsu::~GlobalSettingMinsu()
{
}
