#include "Object.h"
#include <stdio.h>


//********************Object******************
Object::Object() {
	name = " ";
	pos = vector3();
	type = none;
	DebugColor = vector3(100, 100, 100);
}

Object::~Object() {

}

Object::Object(vector3 Pos) {
	name = " ";
	pos = Pos;
	type = none;
	DebugColor = vector3(100, 100, 100);
}

bool Object::hit(vector3 eye, vector3 Npe, vector3& Hitpos, vector3& HitN) {
	//printf("object has no type, cannot hit");
	return false;
}

vector3 Object::getPos() {
	return pos;
}
void Object::setPos(float x, float y, float z) {
	pos.x = x; pos.y = y; pos.z = z;
}

void Object::setPos(vector3 p) {
	pos = p;
}

Objtype Object::getType() {
	return type;
}

//********************Sphere******************
Sphere::Sphere() :Object() {
	type = sphere;
	radius = 1.0f;
}

Sphere::Sphere(vector3 Pos, float r) : Object(Pos) {
	type = sphere;
	radius = r;
}


Sphere::~Sphere() {

}

bool Sphere::hit(vector3 eye, vector3 Npe, vector3& HitPos, vector3& hitN) {

	
	vector3 ei = (eye - pos);
	//vector3 ie = (pos - eye);
	float c = vector3::dot(ei, ei) - (radius * radius); //b and c are references to the quadratic formula
	if (c >= 0.0f) {
		float b = vector3::dot(Npe, ei);
		float tri = (b * b) - c;  //tri is the discriminant
		//printf("%f \n", tri);
		//printf("%f , %f, %f", Npe.x, Npe.y, Npe.z);
		if (b >= 0.000f || tri >= 0.000f) {
			float th = b - sqrt(tri);
			HitPos = eye + (Npe * th);
			hitN = (HitPos - pos) / radius;
			//get normal
			hitN = hitN.normalize();
			return true;
		}
	}


	return false;
}



//********************Plane******************
Plane::Plane() :Object() {
	type = plane;
}

Plane::Plane(vector3 Pos, vector3 Normal) : Object(Pos) {
	type = plane;
	Ni = Normal;
}

bool Plane::hit(vector3 eye, vector3 Npe, vector3& HitPos, vector3& hitN) {
	vector3 ei = (eye - pos);
	//vector3 ie = (pos - eye);
	float surface = vector3::dot(Ni, ei); //b and c are references to the quadratic formula
	if (surface >= 0) {
		float th = (-surface / vector3::dot(Ni, Npe));
		HitPos = eye + (Npe * th);
		hitN = Ni;
		return true;
	}
	return false;
}


//********************Light******************

Light::Light() : Object() {
	color = vector3(255.0f, 255.0f, 255.0f);
	intensity = 0.5f;
}
Light::Light(vector3 Pos, vector3 c, float i) : Object(Pos) {
	color = c;
	intensity = i;
}

//**************material*********************

Material::Material(vector3 color) {
	base = color;
	dp = 1.0; rp = 0.0; sp = 0.0; tp = 0.0;
}
Material::~Material() {

}

vector3 Material::GetColor(std::vector<Light*>& lights, vector3& surfacenormal,
	vector3* transmissionColor, vector3* reflectionColor)
{
	diffuse = Diffuse(lights);
	specular = Specular(lights);
	return (diffuse * dp) + (specular * sp) + (reflection * rp) + (transmission * tp);

}
vector3 Material::Diffuse(std::vector<Light*>& lights){
	return vector3();
}
vector3 Material::Specular(std::vector<Light*>& lights) {
	return vector3();
}
vector3 Material::Reflection() {
	return vector3();
}
vector3 Material::Transmission() {
	return vector3();
}


