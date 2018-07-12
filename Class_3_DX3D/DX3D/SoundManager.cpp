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
	AMBIENT,
	_3D
};

SoundManager::SoundManager()
{
	m_pMusic = NULL;
	m_pAmbient = NULL;

	m_p3D = NULL;

	m_pShot_1 = NULL;
	m_pReload = NULL;
	m_pWalk_Dirt = NULL;
	m_pRun_Dirt = NULL;
	m_pGear_Walk = NULL;
	m_pWhistle = NULL;
	
	m_pV_Death = NULL;

	walkInterval = 0;
	runInterval = 0;
	reloadInterval = 0;
	volume_music = GSM().volume_music_init;
	volume_effect = GSM().volume_music_init;

	// 3D Setting
	ListenerPos = { 0.0f, 0.0f, 0.0f };
	ListenerVel = { 0.0f, 0.0f, 0.0f };
	ListenerForward = { 0.0f, 0.0f, 1.0f };
	ListenerUp = { 0.0f, 1.0f, 0.0f };
	ListenerLastPos = { 0.0f, 0.0f, 0.0f };

	SpeakerPos = { 0.0f, 0.0f, 0.0f };
	SpeakerVel = { 0.0f, 0.0f, 0.0f };

	isCreate = false;

}


SoundManager::~SoundManager()
{
	m_pMusic->ReleaseSound();
	m_pAmbient->ReleaseSound();

	m_p3D->ReleaseSound();

	m_pShot_1->ReleaseSound();
	m_pReload->ReleaseSound();
	m_pWalk_Dirt->ReleaseSound();
	m_pRun_Dirt->ReleaseSound();
	m_pGear_Walk->ReleaseSound();
	m_pWhistle->ReleaseSound();

	m_pV_Death->ReleaseSound();
}

void SoundManager::soundList()
{
	// 배경음
	s_music_f.push_back("12. HoI IV Allies Main Theme");
	s_music_f.push_back("04. Krakow");
	s_music_f.push_back("15. Operation Barbarossa");

	// 환경음
	s_ambient_f.push_back("ambient_test_4");

	// 3D
	s_3D_f.push_back("Kar98az1p");
	s_3D_f.push_back("Kar98az2p");
	s_3D_f.push_back("0815-1pp");
	s_3D_f.push_back("0815-2pp");
	s_3D_f.push_back("0815-3pp");
	s_3D_f.push_back("0815-4pp");
	s_3D_f.push_back("0815-5pp");

	// 총소리
	s_shot_1_f.push_back("Kar98az1p");
	s_shot_1_f.push_back("Kar98az2p");

	// 휘슬
	s_whistle_f.push_back("TrenchWhistle");

	// 재장전
	s_reload_f.push_back("reload7"); 
	s_reload_f.push_back("Reload2altdrycut");

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

	// 음성
	s_vDeath_f.push_back("Death01");
	s_vDeath_f.push_back("Death02");
	s_vDeath_f.push_back("Death03");
	s_vDeath_f.push_back("Death04");
	s_vDeath_f.push_back("Death05");
	s_vDeath_f.push_back("Death06");
	s_vDeath_f.push_back("Death07");
	s_vDeath_f.push_back("Death08");
	s_vDeath_f.push_back("Death09");
	s_vDeath_f.push_back("Death11");
	s_vDeath_f.push_back("Death12");
	s_vDeath_f.push_back("Death13");
	s_vDeath_f.push_back("Death14");
	s_vDeath_f.push_back("Death15");
	s_vDeath_f.push_back("Death16");
	s_vDeath_f.push_back("Death17");
	s_vDeath_f.push_back("Death18");
	s_vDeath_f.push_back("Death19");
	s_vDeath_f.push_back("Death20");
	s_vDeath_f.push_back("Death21");
	s_vDeath_f.push_back("Death22");
	s_vDeath_f.push_back("Death23");
	s_vDeath_f.push_back("Death24");
	s_vDeath_f.push_back("Death25");
	s_vDeath_f.push_back("Death26");

	s_vIncoming_f.push_back("IncomingEnemy2");
	s_vIncoming_f.push_back("IncomingEnemy3");
	s_vIncoming_f.push_back("IncomingEnemy4");
	s_vIncoming_f.push_back("IncomingEnemy5");

	s_vReload_f.push_back("Reload1");
	s_vReload_f.push_back("Reload2");
	s_vReload_f.push_back("Reload3");
	s_vReload_f.push_back("Reload4");
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
	if (!isCreate)
	{
		soundList();

		CreateWAV(m_pWhistle, "Effect/", s_whistle, s_whistle_f, EFFECT);
		CreateWAV(m_pV_Death, "Voice/Death/", s_vDeath, s_vDeath_f, _3D);
		CreateWAV(m_pV_Incoming, "Voice/Incoming/", s_vIncoming, s_vIncoming_f, EFFECT);
		CreateWAV(m_pV_Reload, "Voice/Reload/", s_vReload, s_vReload_f, _3D);

		CreateMP3(m_pMusic, "Music/", s_music, s_music_f, MUSIC);
		CreateWAV(m_pAmbient, "Ambient/", s_ambient, s_ambient_f, AMBIENT);

		CreateWAV(m_p3D, "Shot/", s_3D, s_3D_f, _3D);

		CreateWAV(m_pShot_1, "Shot/", s_shot_1, s_shot_1_f, EFFECT);
		CreateWAV(m_pReload, "Reload/", s_reload, s_reload_f, EFFECT);
		CreateWAV(m_pWalk_Dirt, "Walk/", s_walk_dirt, s_walk_dirt_f, EFFECT);
		CreateWAV(m_pRun_Dirt, "Run/", s_run_dirt, s_run_dirt_f, EFFECT);
		CreateWAV(m_pGear_Walk, "Gear/", s_gear_walk, s_gear_walk_f, EFFECT);
		//CreateWAV(m_pWhistle, "Effect/", s_whistle, s_whistle_f, EFFECT);

		isCreate = true;
	}
}

