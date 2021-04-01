#include "RC.h"
#include <stdio.h>
//_RC_
//********************Object******************
Object::Object() {
	name = " ";
	pos = vector3();
	type = none;
	DebugColor = vector3(100, 100, 100);
	material = &defaultMat;
	N0 = vector3(0.0f, 0.0f, 1.0f);
	N1 = vector3(1.0f, 0.0f, 0.0f);
	N2 = vector3(0.0f, -1.0f, 0.0f);
	out_u = -1.0f;
	out_v = -1.0f;
}

Object::~Object() {

}

Object::Object(vector3 Pos) {
	name = " ";
	pos = Pos;
	type = none;
	DebugColor = vector3(100, 100, 100);
	material = &defaultMat;
	N0 = vector3(0.0f, 0.0f, 1.0f);
	N1 = vector3(1.0f, 0.0f, 0.0f);
	N2 = vector3(0.0f, -1.0f, 0.0f);
	out_u = -1.0f;
	out_v = -1.0f;
}

bool Object::hit(vector3 eye, vector3 Npe, vector3& Hitpos, vector3& HitN) {
	//printf("object has no type, cannot hit");
	return false;
}

void Object::setUV(vector3 p) {
	//printf("object has no type, no UV");
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
	vector3 ie = (pos - eye);
	float c = vector3::dot(ei, ei) - (radius * radius); //b and c are references to the quadratic formula
	if (c >= 0.0f) {
		float b = vector3::dot(Npe, ie);
		float delta = (b * b) - c;  //tri is the discriminant
		//printf("%f \n", tri);
		//printf("%f , %f, %f", Npe.x, Npe.y, Npe.z);
		if (b >= 0.000f && delta >= 0.000f) {
			float th = b - sqrt(delta);
			HitPos = eye + (Npe * th);
			hitN = (HitPos - pos) / radius;
			//get normal
			hitN = hitN.normalize();
			//v = acos(n2 DOT(Ph - Pi) / radius) / PI
			//u = acos((n1 DOT(Ph - Pi) / radius) / sin((PI * v)) / 2PI;
			setUV(HitPos - pos);
			return true;
		}
	}


	return false;
}

void Sphere::setUV(vector3 p) {
	out_v = acos(vector3::dot(N2, p) / radius) / PI;
	out_u = acos(vector3::dot(N1, p) / radius) / sin(PI * out_v) / 2 * PI;
}



//********************Plane******************
Plane::Plane() : Object() {
	type = plane;
}

Plane::Plane(vector3 Pos, vector3 Normal) : Object(Pos) {
	type = plane;
	Ni = Normal;
}

bool Plane::hit(vector3 eye, vector3 Npe, vector3& HitPos, vector3& hitN) {

	vector3 ei = (eye - pos);
	float surface = vector3::dot(Ni, ei); 
	float surface2 = vector3::dot(Ni, Npe);
	if (surface2 < 0) {
		float th = (-surface / vector3::dot(Ni, Npe));
		HitPos = (Npe * th);
		hitN = Ni;
		setUV(pos);
		return true;
	}
	return false;
}

void Plane::setUV(vector3 p) {
	out_v = -1.0f;
	out_u = -1.0f;
}


//********************Light******************

Light::Light(vector3 Pos, vector3 c, float i) : Object(Pos) {
	color = c;
	intensity = i;
	type = pointlight;
}
bool Light::isVisible() {
	Nlh = RRayTracer::ray(pos, HitPos);
	HitPosOffset = HitPos + HitNormal / 5;
	ln = HitPos - pos;
	out_t = -1.0f;
	ln = -ln.normalize();
	if  ( !RRayTracer::raycast(HitPosOffset, Nlh, raytracer->objList, &o, &hitp, &hitn, false) ||
		vector3::distance(hitp, pos) > vector3::distance(HitPosOffset, pos) ||
		vector3::distance(hitp, pos) < 0
		) 
	{
		Cos = vector3::dot(ln, HitNormal);
		out_t = (0.5f * Cos) + 0.5f;
		out_s = -Nlh.z + 2.0f * (vector3::dot(Nlh, HitNormal)) * HitNormal.z;
		if (out_s < 0) out_s = 0; if (out_s > 1) out_s = 1;
	}

	if (out_t > 0) return true;
	return false;
}

//**************material*********************

Material::Material(vector3 DC, vector3 RC, float DP, float SP, float TP, float RP) 
	: diffuseC(DC), specularC(RC)
{
	dif = DP;
	spec = SP;
	trans = TP;
	reflect = RP;
	basefileinput = false;
	normalfileinput = false;
}
Material::~Material() {

}

vector3 Material::GetColor(float dif_i, float spec_i, float trans_i, float reflect_i, float U, float V)
{
	//if there's a mapping, set the diffuse, specular, etc to be whatever mapping you choose.
	if (basefileinput) {
		//Hitpos, HitObj->pos, 
	}
	//if there's a normal file, modify the output color to reflect the normal at that position
	if (normalfileinput) {

	}
	
	temp = (diffuseC * dif * dif_i) + (specularC * spec * spec_i) + (diffuseC * dif * trans_i) + (specularC * spec * reflect_i);

	if (temp.x > 255) temp.x = 255;
	if (temp.y > 255) temp.y = 255;
	if (temp.z > 255) temp.z = 255;
	return temp;
}

void Material::getTexture(const char* imagename){
	basemap = Image(imagename);
	basefileinput = true;
}



