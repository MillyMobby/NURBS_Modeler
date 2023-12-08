#include "Mat3d.h"
#include "Vec3d.h"

using namespace std;


Mat3d::Mat3d() {
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
Mat3d::Mat3d(vtype m0, vtype m1, vtype m2, vtype m3, vtype m4, vtype m5, vtype m6, vtype m7, vtype m8) {

    m.push_back(m0);
    m.push_back(m1);
    m.push_back(m2);
    m.push_back(m3);
    m.push_back(m4);
    m.push_back(m5);
    m.push_back(m6);
    m.push_back(m7);
    m.push_back(m8);
}

Mat3d::~Mat3d() {}

float Mat3d::operator() (const int i, const int j)
{
    return m[i * 3 + j];
}

Mat3d Mat3d::operator+(const Mat3d& other)
{
    return Mat3d(m[0] + other.m[0], m[1] + other.m[1], m[2] + other.m[2],
        m[3] + other.m[3], m[4] + other.m[4], m[5] + other.m[5],
        m[6] + other.m[6], m[7] + other.m[7], m[8] + other.m[8]);
}

/*Mat3f Mat3f::operator+(const Mat3f& other, const vtype& scalare)
{
    return Mat3f(other.m[0] + scalare, other.m[1] + scalare, other.m[2] + scalare,
        other.m[3] + scalare, other.m[4] + scalare, other.m[5] + scalare,
        other.m[6] + scalare, other.m[7] + scalare, other.m[8] + scalare);
}*/

Mat3d Mat3d::operator-(const Mat3d& other)
{
    return Mat3d(m[0] - other.m[0], m[1] - other.m[1], m[2] - other.m[2],
        m[3] - other.m[3], m[4] - other.m[4], m[5] - other.m[5],
        m[6] - other.m[6], m[7] - other.m[7], m[8] - other.m[8]);
}

bool Mat3d::operator == (const Mat3d& other) const {
    return (m[0] == other.m[0] && m[1] == other.m[1] && m[2] == other.m[2]
        && m[3] == other.m[3] && m[4] == other.m[4] && m[5] == other.m[5]
        && m[6] == other.m[6] && m[7] == other.m[7] && m[8] == other.m[8]);
}

bool Mat3d::operator != (const Mat3d& other) const {
    return (m[0] != other.m[0] && m[1] != other.m[1] && m[2] != other.m[2]
        && m[3] != other.m[3] && m[4] != other.m[4] && m[5] != other.m[5]
        && m[6] != other.m[6] && m[7] != other.m[7] && m[8] != other.m[8]);
}

Mat3d Mat3d::operator*(Mat3d& other) {

    return Mat3d(m.at(0) * other.m.at(0) + m.at(1) * other.m.at(3) + m.at(2) * other.m.at(6),
        m.at(0) * other.m.at(1) + m.at(1) * other.m.at(4) + m.at(2) * other.m.at(7),
        m.at(0) * other.m.at(2) + m.at(1) * other.m.at(5) + m.at(2) * other.m.at(8),

        m.at(3) * other.m.at(0) + m.at(4) * other.m.at(3) + m.at(5) * other.m.at(6),
        m.at(3) * other.m.at(1) + m.at(4) * other.m.at(4) + m.at(5) * other.m.at(7),
        m.at(3) * other.m.at(2) + m.at(4) * other.m.at(5) + m.at(5) * other.m.at(8),

        m.at(6) * other.m.at(0) + m.at(7) * other.m.at(3) + m.at(8) * other.m.at(6),
        m.at(6) * other.m.at(1) + m.at(7) * other.m.at(4) + m.at(8) * other.m.at(7),
        m.at(6) * other.m.at(2) + m.at(7) * other.m.at(5) + m.at(8) * other.m.at(8));
}

Mat3d Mat3d::operator*(const vtype& other) {
    return Mat3d(m[0] * other, m[1] * other, m[2] * other, m[3] * other, m[4] * other, m[5] * other, m[6] * other, m[7] * other, m[8] * other);
}

std::ostream& operator<<(std::ostream& output, const Mat3d& a)
{
    output << endl
        << a.m[0] << " " << a.m[1] << " " << a.m[2] << " " << endl
        << a.m[3] << " " << a.m[4] << " " << a.m[5] << " " << endl
        << a.m[6] << " " << a.m[7] << " " << a.m[8] << " " << endl;
    return output;
}

double Mat3d::det() const
{
    return (m[0] * (m[4] * m[8] - m[5] * m[7]) - m[1] * (m[3] * m[8] - m[6] * m[5]) + m[2] * (m[3] * m[7] - m[4] * m[6]));
}

Mat3d Mat3d::trasposta() {
    return Mat3d(m[0], m[3], m[6], m[1], m[4], m[7], m[2], m[5], m[8]);
}

void Mat3d::transpose()
{
    vtype m1 = m[1];
    vtype m2 = m[2];
    vtype m5 = m[5];
    m[0] = m[0];
    m[1] = m[3];
    m[2] = m[6];
    m[3] = m1;
    m[4] = m[4];
    m[5] = m[7];
    m[6] = m2;
    m[7] = m5;
    m[8] = m[8];
    // return *this;
}

bool Mat3d::invertibile() {
    if (det() != 0.0f) { return true; }
    else { return false; }
}


Mat3d Mat3d::cofattori() {

    return Mat3d(m[4] * m[8] - m[5] * m[7], -(m[3] * m[8] - m[5] * m[6]), m[3] * m[7] - m[4] * m[6],
        -(m[1] * m[8] - m[2] * m[7]), m[0] * m[8] - m[2] * m[6], -(m[0] * m[7] - m[1] * m[6]),
        m[1] * m[5] - m[2] * m[4], -(m[0] * m[5] - m[2] * m[3]), m[0] * m[4] - m[1] * m[3]);
}

Mat3d Mat3d::inversa() {
    if (det() != 0.0f)
    {
        vtype m0 = m[0];
        vtype m1 = m[1];
        vtype m2 = m[2];
        vtype m3 = m[3];
        vtype m4 = m[4];
        vtype m5 = m[5];
        vtype m6 = m[6];
        vtype m7 = m[7];
        vtype m8 = m[8];
        vtype detInv = 1.0f / det();
        double m11 = detInv * (m4 * m8 - m5 * m7);
        double m12 = -detInv * (m1 * m8 - m7 * m2);
        double m13 = detInv * (m5 * m1 - m4 * m2);
        double m21 = -detInv * (m3 * m8 - m5 * m6);
        double m22 = detInv * (m0 * m8 - m6 * m2);
        double m23 = -detInv * (m0 * m5 - m3 * m2);
        double m31 = detInv * (m7 * m3 - m4 * m6);
        double m32 = -detInv * (m0 * m7 - m1 * m6);
        double m33 = detInv * (m0 * m4 - m1 * m3);
        return Mat3d(m11, m12, m13, m21, m22, m23, m31, m32, m33);

    }
    else return Mat3d();
}

Mat3d Mat3d::rotateX(double radians)
{
    double c = cos(radians);
    double s = sin(radians);

    return Mat3d
    (
        1, 0, 0,
        0, c, -s,
        0, s, c
    );
}

// static
Mat3d Mat3d::rotateY(double radians)
{
    double c = cos(radians);
    double s = sin(radians);

    return Mat3d
    (
        c, 0, s,
        0, 1, 0,
        -s, 0, c
    );
}

// static
Mat3d Mat3d::rotateZ(double radians)
{
    double c = cos(radians);
    double s = sin(radians);

    return Mat3d
    (
        c, -s, 0,
        s, c, 0,
        0, 0, 1
    );
}

Vec3d operator * (const Mat3d& mat, const Vec3d& v)
{
    double x, y, z;
    x = mat.m[0] * v.x + mat.m[1] * v.y + mat.m[2] * v.z;
    y = mat.m[3] * v.x + mat.m[4] * v.y + mat.m[5] * v.z;
    z = mat.m[6] * v.x + mat.m[7] * v.y + mat.m[8] * v.z;
    Vec3d output(x, y, z);

    return output;
}

Mat3d Mat3d::rotation(Vec3d& rDirection, double radians)
{
    Vec3d normalizedDirection = rDirection.normalize();

    double cosTheta = cos(radians);
    double sinTheta = sin(radians);

    double x = normalizedDirection.x;
    double y = normalizedDirection.y;
    double z = normalizedDirection.z;

    return Mat3d
    (
        x * x * (1.0f - cosTheta) + cosTheta, y * x * (1.0f - cosTheta) - z * sinTheta, z * x * (1.0f - cosTheta) + y * sinTheta,
        x * y * (1.0f - cosTheta) + z * sinTheta, y * y * (1.0f - cosTheta) + cosTheta, z * y * (1.0f - cosTheta) - x * sinTheta,
        x * z * (1.0f - cosTheta) - y * sinTheta, y * z * (1.0f - cosTheta) + x * sinTheta, z * z * (1.0f - cosTheta) + cosTheta
    );
}

Mat3d Mat3d::scaleMatrix(double sx, double sy, double sz) {
    return Mat3d
    (
        sx, 0, 0,
        0, sy, 0,
        0, 0, sz
    );
}

