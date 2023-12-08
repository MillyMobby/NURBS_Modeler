#include "Mat4d.h"
using namespace std;


Mat4d::Mat4d() {
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

Mat4d::Mat4d(double m0, double m1, double m2, double m3, double m4, double m5, double m6, double m7, double m8, double m9, double m10, double m11, double m12, double m13, double m14, double m15) {

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

Mat4d::Mat4d(const double& m0) {

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

Mat4d::~Mat4d() {}

Mat4d::Mat4d(const Mat4d& other)
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

double Mat4d::operator() (const int i, const int j)
{
    return m[i * 4 + j];
}

void Mat4d::setAtIndex(double v, int i, int j)
{
    m[i * 4 + j] = v;
}

Vec4d Mat4d::getCol(int j) const {
    if (j >= 0 && j < 5) return Vec4d(m[j], m[j + 4], m[j + 8], m[j + 12]);
    else return NULL;
}
Vec4d Mat4d::getRow(int i) const {
    if (i >= 0 && i < 5) return Vec4d(m[i], m[i + 1], m[i + 2], m[i + 3]);
    else return NULL;
}
void Mat4d::setCol(int i, const Vec4d& v)
{
    if (i >= 0 && i < 4) {
        m[i] = v.x;
        m[i + 4] = v.y;
        m[i + 8] = v.z;
        m[i + 12] = v.w;
    }
}

void Mat4d::setRow(int j, const Vec4d& v)
{
    if (j >= 0 && j < 4) {
        m[j] = v.x;
        m[j + 1] = v.y;
        m[j + 2] = v.z;
        m[j + 3] = v.w;
    }
}

Mat3d Mat4d::getSubmat3x3()
{
    //std::cout << "stampo in getSubMat i vari valori: ";
    return Mat3d(m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]);

}


Mat4d Mat4d::mat4FromMat3(Mat3d& mat3) // NEW PROVA
{

    Mat4d mat4 = Mat4d(mat3.m[0], mat3.m[1], mat3.m[2], 0.0f,
        mat3.m[3], mat3.m[4], mat3.m[5], 0.0f,
        mat3.m[6], mat3.m[7], mat3.m[8], 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);

    return mat4;
}

Mat4d Mat4d::operator+(const Mat4d& other) const
{
    return Mat4d(
        m[0] + other.m[0], m[1] + other.m[1], m[2] + other.m[2], m[3] + other.m[3],
        m[4] + other.m[4], m[5] + other.m[5], m[6] + other.m[6], m[7] + other.m[7],
        m[8] + other.m[8], m[9] + other.m[9], m[10] + other.m[10], m[11] + other.m[11],
        m[12] + other.m[12], m[13] + other.m[13], m[14] + other.m[14], m[15] + other.m[15]);
}

Mat4d Mat4d::operator-(const Mat4d& other) const
{
    return Mat4d(m[0] - other.m[0], m[1] - other.m[1], m[2] - other.m[2], m[3] - other.m[3],
        m[4] - other.m[4], m[5] - other.m[5], m[6] - other.m[6], m[7] - other.m[7],
        m[8] - other.m[8], m[9] - other.m[9], m[10] - other.m[10], m[11] - other.m[11],
        m[12] - other.m[12], m[13] - other.m[13], m[14] - other.m[14], m[15] - other.m[15]);
}

bool Mat4d::operator == (const Mat4d& other) const {
    return (m[0] == other.m[0] && m[1] == other.m[1] && m[2] == other.m[2] && m[3] == other.m[3]
        && m[4] == other.m[4] && m[5] == other.m[5] && m[6] == other.m[6] && m[7] == other.m[7]
        && m[8] == other.m[8] && m[9] == other.m[9] && m[10] == other.m[10] && m[11] == other.m[11]
        && m[12] == other.m[12] && m[13] == other.m[13] && m[14] == other.m[14] && m[15] == other.m[15]);
}

bool Mat4d::operator != (const Mat4d& other) const {
    return (m[0] != other.m[0] || m[1] != other.m[1] || m[2] != other.m[2] || m[3] != other.m[3]
        || m[4] != other.m[4] || m[5] != other.m[5] || m[6] != other.m[6] || m[7] != other.m[7]
        || m[8] != other.m[8] && m[9] != other.m[9] || m[10] != other.m[10] || m[11] != other.m[11]
        || m[12] != other.m[12] || m[13] != other.m[13] || m[14] != other.m[14] || m[15] != other.m[15]);
}

Mat4d Mat4d::operator*(const Mat4d& other) const
{
    return Mat4d(m.at(0) * other.m.at(0) + m.at(1) * other.m.at(4) + m.at(2) * other.m.at(8) + m.at(3) * other.m.at(12),
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

Vec4d Mat4d::operator*(const Vec4d& v) const {

    float x, y, z, w;
    x = m[0] * v.x + m[1] * v.y + m[2] * v.z + m[3] * v.w;
    y = m[4] * v.x + m[5] * v.y + m[6] * v.z + m[7] * v.w;
    z = m[8] * v.x + m[9] * v.y + m[10] * v.z + m[11] * v.w;
    w = m[12] * v.x + m[13] * v.y + m[14] * v.z + m[15] * v.w;

    return Vec4d(x, y, z, w);

}

Mat4d Mat4d::operator*(const double& other) const {
    return Mat4d(m[0] * other, m[1] * other, m[2] * other, m[3] * other,
        m[4] * other, m[5] * other, m[6] * other, m[7] * other,
        m[8] * other, m[9] * other, m[10] * other, m[11] * other,
        m[12] * other, m[13] * other, m[14] * other, m[15] * other);
}

Mat4d& Mat4d::operator/=(double d)
{
    for (int i = 0; i < 16; i++) {
        m[i] /= d;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& output, const Mat4d& a)
{
    //std::cout << "operator << mat4f " << a.m.size() << std::endl;
    output << endl
        << a.m[0] << " " << a.m[1] << " " << a.m[2] << " " << a.m[3] << endl
        << a.m[4] << " " << a.m[5] << " " << a.m[6] << " " << a.m[7] << endl
        << a.m[8] << " " << a.m[9] << " " << a.m[10] << " " << a.m[11] << endl
        << a.m[12] << " " << a.m[13] << " " << a.m[14] << " " << a.m[15] << endl;
    return output;
}

Mat4d Mat4d::trasposta() {
    return Mat4d(
        m[0], m[4], m[8], m[12],
        m[1], m[5], m[9], m[13],
        m[2], m[6], m[10], m[14],
        m[3], m[7], m[11], m[15]);
}

void Mat4d::transpose()
{

}

double Mat4d::det() const
{
    double m00 = m[0];
    double m10 = m[1];
    double m20 = m[2];
    double m30 = m[3];

    double m01 = m[4];
    double m11 = m[5];
    double m21 = m[6];
    double m31 = m[7];

    double m02 = m[8];
    double m12 = m[9];
    double m22 = m[10];
    double m32 = m[11];

    double m03 = m[12];
    double m13 = m[13];
    double m23 = m[14];
    double m33 = m[15];

    Mat3d sub00 = Mat3d(m11, m12, m13, m21, m22, m23, m31, m32, m33);
    Mat3d sub01 = Mat3d(m12, m13, m10, m22, m23, m20, m32, m33, m30);
    Mat3d sub02 = Mat3d(m13, m10, m11, m23, m20, m21, m33, m30, m31);
    Mat3d sub03 = Mat3d(m10, m11, m12, m20, m21, m22, m30, m31, m32);

    float cofactor00 = sub00.det();
    float cofactor01 = -sub01.det();
    float cofactor02 = sub02.det();
    float cofactor03 = -sub03.det();

    return(m00 * cofactor00 + m01 * cofactor01 + m02 * cofactor02 + m03 * cofactor03);
}

Mat4d Mat4d::identity()
{
    return Mat4d(1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0);
}

Mat4d Mat4d::inverse() {
    double m00 = m[0];
    double m10 = m[1];
    double m20 = m[2];
    double m30 = m[3];

    double m01 = m[4];
    double m11 = m[5];
    double m21 = m[6];
    double m31 = m[7];

    double m02 = m[8];
    double m12 = m[9];
    double m22 = m[10];
    double m32 = m[11];

    double m03 = m[12];
    double m13 = m[13];
    double m23 = m[14];
    double m33 = m[15];

    Mat3d sub00 = Mat3d(m11, m12, m13, m21, m22, m23, m31, m32, m33);
    Mat3d sub01 = Mat3d(m12, m13, m10, m22, m23, m20, m32, m33, m30);
    Mat3d sub02 = Mat3d(m13, m10, m11, m23, m20, m21, m33, m30, m31);
    Mat3d sub03 = Mat3d(m10, m11, m12, m20, m21, m22, m30, m31, m32);

    Mat3d sub10 = Mat3d(m21, m22, m23, m31, m32, m33, m01, m02, m03);
    Mat3d sub11 = Mat3d(m22, m23, m20, m32, m33, m30, m02, m03, m00);
    Mat3d sub12 = Mat3d(m23, m20, m21, m33, m30, m31, m03, m00, m01);
    Mat3d sub13 = Mat3d(m20, m21, m22, m30, m31, m32, m00, m01, m02);

    Mat3d sub20 = Mat3d(m31, m32, m33, m01, m02, m03, m11, m12, m13);
    Mat3d sub21 = Mat3d(m32, m33, m30, m02, m03, m00, m12, m13, m10);
    Mat3d sub22 = Mat3d(m33, m30, m31, m03, m00, m01, m13, m10, m11);
    Mat3d sub23 = Mat3d(m30, m31, m32, m00, m01, m02, m10, m11, m12);

    Mat3d sub30 = Mat3d(m01, m02, m03, m11, m12, m13, m21, m22, m23);
    Mat3d sub31 = Mat3d(m02, m03, m00, m12, m13, m10, m22, m23, m20);
    Mat3d sub32 = Mat3d(m03, m00, m01, m13, m10, m11, m23, m20, m21);
    Mat3d sub33 = Mat3d(m00, m01, m02, m10, m11, m12, m20, m21, m22);

    double cofactor00 = sub00.det();
    double cofactor01 = -sub01.det();
    double cofactor02 = sub02.det();
    double cofactor03 = -sub03.det();

    double cofactor10 = -sub10.det();
    double cofactor11 = sub11.det();
    double cofactor12 = -sub12.det();
    double cofactor13 = sub13.det();

    double cofactor20 = sub20.det();
    double cofactor21 = -sub21.det();
    double cofactor22 = sub22.det();
    double cofactor23 = -sub23.det();

    double cofactor30 = -sub30.det();
    double cofactor31 = sub31.det();
    double cofactor32 = -sub32.det();
    double cofactor33 = sub33.det();

    double determinant = m00 * cofactor00 + m01 * cofactor01 + m02 * cofactor02 + m03 * cofactor03;

    if (determinant != 0.0) {
        double reciprocalDet = 1.0 / determinant;

        return Mat4d
            /*(
                 cofactor00 * reciprocalDet, cofactor10 * reciprocalDet, cofactor20 * reciprocalDet, cofactor30 * reciprocalDet,
                 cofactor01 * reciprocalDet, cofactor11 * reciprocalDet, cofactor21 * reciprocalDet, cofactor31 * reciprocalDet,
                 cofactor02 * reciprocalDet, cofactor12 * reciprocalDet, cofactor22 * reciprocalDet, cofactor32 * reciprocalDet,
                 cofactor03 * reciprocalDet, cofactor13 * reciprocalDet, cofactor23 * reciprocalDet, cofactor33 * reciprocalDet
             );*/
             (
                 cofactor00 * reciprocalDet, cofactor01 * reciprocalDet, cofactor02 * reciprocalDet, cofactor03 * reciprocalDet,
                 cofactor10 * reciprocalDet, cofactor11 * reciprocalDet, cofactor12 * reciprocalDet, cofactor13 * reciprocalDet,
                 cofactor20 * reciprocalDet, cofactor21 * reciprocalDet, cofactor22 * reciprocalDet, cofactor23 * reciprocalDet,
                 cofactor30 * reciprocalDet, cofactor31 * reciprocalDet, cofactor32 * reciprocalDet, cofactor33 * reciprocalDet
             );

    }
    else return *this;


}

Mat4d Mat4d::translation(double x, double y, double z)
{
    return Mat4d
    (
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    );
}

// static
Mat4d Mat4d::translation(const Vec3d& translation)
{
    return Mat4d
    (
        1, 0, 0, translation.x,
        0, 1, 0, translation.y,
        0, 0, 1, translation.z,
        0, 0, 0, 1
    );
}

Mat4d Mat4d::ProjectionMatrix(double r, double t, double fov, double aspectRatio, double zNear, double zFar) // modificato
{
    Mat4d projection = Mat4d();

    projection.m[0] = zNear / r;
    projection.m[5] = zNear / t;

    projection.m[14] = -1;

    projection.m[10] = -(zFar + zNear) / (zFar - zNear); // ho aggiunto - e cambiato l'ordine... in pratica ho fatto una cosa inutile


    projection.m[11] = -2.f * zFar * zNear / (zFar - zNear); // ho aggiunto -


    //std::cout << "questa è la projectionMatrix" << projection;

    return projection;
}

Mat4d Mat4d::orthographicProjection(double width, double height, double zNear, double zFar)
{
    Mat4d m;

    m.m[0] = 2.0f / width;
    m.m[5] = 2.0f / height;
    m.m[15] = 1.0f;

    m.m[3] = -1;
    m.m[7] = -1;


    m.m[10] = 2.0f / (zNear - zFar);
    m.m[11] = (zNear + zFar) / (zNear - zFar);


    return m;
}
Mat4d Mat4d::orthographic(double left, double right, double bottom, double top, double zNear, double zFar)
{
    Mat4d m;

    m.m[0] = 2.0f / (right - left);
    m.m[5] = 2.0f / (top - bottom);
    m.m[15] = 1.0f;

    m.m[3] = (left + right) / (left - right);
    m.m[7] = (top + bottom) / (bottom - top);


    m.m[10] = 2.0f / (zNear - zFar);
    m.m[11] = (zNear + zFar) / (zNear - zFar);

    return m;
}
Mat4d Mat4d::ViewMatrix(const Vec3d eye, const Vec3d lookAt, const Vec3d up)
{

    Vec3d z3f = (eye - lookAt).normalize(); //zv
    Vec3d y3f = up;
    Vec4d z = Vec4d(z3f, 0.0); // z
    //Vec4f y = Vec4f(up, 0); // y = zv x xv
    Vec3d x3f = y3f.cross(z3f); // new prova
    Vec4d x = Vec4d((y3f.cross(z3f)).normalize(), 0.0); // up x zv x
    Vec4d y = Vec4d((z3f.cross(x3f)).normalize(), 0.0); // new prova y
    Vec4d eye4f = Vec4d(eye, 1.0);


    Mat4d view = Mat4d();

    view.setCol(0, x);
    view.setCol(1, y);
    view.setCol(2, z);
    view.setCol(3, eye4f);

    Mat4d WorldToCam = view.inverse();


    //std::cout << "QUESTA E LA VIEW MATRIX: " << WorldToCam << std::endl;
    return WorldToCam;


}

// static
Mat4d Mat4d::rotateX(double radians)
{
    double a = cos(radians);
    double b = sin(radians);

    return Mat4d
    (
        1, 0, 0, 0,
        0, a, -b, 0,
        0, b, a, 0,
        0, 0, 0, 1
    );
}

// static
Mat4d Mat4d::rotateY(double radians)
{
    double a = cos(radians);
    double b = sin(radians);

    return Mat4d
    (
        a, 0, b, 0,
        0, 1, 0, 0,
        -b, 0, a, 0,
        0, 0, 0, 1
    );
}

// static
Mat4d Mat4d::rotateZ(double radAngle)
{
    double a = cos(radAngle);
    double b = sin(radAngle);

    return Mat4d
    (
        a, -b, 0, 0,
        b, a, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

//Mat4f Mat4f::rotation(const Quat& q)
//{
//    Quat qq = q.normalized();
//
//    float xx = qq.x() * qq.x();
//    float yy = qq.y() * qq.y();
//    float zz = qq.z() * qq.z();
//
//    float xy = qq.x() * qq.y();
//    float zw = qq.z() * qq.w();
//
//    float xz = qq.x() * qq.z();
//    float yw = qq.y() * qq.w();
//
//    float yz = qq.y() * qq.z();
//    float xw = qq.x() * qq.w();
//
//    return Mat4f
//    (
//        1.0f - 2.0f * (yy + zz), 2.0f * (xy - zw), 2.0f * (xz + yw), 0.0f,
//        2.0f * (xy + zw), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - xw), 0.0f,
//        2.0f * (xz - yw), 2.0f * (yz + xw), 1.0f - 2.0f * (xx + yy), 0.0f,
//        0.0f, 0.0f, 0.0f, 1.0f
//    );
//}

// static
Mat4d Mat4d::scaleMatrix(double sx, double sy, double sz)
{
    return Mat4d
    (
        sx, 0, 0, 0,
        0, sy, 0, 0,
        0, 0, sz, 0,
        0, 0, 0, 1
    );
}

Mat4d Mat4d::rotation(Vec3d& rDirection, double radians)
{
    Vec3d normalizedDirection = rDirection.normalize();

    double cosTheta = cos(radians);
    float sinTheta = sin(radians);

    double x = normalizedDirection.x;
    double y = normalizedDirection.y;
    double z = normalizedDirection.z;

    return Mat4d
    (
        x * x * (1.0f - cosTheta) + cosTheta, y * x * (1.0f - cosTheta) - z * sinTheta, z * x * (1.0f - cosTheta) + y * sinTheta, 0.0f,
        x * y * (1.0f - cosTheta) + z * sinTheta, y * y * (1.0f - cosTheta) + cosTheta, z * y * (1.0f - cosTheta) - x * sinTheta, 0.0f,
        x * z * (1.0f - cosTheta) - y * sinTheta, y * z * (1.0f - cosTheta) + x * sinTheta, z * z * (1.0f - cosTheta) + cosTheta, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}