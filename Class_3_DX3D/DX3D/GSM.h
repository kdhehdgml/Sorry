#pragma once
class GSM
{
public:
	GSM();
	virtual ~GSM();

	float mapSize;

	float fogMin;
	float fogMax;

	struct Pos
	{
		float x;
		float y;
		float z;
	};

	Pos camPos;
	Pos mobPos;
};

