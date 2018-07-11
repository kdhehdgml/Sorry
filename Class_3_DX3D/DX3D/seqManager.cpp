#include "stdafx.h"
#include "seqManager.h"

#define waveControl if (waveTime <= 0) { spawnCheck = false; waveTime = WAVE_INTERVAL;\
if (waveCount != MAX_WAVE) waveCount++; else { stopUpdate = true; waveCount = 0; roundStart = false; RESTART; if(seqManager::round == 3) { seqManager::stage++; seqManager::round = 0; } } }

#define SPAWN(num) if (!spawnCheck)	{ spawnNum = num; spawnCheck = true; }

#define STOP stopTime = true
#define RESTART stopTime = false
#define STAGE_END stopTime = true; roundStart = false

#define READY_TIME 200
#define WAVE_INTERVAL 1000

#define MAX_WAVE 5

void seqManager::Init()
{
	checkTime = READY_TIME;
	stopTime = false;
	stage = 1;
	round = 0;

	roundStart = false;
	waveCount = 0;
	waveTime = WAVE_INTERVAL;

	spawnNum = 0;
	spawnCheck = false;

	stopUpdate = true;
	isMusicPlay = false;
}

void seqManager::Update()
{
	if (!stopUpdate)
	{
		if (!stopTime && checkTime > 0)
			checkTime--;

		if (roundStart)
		{
			Level(stage, round);
			waveTime--;
		}

		setStage();

		/*if (GetKeyState('1') & 0x8000)
		{
			if (stopTime)
				stopTime = false;
		}*/

		// ����� �ؽ�Ʈ
		{
			Debug->AddText("=====================================================================");
			Debug->EndLine();
			Debug->AddText("��� Ÿ�̸�: ");
			Debug->AddText(checkTime);
			Debug->AddText(" / ��������: ");
			Debug->AddText(stage);
			Debug->AddText(" / ����: ");
			Debug->AddText(round);
			Debug->AddText(" / ���̺�: ");
			Debug->AddText(waveCount);
			Debug->AddText(" / ���̺� Ÿ�̸� : ");
			Debug->AddText(waveTime);
			Debug->EndLine();
			Debug->AddText("=====================================================================");
			Debug->EndLine();
		}
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
	return READY_TIME;
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

		roundStart = true;
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

			if (!isMusicPlay)
			{
				//g_pSoundManager->playMusic(2);
				isMusicPlay = true;
			}

			switch (waveCount)
			{
			case 0:
				waveCount++;
				break;
			case 1: 
				// ���̺� 1 ==============================================

				SPAWN(9);

				waveControl;
				// =======================================================
				break;
			case 2: 
				// ���̺� 2 ==============================================

				SPAWN(9);

				waveControl;
				// =======================================================
				break;
			case 3:
				// ���̺� 3 ==============================================

				SPAWN(11);

				waveControl;
				// =======================================================
				break;
			case 4:
				// ���̺� 3 ==============================================

				SPAWN(13);

				waveControl;
				// =======================================================
				break;
			case 5:
				// ���̺� 3 ==============================================

				SPAWN(15);

				waveControl;
				// =======================================================
				break;
			}

			// ===========================================================
			break;
		case 2:
			// ���� 2 ==================================================

			switch (waveCount)
			{
			case 0:
				waveCount++;
				break;
			case 1: 
				// ���̺� 1 ==============================================

				SPAWN(9);

				waveControl;
				// =======================================================
				break;
			case 2: 
				// ���̺� 2 ==============================================

				SPAWN(9);

				waveControl;
				// =======================================================
				break;
			case 3:
				// ���̺� 3 ==============================================

				SPAWN(11);

				waveControl;
				// =======================================================
				break;
			case 4:
				// ���̺� 3 ==============================================

				SPAWN(13);

				waveControl;
				// =======================================================
				break;
			case 5:
				// ���̺� 3 ==============================================

				SPAWN(16);

				waveControl;
				// =======================================================
				break;
			}

			// ===========================================================
			break;
		case 3:
			// ���� 3 ==================================================

			switch (waveCount)
			{
			case 0:
				waveCount++;
				break;
			case 1:
				// ���̺� 1 ==============================================

				SPAWN(9);

				waveControl;
				// =======================================================
				break;
			case 2:
				// ���̺� 2 ==============================================

				SPAWN(10);

				waveControl;
				// =======================================================
				break;
			case 3:
				// ���̺� 3 ==============================================

				SPAWN(12);

				waveControl;
				// =======================================================
				break;
			case 4:
				// ���̺� 3 ==============================================

				SPAWN(14);

				waveControl;
				// =======================================================
				break;
			case 5:
				// ���̺� 3 ==============================================

				SPAWN(17);

				waveControl;
				// =======================================================
				break;
			}

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

			switch (waveCount)
			{
			case 0:
				waveCount++;
				break;
			case 1:
				// ���̺� 1 ==============================================



				waveControl;
				// =======================================================
				break;
			case 2:
				// ���̺� 2 ==============================================



				waveControl;
				// =======================================================
				break;
			case 3:
				// ���̺� 3 ==============================================



				waveControl;
				// =======================================================
				break;
			}

			// ===========================================================
			break;
		case 2:
			// ���� 2 ==================================================

			switch (waveCount)
			{
			case 0:
				waveCount++;
				break;
			case 1:
				// ���̺� 1 ==============================================



				waveControl;
				// =======================================================
				break;
			case 2:
				// ���̺� 2 ==============================================



				waveControl;
				// =======================================================
				break;
			case 3:
				// ���̺� 3 ==============================================



				waveControl;
				// =======================================================
				break;
			}

			// ===========================================================
			break;
		case 3:
			// ���� 3 ==================================================

			switch (waveCount)
			{
			case 0:
				waveCount++;
				break;
			case 1:
				// ���̺� 1 ==============================================



				waveControl;
				// =======================================================
				break;
			case 2:
				// ���̺� 2 ==============================================



				waveControl;
				// =======================================================
				break;
			case 3:
				// ���̺� 3 ==============================================



				waveControl;
				// =======================================================
				break;
			}

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

			switch (waveCount)
			{
			case 0:
				waveCount++;
				break;
			case 1:
				// ���̺� 1 ==============================================



				waveControl;
				// =======================================================
				break;
			case 2:
				// ���̺� 2 ==============================================



				waveControl;
				// =======================================================
				break;
			case 3:
				// ���̺� 3 ==============================================



				waveControl;
				// =======================================================
				break;
			}

			// ===========================================================
			break;
		case 2:
			// ���� 2 ==================================================

			switch (waveCount)
			{
			case 0:
				waveCount++;
				break;
			case 1:
				// ���̺� 1 ==============================================



				waveControl;
				// =======================================================
				break;
			case 2:
				// ���̺� 2 ==============================================



				waveControl;
				// =======================================================
				break;
			case 3:
				// ���̺� 3 ==============================================



				waveControl;
				// =======================================================
				break;
			}

			// ===========================================================
			break;
		case 3:
			// ���� 3 ==================================================

			switch (waveCount)
			{
			case 0:
				waveCount++;
				break;
			case 1:
				// ���̺� 1 ==============================================



				waveControl;
				// =======================================================
				break;
			case 2:
				// ���̺� 2 ==============================================



				waveControl;
				// =======================================================
				break;
			case 3:
				// ���̺� 3 ==============================================



				waveControl;
				// =======================================================
				break;
			}

			// ===========================================================
			break;
		}
		break;

	default: // �������� ����
		STAGE_END;
		break;
	}

}