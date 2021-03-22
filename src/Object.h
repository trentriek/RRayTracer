#pragma once
#ifndef OBJS
#define OBJS
#include "VectorMath.h"
//#include "GraphicsMath.h"
#include <vector>
#include <math.h>

class Material;

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
	Material* material;
	bool hit(vector3 eye, vector3 Npe, vector3& HitPos, vector3& HitN) override;
private:


};


class Light : public Object {

public:
	Light();
	Light(vector3 Pos, vector3 c = vector3(255.0f, 255.0f, 255.0f), float i = 0.5f);
	float intensity;
	vector3 color;
	//vector3 getRay(vector3 pointpos);

};

//Material Base class

class Material {
public:
	Material(vector3 color = vector3(0.5f,0.5f,0.5f));
	~Material();
	//image uv map will be here later
	vector3 base;
	float dp;
	float sp;
	float tp;
	float rp;
	virtual vector3 GetColor(std::vector<Light*>& lights, vector3& surfacenormal,
		vector3* transmissionColor = nullptr, vector3* reflectionColor = nullptr);
	virtual vector3 Diffuse(std::vector<Light*>& lights);
	virtual vector3 Specular(std::vector<Light*>& lights);
	virtual vector3 Reflection();
	virtual vector3 Transmission();
protected:
	vector3 diffuse;
	vector3 specular;
	vector3 reflection;
	vector3 transmission;

};



#endif