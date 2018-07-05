#include "stdafx.h"
#include "GSM.h"

/*
	[ Ű���� ���� ]

	R : ���� ��� �ѹ��� ������ ���
	F : ������

	WASD : �ȱ�
	Shift: �޸���

	V : ����ī�޶� On/Off

	Tab : AStar ��� ���� On/Off
	H : �Ʊ� ���� ���� On/Off

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

	// �� �ӵ�
	mobSpeed = 0.25f;

	// ���� �ʱ� ����
	volume_music_init = 5.0f;

	// ���� �ӵ�
	//reload_one = 105;
	//reload_all = 180;
	reload_one = 1750;
	reload_all = 3000;
}


GSM::~GSM()
{
}
