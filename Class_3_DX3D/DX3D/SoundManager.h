#pragma once

class BGSound;
class FxSound;

#define g_pSoundManager SoundManager::GetInstance()

class SoundManager
{
	SINGLETON(SoundManager)
private:
	BGSound * m_BGSound;
	FxSound * m_moveSound;
	FxSound * m_breathingSound;
	FxSound * m_gearSound;

	string * s_bgm;
	vector<string> s_bgm_file;

	string * s_move;
	vector<string> s_move_file;

	string * s_breathing;
	vector<string> s_breathing_file;

	string * s_gear;
	vector<string> s_gear_file;

	int walkInterval;
	int rndWalk;
	int rndGear;

public:
	void musicList();
	void FxList();
	void setMusic();
	void playSound(int soundNum);
	void stopSound(int soundNum);
	
	void ES_Walk();
};

