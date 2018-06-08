#pragma once
class SoundControl
{
private:
	FMOD_SYSTEM *	m_pSystem;	
	FMOD_SOUND **	m_ppSound;
	FMOD_CHANNEL **	m_ppChannel;

	int m_nSoundCount;

public:
	SoundControl();
	~SoundControl();

	void CreateSound(int nCount, string* SoundFileName, int type);
	void PlaySound(int nIndex);
	void StopSound(int nIndex);
	void ReleaseSound();
	void Update();
};

