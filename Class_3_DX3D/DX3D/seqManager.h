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

	bool roundStart;
	int waveCount;
	int waveTime;

	bool spawnCheck;

	bool isMusicPlay;

	bool incomingVoice;
	int incomingVoiceTime;


public:
	int spawnNum;
	bool stopUpdate;

	void Init();
	void Update();
	int getStage();
	int getRound();

private:
	int setReadyTime(int stage, int round);
	void setStage();
	void Level(int stage, int round);
};

