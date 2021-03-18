#include "VectorMath.h"
#include <math.h>

//***************************************** VECTOR 3 *********************************************//
vector3::vector3(float A, float B, float C) {
	x = A; y = B; z = C;
	r = &x;
	g = &y; 
	b = &z;
}
vector3 vector3::normalize() {
	vector3 temp;
	temp.x = x / magnitude();
	temp.y = y / magnitude();
	temp.z = z / magnitude();
	return temp;
}

float vector3::magnitude() {
	//float X = x * x; float Y = y * y; float Z = z * z;
	double X = ( (x * x) + (y * y) + (z * z) );
	return (float)sqrt(X);
}

vector3 vector3::operator+(const vector3& b) {
	vector3 temp;
	temp.x = x + b.x;
	temp.y = y + b.y;
	temp.z = z + b.z;
	return temp;
}

vector3 vector3::operator-(const vector3& b) {
	vector3 temp;
	temp.x = x - b.x;
	temp.y = y - b.y;
	temp.z = z - b.z;
	return temp;
}
vector3 vector3::operator*(const vector3& b) {
	vector3 temp;
	temp.x = x * b.x;
	temp.y = y * b.y;
	temp.z = z * b.z;
	return temp;
}
vector3 vector3::operator/(const vector3& b) {
	vector3 temp;
	temp.x = x / b.x;
	temp.y = y / b.y;
	temp.z = z / b.z;
	return temp;
}

float vector3::dot(vector3& a, vector3& b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

vector3 vector3::operator*(const float& scalar){
	vector3 temp;
	temp.x = x * scalar;
	temp.y = y * scalar;
	temp.z = z * scalar;
	return temp;
}

vector3 vector3::operator/(const float& scalar) {
	vector3 temp;
	temp.x = x / scalar;
	temp.y = y / scalar;
	temp.z = z / scalar;
	return temp;
}

float vector3::distance(vector3& a, vector3& b) {
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
}

float vector3::angle(vector3& a, vector3& b) {
	a = a.normalize();
	b = b.normalize();
	return acos(dot(a, b));
}

vector3 vector3::operator-() const {
	vector3 temp;
	temp.x = -x; temp.y = -y; temp.z = -z;
	return temp;
}

vector3 vector3::cross(vector3& a, vector3& b) {
	vector3 temp;
	temp.x = a.y * b.z - a.z * b.y;
	temp.y = a.z * b.x - a.x * b.z;
	temp.z = a.x * b.y - a.y * b.x;
	return temp;
}

bool vector3::zero() {
	if (x == 0.0f && y == 0.0f && z == 0.0f) return true;
	return false;
}


//***************************************** END OF VECTOR 3 *********************************************//

//**************************************** VECTOR 2 *********************************************//

vector2::vector2(float A, float B) {
	x = A; y = B;
	u = &x; v = &y;
}
vector2 vector2::normalize() {
	vector2 temp;
	temp.x = x / magnitude();
	temp.y = y / magnitude();
	return temp;
}

float vector2::magnitude() {
	float X = x * x; float Y = y * y;
	return sqrt(double(X) + double(Y));

}

vector2 vector2::operator+(const vector2& b) {
	vector2 temp;
	temp.x = x + b.x;
	temp.y = y + b.y;
	return temp;
}

vector2 vector2::operator-(const vector2& b) {
	vector2 temp;
	temp.x = x - b.x;
	temp.y = y - b.y;
	return temp;
}
vector2 vector2::operator*(const vector2& b) {
	vector2 temp;
	temp.x = x * b.x;
	temp.y = y * b.y;
	return temp;
}
vector2 vector2::operator/(const vector2& b) {
	vector2 temp;
	temp.x = x / b.x;
	temp.y = y / b.y;
	return temp;
}

float vector2::dot(vector2& a, vector2& b) {
	return (a.x * b.x) + (a.y * b.y);
}

vector2 vector2::operator*(const float& scalar) {
	vector2 temp;
	temp.x = x * scalar;
	temp.y = y * scalar;
	return temp;
}

vector2 vector2::operator/(const float& scalar) {
	vector2 temp;
	temp.x = x / scalar;
	temp.y = y / scalar;
	return temp;
}

float vector2::distance(vector2& a, vector2& b) {
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

float vector2::angle(vector2& a, vector2& b) {
	a = a.normalize();
	b = b.normalize();
	return acos(dot(a, b));
}

vector2 vector2::operator-() const {
	vector2 temp;
	temp.x = -x; temp.y = -y;
	return temp;
}

bool vector2::zero() {

	if (x == 0.0f && y == 0.0f) return true;
	return false;
}



//***************************************** END OF VECTOR 2 *********************************************//

//**************************************** DUPLICATE/ALTERNATIVE function implementations *********************************************//

void clamp(float& a) {
	if (a > 1.0) {
		a = 1.0;
	}
	else if (a < 0.0) {
		a = 0.0;
	}
}

void clamp(vector3& a) {
	if (a.x > 1.0) {
		a.x = 1.0;
	}
	else if (a.x < 0.0) {
		a.x = 0.0;
	}
	if (a.y > 1.0) {
		a.y = 1.0;
	}
	else if (a.y < 0.0) {
		a.y = 0.0;
	}
	if (a.z > 1.0) {
		a.z = 1.0;
	}
	else if (a.z < 0.0) {
		a.z = 0.0;
	}
}

float dot(float x1, float y1, float z1, float x2, float y2, float z2) {
	return (x1 * x2 + y1 * y2 + z1 * z2);
}

float angle(float x1, float y1, float z1, float x2, float y2, float z2) {
	normalize(x1, y1, z1);
	normalize(x2, y2, z2);
	return  acos(dot(x1, y1, z1, x2, y2, z2));
}

void normalize(float& x, float& y, float& z) {
	float temp = sqrt(x * x + y * y + z * z);
	if (temp > 0.0) {
		x /= temp;
		y /= temp;
		z /= temp;
	}
	else {
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}
}