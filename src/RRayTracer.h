#pragma once
#ifndef RRAY_TRACER
#define RRAY_TRACER
#include "Object.h"
#include <math.h>
#include "Load_Image.h"
#include <vector>

class Camera {

public:
	Camera(vector3 p = vector3(), int w = 960, int h = 540, float fd = 1.0f);
	~Camera();
	vector3 Pos;
	int width;
	int height;
	float focus_dist;
	//return a normalized ray from a pixel from the camera
	vector3 getRay(float u, float v);
	void setlook(vector3 up, vector3 lookview);
	float wratio;
	float hratio;

protected:
	vector3 n2;
	vector3 n1;
	vector3 n0;
	vector3 Up;
	vector3 LookView;
	vector3 P00;

};


class RRayTracer {

public:
	//RRayTracer();
	//~RRayTracer();
	Camera* persp;
	std::vector<Object*> objList;
	std::vector<Light*> lightList;
	void Render(Image& output);



	//helper values placed within the class declaration for quick access - moved to render cache 
	//vector3 Npe;
	//vector3 Pe;
	//vector3 HitPos;
	//vector3 HitNormal;
	//Object* hitobj;


	static bool raycast(vector3& point, vector3& Nr, std::vector<Object*> objList, Object* Obj,
		vector3* hitpoint, vector3* hitnormal, bool checkall = true);
	static vector3 ray(vector3 point, vector3 point2);

private:
	std::vector<Light*> visibleLights;
	vector3 currentHit;
	vector3 currentNormal;
	void rayTrace(vector3& ray, bool& hit, vector3& color, Object* Obj);
	int objnum;

};





#endif