#pragma once
#ifndef OBJS
#define OBJS
#include "VectorMath.h"
//#include "GraphicsMath.h"
#include <vector>
#include <math.h>

class Material;

//Objects

enum Objtype{ none, sphere, plane, pointlight, arealight, spotlight, directionallight};

class Object {

public:
	Object();
	Object(vector3 Pos);
	~Object();
	const char* name;
	Objtype getType();
	virtual bool hit(vector3 eye, vector3 Npe, vector3& HitPos, vector3& HitN);
	vector3 getPos();
	void setPos(float x = 0.0, float y = 0.0, float z = 0.0);
	void setPos(vector3 p);
	Material* material;

	vector3 DebugColor;

protected:
	vector3 pos;
	Objtype type;
};

class Sphere : public Object {

public:
	Sphere();
	Sphere(vector3 Pos, float r = 1.0f);
	~Sphere();
	float radius;
	bool hit(vector3 eye, vector3 Npe, vector3& HitPos, vector3& HitN) override;
private:


};

class Plane : public Object {

public:
	Plane();
	Plane(vector3 Pos, vector3 Normal = vector3(0.0,0.0,1.0) );
	vector3 Ni;
	bool hit(vector3 eye, vector3 Npe, vector3& HitPos, vector3& HitN) override;
private:


};


class Light : public Object {

public:
	//~Light();
	Light(vector3 Pos = vector3(0.0f, 0.0f, 0.0f), vector3 c = vector3(255.0f, 255.0f, 255.0f), float i = 0.5f);
	float intensity;
	vector3 color;
	virtual bool isVisible();
	float out_t;
	float out_s;
protected:
	vector3 Nlh;
	vector3 HitPosOffset;
	Object o;
	vector3 hitp;
	vector3 hitn;
	float Cos;
	vector3 ln;

};


//Material Base class

class Material {
public:
	Material(vector3 DC = vector3(100.0f, 100.0f, 100.0f), vector3 RC = vector3(255.0f, 255.0f, 255.0f), float DP = 1.0f, float SP = 0.0f, float TP = 0.0f, float RP = 0.0f);
	~Material();
	//image uv map will be here later
	float dif;
	float spec;
	float trans;
	float reflect;
	virtual vector3 GetColor(vector3* DC = nullptr, vector3* RC = nullptr, vector3* TC = nullptr, vector3* RFC = nullptr);
	vector3 diffuseC;
	vector3 specularC;
	vector3 reflectionC;
	vector3 transmissionC;

	
protected:
	virtual vector3 Diffuse();
	virtual vector3 Specular();
	virtual vector3 Reflection();
	virtual vector3 Transmission();
};



#endif