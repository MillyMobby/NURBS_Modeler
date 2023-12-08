#include "Mat4f.h"
using namespace std;


Mat4f::Mat4f() {
    m.push_back(0);
    m.push_back(0);
    m.push_back(0);
    m.push_back(0);

    m.push_back(0);
    m.push_back(0);
    m.push_back(0);
    m.push_back(0);

    m.push_back(0);
    m.push_back(0);
    m.push_back(0);
    m.push_back(0);

    m.push_back(0);
    m.push_back(0);
    m.push_back(0);
    m.push_back(0);
}

Mat4f::Mat4f(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15) {

    m.push_back(m0);
    m.push_back(m1);
    m.push_back(m2);
    m.push_back(m3);

    m.push_back(m4);
    m.push_back(m5);
    m.push_back(m6);
    m.push_back(m7);

    m.push_back(m8);
    m.push_back(m9);
    m.push_back(m10);
    m.push_back(m11);

    m.push_back(m12);
    m.push_back(m13);
    m.push_back(m14);
    m.push_back(m15);

}

Mat4f::Mat4f(const float& m0) {

    m.push_back(m0);
    m.push_back(0);
    m.push_back(0);
    m.push_back(0);

    m.push_back(0);
    m.push_back(m0);
    m.push_back(0);
    m.push_back(0);

    m.push_back(0);
    m.push_back(0);
    m.push_back(m0);
    m.push_back(0);

    m.push_back(0);
    m.push_back(0);
    m.push_back(0);
    m.push_back(1);

}


Mat4f::~Mat4f() {}

Mat4f::Mat4f(const Mat4f& other)
{
    m.push_back(other.m[0]);
    m.push_back(other.m[1]);
    m.push_back(other.m[2]);
    m.push_back(other.m[3]);

    m.push_back(other.m[4]);
    m.push_back(other.m[5]);
    m.push_back(other.m[6]);
    m.push_back(other.m[7]);

    m.push_back(other.m[8]);
    m.push_back(other.m[9]);
    m.push_back(other.m[10]);
    m.push_back(other.m[11]);

    m.push_back(other.m[12]);
    m.push_back(other.m[13]);
    m.push_back(other.m[14]);
    m.push_back(other.m[15]);
}

float Mat4f::operator() (const int i, const int j)
{
    return m[i * 4 + j];
}

void Mat4f::setAtIndex(float v, int i, int j)
{
    m[i * 4 + j] = v;
}

Vec4f Mat4f::getCol(int j) const {
    if (j >= 0 && j < 5) return Vec4f(m[j], m[j + 4], m[j + 8], m[j + 12]);
    else return NULL;
}
Vec4f Mat4f::getRow(int i) const {
    if (i >= 0 && i < 5) return Vec4f(m[i], m[i + 1], m[i + 2], m[i + 3]);
    else return NULL;
}
void Mat4f::setCol(int i, const Vec4f& v)
{
    if (i >= 0 && i < 4) {
        m[i] = v.x;
        m[i + 4] = v.y;
        m[i + 8] = v.z;
        m[i + 12] = v.w;
    }
}

void Mat4f::setRow(int j, const Vec4f& v)
{
    if (j >= 0 && j < 4) {
        m[j] = v.x;
        m[j + 1] = v.y;
        m[j + 2] = v.z;
        m[j + 3] = v.w;
    }
}

Mat3f Mat4f::getSubmat3x3() {
    return Mat3f(m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]);
}


Mat4f Mat4f::mat4FromMat3(Mat3f& mat3) {
    Mat4f mat4 = Mat4f(mat3.m[0], mat3.m[1], mat3.m[2], 0.0f,
        mat3.m[3], mat3.m[4], mat3.m[5], 0.0f,
        mat3.m[6], mat3.m[7], mat3.m[8], 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);

    return mat4;
}

Mat4f Mat4f::operator+(const Mat4f& other) const
{
    return Mat4f(
        m[0] + other.m[0], m[1] + other.m[1], m[2] + other.m[2], m[3] + other.m[3],
        m[4] + other.m[4], m[5] + other.m[5], m[6] + other.m[6], m[7] + other.m[7],
        m[8] + other.m[8], m[9] + other.m[9], m[10] + other.m[10], m[11] + other.m[11],
        m[12] + other.m[12], m[13] + other.m[13], m[14] + other.m[14], m[15] + other.m[15]);
}

