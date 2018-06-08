#include "stdafx.h"
#include "SoundManager.h"
#include "SoundControl.h"

enum SoundType
{
	MUSIC,
	EFFECT,
	AMBIENT
};

SoundManager::SoundManager()
{
	m_pBGSound = NULL;
	m_pShotSound_1 = NULL;
}


SoundManager::~SoundManager()
{
	m_pBGSound->ReleaseSound();
	m_pShotSound_1->ReleaseSound();
}

void SoundManager::soundList()
{
	s_music_file.push_back("MoDD");
	s_music_file.push_back("Test");

	s_shot_1_file.push_back("0815-1pp");
	s_shot_1_file.push_back("0815-2pp");
	s_shot_1_file.push_back("0815-3pp");
	s_shot_1_file.push_back("0815-4pp");
	s_shot_1_file.push_back("0815-5pp");
}

void SoundManager::setMP3(string folder, string * s_name, vector<string> s_name_file)
{
	for (int i = 0; i < s_name_file.size(); i++)
	{
		s_name[i] = "resources/Sound/";
		s_name[i].append(folder);
		s_name[i].append(s_name_file[i]);
		s_name[i].append(".mp3");
	}
}

void SoundManager::setWAV(string folder, string * s_name, vector<string> s_name_file)
{
	for (int i = 0; i < s_name_file.size(); i++)
	{
		s_name[i] = "resources/Sound/";
		s_name[i].append(folder);
		s_name[i].append(s_name_file[i]);
		s_name[i].append(".wav");
	}
}

void SoundManager::createSound()
{
	soundList();

	// Dynamic
	s_music = new string[s_music_file.size()];
	s_shot_1 = new string[s_shot_1_file.size()];

	// Set ======================================================
	setMP3("Music/", s_music, s_music_file);
	setWAV("Shot/", s_shot_1, s_shot_1_file);


	// Create ===================================================
	m_pBGSound = new SoundControl;
	m_pShotSound_1 = new SoundControl;

	m_pBGSound->CreateSound(s_music_file.size(), s_music, MUSIC);
	m_pShotSound_1->CreateSound(s_shot_1_file.size(), s_shot_1, EFFECT);
}

void SoundManager::playMusic(int soundNum)
{
	m_pBGSound->PlaySound(soundNum);
}

void SoundManager::stopMusic(int soundNum)
{
	m_pBGSound->StopSound(soundNum);
}

void SoundManager::playSound()
{
	int rN = rand() % 5 + 1;
	m_pShotSound_1->PlaySound(rN);
}