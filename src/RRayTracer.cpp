#include "RC.h"
Camera::Camera(vector3 p, int w, int h, float fd): Pos(p), width(w), height(h), focus_dist(fd) {
	
}

Camera::~Camera() {

}

void Camera::setlook(vector3 up, vector3 lookview) {
	Up = up.normalize();
	LookView = lookview.normalize();
	n2 = lookview / lookview.magnitude();
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



void RRayTracer::Render(Image& output) {
	printf("%s\n", raytracer->lightList[0]->name);
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

	const unsigned short testing = 0;

	color = vector3(0.0, 0.0, 0.0);
	HitPos = vector3(10000000.0f, 100000000.0f, 10000000.0f);
	HitNormal = vector3();
	hit = false; //output hit
	bool didhit = false;
	//Obj = objList[0];
	for (Object* object : objList) {
		hit = object->hit(persp->Pos, ray, currentHit, currentNormal);
		if (hit) {
			didhit = true;
			

			if (vector3::distance(Pe, currentHit) < vector3::distance(Pe, HitPos)) {
				HitPos = currentHit;
				HitNormal = currentNormal;
				Obj = object;
			}
		}
	}
	for (Light* l : lightList) {
		//if (Obj->getType() == sphere) {
		//	printf("%f. %f, %f, %d \n", color.x, color.y, color.z, Obj->getType());
		//}
		if (l->isVisible())
		{
			visibleLights.push_back(l);
		}
	}


	//}

	if (!didhit || visibleLights.size() == 0) {
		color = vector3();
		return;
	}
	else {
		//check the diffuse, specular, transmisstion values; determine if you need to shoot are recursive ray from the hit point
		//if you need to trace another ray, trace it 
		//hitobj.getcolor(s)
		vector3 dc = Obj->DebugColor;
		for (Light* l : visibleLights) {
			if (testing) {
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
			else {
				
				color = Obj->material->GetColor(l->out_t, l->out_s);

			}

		}

		visibleLights.clear();

		

	}

}

bool RRayTracer::raycast(vector3& point, vector3& Nr, std::vector<Object*> objList, Object* Obj, vector3* hitpoint, vector3* hitnormal, bool checkall) {
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

