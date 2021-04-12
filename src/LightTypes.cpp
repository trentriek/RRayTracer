#include "RC.h"


AreaLight::AreaLight(vector3 Pos, vector3 c, float i): Light(Pos, c, i) {
	type = arealight;
}
bool AreaLight::isVisible() {
	//float p = 1 / (float)(width * height);
	out_t = 0.0f;
	out_s = 0.0f;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			PP = P00 + (n0 * i) + (n1 * j);
			Nlh = RRayTracer::ray(PP, HitPos);
			HitPosOffset = HitPos + HitNormal / 5;
			ln = HitPos - PP;
			
			ln = -ln.normalize();
			if (!RRayTracer::raycast(HitPosOffset, Nlh, raytracer->objList, &o, &hitp, &hitn, false)// ||
				//vector3::distance(hitp, PP) > vector3::distance(HitPosOffset, PP) ||
				//vector3::distance(hitp, PP) < 0
				)
			{
				Cos = vector3::dot(ln, HitNormal);
				out_t += ( (0.5f * Cos) + 0.5f);
				out_s += (-Nlh.z + 2.0f * (vector3::dot(Nlh, HitNormal)) * HitNormal.z);
				//out_t += 1;
				//out_s += 0;
			}
			else
			{
				out_t += 1;
				out_t += 0;
			}

		}
	}

	out_t = out_t / (width * height);
	out_s = out_s / (width * height);
	if (out_s < 0) out_s = 0; if (out_s > 1) out_s = 1;

	if (out_t < 0.01) return false;
	return true;
}



SpotLight::SpotLight(vector3 Pos, vector3 c, float i, double ca) : Light(Pos, c, i) {
	type = spotlight;
	coneangle = ca;
}
bool SpotLight::isVisible() {
	Nlh = RRayTracer::ray(pos, HitPos);
	HitPosOffset = HitPos + HitNormal / 5;
	ln = HitPos - pos;
	out_t = -1.0f;
	ln = -ln.normalize();
	if (!RRayTracer::raycast(HitPosOffset, Nlh, raytracer->objList, &o, &hitp, &hitn, false) //||
		//vector3::distance(hitp, pos) > vector3::distance(HitPosOffset, pos) ||
		//vector3::distance(hitp, pos) < 0
		)
	{
		float spotcosine = vector3::dot(Ni, -Nlh);
		//spotlight: adds an extra condition to point light to check for angle
		//vector3::dot(Nlh, Ni) - cos((coneangle / 2)) <= 0
		if (spotcosine >= coneangle) {
			Cos = vector3::dot(ln, HitNormal);
				out_t = (0.5f * Cos) + 0.5f;
				out_s = -Nlh.z + 2.0f * (vector3::dot(Nlh, HitNormal)) * HitNormal.z;
				if (out_s < 0) out_s = 0; if (out_s > 1) out_s = 1;
		}
	}

	if (out_t > 0) return true;
	return false;
}


DirectionalLight::DirectionalLight(vector3 Pos, vector3 c, float i) : Light(Pos, c, i) {
	type = directionallight;
}

bool DirectionalLight::isVisible() {
	Nlh = -Ni;
	HitPosOffset = HitPos + HitNormal / 5;
	out_t = -1.0f;
	if (!RRayTracer::raycast(HitPosOffset, Nlh, raytracer->objList, &o, &hitp, &hitn, false) //||
		//vector3::distance(hitp, pos) > vector3::distance(HitPosOffset, pos) ||
		//vector3::distance(hitp, pos) < 0
		)
	{
		Cos = vector3::dot(Nlh, HitNormal);
		out_t = (0.5f * Cos) + 0.5f;
		out_s = -Nlh.z + 2.0f * (vector3::dot(Nlh, HitNormal)) * HitNormal.z;
		if (out_s < 0) out_s = 0; if (out_s > 1) out_s = 1;
	}

	if (out_t > 0) return true;
	return false;
}