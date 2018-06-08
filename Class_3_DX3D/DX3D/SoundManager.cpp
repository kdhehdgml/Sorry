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
	m_pShotSound_1 = NULL;
	m_pWalk_Dirt = NULL;
	m_pRun_Dirt = NULL;
	m_pGear_Walk = NULL;

	walkInterval = 0;
	runInterval = 0;
}


SoundManager::~SoundManager()
{
	m_pBGSound->ReleaseSound();
	m_pShotSound_1->ReleaseSound();
	m_pWalk_Dirt->ReleaseSound();
	m_pRun_Dirt->ReleaseSound();
	m_pGear_Walk->ReleaseSound();
}

void SoundManager::soundList()
{
	s_music_file.push_back("MoDD");
	s_music_file.push_back("Test");

	s_shot_1_file.push_back("Kar98az1p");
	s_shot_1_file.push_back("Kar98az2p");


	s_walk_dirt_file.push_back("Boot_dirt_walk1");
	s_walk_dirt_file.push_back("Boot_dirt_walk2");
	s_walk_dirt_file.push_back("Boot_dirt_walk3");
	s_walk_dirt_file.push_back("Boot_dirt_walk4");
	s_walk_dirt_file.push_back("Boot_dirt_walk5");
	s_walk_dirt_file.push_back("Boot_dirt_walk6");

	s_run_dirt_file.push_back("Boot_dirt_run1");
	s_run_dirt_file.push_back("Boot_dirt_run2");
	s_run_dirt_file.push_back("Boot_dirt_run3");
	s_run_dirt_file.push_back("Boot_dirt_run4");
	s_run_dirt_file.push_back("Boot_dirt_run5");
	s_run_dirt_file.push_back("Boot_dirt_run6");

	s_gear_walk_file.push_back("Gear_Walk1");
	s_gear_walk_file.push_back("Gear_Walk2");
	s_gear_walk_file.push_back("Gear_Walk3");
	s_gear_walk_file.push_back("Gear_Walk4");
	s_gear_walk_file.push_back("Gear_Walk5");
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

	CreateMP3(m_pBGSound, "Music/", s_music, s_music_file, MUSIC);
	CreateWAV(m_pShotSound_1, "Shot/", s_shot_1, s_shot_1_file, EFFECT);
	CreateWAV(m_pWalk_Dirt, "Walk/", s_walk_dirt, s_walk_dirt_file, EFFECT);
	CreateWAV(m_pRun_Dirt, "Run/", s_run_dirt, s_run_dirt_file, EFFECT);
	CreateWAV(m_pGear_Walk, "Gear/", s_gear_walk, s_gear_walk_file, EFFECT);


}

void SoundManager::playMusic(int soundNum)
{
	m_pBGSound->PlaySound(soundNum);
}

void SoundManager::stopMusic(int soundNum)
{
	m_pBGSound->StopSound(soundNum);
}

void SoundManager::ShotSound()
{
	int rN = rand() % s_shot_1_file.size();
	m_pShotSound_1->PlaySound(rN);
}

void SoundManager::WalkSound()
{
	int r6 = rand() % 6;
	int r5 = rand() % 5;

	walkInterval++;
	if (walkInterval > 30)
	{
		m_pWalk_Dirt->PlaySound(r6);
		m_pGear_Walk->PlaySound(r5);

		walkInterval = 0;
	}
}

void SoundManager::RunSound()
{
	int r6 = rand() % 6;
	int r5 = rand() % 5;

	runInterval++;
	if (runInterval > 20)
	{
		m_pRun_Dirt->PlaySound(r6);
		m_pGear_Walk->PlaySound(r5);

		runInterval = 0;
	}
}
