#include "stdafx.h"
#include "SoundManager.h"
#include "BGSound.h"

SoundManager::SoundManager()
{
	m_pBGSound = NULL;
}


SoundManager::~SoundManager()
{
	m_pBGSound->ReleaseSound();// 상속받은 형태가 없기때문에 직접 접근
}

void SoundManager::setMusic()
{
	// BGM
	m_pBGSound = new BGSound;
	string strBGFileName[] = { "resources/Sound/Music/" };
	// 파일 위치 1개의 BG만 설정했습니다.
	// 배열이라서 여러개 설정가능 채널을 사용해서 연관있는 사운드끼리 채널을 사용해야할것.
	string strEffectFileName = "SoundBG";	 // 파일 이름
	
	strBGFileName[0].append(strEffectFileName);
	strBGFileName[0].append(".mp3");

	m_pBGSound->CreateBGSound(1, strBGFileName); // 첫번째 사운드를 사용하겠다.
}

void SoundManager::playSound(int soundNum)
{
	m_pBGSound->PlaySoundBG(soundNum);
}

void SoundManager::stopSound(int soundNum)
{
	m_pBGSound->StopSoundBG(soundNum);
}
