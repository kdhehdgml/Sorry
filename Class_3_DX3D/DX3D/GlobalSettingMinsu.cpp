#include "stdafx.h"
#include "GlobalSettingMinsu.h"


GlobalSettingMinsu::GlobalSettingMinsu()
{
	// �� ũ��
	mapSize = 500.0f;

	// �Ȱ� �Ÿ�
	fogMin = mapSize * 2;
	fogMax = mapSize * 2;

	// ī�޶� �ʱ� ��ġ
	camPos.x = 100.0f;
	camPos.z = 250.0f;
	camPos.y = -10.0f;
}


GlobalSettingMinsu::~GlobalSettingMinsu()
{
}
