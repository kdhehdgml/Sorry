#include "stdafx.h"
#include "GSM.h"


GSM::GSM()
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

	// �� �ʱ� ��ġ
	mobPos.x = mapSize - 200.0f;
	mobPos.z = 100.0f;
}


GSM::~GSM()
{
}
