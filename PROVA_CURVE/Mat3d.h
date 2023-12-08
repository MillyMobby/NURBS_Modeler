#pragma once
#include <vector>
#include <iostream>

#include "Vec3d.h"
using namespace std;
typedef double vtype;
class Mat3d
{
public:

	std::vector<vtype> m;

	Mat3d();
	Mat3d(vtype m0, vtype m1, vtype m2, vtype m3, vtype m4, vtype m5, vtype m6, vtype m7, vtype m8);
	~Mat3d();
	float operator() (const int i, const int j);
	Mat3d operator+(const Mat3d& other);
	//friend Mat3f operator+(const Mat3f& other, const vtype& scalare);
	Mat3d operator-(const Mat3d& other);
	Mat3d operator*(Mat3d& other);
	Mat3d operator*(const vtype& other);
	bool operator == (const Mat3d& other) const;
	bool operator != (const Mat3d& other) const;

	friend std::ostream& operator<<(std::ostream& output, const Mat3d& a);

	vtype det() const;
	Mat3d trasposta();
	void transpose();
	bool invertibile();
	Mat3d cofattori();
	Mat3d inversa();
	//Mat3f inversa2();

	static Mat3d rotateX(double radians);
	static Mat3d rotateY(double radians);
	static Mat3d rotateZ(double radians);
	static Mat3d rotation(Vec3d& rDirection, double radians);
	static Mat3d scaleMatrix(double sx, double sy, double sz);
};

Vec3d operator* (const Mat3d& mat, const Vec3d& v);