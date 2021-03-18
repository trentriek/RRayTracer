
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
	persp.setlook(vector3(0.0f, 1.0f, 0.0f), vector3(0.0f, 0.0f, 1.0f)); //setup camera - make position and set up viewing angle.
	RRayTracer rt;
	rt.persp = &persp;
	
	Sphere sphereone = Sphere(vector3(0.0f, 0.0f, 6.0f), 1.0f);
	Sphere spheretwo = Sphere(vector3(2.0f, 1.0f, 4.0f), 1.0f);

	rt.objList.push_back(&sphereone);
	rt.objList.push_back(&spheretwo); //create and add objects

	rt.lightList.push_back(Light(vector3(1.0f, 1.0f, 4.0f))); //create and add lights

	rt.Render(output);
	output.write(outName);

	return 0;
}

