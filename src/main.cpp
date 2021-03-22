
#include <stdlib.h>
#include <iostream>
//#include <string>
//#include "VectorMath.h"
//#include "Load_Image.h"
//#include "GraphicsMath.h"
#include "RRayTracer.h"



const char* outName = "../resources/output.png";
int width = 960;
int height = 540;

using namespace std;
int main(int args, char** argv) {

	Image output = Image(width, height);

	Camera persp = Camera(vector3(0.0,0.0,0.0f));
	persp.focus_dist = 1000.0f;
	persp.setlook(vector3(0.0f, 1.0f, 0.0f), vector3(0.0f, 0.0f, -1.0f)); //setup camera - make position and set up viewing angle.
	RRayTracer rt;
	rt.persp = &persp;
	
	//Material

	Sphere sphereone = Sphere(vector3(0.0f, 0.0f, -6.0f), 0.5f);
	sphereone.DebugColor = vector3(255.0f, 0.0f, 0.0f);
	Sphere spheretwo = Sphere(vector3(0.0f, 1.0f, -4.0f), 1.0f);
	spheretwo.DebugColor = vector3(0.0f, 255.0f, 0.0f);

	
	Plane backplane = Plane(vector3(0.0f, 0.0f, -100.0f), vector3(0.0f, 0.0f, 1.0f));
	backplane.DebugColor = vector3(255.0f, 255.0f, 255.0f);
	Plane leftplane = Plane(vector3(-3.0f, 0.0f, -10.0f), vector3(1.0f, -0.237f, 0.0f));
	leftplane.DebugColor = vector3(10.0f, 10.0f, 10.0f);
	Plane rightplane = Plane(vector3(3.0f, 0.0f, -10.0f), vector3(-1.0f, 0.361f, 0.12f));
	rightplane.DebugColor = vector3(50.0f, 200.0f, 200.0f);
	

	rt.objList.push_back(&sphereone);
	rt.objList.push_back(&spheretwo);

	rt.objList.push_back(&backplane);
	rt.objList.push_back(&leftplane);
	rt.objList.push_back(&rightplane);
	Light lightOne = Light(vector3(4.0f, 1.0f, -3.0f));

	rt.lightList.push_back(&lightOne); //create and add lights

	rt.Render(output);
	output.write(outName);

	return 0;
}

