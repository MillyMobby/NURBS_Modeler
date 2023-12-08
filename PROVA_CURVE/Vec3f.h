#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Vec3f
{
public:
	typedef float vType;
	float x;
	float y;
	float z;

	Vec3f();
	Vec3f(float n);
	Vec3f(float v1, float v2, float v3);
	Vec3f(const Vec3f& v); //copy constructor
	~Vec3f();

	Vec3f operator+(const Vec3f& other) const;
	Vec3f operator+(const float& other) const;
	Vec3f operator+=(Vec3f& other);
	Vec3f operator+=(float other);


	/*Vec3f operator-(const Vec3f& other) const;
	Vec3f operator-(const float& other) const;*/


	//Vec3f operator*(const float& other) const;
	//Vec3f operator*(const Vec3f& other) const;

	friend std::ostream& operator<<(std::ostream& output, const Vec3f& a);

	float dot(Vec3f& other);
	float length();
	float length2();
	Vec3f normalize();
	Vec3f cross(const Vec3f& other) const;
	static Vec3f lerp(const Vec3f& v0, const Vec3f& v1, float alpha);
};

Vec3f operator - (const float& scalare, const Vec3f& other);
Vec3f operator - (const Vec3f& v0, const Vec3f& v1);

// multiply and divide by scalar
Vec3f operator * (float f, const Vec3f& v);
Vec3f operator * (const Vec3f& v, float f);
Vec3f operator / (const Vec3f& v, float f);