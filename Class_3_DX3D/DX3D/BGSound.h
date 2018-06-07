#pragma once
class BGSound // Ŭ���� �̸��� ���� ����
{
private:
	//fmod����� ���� ������
	FMOD_SYSTEM *	m_pSystem;	
	FMOD_SOUND **	m_ppBGSound;
	FMOD_CHANNEL **	m_ppBGChannel;

	int m_nBGSoundCount;

public:
	BGSound();
	~BGSound();

	void CreateBGSound(int nCount, string* SoundFileName);
	void PlaySoundBG(int nIndex);
	void StopSoundBG(int nIndex);
	void ReleaseSound();
	void Update();
};

