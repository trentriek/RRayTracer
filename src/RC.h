#pragma once
#ifndef RENDER_CACHE
#define RENDER_CACHE
#include "VectorMath.h"
#include "Object.h"
#include "RRayTracer.h"
#include "LightTypes.h"
#include "PolygonMesh.h"


	extern RRayTracer* raytracer;
	//extern vector3 Npe;           removed these, they are located in the RRayTracer
	//extern vector3 Pe;
	//extern vector3 HitPos;
	//extern vector3 HitNormal;
	//extern Object* hitobj;
	extern Camera* CurrentCam;
	extern Material defaultMat;

#endif // !RENDER_CACHE
