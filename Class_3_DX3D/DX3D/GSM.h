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

	bool IntersectSphereBox(BoundingSphere* pSphere, BoundingBox* pBox) {
		float rr = pSphere->radius * pSphere->radius;
		float dmin = 0;
		if (pSphere->center.x < pBox->aa.x){
			dmin += sqrt(pSphere->center.x - pBox->aa.x);
		}
		else if (pSphere->center.x > pBox->bb.x){
			dmin += sqrt(pSphere->center.x - pBox->bb.x);
		}

		if (pSphere->center.y < pBox->aa.y){
			dmin += sqrt(pSphere->center.y - pBox->aa.y);
		}
		else if (pSphere->center.y > pBox->bb.y){
			dmin += sqrt(pSphere->center.y - pBox->bb.y);
		}

		if (pSphere->center.z < pBox->aa.z){
			dmin += sqrt(pSphere->center.z - pBox->aa.z);
		}
		else if (pSphere->center.z > pBox->bb.z){
			dmin += sqrt(pSphere->center.z - pBox->bb.z);
		}
		if (dmin <= rr) {
			return true;
		}
		return false;
	}
};