Mat4f Mat4f::operator-(const Mat4f& other) const
{
    return Mat4f(m[0] - other.m[0], m[1] - other.m[1], m[2] - other.m[2], m[3] - other.m[3],
        m[4] - other.m[4], m[5] - other.m[5], m[6] - other.m[6], m[7] - other.m[7],
        m[8] - other.m[8], m[9] - other.m[9], m[10] - other.m[10], m[11] - other.m[11],
        m[12] - other.m[12], m[13] - other.m[13], m[14] - other.m[14], m[15] - other.m[15]);
}

bool Mat4f::operator == (const Mat4f& other) const {
    return (m[0] == other.m[0] && m[1] == other.m[1] && m[2] == other.m[2] && m[3] == other.m[3]
        && m[4] == other.m[4] && m[5] == other.m[5] && m[6] == other.m[6] && m[7] == other.m[7]
        && m[8] == other.m[8] && m[9] == other.m[9] && m[10] == other.m[10] && m[11] == other.m[11]
        && m[12] == other.m[12] && m[13] == other.m[13] && m[14] == other.m[14] && m[15] == other.m[15]);
}

bool Mat4f::operator != (const Mat4f& other) const {
    return (m[0] != other.m[0] || m[1] != other.m[1] || m[2] != other.m[2] || m[3] != other.m[3]
        || m[4] != other.m[4] || m[5] != other.m[5] || m[6] != other.m[6] || m[7] != other.m[7]
        || m[8] != other.m[8] && m[9] != other.m[9] || m[10] != other.m[10] || m[11] != other.m[11]
        || m[12] != other.m[12] || m[13] != other.m[13] || m[14] != other.m[14] || m[15] != other.m[15]);
}

Mat4f Mat4f::operator*(const Mat4f& other) const
{
    return Mat4f(m.at(0) * other.m.at(0) + m.at(1) * other.m.at(4) + m.at(2) * other.m.at(8) + m.at(3) * other.m.at(12),
        m.at(0) * other.m.at(1) + m.at(1) * other.m.at(5) + m.at(2) * other.m.at(9) + m.at(3) * other.m.at(13),
        m.at(0) * other.m.at(2) + m.at(1) * other.m.at(6) + m.at(2) * other.m.at(10) + m.at(3) * other.m.at(14),
        m.at(0) * other.m.at(3) + m.at(1) * other.m.at(7) + m.at(2) * other.m.at(11) + m.at(3) * other.m.at(15),

        m.at(4) * other.m.at(0) + m.at(5) * other.m.at(4) + m.at(6) * other.m.at(8) + m.at(7) * other.m.at(12),
        m.at(4) * other.m.at(1) + m.at(5) * other.m.at(5) + m.at(6) * other.m.at(9) + m.at(7) * other.m.at(13),
        m.at(4) * other.m.at(2) + m.at(5) * other.m.at(6) + m.at(6) * other.m.at(10) + m.at(7) * other.m.at(14),
        m.at(4) * other.m.at(3) + m.at(5) * other.m.at(7) + m.at(6) * other.m.at(11) + m.at(7) * other.m.at(15),

        m.at(8) * other.m.at(0) + m.at(9) * other.m.at(4) + m.at(10) * other.m.at(8) + m.at(11) * other.m.at(12),
        m.at(8) * other.m.at(1) + m.at(9) * other.m.at(5) + m.at(10) * other.m.at(9) + m.at(11) * other.m.at(13),
        m.at(8) * other.m.at(2) + m.at(9) * other.m.at(6) + m.at(10) * other.m.at(10) + m.at(11) * other.m.at(14),
        m.at(8) * other.m.at(3) + m.at(9) * other.m.at(7) + m.at(10) * other.m.at(11) + m.at(11) * other.m.at(15),

        m.at(12) * other.m.at(0) + m.at(13) * other.m.at(4) + m.at(14) * other.m.at(8) + m.at(15) * other.m.at(12),
        m.at(12) * other.m.at(1) + m.at(13) * other.m.at(5) + m.at(14) * other.m.at(9) + m.at(15) * other.m.at(13),
        m.at(12) * other.m.at(2) + m.at(13) * other.m.at(6) + m.at(14) * other.m.at(10) + m.at(15) * other.m.at(14),
        m.at(12) * other.m.at(3) + m.at(13) * other.m.at(7) + m.at(14) * other.m.at(11) + m.at(15) * other.m.at(15));
}

