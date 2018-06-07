#include "stdafx.h"
#include "SoundManager.h"
#include "BGSound.h"
#include "FxSound.h"

SoundManager::SoundManager()
{
	m_BGSound = NULL;
	m_moveSound = NULL;
	m_breathingSound = NULL;
	m_gearSound = NULL;
	walkInterval = 0;
}


SoundManager::~SoundManager()
{
	m_BGSound->ReleaseSound();// 상속받은 형태가 없기때문에 직접 접근
	m_moveSound->ReleaseSound();
	m_breathingSound->ReleaseSound();
	m_gearSound->ReleaseSound();
}

void SoundManager::musicList()
{
	// BGM
	s_bgm_file.push_back("MoDD");
	s_bgm_file.push_back("Test");
	s_bgm_file.push_back("Test2");

}

void SoundManager::FxList()
{
	// 달리기 발소리 (진흙)
	s_move_file.push_back("Boot_dirt_run1");
	s_move_file.push_back("Boot_dirt_run2");
	s_move_file.push_back("Boot_dirt_run3");
	s_move_file.push_back("Boot_dirt_run4");
	s_move_file.push_back("Boot_dirt_run5");
	s_move_file.push_back("Boot_dirt_run6");

	s_breathing_file.push_back("breathingoutfast");

	s_gear_file.push_back("Gear_Walk1");
	s_gear_file.push_back("Gear_Walk2");
	s_gear_file.push_back("Gear_Walk3");
	s_gear_file.push_back("Gear_Walk4");
	s_gear_file.push_back("Gear_Walk5");
}

void SoundManager::setMusic()
{
	musicList();
	FxList();

	// BGM
	s_bgm = new string[s_bgm_file.size()];

	for (int i = 0; i < s_bgm_file.size(); i++)
	{
		s_bgm[i] = "resources/Sound/Music/";
		s_bgm[i].append(s_bgm_file[i]);
		s_bgm[i].append(".mp3");
	}


	// 발소리
	s_move = new string[s_move_file.size()];

	for (int i = 0; i < s_move_file.size(); i++)
	{
		s_move[i] = "resources/Sound/Effect/Move/";
		s_move[i].append(s_move_file[i]);
		s_move[i].append(".wav");
	}

	// 숨소리
	s_breathing = new string[s_breathing_file.size()];

	for (int i = 0; i < s_breathing_file.size(); i++)
	{
		s_breathing[i] = "resources/Sound/Effect/Move/";
		s_breathing[i].append(s_breathing_file[i]);
		s_breathing[i].append(".wav");
	}

	// 기어
	s_gear = new string[s_gear_file.size()];

	for (int i = 0; i < s_gear_file.size(); i++)
	{
		s_gear[i] = "resources/Sound/Effect/Move/";
		s_gear[i].append(s_gear_file[i]);
		s_gear[i].append(".wav");
	}

	//=================================================

	// BGM
	m_BGSound = new BGSound;
	m_moveSound = new FxSound;
	m_breathingSound = new FxSound;
	m_gearSound = new FxSound;

	m_BGSound->CreateBGSound(s_bgm_file.size(), s_bgm);
	m_moveSound->CreateFxSound(s_move_file.size(), s_move);
	m_breathingSound->CreateFxSound(s_breathing_file.size(), s_breathing);
	m_gearSound->CreateFxSound(s_gear_file.size(), s_gear);
}

void SoundManager::playSound(int soundNum)
{
	m_BGSound->PlaySoundBG(soundNum);
}

void SoundManager::stopSound(int soundNum)
{
	m_BGSound->StopSoundBG(soundNum);
}

void SoundManager::ES_Walk()
{
	rndWalk = rand() % 6 + 1;
	rndGear = rand() % 5 + 1;
	walkInterval++;
	if (walkInterval > 20)
	{
		m_moveSound->PlaySoundFx(rndWalk);
		m_gearSound->PlaySoundFx(rndGear);
		walkInterval = 0;
	}
}
