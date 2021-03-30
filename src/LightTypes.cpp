#include "RC.h"


AreaLight::AreaLight(vector3 Pos, vector3 c, float i): Light(Pos, c, i) {
	type = arealight;
}
bool AreaLight::isVisible() {
	float p = 1 / (width * height);
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			PP = P00 + (n0 * i) + (n1 * j);
			Nlh = RRayTracer::ray(pos, HitPos);
			if (!RRayTracer::raycast(HitPosOffset, Nlh, raytracer->objList, &o, &hitp, &hitn, false)) {
				out_t += vector3::dot(Nlh, HitNormal); //find t here
				out_s += -Nlh.z + 2.0f * (vector3::dot(Nlh, HitNormal)) * HitNormal.z;
			}
			else if (vector3::distance(hitp, pos) > vector3::distance(HitPosOffset, pos) || vector3::distance(hitp, pos) < 0) {
				out_t += vector3::dot(Nlh, HitNormal);
				out_s += -Nlh.z + 2.0f * (vector3::dot(Nlh, HitNormal)) * HitNormal.z;
			}
		}
	}
	if (out_t < 0.01) return false;
	return true;
}



SpotLight::SpotLight(vector3 Pos, vector3 c, float i) : Light(Pos, c, i) {
	type = spotlight;
}
bool SpotLight::isVisible(){
	/*
	Nlh = RRayTracer::ray(pos, HitPos);
	HitPosOffset = HitPos + HitNormal / 5;
	//Object o;
	//vector3 hitp;
	//vector3 hitn;
	if (!RRayTracer::raycast(HitPosOffset, Nlh, raytracer->objList, &o, &hitp, &hitn, false)) {
		if ( ( vector3::dot(Nlh, Ni) - cos( (coneangle/2) ) <= 0 ) {

		}
	}
	else if (vector3::distance(hitp, pos) > vector3::distance(HitPosOffset, pos) || vector3::distance(hitp, pos) < 0) {
		if ( (vector3::dot(Nlh, Ni) - cos((coneangle / 2)) <= 0 ) {

		}
	}
	*/
	return false;
}


DirectionalLight::DirectionalLight(vector3 Pos, vector3 c, float i) : Light(Pos, c, i) {
	type = directionallight;
}

bool DirectionalLight::isVisible() {
	vector3 Nlh = Ni;
	vector3 HitPosOffset = HitPos + HitNormal / 5;
	Object o;
	vector3 hitp;
	vector3 hitn;
	if (!RRayTracer::raycast(HitPosOffset, Nlh, raytracer->objList, &o, &hitp, &hitn, false)) {
		return true;
	}
	else if (vector3::distance(hitp, pos) > vector3::distance(HitPosOffset, pos) || vector3::distance(hitp, pos) < 0) {
		return true;
	}
	return false;
}