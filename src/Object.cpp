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
			return true;
		}
	}


	return false;
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
		return true;
	}
	return false;
}


//********************Light******************

//Light::Light() : Object() {
//	color = vector3(255.0f, 255.0f, 255.0f);
//	intensity = 0.5f;
//	type = pointlight;
//}
Light::Light(vector3 Pos, vector3 c, float i) : Object(Pos) {
	color = c;
	intensity = i;
	type = pointlight;
}
bool Light::isVisible() {
	Nlh = RRayTracer::ray(pos, HitPos);
	HitPosOffset = HitPos + HitNormal/5;
	ln = HitPos - pos;
	ln = -ln.normalize();
	if (!RRayTracer::raycast(HitPosOffset, Nlh , raytracer->objList, &o, &hitp, &hitn, false)) {
		Cos = vector3::dot(ln, HitNormal);
		out_t = (0.5f * Cos) + 0.5f;
		out_s = -Nlh.z + 2.0f * (vector3::dot(Nlh, HitNormal)) * HitNormal.z;
		if (out_s < 0) out_s = 0; if (out_s > 1) out_s = 1;
		return true;
	}
	else if (vector3::distance(hitp, pos) > vector3::distance(HitPosOffset, pos) || vector3::distance(hitp, pos) < 0) {
		Cos = vector3::dot(ln, HitNormal);
		out_t = (0.5f * Cos) + 0.5f;
		out_s = -Nlh.z + 2.0f * (vector3::dot(Nlh, HitNormal)) * HitNormal.z;
		if (out_s < 0) out_s = 0; if (out_s > 1) out_s = 1;
		return true;
	}
	if (out_t) return true;
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
	//try {

		//if ((dif + spec + trans + reflect) > 1.0f) {
		//	std::printf("the material's intensity value cannot exceed 1");
		//	throw 1;
		//}
	//}
	//catch (int e) {

	//}
}
Material::~Material() {

}

vector3 Material::GetColor(vector3* DC, vector3* RC, vector3* TC, vector3* RFC)
{
	vector3 output;
		if ( dif > 0.0001f) output = output + Diffuse() * dif;
		if (spec > 0.0001f) output = output + Specular() * spec;
		if (trans > 0.0001f) output = output + Transmission() * trans;
		if (reflect > 0.0001f) output = output + Reflection() * reflect;
		return output;
}
vector3 Material::Diffuse(){
	vector3 x = HitPos;
	//printf("%d", raytracer->lightList.size());
	vector3 ln = HitPos - raytracer->lightList[0]->getPos();
	ln = -ln.normalize();
	float Cos = vector3::dot(ln, HitNormal);
	float t = (0.5f * Cos) + 0.5f;
	//clamp between 0 and 1
	clamp(t);
	return diffuseC * t;
}
vector3 Material::Specular() {
	vector3 ln = HitPos - raytracer->lightList[0]->getPos();
	float S = -ln.z + 2.0f * (ln.x * HitNormal.x + ln.y * HitNormal.y + ln.z * HitNormal.z) * HitNormal.z;
	if (S < 0) S = 0; if (S > 1) S = 1;
	return specularC * S;
}
vector3 Material::Reflection() {
	return vector3();
}
vector3 Material::Transmission() {
	return vector3();
}


