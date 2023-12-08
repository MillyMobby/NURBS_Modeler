#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Vec3d
{
public:
	typedef float vType;
	double x;
	double y;
	double z;

	Vec3d();
	Vec3d(double n);
	Vec3d(double v1, double v2, double v3);
	Vec3d(const Vec3d& v); //copy constructor
	~Vec3d();

	Vec3d operator+(const Vec3d& other) const;
	Vec3d operator+(const double& other) const;
	Vec3d operator+=(Vec3d& other);
	Vec3d operator+=(double other);


	/*Vec3f operator-(const Vec3f& other) const;
	Vec3f operator-(const float& other) const;*/


	/*Vec3d operator*(const double& other) const;
	Vec3d operator*(const Vec3d& other) const;*/

	friend std::ostream& operator<<(std::ostream& output, const Vec3d& a);

	double dot(Vec3d& other);
	double length();
	double length2();
	Vec3d normalize();
	Vec3d cross(const Vec3d& other) const;
	static Vec3d lerp(const Vec3d& v0, const Vec3d& v1, double alpha);
};

Vec3d operator - (const double& scalare, const Vec3d& other);
Vec3d operator - (const Vec3d& v0, const Vec3d& v1);

// multiply and divide by scalar
Vec3d operator * (double f, const Vec3d& v);
Vec3d operator * (const Vec3d& v, double f);
Vec3d operator / (const Vec3d& v, double f);