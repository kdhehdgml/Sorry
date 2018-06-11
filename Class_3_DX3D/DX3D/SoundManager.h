#pragma once

class SoundControl;

#define g_pSoundManager SoundManager::GetInstance()

class SoundManager
{
	SINGLETON(SoundManager)
private:
	//===================================================================================
	SoundControl * m_pBGSound;		string * s_music;		vector<string> s_music_f;
	SoundControl * m_pAmbient;		string * s_ambient;		vector<string> s_ambient_f;

	SoundControl * m_pShot_1;		string * s_shot_1;		vector<string> s_shot_1_f;
	SoundControl * m_pWalk_Dirt;	string * s_walk_dirt;	vector<string> s_walk_dirt_f;
	SoundControl * m_pRun_Dirt;		string * s_run_dirt;	vector<string> s_run_dirt_f;
	SoundControl * m_pGear_Walk;	string * s_gear_walk;	vector<string> s_gear_walk_f;
	//===================================================================================

	int walkInterval;
	int runInterval;

public:
	void soundList();
	void setMP3(string folder, string * s_name, vector<string> s_name_file);
	void setWAV(string folder, string * s_name, vector<string> s_name_file);
	void createSound();

	void playMusic(int soundNum);
	void stopMusic(int soundNum);

	void playAmbient(int soundNum);
	void stopAmbient(int soundNum);

	void ShotSound();
	void WalkSound();
	void RunSound();
};

