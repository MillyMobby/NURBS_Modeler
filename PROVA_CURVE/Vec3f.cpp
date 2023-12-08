#include "Vec3f.h"
#include <iostream>

Vec3f::Vec3f() : x(0), y(0), z(0) {}
Vec3f::Vec3f(float n) : x(n), y(n), z(n) {}
Vec3f::Vec3f(float v1, float v2, float v3) : x(v1), y(v2), z(v3) {}
Vec3f::Vec3f(const Vec3f& v) : x(v.x), y(v.y), z(v.z) {}  //copy constructor
Vec3f::~Vec3f() {}


Vec3f Vec3f::operator+(const Vec3f& other) const { // ho levato la reference
	return Vec3f(x + other.x, y + other.y, z + other.z);
}

Vec3f Vec3f::operator+(const float& other) const {
	return Vec3f(x + other, y + other, z + other);
}
Vec3f Vec3f::operator+=(Vec3f& other) {//??????????????????????
	return Vec3f(x = x + other.x, y = y + other.y, z = z + other.z);
}
Vec3f Vec3f::operator+=(float other) {//???????????????????????
	return Vec3f(x = x + other, y = y + other, z = z + other);
}

//Vec3f Vec3f::operator-(const Vec3f& other) const { return Vec3f(x - other.x, y - other.y, z - other.z); }
//
//
//Vec3f Vec3f::operator-(const float& other) const { return Vec3f(x - other, y - other, z - other); }
Vec3f operator-(const float& scalare, const Vec3f& other) { return Vec3f(scalare - other.x, scalare - other.y, scalare - other.z); }

//Vec3f Vec3f::operator*(const float& other) const { return Vec3f(x * other, y * other, z * other); }
//Vec3f Vec3f::operator*(const Vec3f& other) const { return Vec3f(x * other.x, y * other.y, z * other.z); }

std::ostream& operator<<(std::ostream& output, const Vec3f& a) {
	output << endl
		<< a.x << " " << a.y << " " << a.z << " " << endl;
	return output;
}

float Vec3f::dot(Vec3f& other)
{
	return (x * other.x + y * other.y + z * other.z);
}

float Vec3f::length()
{
	return(sqrt(x * x + y * y + z * z));
}

float Vec3f::length2()
{
	return (x * x + y * y + z * z);
}

Vec3f Vec3f::normalize()
{
	return Vec3f(x / length(), y / length(), z / length());
}

Vec3f Vec3f::cross(const Vec3f& other) const {

	vType v1 = y * other.z - z * other.y;
	vType v2 = -1 * (x * other.z - other.x * z);
	vType v3 = x * other.y - y * other.x;
	return Vec3f(v1, v2, v3);
}
// static
Vec3f Vec3f::lerp(const Vec3f& v0, const Vec3f& v1, float alpha)
{
	return alpha * (v1 - v0) + v0;
}

Vec3f operator - (const Vec3f& v0, const Vec3f& v1)
{
	return Vec3f(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
}



Vec3f operator * (float f, const Vec3f& v)
{
	return Vec3f(v.x * f, v.y * f, v.z * f);
}

Vec3f operator * (const Vec3f& v, float f)
{
	return Vec3f(v.x * f, v.y * f, v.z * f);
}

Vec3f operator / (const Vec3f& v, float f)
{
	return Vec3f(v.x / f, v.y / f, v.z / f);
}