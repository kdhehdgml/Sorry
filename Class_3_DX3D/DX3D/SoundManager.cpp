#include "stdafx.h"
#include "SoundManager.h"
#include "BGSound.h"

SoundManager::SoundManager()
{
	m_pBGSound = NULL;
}


SoundManager::~SoundManager()
{
	m_pBGSound->ReleaseSound();// ��ӹ��� ���°� ���⶧���� ���� ����
}

void SoundManager::setMusic()
{
	// BGM
	m_pBGSound = new BGSound;
	string strBGFileName[] = { "resources/Sound/Music/" };
	// ���� ��ġ 1���� BG�� �����߽��ϴ�.
	// �迭�̶� ������ �������� ä���� ����ؼ� �����ִ� ���峢�� ä���� ����ؾ��Ұ�.
	string strEffectFileName = "SoundBG";	 // ���� �̸�
	
	strBGFileName[0].append(strEffectFileName);
	strBGFileName[0].append(".mp3");

	m_pBGSound->CreateBGSound(1, strBGFileName); // ù��° ���带 ����ϰڴ�.
}

void SoundManager::playSound(int soundNum)
{
	m_pBGSound->PlaySoundBG(soundNum);
}

void SoundManager::stopSound(int soundNum)
{
	m_pBGSound->StopSoundBG(soundNum);
}
