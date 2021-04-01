#pragma once
#ifndef OBJS
#define OBJS
#include "VectorMath.h"
//#include "GraphicsMath.h"
#include <vector>
#include <math.h>
#include "Load_Image.h"

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
	float out_u;
	float out_v;

protected:
	virtual void setUV(vector3 p);
	vector3 pos;
	Objtype type;
	vector3 N0;
	vector3 N1;
	vector3 N2;
};

class Sphere : public Object {

public:
	Sphere();
	Sphere(vector3 Pos, float r = 1.0f);
	~Sphere();
	float radius;
	bool hit(vector3 eye, vector3 Npe, vector3& HitPos, vector3& HitN) override;
private:
	void setUV(vector3 p);

};

class Plane : public Object {

public:
	Plane();
	Plane(vector3 Pos, vector3 Normal = vector3(0.0,0.0,1.0) );
	vector3 Ni;
	bool hit(vector3 eye, vector3 Npe, vector3& HitPos, vector3& HitN) override;
private:
	void setUV(vector3 p);

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
	float dif;
	float spec;
	float trans;
	float reflect;
	virtual vector3 GetColor(float dif_i = 1.0f, float spec_i = 0.0f, float trans_i = 0.0f, float reflect_i = 0.0f, float U = 0.0f, float V = 0.0f);
	void getTexture(const char* imagename);
	vector3 diffuseC;
	vector3 specularC;
	vector3 transmissionC;
	vector3 reflectionC;
	bool basefileinput;
	bool normalfileinput;
	Image basemap;
	Image normalmap;
	
protected:
	vector3 temp;
};



#endif