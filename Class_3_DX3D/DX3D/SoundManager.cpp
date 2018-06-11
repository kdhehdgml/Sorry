#include "stdafx.h"
#include "SoundManager.h"
#include "SoundControl.h"

#define CreateMP3(m_pSound, folder, s_name, s_name_file, type) s_name = new string[s_name_file.size()];\
				setMP3(folder, s_name, s_name_file);\
				m_pSound = new SoundControl;\
				m_pSound->CreateSound(s_name_file.size(), s_name, type);

#define CreateWAV(m_pSound, folder, s_name, s_name_file, type) s_name = new string[s_name_file.size()];\
				setWAV(folder, s_name, s_name_file);\
				m_pSound = new SoundControl;\
				m_pSound->CreateSound(s_name_file.size(), s_name, type);


enum SoundType
{
	MUSIC,
	EFFECT,
	AMBIENT
};

SoundManager::SoundManager()
{
	m_pBGSound = NULL;
	m_pAmbient = NULL;

	m_pShot_1 = NULL;
	m_pReload = NULL;
	m_pWalk_Dirt = NULL;
	m_pRun_Dirt = NULL;
	m_pGear_Walk = NULL;

	walkInterval = 0;
	runInterval = 0;
	reloadInterval = 0;
}


SoundManager::~SoundManager()
{
	m_pBGSound->ReleaseSound();
	m_pAmbient->ReleaseSound();

	m_pShot_1->ReleaseSound();
	m_pReload->ReleaseSound();
	m_pWalk_Dirt->ReleaseSound();
	m_pRun_Dirt->ReleaseSound();
	m_pGear_Walk->ReleaseSound();
}

void SoundManager::soundList()
{
	// 배경음
	s_music_f.push_back("MoDD");
	s_music_f.push_back("Test");

	// 환경음
	s_ambient_f.push_back("ambient_test_4");


	// 총소리
	s_shot_1_f.push_back("Kar98az1p");
	s_shot_1_f.push_back("Kar98az2p");

	// 재장전
	s_reload_f.push_back("reload7");

	// 발소리
	s_walk_dirt_f.push_back("Boot_dirt_walk1");
	s_walk_dirt_f.push_back("Boot_dirt_walk2");
	s_walk_dirt_f.push_back("Boot_dirt_walk3");
	s_walk_dirt_f.push_back("Boot_dirt_walk4");
	s_walk_dirt_f.push_back("Boot_dirt_walk5");
	s_walk_dirt_f.push_back("Boot_dirt_walk6");

	s_run_dirt_f.push_back("Boot_dirt_run1");
	s_run_dirt_f.push_back("Boot_dirt_run2");
	s_run_dirt_f.push_back("Boot_dirt_run3");
	s_run_dirt_f.push_back("Boot_dirt_run4");
	s_run_dirt_f.push_back("Boot_dirt_run5");
	s_run_dirt_f.push_back("Boot_dirt_run6");

	s_gear_walk_f.push_back("Gear_Walk1");
	s_gear_walk_f.push_back("Gear_Walk4");
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

	CreateMP3(m_pBGSound, "Music/", s_music, s_music_f, MUSIC);
	CreateWAV(m_pAmbient, "Ambient/", s_ambient, s_ambient_f, AMBIENT);

	CreateWAV(m_pShot_1, "Shot/", s_shot_1, s_shot_1_f, EFFECT);
	CreateWAV(m_pReload, "Reload/", s_reload, s_reload_f, EFFECT);
	CreateWAV(m_pWalk_Dirt, "Walk/", s_walk_dirt, s_walk_dirt_f, EFFECT);
	CreateWAV(m_pRun_Dirt, "Run/", s_run_dirt, s_run_dirt_f, EFFECT);
	CreateWAV(m_pGear_Walk, "Gear/", s_gear_walk, s_gear_walk_f, EFFECT);

}

void SoundManager::playMusic(int soundNum)
{
	m_pBGSound->PlaySound(soundNum);
}

void SoundManager::stopMusic(int soundNum)
{
	m_pBGSound->StopSound(soundNum);
}

void SoundManager::playAmbient(int soundNum)
{
	m_pAmbient->PlaySound(soundNum);
}

void SoundManager::stopAmbient(int soundNum)
{
	m_pAmbient->StopSound(soundNum);
}

void SoundManager::ShotSound()
{
	int rN = rand() % s_shot_1_f.size();

	m_pShot_1->PlaySound(rN);
	m_pReload->PlaySound(0);

}

void SoundManager::WalkSound()
{
	int r6 = rand() % 6;
	int rGW = rand() % s_gear_walk_f.size();

	walkInterval++;
	if (walkInterval > 30)
	{
		m_pWalk_Dirt->PlaySound(r6);
		m_pGear_Walk->PlaySound(rGW);

		walkInterval = 0;
	}
}

void SoundManager::RunSound()
{
	int r6 = rand() % 6;
	int rGW = rand() % s_gear_walk_f.size();

	runInterval++;
	if (runInterval > 20)
	{
		m_pRun_Dirt->PlaySound(r6);
		m_pGear_Walk->PlaySound(rGW);

		runInterval = 0;
	}
}
