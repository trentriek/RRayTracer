
#include <stdlib.h>
#include <iostream>
#include "RC.h"

RRayTracer* raytracer;
vector3 Npe;
vector3 Pe;
vector3 HitPos;
vector3 HitNormal;
Object* hitobj;
Camera* CurrentCam;
Material defaultMat;
const char* outName = "../resources/output.png";
int width = 960;
int height = 540;


using namespace std;
int main(int args, char** argv) {

	Image output = Image(width, height);
	Material mat1 = Material(vector3(255.0f, 0.0f, 0.0f), vector3(255.0f, 255.0f, 255.0f), 1.0f, 0.5f);
	Material mat2 = Material(vector3(0.0f, 255.0f, 0.0f), vector3(255.0f, 255.0f, 255.0f), 1.0f, 0.5f);
	Material mat3 = Material(vector3(0.0f, 0.0f, 255.0f), vector3(255.0f, 255.0f, 255.0f), 1.0f, 0.0f);
	Material backmat = Material(vector3(130.0f, 150.0f, 10.0f), vector3(255.0f, 255.0f, 255.0f), 1.0f, 0.0f);
	backmat.basefileinput = true;
	backmat.basemap.load("../resources/uvs/koolshadow.jpg");
	Material worldmat = Material(vector3(255.0f, 0.0f, 0.0f), vector3(255.0f, 255.0f, 255.0f), 1.0f, 0.5f);
	worldmat.basemap.load("../resources/uvs/earthmap.png");
	worldmat.basefileinput = true;

	Camera persp = Camera(vector3(0.0,0.0,0.0f));
	persp.focus_dist = 1000.0f;
	persp.setlook(vector3(0.0f, 1.0f, 0.0f), vector3(0.0f, 0.0f, -1.0f)); //setup camera - make position and set up viewing angle.
	RRayTracer rt;
	rt.persp = &persp;
	
	//Material
	Sphere sphereone = Sphere(vector3(0.0f, 0.0f, -6.0f), 0.5f);
	sphereone.DebugColor = vector3(255.0f, 0.0f, 0.0f);
	sphereone.material = &worldmat;
	Sphere spheretwo = Sphere(vector3(0.0f, 1.0f, -4.0f), 1.0f);
	spheretwo.DebugColor = vector3(0.0f, 255.0f, 0.0f);
	spheretwo.material = &mat2;
	Sphere spherethree = Sphere(vector3(2.0f, 1.0f, -4.0f), 0.5f);
	spherethree.DebugColor = vector3(0.0f, 0.0f, 255.0f);
	spherethree.material = &mat1;

	
	Plane backplane = Plane(vector3(0.0f, 0.0f, -100.0f), vector3(0.0f, 0.0f, 1.0f));
	backplane.DebugColor = vector3(255.0f, 255.0f, 255.0f);
	backplane.setview(vector3(0.0f, -1.0f, 0.0f), vector3(0.0f, 0.0f, 1.0f));
	backplane.material = &backmat;
	Plane leftplane = Plane(vector3(-3.0f, 0.0f, -10.0f), vector3(1.0f, -0.23f, 0.0f));
	leftplane.DebugColor = vector3(255.0f, 10.0f, 10.0f);
	leftplane.material = &mat3;
	
	Light lightOne = Light(vector3(4.0f, -1.0f, -3.0f));
	lightOne.intensity = 1.0f;
	Light lightTwo = Light(vector3(-2.0f, -4.0f, -5.0f));
	lightTwo.intensity = 1.0f;

	DirectionalLight Sun = DirectionalLight(vector3(-50.0f, 100.0f, -3.0f), vector3(0, 0, 200), 1.0f);
	Sun.Ni = vector3(-1.0, 0.0, 0.0);

	SpotLight Show = SpotLight(vector3(4.0f, -1.0f, -2.0f), vector3(0, 0, 200), 1.0f);
	Show.Ni = vector3(-0.8f, 0.12f, -0.45f);
	Show.coneangle = 0.9f;

	AreaLight area = AreaLight(vector3(4.0f, -1.0f, -3.0f), vector3(150, 150, 30), 1.0f);
	area.focus_dist = 100.0;
	area.setlook(vector3(9.0f, -2.0f, -3.0f), vector3(10.0f, -1.0f, -3.0f));
	area.width = 3;
	area.height = 3;

	rt.objList.push_back(&sphereone);
	rt.objList.push_back(&spheretwo);
	rt.objList.push_back(&spherethree);

	rt.objList.push_back(&backplane);
	rt.objList.push_back(&leftplane);

	rt.lightList.push_back(&lightOne); //create and add lights
	//rt.lightList.push_back(&lightTwo);
	//rt.lightList.push_back(&Sun);
	//rt.lightList.push_back(&Show);
	//rt.lightList.push_back(&area);
	raytracer = &rt;
	cout << raytracer->lightList[0]->name << endl;
	rt.Render(output);
	output.write(outName);

	return 0;
}

