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

	struct Pos
	{
		float x;
		float y;
		float z;
	};

	Pos camPos;
	Pos mobPos;
	Pos TeamPos;
};

