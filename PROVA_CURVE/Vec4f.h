#pragma once
#include "Vec3f.h"
#pragma once
class Vec4f
{
public:
	typedef float vType;

	vType x;
	vType y;
	vType z;
	vType w;

	Vec4f();
	Vec4f(vType n);
	Vec4f(vType v0, vType v1, vType v2, vType v3);
	Vec4f(const Vec4f& v); //copy constructor
	Vec4f(const Vec3f& v);
	Vec4f(const Vec3f& v, const vType& w);
	~Vec4f();

	Vec4f operator+(const Vec4f& other) const;
	Vec4f operator+(const float& other) const;
	Vec4f operator+=(const Vec4f& other);//??????????????????'
	Vec4f operator+=(const float& other);//????????????????????????


	Vec4f operator-(const Vec4f& other) const;
	Vec4f operator-(const float& other) const;

	Vec4f operator*(const float& other) const;
	Vec4f operator*(const Vec4f& other) const;

	friend std::ostream& operator<<(std::ostream& output, const Vec4f& a);

	float pScalare(const Vec4f& other) const;
	float length();
	float length2();
	Vec4f normalize();
};

Vec4f operator - (const Vec4f& v0, const Vec4f& v1);