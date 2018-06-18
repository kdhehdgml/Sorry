#include "stdafx.h"
#include "SoundControl.h"

enum SoundType
{
	MUSIC,
	EFFECT,
	AMBIENT
};

SoundControl::SoundControl()
{
	//fmod 사용을 위한 설정
	FMOD_System_Create(&m_pSystem);
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);
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

	switch(type)
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
	}

}

void SoundControl::PlaySound(int nIndex)
{
	FMOD_CHANNELGROUP *pChannelss = NULL;
	if (nIndex < m_nSoundCount)
	{
		FMOD_System_PlaySound(m_pSystem, m_ppSound[nIndex], pChannelss, 0, &m_ppChannel[nIndex]);
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

void SoundControl::sound3D(int nIndex)
{
	FMOD_System_Set3DSettings(m_pSystem, 1.0, 1.0, 1.0);
	FMOD_VECTOR pos = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR alt_pan_pos = { 0.0f,0.0f,0.0f };
	float freq = 0.0f;
	FMOD_Channel_Set3DAttributes(m_ppChannel[nIndex], &pos, &vel, &alt_pan_pos);
	FMOD_Channel_GetFrequency(m_ppChannel[nIndex], &freq);
	//FMOD_Channel_SetVolume(m_ppChannel[nIndex], volume);

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
	if (!m_pSystem)
		FMOD_System_Update(m_pSystem);
}