void SoundManager::volumeControl_Music(float volume)
{
	for (int i = 0; i < s_music_f.size(); i++)
	{
		m_pMusic->volumeControl(i, volume);
		volume_music = volume;
	}
}

void SoundManager::playMusic(int soundNum)
{
	for (int i = 0; i < s_music_f.size(); i++)
	{
		if(i != soundNum)
			m_pMusic->StopSound(i);
	}

	if (!m_pMusic->isPlaying(soundNum))
	{
		m_pMusic->volumeControl(soundNum, volume_music);
		m_pMusic->PlaySound(soundNum);
	}
}

void SoundManager::stopMusic(int soundNum)
{
	m_pMusic->StopSound(soundNum);
}

void SoundManager::changeMusic(int soundNum1, int soundNum2)
{
	m_pMusic->ChangeSound(soundNum1, soundNum2);
}

void SoundManager::playAmbient(int soundNum)
{
	m_pAmbient->PlaySound(soundNum);
}

void SoundManager::stopAmbient(int soundNum)
{
	m_pAmbient->StopSound(soundNum);
}

// 3D

void SoundManager::play3D(int soundNum)
{
	//if (!m_p3D->isPlaying(soundNum))
	//{
		m_p3D->volumeControl(soundNum, volume_music);
		m_p3D->PlaySound(soundNum);
	//}
}

void SoundManager::updateSpeaker(int type, int soundNum, D3DXVECTOR3 sPos)
{
	SpeakerPos = { sPos.x, sPos.y, sPos.z };
	
	switch (type)
	{
	case 1:
		m_p3D->setSpeaker(soundNum, SpeakerPos, SpeakerVel);
		play3D(soundNum);
		break;
	case 2:
		r = rand() % 26;
		m_pV_Death->setSpeaker(r, SpeakerPos, SpeakerVel);
		voiceSound(vType::DEATH, r);
		break;
	case 3:
		r = rand() % 4;
		m_pV_Reload->setSpeaker(r, SpeakerPos, SpeakerVel);
		voiceSound(vType::RELOAD, r);
	}
}

void SoundManager::updateListener(D3DXVECTOR3 lPos)
{
	ListenerPos = { lPos.x, lPos.y, lPos.z };

	ListenerVel.x = (ListenerPos.x - ListenerLastPos.x) * (1000.0 / 50.0);
	ListenerVel.y = (ListenerPos.y - ListenerLastPos.y) * (1000.0 / 50.0);
	ListenerVel.z = (ListenerPos.z - ListenerLastPos.z) * (1000.0 / 50.0);

	ListenerLastPos = ListenerPos;

	ListenerForward = { g_pCamera->getDir().x , 0, g_pCamera->getDir().z };

	m_p3D->setListener(ListenerPos, ListenerVel, ListenerForward, ListenerUp);
	update3D();
}

D3DXVECTOR3 SoundManager::getSpeakerPos()
{
	D3DXVECTOR3 sPos;
	sPos.x = SpeakerPos.x;
	sPos.y = SpeakerPos.y;
	sPos.z = SpeakerPos.z;

	return sPos;
}

D3DXVECTOR3 SoundManager::getListenerPos()
{
	D3DXVECTOR3 lPos;
	lPos.x = ListenerPos.x;
	lPos.y = ListenerPos.y;
	lPos.z = ListenerPos.z;

	return lPos;
}

void SoundManager::setSpeakerPos(D3DXVECTOR3 sPos)
{
	SpeakerPos.x = sPos.x;
	SpeakerPos.y = sPos.y;
	SpeakerPos.z = sPos.z;
}

void SoundManager::update3D()
{
	m_p3D->Update();
}



//===========================================================================================
//     넘을 수 없는 4차원의 벽
//===========================================================================================



void SoundManager::ShotSound()
{
	r = rand() % s_shot_1_f.size();

	m_pShot_1->PlaySound(r);
}

void SoundManager::ReloadSound()
{
	m_pReload->PlaySound(1);
}

void SoundManager::WalkSound()
{
	int r6 = rand() % 6;
	r = rand() % s_gear_walk_f.size();

	walkInterval++;
	if (walkInterval > 30)
	{
		m_pWalk_Dirt->PlaySound(r6);
		m_pGear_Walk->PlaySound(r);

		walkInterval = 0;
	}
}

void SoundManager::RunSound()
{
	int r6 = rand() % 6;
	r = rand() % s_gear_walk_f.size();

	runInterval++;
	if (runInterval > 20)
	{
		m_pRun_Dirt->PlaySound(r6);
		m_pGear_Walk->PlaySound(r);

		runInterval = 0;
	}
}

void SoundManager::effectSound(int type, int soundNum)
{
	switch (type)
	{
	case 0:
		m_pWhistle->PlaySound(soundNum);
		break;
	case 1:
		break;
	}
	
}

void SoundManager::voiceSound(int type, int soundNum)
{
	switch (type)
	{
	case 1: // 사망
		m_pV_Death->volumeControl(soundNum, volume_music);
		m_pV_Death->PlaySound(soundNum);
		break;
	case 2: // 인커밍
		r = rand() % 4;
		m_pV_Incoming->volumeControl(r, volume_music);
		m_pV_Incoming->PlaySound(r);
	case 3: // 재장전
		m_pV_Reload->volumeControl(soundNum, volume_music);
		m_pV_Reload->PlaySound(soundNum);
	}
}
