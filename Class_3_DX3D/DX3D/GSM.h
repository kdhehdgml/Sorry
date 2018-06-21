#pragma once
class GSM
{
public:
	GSM();
	virtual ~GSM();

	int StartScene;

	float mapSize;

	float fogMin;
	float fogMax;

	float mobSpeed;

	float volume_music_init;

	D3DXVECTOR3 camPos;
	D3DXVECTOR3 mobPos;
	D3DXVECTOR3 TeamPos;
};

