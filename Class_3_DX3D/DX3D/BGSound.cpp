#include "stdafx.h"
#include "BGSound.h"


BGSound::BGSound()
{
	//fmod 사용을 위한 설정
	FMOD_System_Create(&m_pSystem);
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);
}


BGSound::~BGSound()
{
	FMOD_System_Close(m_pSystem);
	FMOD_System_Release(m_pSystem);
}

void BGSound::CreateBGSound(int nCount, string * SoundFileName)
{
	m_nBGSoundCount = nCount;
	m_ppBGSound = new FMOD_SOUND*[nCount];
	m_ppBGChannel = new FMOD_CHANNEL*[nCount];

	for (int i = 0; i < nCount; i++)
		FMOD_System_CreateSound(m_pSystem, SoundFileName[i].data(), FMOD_LOOP_NORMAL, 0, &m_ppBGSound[i]);
}

void BGSound::PlaySoundBG(int nIndex)
{
	FMOD_CHANNELGROUP *pChannelss = NULL;
	if (nIndex < m_nBGSoundCount)
	{
		FMOD_System_PlaySound(m_pSystem, m_ppBGSound[nIndex], pChannelss, 0, &m_ppBGChannel[nIndex]);
	}
}

void BGSound::StopSoundBG(int nIndex)
{
	if (nIndex < m_nBGSoundCount)
	{
		FMOD_Channel_Stop(m_ppBGChannel[nIndex]);
	}
}

void BGSound::ReleaseSound()
{
	int i;
	delete[] m_ppBGChannel;
	for (i = 0; i < m_nBGSoundCount; i++)
		FMOD_Sound_Release(m_ppBGSound[i]);
	delete[] m_ppBGSound;
}

void BGSound::Update()
{
	if (!m_pSystem)
		FMOD_System_Update(m_pSystem);
}
