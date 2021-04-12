#include "PolygonMesh.h"


bool triangle::barycentric(vector3 P, vector3& Bcoord){

	return false;
}

float triangle::area(vector3 a, vector3 b, vector3 c) {
	vector3 cross = vector3::cross((b - a), (c - a));
	return = cross.magnitude() / 2.0f;
	
}
float triangle::area() {
	vector3 cross = vector3::cross((p1 - p0), (p2 - p0));
	return = cross.magnitude() / 2.0f;
}