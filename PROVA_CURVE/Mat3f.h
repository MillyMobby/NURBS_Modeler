#pragma once
#include <vector>
#include <iostream>
#include "Vec3f.h"
using namespace std;
typedef float vtype;
class Mat3f
{
public:

	std::vector<vtype> m;

	Mat3f();
	Mat3f(vtype m0, vtype m1, vtype m2, vtype m3, vtype m4, vtype m5, vtype m6, vtype m7, vtype m8);
	~Mat3f();
	float operator() (const int i, const int j);
	Mat3f operator+(const Mat3f& other);
	//friend Mat3f operator+(const Mat3f& other, const vtype& scalare);
	Mat3f operator-(const Mat3f& other);
	Mat3f operator*(Mat3f& other);
	Mat3f operator*(const vtype& other);
	bool operator == (const Mat3f& other) const;
	bool operator != (const Mat3f& other) const;

	friend std::ostream& operator<<(std::ostream& output, const Mat3f& a);

	vtype det() const;
	Mat3f trasposta();
	void transpose();
	bool invertibile();
	Mat3f cofattori();
	Mat3f inversa();
	//Mat3f inversa2();

	static Mat3f rotateX(float radians);
	static Mat3f rotateY(float radians);
	static Mat3f rotateZ(float radians);
	static Mat3f rotation(Vec3f& rDirection, float radians);
};

Vec3f operator* (const Mat3f& mat, const Vec3f& v);