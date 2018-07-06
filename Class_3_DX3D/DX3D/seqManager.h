#pragma once

#define g_pSeqManager seqManager::GetInstance()



class seqManager
{
	SINGLETON(seqManager)
private:
	int checkTime;
	bool stopTime;
	int stage;
	int round;

public:
	void Init();
	void Update();
	int getStage();
	int getRound();
	
private:
	void setStage();
	void stage_1();
	void stage_2();
	void stage_3();
};

