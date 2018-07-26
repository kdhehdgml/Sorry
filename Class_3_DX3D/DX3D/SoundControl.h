#pragma once
class SoundControl
{
private:
	FMOD_SYSTEM *		m_pSystem;	
	FMOD_SOUND **		m_ppSound;
	FMOD_CHANNEL **		m_ppChannel;
	FMOD_CHANNELGROUP * m_pChannelGroup;

	FMOD_BOOL *			m_isPlaying;

	FMOD_RESULT result;

	//FMOD_RESULT result;

	int m_nSoundCount;

public:
	SoundControl();
	~SoundControl();
	
	void CreateSound(int nCount, string* SoundFileName, int type);
	void PlaySound(int nIndex);
	void StopSound(int nIndex);
	void ChangeSound(int nIndex, int nIndex2);
	bool isPlaying(int nIndex);
	void volumeControl(int nIndex, float volume);
	bool setSpeaker(int nIndex, FMOD_VECTOR sPos, FMOD_VECTOR sVel);
	void setListener(FMOD_VECTOR lPos, FMOD_VECTOR lVel, FMOD_VECTOR lFoward, FMOD_VECTOR lUp);

	void ReleaseSound();
	void Update();
};

