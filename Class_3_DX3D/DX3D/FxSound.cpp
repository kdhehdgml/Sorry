#include "stdafx.h"
#include "FxSound.h"


FxSound::FxSound()
{
	FMOD_System_Create(&m_pSystem);
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);

}

FxSound::~FxSound()
{
	FMOD_System_Close(m_pSystem);
	FMOD_System_Release(m_pSystem);
}

void FxSound::CreateFxSound(int nCount, string * SoundFileName)
{
	m_nFxSoundCount = nCount;
	m_ppFxSound = new FMOD_SOUND*[nCount];
	m_ppFxChannel = new FMOD_CHANNEL*[nCount];

	for (int i = 0; i < nCount; i++)
		FMOD_System_CreateSound(m_pSystem, SoundFileName[i].data(), FMOD_DEFAULT, 0, &m_ppFxSound[i]);

}

void FxSound::PlaySoundFx(int nIndex)
{
	FMOD_CHANNELGROUP *pChannelss = NULL;
	if (nIndex < m_nFxSoundCount)
	{
		FMOD_System_PlaySound(m_pSystem, m_ppFxSound[nIndex], pChannelss, 0, &m_ppFxChannel[nIndex]);
	}

}

void FxSound::StopSoundFx(int nIndex)
{
	if (nIndex < m_nFxSoundCount)
	{
		FMOD_Channel_Stop(m_ppFxChannel[nIndex]);
	}
}

void FxSound::ReleaseSound()
{
	int i;
	delete[] m_ppFxChannel;
	for (i = 0; i < m_nFxSoundCount; i++)
		FMOD_Sound_Release(m_ppFxSound[i]);
	delete[] m_ppFxSound;
}

void FxSound::Update()
{
	if (!m_pSystem)
		FMOD_System_Update(m_pSystem);

}
