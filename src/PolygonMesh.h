#pragma once
#ifndef POLY_MESH
#define POLY_MESH
#include "Object.h"
#include "RRayTracer.h"
#include <vector>

struct triangle {
	vector3 p0;
	vector3 p1;
	vector3 p2;
	bool barycentric(vector3 P, vector3& Bcoord);
	static float area(vector3 a, vector3 b, vector3 c);
	float area();
	float Ni;
};


class PolygoneMesh : public Object {
public:
	std::vector<triangle> polygons;

};


#endif