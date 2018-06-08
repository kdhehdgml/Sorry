#pragma once

class SoundControl;

#define g_pSoundManager SoundManager::GetInstance()

class SoundManager
{
	SINGLETON(SoundManager)
private:
	SoundControl * m_pBGSound;
	SoundControl * m_pShotSound_1;

	string * s_music;
	vector<string> s_music_file;

	string * s_shot_1;
	vector<string> s_shot_1_file;

public:
	void soundList();
	void setMP3(string folder, string * s_name, vector<string> s_name_file);
	void setWAV(string folder, string * s_name, vector<string> s_name_file);
	void createSound();
	void playMusic(int soundNum);
	void stopMusic(int soundNum);
	void playSound();
};

