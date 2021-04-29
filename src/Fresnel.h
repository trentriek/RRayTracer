#pragma once
#ifndef FRENSEL
#define FRESNEL
#include "VectorMath.h"
#include <math.h>

//namespace fresnel {

	static double snells(double n1, double n2, double theta_i) { //returns angle of transmission
		if (abs((n1 / n2) * sin(theta_i)) > 1) {
			return asin(1);
		}
		return(asin((n1 / n2) * sin(theta_i)));
	}

	static vector3 reflection_angle(vector3& V, vector3& N) {
		//c = cos(theta) = dot(v,n)
		return -V + N * ( 2 * ( vector3::dot(V,N) ) ) ;
		//return vector3(2 * N.x * N.z, 2 * N.y * N.z, (2 * N.z * N.z) - 1);
	}


	static double angle(vector3 a, vector3 b) {
		normalize(a.x, a.y, a.z);
		normalize(b.x, b.y, b.z);
		return acos(vector3::dot(a, b));
	}

	static double fresnels(vector3& V, vector3& N, double& theta_i, double& theta_t, double n1, double n2 = 1.0) {

		theta_i = angle(V, N);
		theta_t = snells(n1, n2, theta_i);
		//theta_r = angle(V, N); //is theta_r the same as theta_i?

		double Rp, Rs, R = 0.0;
		/********needs to be updated!*******/
		Rs = pow(
			((n1 * cos(theta_i)) - (n2 * cos(theta_t)))
			/
			((n1 * cos(theta_i)) + (n2 * cos(theta_t)))

			, 2);
		Rp = pow(
			((n1 * cos(theta_t)) - (n2 * cos(theta_i)))
			/
			((n1 * cos(theta_t)) + (n2 * cos(theta_i)))

			, 2);

		R = (Rs + Rp) / 2;
		return R;
	}

	static bool fresnels(vector3& V, vector3& N, vector3& outray, double n1, double n2 = 1.0) {
		float C = vector3::dot(V, N);
		float inofref = n1 / n2;

		float discriminant = ((C * C - 1) / (inofref * inofref) ) + 1.0f;

		if (discriminant > 0) {

			float b = (C / inofref) + sqrt(discriminant);

			outray = V * (-1.0f / inofref) + N * b;
			return false;
		}
		else {
			outray = -V + ( N * (2.0f * C) );
			return true;
		}
	}

//};




#endif // !FRENSEL
