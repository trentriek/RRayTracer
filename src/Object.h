#pragma once
#ifndef OBJS
#define OBJS
#include "VectorMath.h"
//#include "GraphicsMath.h"
#include <math.h>

//Objects

enum Objtype{ none, sphere, plane };


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

/*
class Material {
public:
	virtual vector3 GetColor();
	virtual vector3 Diffuse();
	virtual vector3 Specular();
	virtual vector3 reflection();
	virtual vector3 Transmission();
protected:
};
*/

class Light : public Object {

public:
	Light();
	Light(vector3 Pos, vector3 c = vector3(255.0f, 255.0f, 255.0f), float i = 0.5f);
	float intensity;
	vector3 color;
};

/*
class texture {

};
*/


#endif