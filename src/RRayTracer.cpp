#include "RC.h"
#include "Fresnel.h"
#include <stdlib.h>
#include <time.h>  
#include <ctime>  
//#include <omp.h>

Camera::Camera(vector3 p, int w, int h, float fd): Pos(p), width(w), height(h), focus_dist(fd) {
	
}

Camera::~Camera() {

}

void Camera::setlook(vector3 up, vector3 lookview) {
	Up = up.normalize();
	LookView = lookview.normalize();
	//n2 = lookview / lookview.magnitude();
	n2 = LookView;
	vector3 V0 = vector3::cross(lookview, up);
	//if (V0.zero()) n0 = vector3();
	n0 = V0 / V0.magnitude();
	n1 = vector3::cross(n0, n2);
	vector3 Pc = Pos + (n2 * focus_dist);
	//vector3 temp = (n0 * width + n1 * height);
	P00 = Pc - (n0 * width + n1 * height) / 2;
}

vector3 Camera::getRay(float u, float v) {
	vector3 PP = P00 + (n0 * u) + (n1 * v);
	PP = PP - Pos;
	PP = PP.normalize();
	return PP;
}

RRayTracer::RRayTracer() {
	sampleamount = 3;
}
RRayTracer::~RRayTracer() {

}



void RRayTracer::Render(Image& output) {
	//printf("%s\n", raytracer->lightList[0]->name);
	vector3 Ray;
	bool ishit;
	vector3 HitColor;
	int pixel[3];
	Object* hitObj = NULL;
	std::srand(time(0));
	float rayXoffset;
	float rayYoffset;
	int w = output.getWidth();
	int h = output.getHeight();
	
	//#pragma omp parallel //PROJECT READY FOR MULTITHREADING - OBJECT OUT UV's DONT WORK WITH THIS NEED TO FIX for threading to work.
	for (int j = 0; j < h; j++) { 
		for (int i = 0; i < w; i++) {
			//RANDOM Aliasing
			
			pixel[0] = 0.0f; pixel[1] = 0.0f; pixel[2] = 0.0f;
			for(int k = 0; k < sampleamount; k++){
				
				if (sampleamount > 2.0f) {
					rayXoffset = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					rayYoffset = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				}
				else {
					rayXoffset = (1.0f / sampleamount) * k;
					rayYoffset = (1.0f / sampleamount) * k;
				}

				//if we want out of focus , we will also offset the camera position 



				Ray = persp->getRay(i + rayXoffset, j + rayYoffset);
				
				ishit = rayTrace(Ray, persp->Pos, HitColor, &hitObj);
				pixel[0] += HitColor.x; pixel[1] += HitColor.y; pixel[2] += HitColor.z;
				
			}
			pixel[0] = pixel[0] / sampleamount; pixel[1] = pixel[1] / sampleamount; pixel[2] = pixel[2] / sampleamount;
			output.setPixel(i, j, pixel);
			/*
			Ray = persp->getRay(i, j);
			ishit = rayTrace(Ray, persp->Pos, HitColor, &hitObj);

			pixel[0] = HitColor.x; pixel[1] = HitColor.y; pixel[2] = HitColor.z;
			output.setPixel(i, j, pixel);
			*/
		}

	}



}

