#include "PolygonMesh.h"
#include "tiny_obj_loader.h"


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
	for (triangle Triangle : polygons) {
		float denom = vector3::dot(Triangle.Ni, Npe);
		if (abs(denom) > 0.0001f) {
			float t = (vector3::dot((pos - eye), Triangle.Ni)) / denom;
			if (t >= 0) {
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

	bool PolygonMesh::loadmesh(unsigned char* filename) {
		string meshName(filename);

		// Load geometry
		vector<float> posBuf; // list of vertex positions
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		string errStr;
		bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
		if (!rc) {
			cerr << errStr << endl;
		}
		else {
			// Some OBJ files have different indices for vertex positions, normals,
			// and texture coordinates. For example, a cube corner vertex may have
			// three different normals. Here, we are going to duplicate all such
			// vertices.
			// Loop over shapes
			for (size_t s = 0; s < shapes.size(); s++) {
				// Loop over faces (polygons)
				size_t index_offset = 0;
				for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
					size_t fv = shapes[s].mesh.num_face_vertices[f];
					// Loop over vertices in the face.
					for (size_t v = 0; v < fv; v++) {
						// access to vertex
						tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
						posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 0]);
						posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 1]);
						posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 2]);
					}
					index_offset += fv;
					// per-face material (IGNORE)
					shapes[s].mesh.material_ids[f];
				}
			}
}
}