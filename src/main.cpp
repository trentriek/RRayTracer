
#include <stdlib.h>
#include <iostream>
#include "RC.h"

RRayTracer* raytracer;
Camera* CurrentCam;
Material defaultMat = Material(vector3(255.0f, 0.0f, 0.0f), 1.0f, 0.5f);
const char* outName = "../resources/output.png";
const char* cubefile = "../resources/objs/cube.obj";
const char* bunnyfile = "../resources/objs/bunny.obj";
int width = 960;
int height = 540;


bool singleframe = true;
int numofframes = 1;

using namespace std;
int main(int args, char** argv) {
	/*s
	triangle test;
	test.p0 = vector3(35, 11, -49);
	test.p1 = vector3(43, 21, -45);
	test.p2 = vector3(48, 26, -41);
	vector3 op;
	test.barycentric(vector3(58.47, 39.35, -36.08), op);
	*/

	if (false) {
		width = 480;
		height = 360;
	}


	//*******************CREATE MATERIALS************************//

	Image output = Image(width, height);
	Material mat1 = Material(vector3(255.0f, 0.0f, 0.0f), 0.0f, 0.5f, 1.0f, 0.0f);
	Material mat2 = Material(vector3(0.0f, 255.0f, 0.0f), 1.0f, 0.5f);
	Material mat3 = Material(vector3(0.0f, 0.0f, 255.0f), 1.0f, 0.0f);
	
	Material backmat = Material(vector3(130.0f, 150.0f, 10.0f), 1.0f, 0.2f);
	backmat.basefileinput = true;
	backmat.basemap.load("../resources/uvs/bw.png");

	Material worldmat = Material(vector3(255.0f, 0.0f, 0.0f), 1.0f, 0.5f);
	worldmat.basefileinput = true;
	worldmat.basemap.load("../resources/uvs/earthmap.png");

	//*******************SETUP RAYTRACTER************************//
	Camera persp = Camera(vector3(0.0,0.0,0.0f));
	persp.focus_dist = 1000.0f;
	persp.setlook(vector3(0.0f, 1.0f, 0.0f), vector3(0.0f, 0.0f, -1.0f)); //setup camera - make position and set up viewing angle.
	RRayTracer rt;
	rt.persp = &persp;
	rt.sampleamount = 4;
	
	//*******************CREATE OBJECTS************************//
	Sphere sphereone = Sphere(vector3(1.0f, -0.3f, -3.0f), 0.5f);
	sphereone.material = &mat3;
	Sphere spheretwo = Sphere(vector3(-1.0f, 1.0f, -4.0f), 1.0f);
	spheretwo.material = &mat2;
	Sphere spherethree = Sphere(vector3(1.0f, -0.1f, -5.0f), 1.0f);
	spherethree.material = &mat1;
	spherethree.name = "reflactivesphere";
	Sphere worldsphere = Sphere(vector3(0.0f, 0.0, 0.0f), 200.0f);
	worldsphere.isinverted = true;
	worldsphere.material = &mat3;

	PolygonMesh Triangle = PolygonMesh(vector3(0.0f, 0.0f, -2.0f));
	triangle temp = triangle(
		vector3(0.3f, 0.0f, -2.5f),
		vector3(-0.1f, 0.0f, -2.5f),
		vector3(0.6f, -0.1f, -2.5f)
	);
	Triangle.polygons.push_back(temp);

	PolygonMesh cube = PolygonMesh(vector3(0.0f, 0.0f, -6.0f));
	cube.loadmesh(cubefile);

	
	Plane backplane = Plane(vector3(0.0f, 0.0f, -100.0f), vector3(0.0f, 0.0f, 1.0f));
	backplane.setview(vector3(0.0f, -1.0f, 0.0f), vector3(0.0f, 0.0f, 1.0f));
	backplane.material = &backmat;
	Plane leftplane = Plane(vector3(-3.0f, 0.0f, -10.0f), vector3(1.0f, -0.7f, 0.0f));
	leftplane.material = &mat3;
	sphereone.name = "leftsphere";
	



	//*******************CREATE LIGHTS************************//


	Light lightOne = Light(vector3(4.0f, 5.0f, -3.0f));
	lightOne.intensity = 1.0f;

	Light lightTwo = Light(vector3(2.0f, -4.0f, 5.0f));
	lightTwo.intensity = 0.5f;
	lightTwo.color = vector3(255.0, 0.0, 0.0);

	DirectionalLight Sun = DirectionalLight(vector3(-50.0f, 100.0f, -3.0f), vector3(0, 0, 200), 1.0f);
	Sun.Ni = vector3(-1.0, 0.0, 0.0);

	SpotLight Show = SpotLight(vector3(4.0f, -1.0f, -2.0f), vector3(0, 0, 200), 1.0f);
	Show.Ni = vector3(-0.8f, 0.12f, -0.45f);
	Show.coneangle = 0.9f;

	AreaLight area = AreaLight(vector3(4.0f, -1.0f, -3.0f), vector3(150, 150, 30), 1.0f);
	area.focus_dist = 100.0;
	area.setlook(vector3(9.0f, -2.0f, -3.0f), vector3(10.0f, -1.0f, -3.0f));
	area.width = 2;
	area.height = 2;



	//rt.objList.push_back(&sphereone);
	//rt.objList.push_back(&spheretwo);
	rt.objList.push_back(&spherethree);
	//rt.objList.push_back(&worldsphere);
	//rt.objList.push_back(&cube);
	//rt.objList.push_back(&Triangle);
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

/*
void setMaterials(RRayTracer& rr, vector<Material*>& mats) {

}

void addObjects(RRayTracer& rr, vector<Object*>& objs) {

}

void addLights(RRayTracer& rr, vector<Object*>& objs) {

}
*/

