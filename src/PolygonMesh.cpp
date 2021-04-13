#include "PolygonMesh.h"


bool triangle::barycentric(vector3 P, vector3& Bcoord){
	float u = triangle::area(p2, p0, P) / triangle::area();
	float v = triangle::area(p0, p1, P) / triangle::area();
	float w = triangle::area(p0, p1, P) / area();
	Bcoord = vector3(u, v, w);
	if(u < 0 || u > 1 || v < 0 || v > 1 || 1 - u - v < 0) return false;
	return true;
}

float triangle::area(vector3 a, vector3 b, vector3 c) {
	vector3 cross = vector3::cross((b - a), (c - a));
	return cross.magnitude() / 2.0f;
	
}
float triangle::area() {
	vector3 cross = vector3::cross((p1 - p0), (p2 - p0));
	return cross.magnitude() / 2.0f;
}

bool PolygonMesh::hit(vector3 eye, vector3 Npe, vector3& HitPos, vector3& hitN) {
	bool ishit;
	for (triangle Triangle : polygons) {
		ishit = Triangle.barycentric();
	}
}