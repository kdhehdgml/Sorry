#include "stdafx.h"
#include "GSM.h"


GSM::GSM()
{
	// ���� ��
	StartScene = SCENE_HEIGHTMAP;

	// �� ũ��
	mapSize = 500.0f;

	// �Ȱ� �Ÿ�
	fogMin = mapSize / 5;
	fogMax = mapSize;

	// ī�޶� �ʱ� ��ġ
	camPos.x = 100.0f;
	camPos.z = 250.0f;
	camPos.y = -10.0f;

	// �� �ʱ� ��ġ
	mobPos.x = mapSize - 200.0f;
	mobPos.z = 100.0f;

	// �Ʊ� �ʱ� ��ġ
	TeamPos.x = mapSize - 450.0f;
	TeamPos.z = 100.0f;

	// �� �ӵ�
	mobSpeed = 1.0f;

	/*Debug->AddText("= Ű���� ============");
	Debug->EndLine();
	Debug->AddText("V : ����ī�޶� On/Off");
	Debug->EndLine();
	Debug->AddText("R : ��� (����ī�޶�)");
	Debug->EndLine();
	Debug->AddText("F : �ϰ� (����ī�޶�)");
	Debug->EndLine();
	Debug->AddText("Tab : AStar ��� ���� On/Off");
	Debug->EndLine();
	Debug->AddText("H : ��� �ٲٴ� ť�� ���� On/Off");
	Debug->EndLine();
	Debug->AddText("1 : ������� On/Off");
	Debug->EndLine();*/
}


GSM::~GSM()
{
}
