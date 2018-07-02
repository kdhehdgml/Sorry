#include "stdafx.h"
#include "GSM.h"

/*
	[ Ű���� ���� ]

	V : �� �̶� �� ���� ����Ű��
	R : ���� ��� �ѹ��� ������ ���
	F : ������

	WASD : �ȱ�
	Shift: �޸���

	V : ����ī�޶� On/Off

	Tab : AStar ��� ���� On/Off
	H : ��� �ٲٴ� ť�� ���� On/Off

	0 : ������� On/Off

	4 : ī�޶� ����� �ؽ�Ʈ On/Off

	P : ���� �Ͻ�����

	F1 ~ F4 : ���� ��ȯ
	F5 : �Ʊ� ��ȯ
	F6 : �Ʊ� ����

	I, K : ������� ���� ����

	M : ����� �˾�â

	E : �Ʊ�AI�� ��ȣ�ۿ�
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
	mapSize = 750.0f;

	// �Ȱ� �Ÿ�
	fogMin = mapSize / 5;
	fogMax = mapSize;

	// ī�޶� �ʱ� ��ġ
	camPos.x = 160.0f;
	camPos.z = 375.0f;
	camPos.y = -10.0f;

	// �� �ʱ� ��ġ
	// mobPos.x = mapSize - 50.0f;
	mobPos.x = NODE_POSITSIZEX + 360; // �׽�Ʈ��
	mobPos.z = NODE_POSITSIZEZ;

	// �Ʊ� �ʱ� ��ġ
	TeamPos.x = mapSize / 10.0f;
	TeamPos.z = NODE_POSITSIZEZ + 20.0f;

	// �� �ӵ�
	mobSpeed = 0.5f;

	// ���� �ʱ� ����
	volume_music_init = 5.0f;
}


GSM::~GSM()
{
}
