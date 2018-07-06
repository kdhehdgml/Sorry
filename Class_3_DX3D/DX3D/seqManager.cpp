#include "stdafx.h"
#include "seqManager.h"
#include "UnitBox.h"

#define Max 100

seqManager::seqManager()
{
	checkTime = 0;
	stopTime = false;
	stage = 0;
	round = 0;
}

seqManager::~seqManager()
{
}

void seqManager::Init()
{
	UnitBox().CreateMob(20);
}

void seqManager::Update()
{
	if(!stopTime)
		checkTime++;
	
	setStage();

	// 디버그 텍스트
	{
		Debug->AddText("이벤트 타이머: ");
		Debug->AddText(checkTime);
		Debug->AddText(" / 스테이지: ");
		Debug->AddText(stage);
		Debug->AddText(" / 라운드: ");
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

void seqManager::setStage()
{
	if (stage == 0)
	{
		if (checkTime > Max)
		{
			checkTime = 0;
			stage = 1;
		}
	}
	else if (stage == 1)
	{
		if (checkTime > Max)
		{
			if (round < 3)
			{
				checkTime = 0;
				round++;
			}
			else if (round == 3)
			{
				checkTime = 0;
				round = 0;
				stage = 2;
			}
		}
	}
	else if (stage == 2)
	{
		if (checkTime > Max)
		{
			if (round < 3)
			{
				checkTime = 0;
				round++;
			}
			else if (round == 3)
			{
				checkTime = 0;
				round = 0;
				stage = 3;
			}
		}
	}
	else if (stage == 3)
	{
		if (checkTime > Max)
		{
			if (round < 3)
			{
				checkTime = 0;
				round++;
			}
			else if (round == 3)
			{
				checkTime = 0;
				stopTime = true;
			}
		}
	}
}

void seqManager::stage_1()
{
}

void seqManager::stage_2()
{
}

void seqManager::stage_3()
{
}
