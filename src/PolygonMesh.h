#pragma once
#ifndef POLY_MESH
#define POLY_MESH
#include "Object.h"
#include "RRayTracer.h"
#include <vector>

struct triangle {
	vector3 p1;
	vector3 p2;
	vector3 p3;
	bool barycentric(vector3 p, vector3& Bcoord);
};


class PolygoneMesh : public Object {
public:
	std::vector<triangle> polygons;

};


#endif