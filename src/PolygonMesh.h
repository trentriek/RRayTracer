#pragma once
#ifndef POLY_MESH
#define POLY_MESH
#include "Object.h"
#include "RRayTracer.h"
#include <vector>

class triangle {
public:
	triangle();
	triangle(vector3 a, vector3 b, vector3 c);
	vector3 p0;
	vector3 p1;
	vector3 p2;
	bool barycentric(vector3 P, vector3& Bcoord);
	static float area(vector3 a, vector3 b, vector3 c);
	float area();
	vector3 Ni;
private:
	float u;
	float v;
	float w;
};


class PolygonMesh : public Object {
public:
	PolygonMesh();
	PolygonMesh(vector3 Pos);
	std::vector<triangle> polygons;
	bool hit(vector3 eye, vector3 Npe, vector3& HitPos, vector3& hitN);
	bool loadmesh(const char* filename);

private:
	std::vector<vector3> vertexBuf;
};


#endif