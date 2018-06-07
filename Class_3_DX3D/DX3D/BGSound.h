#pragma once
class BGSound // 클래스 이름은 추후 변경
{
private:
	//fmod사용을 위한 변수들
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

