#include "stdafx.h"
#include "seqManager.h"

#define STOP stopTime = true

seqManager::seqManager()
{
	checkTime = 100;
	stopTime = false;
	stage = 1;
	round = 0;
}

seqManager::~seqManager()
{
}

void seqManager::Init()
{
	
}

void seqManager::Update()
{
	if (!stopTime && checkTime > 0)
		checkTime--;
	
	setStage();

	if (GetKeyState('1') & 0x8000)
	{
		if(stopTime)
			stopTime = false;
	}

	// ����� �ؽ�Ʈ
	{
		Debug->AddText("�̺�Ʈ Ÿ�̸�: ");
		Debug->AddText(checkTime);
		Debug->AddText(" / ��������: ");
		Debug->AddText(stage);
		Debug->AddText(" / ����: ");
		Debug->AddText(round);
		Debug->EndLine();
	}
}

int seqManager::getStage()
{
	return stage;
}

int seqManager::getRound()
{
	return round;
}

int seqManager::setReadyTime(int stage, int round)
{
	return 100;
}

void seqManager::setStage()
{
	if (checkTime <= 0)
	{
		if (round != 3)
			round++;
		else
		{
			stage++;
			round = 0;
		}
		checkTime = setReadyTime(stage, round);
		STOP;

		Level(stage, round);
	}
}

void seqManager::Level(int stage, int round)
{
	switch (stage)
	{
	// ����
	case 0:
		break;

	// �������� 1
	case 1:
		switch (round)
		{
		case 1:
			// ���� 1 ==================================================

			//g_pSoundManager->playMusic(1);

			// ===========================================================
			break;
		case 2:
			// ���� 2 ==================================================

			//g_pSoundManager->playMusic(0);

			// ===========================================================
			break;
		case 3:
			// ���� 3 ==================================================



			// ===========================================================
			break;
		}
		break;

	// �������� 2
	case 2:
		switch (round)
		{
		case 1:
			// ���� 1 ==================================================



			// ===========================================================
			break;
		case 2:
			// ���� 2 ==================================================



			// ===========================================================
			break;
		case 3:
			// ���� 3 ==================================================



			// ===========================================================
			break;
		}
		break;

	// �������� 3
	case 3:
		switch (round)
		{
		case 1:
			// ���� 1 ==================================================



			// ===========================================================
			break;
		case 2:
			// ���� 2 ==================================================



			// ===========================================================
			break;
		case 3:
			// ���� 3 ==================================================



			// ===========================================================
			break;
		}
		break;
	}

}