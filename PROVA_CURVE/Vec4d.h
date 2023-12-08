#pragma once
#include "Vec3d.h"
#pragma once
class Vec4d
{
public:
	typedef double vType;

	vType x;
	vType y;
	vType z;
	vType w;

	Vec4d();
	Vec4d(vType n);
	Vec4d(vType v0, vType v1, vType v2, vType v3);
	Vec4d(const Vec4d& v); //copy constructor
	Vec4d(const Vec3d& v);
	Vec4d(const Vec3d& v, const vType& w);
	~Vec4d();

	Vec4d operator+(const Vec4d& other) const;
	Vec4d operator+(const double& other) const;
	Vec4d operator+=(const Vec4d& other);//??????????????????'
	Vec4d operator+=(const double& other);//????????????????????????


	Vec4d operator-(const Vec4d& other) const;
	Vec4d operator-(const double& other) const;

	Vec4d operator*(const double& other) const;
	Vec4d operator*(const Vec4d& other) const;

	friend std::ostream& operator<<(std::ostream& output, const Vec4d& a);

	double pScalare(const Vec4d& other) const;
	double length();
	double length2();
	Vec4d normalize();
};

Vec4d operator - (const Vec4d& v0, const Vec4d& v1);