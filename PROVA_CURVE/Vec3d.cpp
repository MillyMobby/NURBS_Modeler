#include "Vec3d.h"

#include <iostream>

Vec3d::Vec3d() : x(0), y(0), z(0) {}
Vec3d::Vec3d(double n) : x(n), y(n), z(n) {}
Vec3d::Vec3d(double v1, double v2, double v3) : x(v1), y(v2), z(v3) {}
Vec3d::Vec3d(const Vec3d& v) : x(v.x), y(v.y), z(v.z) {}  //copy constructor
Vec3d::~Vec3d() {}


Vec3d Vec3d::operator+(const Vec3d& other) const { // ho levato la reference
	return Vec3d(x + other.x, y + other.y, z + other.z);
}

Vec3d Vec3d::operator+(const double& other) const {
	return Vec3d(x + other, y + other, z + other);
}
Vec3d Vec3d::operator+=(Vec3d& other) {//??????????????????????
	return Vec3d(x = x + other.x, y = y + other.y, z = z + other.z);
}
Vec3d Vec3d::operator+=(double other) {//???????????????????????
	return Vec3d(x = x + other, y = y + other, z = z + other);
}

//Vec3f Vec3f::operator-(const Vec3f& other) const { return Vec3f(x - other.x, y - other.y, z - other.z); }
//
//
//Vec3f Vec3f::operator-(const float& other) const { return Vec3f(x - other, y - other, z - other); }
Vec3d operator-(const double& scalare, const Vec3d& other) { return Vec3d(scalare - other.x, scalare - other.y, scalare - other.z); }

//Vec3d Vec3d::operator*(const double& other) const { return Vec3d(x * other, y * other, z * other); }
//Vec3d Vec3d::operator*(const Vec3d& other) const { return Vec3d(x * other.x, y * other.y, z * other.z); }

std::ostream& operator<<(std::ostream& output, const Vec3d& a) {
	output << endl
		<< a.x << " " << a.y << " " << a.z << " " << endl;
	return output;
}

double Vec3d::dot(Vec3d& other)
{
	return (x * other.x + y * other.y + z * other.z);
}

double Vec3d::length()
{
	return(sqrt(x * x + y * y + z * z));
}

double Vec3d::length2()
{
	return (x * x + y * y + z * z);
}

Vec3d Vec3d::normalize()
{
	return Vec3d(x / length(), y / length(), z / length());
}

Vec3d Vec3d::cross(const Vec3d& other) const {

	double v1 = y * other.z - z * other.y;
	double v2 = -1 * (x * other.z - other.x * z);
	double v3 = x * other.y - y * other.x;
	return Vec3d(v1, v2, v3);
}
// static
Vec3d Vec3d::lerp(const Vec3d& v0, const Vec3d& v1, double alpha)
{
	return alpha * (v1 - v0) + v0;
}

Vec3d operator - (const Vec3d& v0, const Vec3d& v1)
{
	return Vec3d(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
}



Vec3d operator * (double f, const Vec3d& v)
{
	return Vec3d(v.x * f, v.y * f, v.z * f);
}

Vec3d operator * (const Vec3d& v, double f)
{
	return Vec3d(v.x * f, v.y * f, v.z * f);
}

Vec3d operator / (const Vec3d& v, double f)
{
	return Vec3d(v.x / f, v.y / f, v.z / f);
}