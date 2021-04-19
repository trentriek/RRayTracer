#include "RC.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <string>

triangle::triangle() {

}
triangle::triangle(vector3 a, vector3 b, vector3 c) {
	p0 = a;
	p1 = b;
	p2 = c;
	Ni = vector3::cross((b - a), (c - a));
	Ni = Ni.normalize();
}



bool triangle::barycentric(vector3 P, vector3& Bcoord){
	u = triangle::area(p2, p0, P) / area();
	v = triangle::area(p0, p1, P) / area();
	w = triangle::area(p1, p2, P) / area();
	Bcoord = vector3(u, v, w);
	if ( (1 - u - v < 1) && (1 - u - v) > 0) 
		return true;
	/*
	if(u < 0 
		|| u > 1 
		|| v < 0 
		|| v > 1 
		|| ( 1 - u - v < 0 ) ) return false;
		*/
	return false;
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
	for (triangle Triangle : polygons) {
		//check if ray hits plane
		float denom = vector3::dot(Triangle.Ni, Npe);
		if (abs(denom) > 0.0001f) {
			float t = (vector3::dot((Triangle.p0 - eye), Triangle.Ni)) / denom;
			if (t >= 0) { //if ray hits plane, check to see if its within the triangle
				vector3 uvw;
				if (Triangle.barycentric(Npe * t, uvw)) {
					HitPos = (Npe * t);
					hitN = Triangle.Ni;
					out_u = uvw.x;
					out_v = uvw.y;
					return true;
				}
			}
		}
		return false;
	}
}
	PolygonMesh::PolygonMesh() : Object() {

	}
	PolygonMesh::PolygonMesh(vector3 Pos) : Object(Pos) {

	}


	bool PolygonMesh::loadmesh(const char* filename) {

		// Load geometry
		//std::vector<float> posBuf; // list of vertex positions. inside class
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string errStr;
		bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, filename);
		if (!rc) {
			return false;
		}
		else {
			// Some OBJ files have different indices for vertex positions, normals,
			// and texture coordinates. For example, a cube corner vertex may have
			// three different normals. Here, we are going to duplicate all such
			// vertices.
			// Loop over shapes
			triangle temptri;
			vector3 tempvertex;
			for (size_t s = 0; s < shapes.size(); s++) {
				// Loop over faces (polygons)
				size_t index_offset = 0;
				for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
					size_t fv = shapes[s].mesh.num_face_vertices[f];
					// Loop over vertices in the face.
					for (size_t v = 0; v < fv; v++) {
						// access to vertex
						tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
						//posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 0]);
						//posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 1]);
						//posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 2]);
						tempvertex = vector3(
							attrib.vertices[3 * idx.vertex_index + 0],
							attrib.vertices[3 * idx.vertex_index + 1],
							attrib.vertices[3 * idx.vertex_index + 2]
						);
						tempvertex += pos;
						vertexBuf.push_back(tempvertex);

						//polygons.push_back(temptri);

					}
					index_offset += fv;
					// per-face material (IGNORE)
					shapes[s].mesh.material_ids[f];
					temptri = triangle(
						vertexBuf[f],
						vertexBuf[f + 1],
						vertexBuf[f + 2]
					);
					polygons.push_back(temptri);
				}
			}
		}
		return rc;
}