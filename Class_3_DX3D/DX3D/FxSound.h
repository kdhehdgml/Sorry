#pragma once
class FxSound
{
private:
	//fmod����� ���� ������
	FMOD_SYSTEM * m_pSystem;
	FMOD_SOUND **	m_ppFxSound;
	FMOD_CHANNEL **	m_ppFxChannel;

	int m_nFxSoundCount;

public:
	FxSound();
	~FxSound();

	void CreateFxSound(int nCount, string* SoundFileName);
	void PlaySoundFx(int nIndex);
	void StopSoundFx(int nIndex);
	void ReleaseSound();
	void Update();
};

