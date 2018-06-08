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

	s_shot_1_file.push_back("0815-1pp");
	s_shot_1_file.push_back("0815-2pp");
	s_shot_1_file.push_back("0815-3pp");
	s_shot_1_file.push_back("0815-4pp");
	s_shot_1_file.push_back("0815-5pp");

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

	// Dynamic
	s_music = new string[s_music_file.size()];
	s_shot_1 = new string[s_shot_1_file.size()];
	s_walk_dirt = new string[s_walk_dirt_file.size()];
	s_run_dirt = new string[s_run_dirt_file.size()];
	s_gear_walk = new string[s_gear_walk_file.size()];

	// Set ======================================================
	setMP3("Music/", s_music, s_music_file);
	setWAV("Shot/", s_shot_1, s_shot_1_file);
	setWAV("Walk/", s_walk_dirt, s_walk_dirt_file);
	setWAV("Run/", s_run_dirt, s_run_dirt_file);
	setWAV("Gear/", s_gear_walk, s_gear_walk_file);

	// Create ===================================================
	m_pBGSound = new SoundControl;
	m_pShotSound_1 = new SoundControl;
	m_pWalk_Dirt = new SoundControl;
	m_pRun_Dirt = new SoundControl;
	m_pGear_Walk = new SoundControl;


	m_pBGSound->CreateSound(s_music_file.size(), s_music, MUSIC);
	m_pShotSound_1->CreateSound(s_shot_1_file.size(), s_shot_1, EFFECT);
	m_pWalk_Dirt->CreateSound(s_walk_dirt_file.size(), s_walk_dirt, EFFECT);
	m_pRun_Dirt->CreateSound(s_run_dirt_file.size(), s_run_dirt, EFFECT);
	m_pGear_Walk->CreateSound(s_gear_walk_file.size(), s_gear_walk, EFFECT);
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
	int rN = rand() % 5 + 1;
	m_pShotSound_1->PlaySound(rN);
}

void SoundManager::WalkSound()
{
	int r6 = rand() % 6 + 1;
	int r5 = rand() % 5 + 1;

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
	int r6 = rand() % 6 + 1;
	int r5 = rand() % 5 + 1;

	runInterval++;
	if (runInterval > 20)
	{
		m_pRun_Dirt->PlaySound(r6);
		m_pGear_Walk->PlaySound(r5);

		runInterval = 0;
	}
}
