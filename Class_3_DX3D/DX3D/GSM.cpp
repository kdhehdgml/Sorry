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

	// 몹 속도
	mobSpeed = 0.5f;

	/*Debug->AddText("= 키보드 ============");
	Debug->EndLine();
	Debug->AddText("V : 프리카메라 On/Off");
	Debug->EndLine();
	Debug->AddText("R : 상승 (프리카메라)");
	Debug->EndLine();
	Debug->AddText("F : 하강 (프리카메라)");
	Debug->EndLine();
	Debug->AddText("Tab : AStar 노드 렌더 On/Off");
	Debug->EndLine();
	Debug->AddText("H : 노드 바꾸는 큐브 렌더 On/Off");
	Debug->EndLine();
	Debug->AddText("방향키 : 큐브 이동 ");
	Debug->EndLine();*/
}


GSM::~GSM()
{
}
