#pragma once

class SoundControl;

#define g_pSoundManager SoundManager::GetInstance()

class SoundManager
{
	SINGLETON(SoundManager)
private:
	SoundControl * m_pBGSound;
	SoundControl * m_pShotSound_1;
	SoundControl * m_pWalk_Dirt;
	SoundControl * m_pRun_Dirt;
	SoundControl * m_pGear_Walk;
	

	string * s_music;
	vector<string> s_music_file;

	string * s_shot_1;
	vector<string> s_shot_1_file;

	string * s_walk_dirt;
	vector<string> s_walk_dirt_file;

	string * s_run_dirt;
	vector<string> s_run_dirt_file;

	string * s_gear_walk;
	vector<string> s_gear_walk_file;

	int walkInterval;
	int runInterval;

public:
	void soundList();
	void setMP3(string folder, string * s_name, vector<string> s_name_file);
	void setWAV(string folder, string * s_name, vector<string> s_name_file);
	void createSound();
	void playMusic(int soundNum);
	void stopMusic(int soundNum);
	void ShotSound();
	void WalkSound();
	void RunSound();
};

