#include "stdafx.h"
#include "seqManager.h"

#define STOP stopTime = true
#define RESTART stopTime = false
#define WAVE_INTERVAL 100

seqManager::seqManager()
{
	checkTime = 100;
	stopTime = false;
	stage = 1;
	round = 0;
	
	roundStart = false;
	waveCount = 0;
	waveTime = WAVE_INTERVAL;
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
	
	if (roundStart)
	{
		Level(stage, round);
		waveTime--;
	}

	setStage();

	if (GetKeyState('1') & 0x8000)
	{
		if(stopTime)
			stopTime = false;
	}

	// 디버그 텍스트
	{
		Debug->AddText("이벤트 타이머: ");
		Debug->AddText(checkTime);
		Debug->AddText(" / 스테이지: ");
		Debug->AddText(stage);
		Debug->AddText(" / 라운드: ");
		Debug->AddText(round);
		Debug->AddText(" / 웨이브: ");
		Debug->AddText(waveCount);
		Debug->AddText(" / 웨이브 타이머 : ");
		Debug->AddText(waveTime);
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

		roundStart = true;
	}
}

void seqManager::Level(int stage, int round)
{
	switch (stage)
	{
	// 시작
	case 0:
		break;

	// 스테이지 1
	case 1:
		switch (round)
		{
		case 1:
			// 라운드 1 ==================================================

			switch (waveCount)
			{
			case 0:
				waveCount++;
				break;
			case 1:
				//g_pSoundManager->playMusic(2);
				if(waveTime <= 0)
				{
					waveTime = WAVE_INTERVAL;
					waveCount++;
				}
				break;
			case 2:
				//g_pSoundManager->playMusic(3);
				if (waveTime <= 0)
				{
					waveTime = WAVE_INTERVAL;
					waveCount++;
				}
				break;
			case 3:
				//g_pSoundManager->playMusic(4);
				if (waveTime <= 0)
				{
					waveTime = WAVE_INTERVAL;
					waveCount = 0;
					roundStart = false;
					RESTART;
				}
				break;
			}

			// ===========================================================
			break;
		case 2:
			// 라운드 2 ==================================================

			//g_pSoundManager->playMusic(0);

			// ===========================================================
			break;
		case 3:
			// 라운드 3 ==================================================



			// ===========================================================
			break;
		}
		break;

	// 스테이지 2
	case 2:
		switch (round)
		{
		case 1:
			// 라운드 1 ==================================================



			// ===========================================================
			break;
		case 2:
			// 라운드 2 ==================================================



			// ===========================================================
			break;
		case 3:
			// 라운드 3 ==================================================



			// ===========================================================
			break;
		}
		break;

	// 스테이지 3
	case 3:
		switch (round)
		{
		case 1:
			// 라운드 1 ==================================================



			// ===========================================================
			break;
		case 2:
			// 라운드 2 ==================================================



			// ===========================================================
			break;
		case 3:
			// 라운드 3 ==================================================



			// ===========================================================
			break;
		}
		break;
	}

}