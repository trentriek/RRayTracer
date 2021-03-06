#pragma once
#ifndef LIGHT_TYPES
#define LIGHT_TYPES
#include "Object.h"
#include "RRayTracer.h"
//Light(vector3 Pos, vector3 c, float i)
class AreaLight : public Camera, public Light {
public:
	AreaLight(vector3 Pos = vector3(0.0f, 0.0f, 0.0f), vector3 c = vector3(255.0f, 255.0f, 255.0f), float i = 0.5f);
	//~AreaLight();
	bool isVisible(vector3 HitPos, vector3 HitNormal, vector3 Pe) override;
private:
	vector3 PP;
};

class SpotLight : public Light {
public:
	SpotLight(vector3 Pos = vector3(0.0f, 0.0f, 0.0f), vector3 c = vector3(255.0f, 255.0f, 255.0f), float i = 0.5f, double ca = 3.14f);
	//~SpotLight();
	bool isVisible(vector3 HitPos, vector3 HitNormal, vector3 Pe) override;
	vector3 Ni;
	double coneangle;
private:
};

class DirectionalLight : public Light {
public:
	DirectionalLight(vector3 Pos = vector3(0.0f, 0.0f, 0.0f), vector3 c = vector3(255.0f, 255.0f, 255.0f), float i = 0.5f);
	//~DirectionalLight();
	bool isVisible(vector3 HitPos, vector3 HitNormal, vector3 Pe) override;
	vector3 Ni;
private:
};


#endif // !LIGHT_TYPES
