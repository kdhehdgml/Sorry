#pragma once
class GSM
{
public:
	GSM();
	virtual ~GSM();

	float mapSize;

	float fogMin;
	float fogMax;

	float mobSpeed;

	float mobDestLine;

	struct Pos
	{
		float x;
		float y;
		float z;
	};

	Pos camPos;
	Pos mobPos;
};

