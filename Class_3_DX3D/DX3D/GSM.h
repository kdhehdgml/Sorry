#pragma once

enum sType
{
	SHOOT = 1,
	VOICE_DEATH,
	VOICE_INCOMING
};

enum vType
{
	DEATH = 1,
	INCOMING
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