#pragma once

class BGSound;

#define g_pSoundManager SoundManager::GetInstance()

class SoundManager
{
	SINGLETON(SoundManager)
private:
	BGSound * m_pBGSound;

public:
	void setMusic();
	void playSound(int soundNum);
	void stopSound(int soundNum);
};