bool RRayTracer::rayTrace(vector3& ray, vector3& Pe, vector3& color, Object** Obj, int RecurssionDepth) {
	//hit values need to be stored
	vector3 HitPos;
	vector3 HitNormal;
	Object* hitobj;
	vector3 currentHit;
	vector3 currentNormal;
	//some settup
	//const unsigned short testing = 0;
	color = vector3();
	HitPos = vector3(10000000.0f, 100000000.0f, 10000000.0f);
	HitNormal = vector3();

	//********PART 1 - check for a hit************//
	bool hit = false; //current hit check
	bool didhit = false; //output hit - did it hit anything?
	Object* obj = NULL;
	for (Object* object : objList) {
		hit = object->hit(Pe, ray, currentHit, currentNormal);
		if (hit) {
			didhit = true;
			

			if (vector3::distance(Pe, currentHit) < vector3::distance(Pe, HitPos)) {
				HitPos = currentHit;
				HitNormal = currentNormal;
				obj = object;
				*Obj = obj;
			}
		}
	}

	if (didhit) {
		//*************PART 2 - get the diffuse & specular color of the hit*********************//
		//this loop is a cast to check for  "direct" light sources - is there a direct path to this point from each light?
		for (Light* l : lightList) {

			if (l->isVisible(HitPos, HitNormal, Pe))
			{
				//l->isVisible(HitPos, HitNormal, Pe);

				color += (obj->material->GetDiffuseColor(l->out_t, obj->out_u, obj->out_v)); //diffuse
				color += l->color * l->out_s * obj->material->spec; //specular
				color = color * l->intensity;
			}
		}
		//after this, a second loop calculates reflection & refraction

		//*****************************PART 3 - check for recursive reflection/refraction rays*********************//
		Object* recursivehit = NULL;
		vector3 bias = HitNormal * 0.05f;
		bool outside;

		if (RecurssionDepth >= 3) {
			//printf("%d\n", RecurssionDepth);
			return didhit;
		}
		//*************************************************reflection
		if (obj->material->reflect > 0.01f) {
			vector3 reflectivecolor;
			vector3 reflectionray = reflection_angle(ray, HitNormal);
			reflectionray = reflectionray.normalize();

			outside = vector3::dot(HitNormal, ray) < 0.0f;
			HitPos = outside ? HitPos + bias : HitPos - bias;
			//HitPos += bias;

			bool theHit = rayTrace(reflectionray, HitPos, reflectivecolor, &recursivehit , RecurssionDepth + 1);
			color += reflectivecolor * obj->material->reflect;
		}
		//*************************************************refraction
		if (obj->material->refract > 0.01f) {
			vector3 refractivecolor;
			vector3 refractionray;
			HitPos;
			//printf("%d\n", fresnels(ray, HitNormal, refractionray, Obj->material->refractvie_index) );
			fresnels(ray, HitNormal, refractionray, obj->material->refractvie_index); //sets the refraction ray, third argument
			refractionray = refractionray.normalize();


			outside = vector3::dot(HitNormal, ray) < 0.0f;
			HitPos = outside ? HitPos + bias : HitPos - bias;

			rayTrace(refractionray, HitPos, refractivecolor, &recursivehit, RecurssionDepth + 1);
			color += refractivecolor * obj->material->refract;
		}

		//*****************************PART 4 - CLAMP and return ***********************************//
		if (color.x > 255) color.x = 255;
		if (color.y > 255) color.y = 255;
		if (color.z > 255) color.z = 255;

	}
	return didhit;
}

bool RRayTracer::raycast(vector3& point, vector3& Nr, std::vector<Object*> objList, Object* Obj, vector3* hitpoint, vector3* hitnormal, vector3 Pe, bool checkall) {
	vector3 currentHit;
	vector3 currentNormal;
	*hitpoint = vector3(10000000.0f, 100000000.0f, 10000000.0f);
	bool hit = false;
	bool didhit = false;
	for (Object* object : objList) {
		hit = object->hit(point, Nr, currentHit, currentNormal);
		if (hit) {
			didhit = true;
			if (vector3::distance(Pe, currentHit) < vector3::distance(Pe, *hitpoint)) {
				*hitpoint = currentHit;
				*hitnormal = currentNormal;
				Obj = object;
				if (!checkall) break;
			}
		}
	}
	return didhit;
}

vector3 RRayTracer::ray(vector3 point, vector3 point2) {
	vector3 temp = point - point2;
	temp = temp.normalize();
	return temp;
}



//**************************test render- not really used anymore************************//

void RRayTracer::testcolor(Object* Obj, Light* l, vector3 &color, vector3& HitPos, vector3& HitNormal) {
	vector3 dc = Obj->DebugColor;
	vector3 ln = HitPos - l->getPos();
	ln = -ln.normalize();
	float Cos = vector3::dot(ln, HitNormal);
	float t = (0.5f * Cos) + 0.5f;
	//clamp between 0 and 1
	clamp(t);
	dc = Obj->DebugColor;
	float S = 0.0;
	//specular if note plane
	//if (Obj->getType() != plane) {
	S = -ln.z + 2.0f * (ln.x * HitNormal.x + ln.y * HitNormal.y + ln.z * HitNormal.z) * HitNormal.z;
	if (S < 0) S = 0; if (S > 1) S = 1;
	float specular_intensity = 0.5;
	S = S * specular_intensity;
	//}
	vector3 lc = l->color;
	color.x = color.x + ((dc.x * t) + (lc.x * S)) * l->intensity;
	if (color.x > 255) color.x = 255;
	color.y = color.y + ((dc.y * t) + (lc.y * S)) * l->intensity;
	if (color.y > 255) color.y = 255;
	color.z = color.z + ((dc.z * t) + (lc.z * S)) * l->intensity;
	if (color.z > 255) color.z = 255;

	//} //multiply by light intensity
}




