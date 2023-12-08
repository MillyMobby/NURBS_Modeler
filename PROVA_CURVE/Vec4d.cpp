#include "Vec4d.h"
#include <iostream>

Vec4d::Vec4d() : x(0), y(0), z(0), w(0) {};
Vec4d::Vec4d(vType n) : x(n), y(n), z(n), w(n) {};
Vec4d::Vec4d(vType v0, vType v1, vType v2, vType v3) : x(v0), y(v1), z(v2), w(v3) {};
Vec4d::Vec4d(const Vec4d& v) : x(v.x), y(v.y), z(v.z), w(v.w) {};  //copy constructor

Vec4d::Vec4d(const Vec3d& v, const vType& w) : x(v.x), y(v.y), z(v.z), w(w) {};
Vec4d::Vec4d(const Vec3d& v) : x(v.x), y(v.y), z(v.z), w(1.0f) {};
Vec4d::~Vec4d() {}; //?????????????????????????????????????????'



Vec4d Vec4d::operator+(const Vec4d& other) const {
	return Vec4d(x + other.x, y + other.y, z + other.z, other.w);
}

Vec4d Vec4d::operator+(const double& other) const {
	return Vec4d(x + other, y + other, z + other, w + other);
}

Vec4d Vec4d::operator+=(const Vec4d& other) { // ????????????????????????????????'
	return Vec4d(x = x + other.x, y = y + other.y, z = z + other.z, w + other.w);
}

Vec4d Vec4d::operator+=(const double& other) { // ??????????????????????????'
	return Vec4d(x = x + other, y = y + other, z = z + other, w = w + other);
}

Vec4d Vec4d::operator-(const Vec4d& other) const { return Vec4d(x - other.x, y - other.y, z - other.z, w - other.w); }
Vec4d Vec4d::operator-(const double& other) const { return Vec4d(x - other, y - other, z - other, w - other); }

// ????????????????????????????????????????????????
Vec4d operator-(float scalare, Vec4d& other) { return Vec4d(scalare - other.x, scalare - other.y, scalare - other.z, scalare - other.w); }

Vec4d Vec4d::operator*(const double& other) const { return Vec4d(x * other, y * other, z * other, w * other); }
Vec4d Vec4d::operator*(const Vec4d& other) const { return Vec4d(x * other.x, y * other.y, z * other.z, w * other.w); }


double Vec4d::pScalare(const Vec4d& other) const
{
	return (x * other.x + y * other.y + z * other.z + w * other.w);
}

double Vec4d::length()
{
	return(sqrt(x * x + y * y + z * z + w * w));
}

double Vec4d::length2()
{
	return (x * x + y * y + z * z + w * w);
}

Vec4d Vec4d::normalize()
{
	return Vec4d(x / length(), y / length(), z / length(), w / length());
}

Vec4d operator - (const Vec4d& v0, const Vec4d& v1)
{
	return Vec4d(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w);
}

std::ostream& operator<<(std::ostream& output, const Vec4d& a) {
	output << endl
		<< a.x << " " << a.y << " " << a.z << " " << a.w << endl;
	return output;
}