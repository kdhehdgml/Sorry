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

	int setReadyTime(int stage, int round);
	void setStage();
	void Level(int stage, int round);
};

