#include "RRayTracer.h"

Camera::Camera(vector3 p, int w, int h, float fd): pos(p), width(w), height(h), focus_dist(fd) {
	
}

Camera::~Camera() {

}

void Camera::setlook(vector3 up, vector3 lookview) {
	Up = up;
	LookView = lookview;
	n2 = lookview / lookview.magnitude();
	vector3 V0 = vector3::cross(up, lookview);
	//if (V0.zero()) n0 = vector3();
	n0 = V0 / V0.magnitude();
	n1 = vector3::cross(n2, n0);
	vector3 Pc = pos + (n2 * focus_dist);
	//vector3 temp = (n0 * width + n1 * height);
	P00 = Pc - (n0 * width + n1 * height) / 2;
}

vector3 Camera::getRay(float u, float v) {
	vector3 PP = P00 + (n0 * u) + (n1 * v);
	PP = PP - pos;
	PP = PP.normalize();
	return PP;
}



void RRayTracer::Render(Image& output) {

	int w = output.getWidth();
	int h = output.getHeight();
	vector3 Ray;
	bool ishit;
	vector3 HitColor;
	int pixel[3];
	Object* hitObj = NULL;
	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			//here we could add a third for loop to itterate over every ray cast within a pixel
			Ray = persp->getRay(i, j);
			rayTrace(Ray, ishit, HitColor, hitObj);
			//again, in this third loop we would do some form of averaging for the pixel. We can also do other processing here - but Currently we just want to see if we can hit stuff.

			pixel[0] = HitColor.x; pixel[1] = HitColor.y; pixel[2] = HitColor.z;
			output.setPixel(i, j, pixel);
		}

	}



}

void RRayTracer::rayTrace(vector3& ray, bool& hit, vector3& color, Object* Obj) {
	const unsigned int testing = 1;
	currentHit = 10000000000000;
	hit = false; //output hit
	bool didHit = false;
	for (Object* object : objList) {
		didHit = object->hit(persp->pos, ray, HitPos, HitNormal);
		if (didHit) {
			hit = true;
			//	printf("Hit\n");
			if (vector3::distance(Pe, HitPos) < vector3::distance(Pe, currentHit)) {
				currentHit = HitPos;
				hitobj = object;
				Obj = object;
			}
		}
	}

	if (!hit) {
		color = vector3();
		return;
	}
	else {
		//check the diffuse, specular, transmisstion values; determine if you need to shoot are recursive ray from the hit point
		//if you need to trace another ray, trace it 
		//hitobj.getcolor(s)

		if (testing) {
			//for (Light* l : lightList) {
				//vector3 light = l->getPos();
				vector3 light = lightList[0]->getPos();
				light = light.normalize();
				float cos = vector3::dot(light, HitNormal);
				//clamp between 0 and 1
				float t = (0.5f * cos) + 0.5f;
				//printf("%f\n", t);
				clamp(t);
				vector3 g = Obj->DebugColor;
				color.x = g.x * t;
				color.y = g.y * t;
				color.z = g.z * t;


			//}

			//color.x = 255.0f;
			//color.y = 0.0f;
			//color.z = 64.0f;
		}

		

	}

}

