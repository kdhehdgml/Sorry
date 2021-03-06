#pragma once

enum sType
{
	SHOOT = 1,
	VOICE_DEATH,
	VOICE_RELOAD
};

enum vType
{
	DEATH = 1,
	INCOMING,
	RELOAD
};

enum eType
{
	WHISTLE,
	WHIZ,
	ART_FIRE,
	ART_EXP
};

class GSM
{
public:
	GSM();
	virtual ~GSM();

	int StartScene;
	int InitScene;

	float playerHeight;

	float mapSize;

	float fogMin;
	float fogMax;

	float mobSpeed;

	float volume_music_init;

	float reload_one;
	float reload_all;

	D3DXVECTOR3 camPos;
	D3DXVECTOR3 mobPos;

	bool	Debug_Mode_On;
};