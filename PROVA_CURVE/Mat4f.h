#pragma once
#include <vector>
#include <iostream>
#include "Vec4f.h"
#include "Vec3f.h"
#include "Mat3f.h"
using namespace std;
typedef float vtype;
class Mat4f
{
public:
	std::vector<float> m;

	Mat4f();
	Mat4f(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15);
	Mat4f(const float& m0);
	~Mat4f();

	Mat4f(const Mat4f& other); //copy constructor

	float operator()(const int i, const int j);
	void setAtIndex(float v, int i, int j);
	Vec4f getCol(int j) const;
	Vec4f getRow(int i) const;
	void setCol(int i, const Vec4f& v);
	void setRow(int j, const Vec4f& v);

	Mat3f getSubmat3x3();

	//static Mat3f getSubmat3x3(const Mat4f& mat);
	static Mat4f mat4FromMat3(Mat3f& mat3);

	Mat4f operator+(const Mat4f& other) const;
	//friend Mat3f operator+(const Mat3f& other, const vtype& scalare);
	Mat4f operator-(const Mat4f& other) const;
	bool operator == (const Mat4f& other) const;
	bool operator != (const Mat4f& other) const;
	Mat4f operator*(const float& other) const;
	Mat4f operator*(const Mat4f& other) const;
	Vec4f operator* (const Vec4f& v) const;

	Mat4f& operator/=(float d);

	friend std::ostream& operator<<(std::ostream& output, const Mat4f& a);

	Mat4f trasposta();
	void transpose();
	float det() const;
	static Mat4f identity();
	Mat4f inverse();

	static Mat4f translation(float x, float y, float z);
	static Mat4f translation(const Vec3f& translation);
	//static Mat4f ProjectionMatrix(float l, float r, float b, float t, float n, float f);
	static Mat4f ProjectionMatrix(float r, float t, float fov, float aspectRatio, float zNear, float zFar); // modificata per prova
	static Mat4f orthographicProjection(float width, float height, float zNear, float zFar);
	static Mat4f orthographic(float left, float right, float bottom, float top, float zNear, float zFar);
	static Mat4f ViewMatrix(const Vec3f eye, const Vec3f lookAt, const Vec3f up);
	static Mat4f scaleMatrix(float sx, float sy, float sz);

	static Mat4f rotateX(float radians);
	static Mat4f rotateY(float radians);
	static Mat4f rotateZ(float radAngle);
	static Mat4f rotation(Vec3f& rDirection, float radians);
	//static Mat4f rotation(const Quat& q);
};