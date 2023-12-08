#pragma once
#include <vector>
#include <iostream>
#include "Vec4d.h"
#include "Vec3d.h"
#include "Mat3d.h"
//#include "Quat.h"
using namespace std;
typedef double vtype;
class Mat4d
{
public:
	std::vector<float> m;


	Mat4d();
	Mat4d(double m0, double m1, double m2, double m3, double m4, double m5, double m6, double m7, double m8, double m9, double m10, double m11, double m12, double m13, double m14, double m15);
	Mat4d(const double& m0);
	~Mat4d();

	Mat4d(const Mat4d& other); //copy constructor

	double operator()(const int i, const int j);
	void setAtIndex(double v, int i, int j);
	Vec4d getCol(int j) const;
	Vec4d getRow(int i) const;
	void setCol(int i, const Vec4d& v);
	void setRow(int j, const Vec4d& v);

	Mat3d getSubmat3x3();

	//static Mat3f getSubmat3x3(const Mat4f& mat);
	static Mat4d mat4FromMat3(Mat3d& mat3);

	Mat4d operator+(const Mat4d& other) const;
	//friend Mat3f operator+(const Mat3f& other, const vtype& scalare);
	Mat4d operator-(const Mat4d& other) const;
	bool operator == (const Mat4d& other) const;
	bool operator != (const Mat4d& other) const;
	Mat4d operator*(const double& other) const;
	Mat4d operator*(const Mat4d& other) const;
	Vec4d operator* (const Vec4d& v) const;

	Mat4d& operator/=(double d);

	friend std::ostream& operator<<(std::ostream& output, const Mat4d& a);

	Mat4d trasposta();
	void transpose();
	double det() const;
	static Mat4d identity();
	//bool invertibile();
	//Mat4f cofattori();
	Mat4d inverse();
	//Mat4f inversa2();

	static Mat4d translation(double x, double y, double z);
	static Mat4d translation(const Vec3d& translation);
	//static Mat4f ProjectionMatrix(float l, float r, float b, float t, float n, float f);
	static Mat4d ProjectionMatrix(double r, double t, double fov, double aspectRatio, double zNear, double zFar); // modificata per prova
	static Mat4d orthographicProjection(double width, double height, double zNear, double zFar);
	static Mat4d orthographic(double left, double right, double bottom, double top, double zNear, double zFar);
	static Mat4d ViewMatrix(const Vec3d eye, const Vec3d lookAt, const Vec3d up);
	static Mat4d scaleMatrix(double sx, double sy, double sz);

	static Mat4d rotateX(double radians);
	static Mat4d rotateY(double radians);
	static Mat4d rotateZ(double radAngle);
	static Mat4d rotation(Vec3d& rDirection, double radians);
	//static Mat4f rotation(const Quat& q);
};