Vec4f Mat4f::operator*(const Vec4f& v) const {

    float x, y, z, w;
    x = m[0] * v.x + m[1] * v.y + m[2] * v.z + m[3] * v.w;
    y = m[4] * v.x + m[5] * v.y + m[6] * v.z + m[7] * v.w;
    z = m[8] * v.x + m[9] * v.y + m[10] * v.z + m[11] * v.w;
    w = m[12] * v.x + m[13] * v.y + m[14] * v.z + m[15] * v.w;

    return Vec4f(x, y, z, w);
}

Mat4f Mat4f::operator*(const float& other) const {
    return Mat4f(m[0] * other, m[1] * other, m[2] * other, m[3] * other,
        m[4] * other, m[5] * other, m[6] * other, m[7] * other,
        m[8] * other, m[9] * other, m[10] * other, m[11] * other,
        m[12] * other, m[13] * other, m[14] * other, m[15] * other);
}

Mat4f& Mat4f::operator/=(float d) {
    for (int i = 0; i < 16; i++) {
        m[i] /= d;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& output, const Mat4f& a) {   
    output << endl
        << a.m[0] << " " << a.m[1] << " " << a.m[2] << " " << a.m[3] << endl
        << a.m[4] << " " << a.m[5] << " " << a.m[6] << " " << a.m[7] << endl
        << a.m[8] << " " << a.m[9] << " " << a.m[10] << " " << a.m[11] << endl
        << a.m[12] << " " << a.m[13] << " " << a.m[14] << " " << a.m[15] << endl;
    return output;
}

Mat4f Mat4f::trasposta() {
    return Mat4f(
        m[0], m[4], m[8], m[12],
        m[1], m[5], m[9], m[13],
        m[2], m[6], m[10], m[14],
        m[3], m[7], m[11], m[15]);
}

void Mat4f::transpose() {  }

float Mat4f::det() const
{
    float m00 = m[0];
    float m10 = m[1];
    float m20 = m[2];
    float m30 = m[3];

    float m01 = m[4];
    float m11 = m[5];
    float m21 = m[6];
    float m31 = m[7];

    float m02 = m[8];
    float m12 = m[9];
    float m22 = m[10];
    float m32 = m[11];

    float m03 = m[12];
    float m13 = m[13];
    float m23 = m[14];
    float m33 = m[15];

    Mat3f sub00 = Mat3f(m11, m12, m13, m21, m22, m23, m31, m32, m33);
    Mat3f sub01 = Mat3f(m12, m13, m10, m22, m23, m20, m32, m33, m30);
    Mat3f sub02 = Mat3f(m13, m10, m11, m23, m20, m21, m33, m30, m31);
    Mat3f sub03 = Mat3f(m10, m11, m12, m20, m21, m22, m30, m31, m32);

    float cofactor00 = sub00.det();
    float cofactor01 = -sub01.det();
    float cofactor02 = sub02.det();
    float cofactor03 = -sub03.det();

    return(m00 * cofactor00 + m01 * cofactor01 + m02 * cofactor02 + m03 * cofactor03);
}

Mat4f Mat4f::identity()
{
    return Mat4f(1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4f Mat4f::inverse() {
    float m00 = m[0];
    float m10 = m[1];
    float m20 = m[2];
    float m30 = m[3];

    float m01 = m[4];
    float m11 = m[5];
    float m21 = m[6];
    float m31 = m[7];
    float m02 = m[8];
    float m12 = m[9];
    float m22 = m[10];
    float m32 = m[11];

    float m03 = m[12];
    float m13 = m[13];
    float m23 = m[14];
    float m33 = m[15];

    Mat3f sub00 = Mat3f(m11, m12, m13, m21, m22, m23, m31, m32, m33);
    Mat3f sub01 = Mat3f(m12, m13, m10, m22, m23, m20, m32, m33, m30);
    Mat3f sub02 = Mat3f(m13, m10, m11, m23, m20, m21, m33, m30, m31);
    Mat3f sub03 = Mat3f(m10, m11, m12, m20, m21, m22, m30, m31, m32);

    Mat3f sub10 = Mat3f(m21, m22, m23, m31, m32, m33, m01, m02, m03);
    Mat3f sub11 = Mat3f(m22, m23, m20, m32, m33, m30, m02, m03, m00);
    Mat3f sub12 = Mat3f(m23, m20, m21, m33, m30, m31, m03, m00, m01);
    Mat3f sub13 = Mat3f(m20, m21, m22, m30, m31, m32, m00, m01, m02);

    Mat3f sub20 = Mat3f(m31, m32, m33, m01, m02, m03, m11, m12, m13);
    Mat3f sub21 = Mat3f(m32, m33, m30, m02, m03, m00, m12, m13, m10);
    Mat3f sub22 = Mat3f(m33, m30, m31, m03, m00, m01, m13, m10, m11);
    Mat3f sub23 = Mat3f(m30, m31, m32, m00, m01, m02, m10, m11, m12);

    Mat3f sub30 = Mat3f(m01, m02, m03, m11, m12, m13, m21, m22, m23);
    Mat3f sub31 = Mat3f(m02, m03, m00, m12, m13, m10, m22, m23, m20);
    Mat3f sub32 = Mat3f(m03, m00, m01, m13, m10, m11, m23, m20, m21);
    Mat3f sub33 = Mat3f(m00, m01, m02, m10, m11, m12, m20, m21, m22);

    float cofactor00 = sub00.det();
    float cofactor01 = -sub01.det();
    float cofactor02 = sub02.det();
    float cofactor03 = -sub03.det();

    float cofactor10 = -sub10.det();
    float cofactor11 = sub11.det();
    float cofactor12 = -sub12.det();
    float cofactor13 = sub13.det();

    float cofactor20 = sub20.det();
    float cofactor21 = -sub21.det();
    float cofactor22 = sub22.det();
    float cofactor23 = -sub23.det();

    float cofactor30 = -sub30.det();
    float cofactor31 = sub31.det();
    float cofactor32 = -sub32.det();
    float cofactor33 = sub33.det();

    float determinant = m00 * cofactor00 + m01 * cofactor01 + m02 * cofactor02 + m03 * cofactor03;

    if (determinant != 0.0f) {
        float reciprocalDet = 1.0f / determinant;

        return Mat4f            
             (
                 cofactor00 * reciprocalDet, cofactor01 * reciprocalDet, cofactor02 * reciprocalDet, cofactor03 * reciprocalDet,
                 cofactor10 * reciprocalDet, cofactor11 * reciprocalDet, cofactor12 * reciprocalDet, cofactor13 * reciprocalDet,
                 cofactor20 * reciprocalDet, cofactor21 * reciprocalDet, cofactor22 * reciprocalDet, cofactor23 * reciprocalDet,
                 cofactor30 * reciprocalDet, cofactor31 * reciprocalDet, cofactor32 * reciprocalDet, cofactor33 * reciprocalDet
             );

    }
    else return *this;


}

Mat4f Mat4f::translation(float x, float y, float z)
{
    return Mat4f
    (
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    );
}

// static
Mat4f Mat4f::translation(const Vec3f& translation)
{
    return Mat4f
    (
        1, 0, 0, translation.x,
        0, 1, 0, translation.y,
        0, 0, 1, translation.z,
        0, 0, 0, 1
    );
}

//Mat4f Mat4f::ProjectionMatrix(float l, float r, float b, float t, float n, float f)
//{
//    Mat4f projection = Mat4f();
//
//    projection.m[0] = (2.0f * n) / (r - l);
//    projection.m[5] = (2.0f * n) / (t - b);
//    projection.m[2] = (r + l) / (r - l);
//    projection.m[6] = (t + b) / (t - b);
//    projection.m[1] = -1;
//    projection.m[10] = (n + f) / (n - f);
//    projection.m[11] = (2.0f * n * f) / (n - f);
//
//    return projection;
//}

Mat4f Mat4f::ProjectionMatrix(float r, float t, float fov, float aspectRatio, float zNear, float zFar) // modificato
{
    Mat4f projection = Mat4f();

    projection.m[0] = zNear / r;
    projection.m[5] = zNear / t;

    projection.m[14] = -1;

    projection.m[10] = -(zFar + zNear) / (zFar - zNear); 


    projection.m[11] = -2.f * zFar * zNear / (zFar - zNear);


    //std::cout << "questa è la projectionMatrix" << projection;

    return projection;
}

Mat4f Mat4f::orthographicProjection(float width, float height, float zNear, float zFar)
{
    Mat4f m;

    m.m[0] = 2.0f / width;
    m.m[5] = 2.0f / height;
    m.m[15] = 1.0f;

    m.m[3] = -1;
    m.m[7] = -1;


    m.m[10] = 2.0f / (zNear - zFar);
    m.m[11] = (zNear + zFar) / (zNear - zFar);


    return m;
}
Mat4f Mat4f::orthographic(float left, float right, float bottom, float top, float zNear, float zFar)
{
    Mat4f m;

    m.m[0] = 2.0f / (right - left);
    m.m[5] = 2.0f / (top - bottom);
    m.m[15] = 1.0f;

    m.m[3] = (left + right) / (left - right);
    m.m[7] = (top + bottom) / (bottom - top);

    
    m.m[10] = 2.0f / (zNear - zFar);
    m.m[11] = (zNear + zFar) / (zNear - zFar);
   
    return m;
}
Mat4f Mat4f::ViewMatrix(const Vec3f eye, const Vec3f lookAt, const Vec3f up)
{

    Vec3f z3f = (eye - lookAt).normalize(); //zv
    Vec3f y3f = up;
    Vec4f z = Vec4f(z3f, 0.0); 
    //Vec4f y = Vec4f(up, 0); // y = zv x xv
    Vec3f x3f = y3f.cross(z3f); 
    Vec4f x = Vec4f((y3f.cross(z3f)).normalize(), 0.0); // up x zv x
    Vec4f y = Vec4f((z3f.cross(x3f)).normalize(), 0.0); // new prova y
    Vec4f eye4f = Vec4f(eye, 1.0);


    Mat4f view = Mat4f();

    view.setCol(0, x);
    view.setCol(1, y);
    view.setCol(2, z);
    view.setCol(3, eye4f);

    Mat4f WorldToCam = view.inverse();
    return WorldToCam;


}

// static
Mat4f Mat4f::rotateX(float radians)
{
    float a = cos(radians);
    float b = sin(radians);

    return Mat4f
    (
        1, 0, 0, 0,
        0, a, -b, 0,
        0, b, a, 0,
        0, 0, 0, 1
    );
}

// static
Mat4f Mat4f::rotateY(float radians)
{
    float a = cos(radians);
    float b = sin(radians);

    return Mat4f
    (
        a, 0, b, 0,
        0, 1, 0, 0,
        -b, 0, a, 0,
        0, 0, 0, 1
    );
}

// static
Mat4f Mat4f::rotateZ(float radAngle)
{
    float a = cos(radAngle);
    float b = sin(radAngle);

    return Mat4f
    (
        a, -b, 0, 0,
        b, a, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

// static
Mat4f Mat4f::scaleMatrix(float sx, float sy, float sz)
{
    return Mat4f
    (
        sx, 0, 0, 0,
        0, sy, 0, 0,
        0, 0, sz, 0,
        0, 0, 0, 1
    );
}

Mat4f Mat4f::rotation(Vec3f& rDirection, float radians)
{
    Vec3f normalizedDirection = rDirection.normalize();

    float cosTheta = cos(radians);
    float sinTheta = sin(radians);

    float x = normalizedDirection.x;
    float y = normalizedDirection.y;
    float z = normalizedDirection.z;

    return Mat4f
    (
        x * x * (1.0f - cosTheta) + cosTheta, y * x * (1.0f - cosTheta) - z * sinTheta, z * x * (1.0f - cosTheta) + y * sinTheta, 0.0f,
        x * y * (1.0f - cosTheta) + z * sinTheta, y * y * (1.0f - cosTheta) + cosTheta, z * y * (1.0f - cosTheta) - x * sinTheta, 0.0f,
        x * z * (1.0f - cosTheta) - y * sinTheta, y * z * (1.0f - cosTheta) + x * sinTheta, z * z * (1.0f - cosTheta) + cosTheta, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}


