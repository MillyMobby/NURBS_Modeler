#include "Vec4f.h"
#include <iostream>

Vec4f::Vec4f() : x(0), y(0), z(0), w(0) {};
Vec4f::Vec4f(vType n) : x(n), y(n), z(n), w(n) {};
Vec4f::Vec4f(vType v0, vType v1, vType v2, vType v3) : x(v0), y(v1), z(v2), w(v3) {};
Vec4f::Vec4f(const Vec4f& v) : x(v.x), y(v.y), z(v.z), w(v.w) {};  //copy constructor

Vec4f::Vec4f(const Vec3f& v, const vType& w) : x(v.x), y(v.y), z(v.z), w(w) {};
Vec4f::Vec4f(const Vec3f& v) : x(v.x), y(v.y), z(v.z), w(1.0f) {};
Vec4f::~Vec4f() {}; //?????????????????????????????????????????'



Vec4f Vec4f::operator+(const Vec4f& other) const {
	return Vec4f(x + other.x, y + other.y, z + other.z, other.w);
}

Vec4f Vec4f::operator+(const float& other) const {
	return Vec4f(x + other, y + other, z + other, w + other);
}

Vec4f Vec4f::operator+=(const Vec4f& other) { // ????????????????????????????????'
	return Vec4f(x = x + other.x, y = y + other.y, z = z + other.z, w + other.w);
}

Vec4f Vec4f::operator+=(const float& other) { // ??????????????????????????'
	return Vec4f(x = x + other, y = y + other, z = z + other, w = w + other);
}

Vec4f Vec4f::operator-(const Vec4f& other) const { return Vec4f(x - other.x, y - other.y, z - other.z, w - other.w); }
Vec4f Vec4f::operator-(const float& other) const { return Vec4f(x - other, y - other, z - other, w - other); }

// ????????????????????????????????????????????????
Vec4f operator-(float scalare, Vec4f& other) { return Vec4f(scalare - other.x, scalare - other.y, scalare - other.z, scalare - other.w); }

Vec4f Vec4f::operator*(const float& other) const { return Vec4f(x * other, y * other, z * other, w * other); }
Vec4f Vec4f::operator*(const Vec4f& other) const { return Vec4f(x * other.x, y * other.y, z * other.z, w * other.w); }


float Vec4f::pScalare(const Vec4f& other) const
{
	return (x * other.x + y * other.y + z * other.z + w * other.w);
}

float Vec4f::length()
{
	return(sqrt(x * x + y * y + z * z + w * w));
}

float Vec4f::length2()
{
	return (x * x + y * y + z * z + w * w);
}

Vec4f Vec4f::normalize()
{
	return Vec4f(x / length(), y / length(), z / length(), w / length());
}

Vec4f operator - (const Vec4f& v0, const Vec4f& v1)
{
	return Vec4f(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w);
}

std::ostream& operator<<(std::ostream& output, const Vec4f& a) {
	output << endl
		<< a.x << " " << a.y << " " << a.z << " " << a.w << endl;
	return output;
}