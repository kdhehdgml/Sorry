#include "stdafx.h"
#include "GSM.h"

/*
	[ Ű���� ���� ]

	F2 : �� ���� �ʱ���� (1���� ���� ��)
	F3 : ������ �Ŵ��� ������Ʈ On

	R : ������

	WASD : �ȱ�
	Shift: �޸���

	V : ����ī�޶� On/Off

	Tab : AStar ��� ���� On/Off
	H : �Ʊ� ���� ���� On/Off

	4 : ī�޶� ����� �ؽ�Ʈ On/Off

	P : ���� �Ͻ�����

	F5 : �Ʊ� ��ȯ �� ��ġ
	F6 : �Ʊ� ����

	I, K : ���� ���� ����

	M : ����� �˾�â

	E : �Ʊ�AI�� ��ȣ�ۿ�

	Ű�е� 1~4 : �÷��̾� ü�� ����
*/


GSM::GSM()
{
	Debug_Mode_On = false;

	//(���μ��� ���� ������)���� ��
	InitScene = SCENE_LOADING;
	// (�ε� ���� ����)���� ��
	StartScene = SCENE_HEIGHTMAP;
	// SCENE_LOADING       // ���ٿ�
	// SCENE_HEIGHTMAP     //
	// SCENE_GRID          //
	// SCENE_OBJMAP        //
	// SCENE_TEST          //
	// SCENE_XFILE         //
	// SCENE_MAIN          //

	// �� ũ��
	mapSize = 750.0f;

	playerHeight = 8.5f;

	// �Ȱ� �Ÿ�
	fogMin = mapSize / 5;
	fogMax = mapSize;

	// ī�޶� �ʱ� ��ġ
	camPos.x = 152.0f;
	camPos.z = 331.0f;
	camPos.y = 22.0f;

	// �� �ʱ� ��ġ
	// mobPos.x = mapSize - 50.0f;
	mobPos.x = NODE_POSITSIZEX + 460; // �׽�Ʈ��
	mobPos.z = NODE_POSITSIZEZ;

	// �� �ӵ�
	mobSpeed = 0.2f;

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
