#include "stdafx.h"
#include "GSM.h"

/*
	[ Ű���� ���� ]

	WASD : �ȱ�
	Shift: �޸���

	V : ����ī�޶� On/Off
	R : ��� (����ī�޶�)
	F : �ϰ� (����ī�޶�)

	Tab : AStar ��� ���� On/Off
	H : ��� �ٲٴ� ť�� ���� On/Off

	0 : ������� On/Off

	4 : ī�޶� ����� �ؽ�Ʈ On/Off

	P : ���� �Ͻ�����

	F1 ~ F4 : ���� ��ȯ
	F5 ~ F6 : �Ʊ� ��ȯ
	F7 : �Ʊ� ����

	M : ����� �˾�â
*/


GSM::GSM()
{
	// ���� ��
	StartScene = SCENE_HEIGHTMAP;
	// SCENE_LOADING       // ���ٿ�
	// SCENE_HEIGHTMAP     //
	// SCENE_GRID          //
	// SCENE_OBJMAP        //
	// SCENE_TEST          //
	// SCENE_XFILE         //
	// SCENE_BATTLEFIELD   //

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
	mobSpeed = 2.0f;
}


GSM::~GSM()
{
}
