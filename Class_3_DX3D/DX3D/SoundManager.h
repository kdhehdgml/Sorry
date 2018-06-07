#pragma once

class BGSound;

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

private:
	BGSound * m_pBGSound;

public:
	void setMusic();
	void playSound(int soundNum);
	void stopSound(int soundNum);
};

