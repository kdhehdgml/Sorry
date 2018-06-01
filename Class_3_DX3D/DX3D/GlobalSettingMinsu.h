#pragma once
class GlobalSettingMinsu
{
public:
	GlobalSettingMinsu();
	virtual ~GlobalSettingMinsu();

	float mapSize;

	float fogMin;
	float fogMax;

	struct cameraPosition
	{
		float x;
		float y;
		float z;
	};

	cameraPosition camPos;
};

