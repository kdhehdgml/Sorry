#include "stdafx.h"
#include "SoundControl.h"

#define ERRCHK(TEXT) 	if (result != FMOD_OK) cout << TEXT << " FAIL" << endl; else cout << TEXT << " OK" << endl

#define INTERFACE_UPDATETIME 50

#define MAX_CHANNELS 100

#define DOPPLER_SCALE	0.0
#define DISTANCE_FACTOR 10.0
#define ROLLOFF_SCALE	0.1

#define minDistance 5.0
#define maxDistance 50.0

enum SoundType
{
	MUSIC,
	EFFECT,
	AMBIENT,
	_3D
};

SoundControl::SoundControl()
{
	m_pChannelGroup = NULL;

	result = FMOD_System_Create(&m_pSystem);
	result = FMOD_System_Init(m_pSystem, MAX_CHANNELS, FMOD_INIT_NORMAL, NULL);

	// 3D Setting
	result = FMOD_System_Set3DSettings(m_pSystem, DOPPLER_SCALE, DISTANCE_FACTOR, ROLLOFF_SCALE);
}


SoundControl::~SoundControl()
{
	FMOD_System_Close(m_pSystem);
	FMOD_System_Release(m_pSystem);
}

void SoundControl::CreateSound(int nCount, string * SoundFileName, int type)
{
	m_nSoundCount = nCount;
	m_ppSound = new FMOD_SOUND*[nCount];
	m_ppChannel = new FMOD_CHANNEL*[nCount];

	switch (type)
	{
	case MUSIC:
		for (int i = 0; i < nCount; i++)
		{
			FMOD_System_CreateSound(m_pSystem, SoundFileName[i].data(), FMOD_LOOP_NORMAL, 0, &m_ppSound[i]);
		}
		break;
	case EFFECT:
		for (int i = 0; i < nCount; i++)
		{
			FMOD_System_CreateSound(m_pSystem, SoundFileName[i].data(), FMOD_DEFAULT, 0, &m_ppSound[i]);
		}
		break;
	case AMBIENT:
		for (int i = 0; i < nCount; i++)
		{
			FMOD_System_CreateSound(m_pSystem, SoundFileName[i].data(), FMOD_LOOP_NORMAL, 0, &m_ppSound[i]);
		}
		break;
	case _3D:
		for (int i = 0; i < nCount; i++)
		{
			result = FMOD_System_CreateSound(m_pSystem, SoundFileName[i].data(), FMOD_3D, 0, &m_ppSound[i]);
			result = FMOD_Sound_Set3DMinMaxDistance(m_ppSound[i], minDistance, maxDistance);
		}
		break;
	}
}


void SoundControl::PlaySound(int nIndex)
{
	if (nIndex < m_nSoundCount)
	{
		result = FMOD_System_PlaySound(m_pSystem, m_ppSound[nIndex], m_pChannelGroup, false, &m_ppChannel[nIndex]);
	}
}

void SoundControl::StopSound(int nIndex)
{
	if (nIndex < m_nSoundCount)
	{
		FMOD_Channel_Stop(m_ppChannel[nIndex]);
	}
}

void SoundControl::ChangeSound(int nIndex, int nIndex2)
{
	if ((nIndex < m_nSoundCount) && (nIndex2 < m_nSoundCount))
	{
		if (!(FMOD_Channel_IsPlaying(m_ppChannel[nIndex], m_isPlaying)))
		{
			StopSound(nIndex);
			PlaySound(nIndex2);
		}
	}
}

bool SoundControl::isPlaying(int nIndex)
{
	if (nIndex < m_nSoundCount)
		if (!(FMOD_Channel_IsPlaying(m_ppChannel[nIndex], m_isPlaying)))
			return true;

	return false;
}

void SoundControl::volumeControl(int nIndex, float volume)
{
	if (nIndex < m_nSoundCount)
	{
		FMOD_Channel_SetVolume(m_ppChannel[nIndex], volume);
	}
}

void SoundControl::setSpeaker(int nIndex, FMOD_VECTOR sPos, FMOD_VECTOR sVel)
{	
	result = FMOD_Channel_Set3DAttributes(m_ppChannel[nIndex], &sPos, &sVel, 0);
	//FMOD_Channel_SetVolume(m_ppChannel[nIndex], volume);
}

void SoundControl::setListener(FMOD_VECTOR lPos, FMOD_VECTOR lVel, FMOD_VECTOR lFoward, FMOD_VECTOR lUp)
{
	result = FMOD_System_Set3DListenerAttributes(m_pSystem, 0, &lPos, &lVel, &lFoward, &lUp);
}

void SoundControl::ReleaseSound()
{
	int i;
	delete[] m_ppChannel;
	for (i = 0; i < m_nSoundCount; i++)
		FMOD_Sound_Release(m_ppSound[i]);
	delete[] m_ppSound;
}

void SoundControl::Update()
{
	result = FMOD_System_Update(m_pSystem);

}
