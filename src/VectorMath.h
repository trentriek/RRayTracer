#pragma once
#ifndef VECTOR_MATH
#define VECTOR_MATH

#define PI 3.14159
struct vector3 {

	float x, y, z;
	float* r; float* g; float *b;
	vector3(float a = 0.0, float b = 0.0, float c = 0.0);
	vector3 normalize();
	float magnitude();
	static float dot(vector3& a, vector3& b);
	static vector3 cross(vector3& a, vector3& b);
	static float distance(vector3& a, vector3& b);
	static float angle(vector3& a, vector3& b);
	vector3 operator+(const vector3& b);
	vector3 operator-(const vector3& b);
	vector3 operator*(const vector3& b);
	vector3 operator/(const vector3& b);
	vector3 operator*(const float& scalar);
	vector3 operator/(const float& scalar);
	vector3 operator-() const;
	void getvalues(float* out);
	void getvalues(int* out);
	bool zero();

};


struct vector2 {
	float x, y;
	float* u; float* v;
	vector2(float a = 0.0, float b = 0.0);
	vector2 normalize();
	float magnitude();
	static float dot(vector2& a, vector2& b);
	//static vector2 cross(vector2& a, vector2& b);
	static float distance(vector2& a, vector2& b);
	static float angle(vector2& a, vector2& b);
	vector2 operator+(const vector2& b);
	vector2 operator-(const vector2& b);
	vector2 operator*(const vector2& b);
	vector2 operator/(const vector2& b);
	vector2 operator*(const float& scalar);
	vector2 operator/(const float& scalar);
	vector2 operator-() const;
	void getvalues(float* out);
	void getvalues(int* out);
	bool zero();
};

void clamp(float &a);

float dot(float x1, float y1, float z1, float x2, float y2, float z2);

void normalize(float& x, float& y, float& z);

float angle(float x1, float y1, float z1, float x2, float y2, float z2);

#endif
