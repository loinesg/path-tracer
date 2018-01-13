#include "Quaternion.hpp"

#include <math.h>

Quaternion::Quaternion()
    : v(Vector3(0.0, 0.0, 0.0)), w(1.0)
{

}

Quaternion::Quaternion(const Vector3 &v, float w)
    : v(v), w(w)
{

}

Quaternion::Quaternion(float x, float y, float z, float w)
    : v(Vector3(x, y, z)), w(w)
{

}

Quaternion Quaternion::identity()
{
    return Quaternion(0.0, 0.0, 0.0, 1);
}

float Quaternion::sqrNorm() const
{
    // All quaternions in the application are unit length
    return 1.0f;
    
    // return Vector3::dot(v, v) + (w * w);
}

float Quaternion::norm() const
{
    // All quaternions in the application are unit length
    return 1.0f;
    
    // return sqrt(sqrNorm());
}

Quaternion Quaternion::conjugate() const
{
    return Quaternion(-1.0 * v, w);
}

Quaternion Quaternion::inverse() const
{
    // All quaternions in the application are unit length
    return conjugate();
    
    // return (1.0 / sqrNorm()) * conjugate();
}

Quaternion Quaternion::rotation(float angle, const Vector3 &axis)
{
    float phi = (angle / 2.0) * (M_PI / 180.0);
    float sinPhi = sin(phi);
    float cosPhi = cos(phi);

    return Quaternion(sinPhi * axis, cosPhi);
}

Quaternion Quaternion::euler(float x, float y, float z)
{
    Quaternion zRotation = Quaternion::rotation(z, Vector3(0.0, 0.0, 1.0));
    Quaternion xRotation = Quaternion::rotation(x, Vector3(1.0, 0.0, 0.0));
    Quaternion yRotation = Quaternion::rotation(y, Vector3(0.0, 1.0, 0.0));

    // Rotate z, then x then y.
    return yRotation * xRotation * zRotation;
}

Quaternion Quaternion::euler(Vector3 &euler)
{
    return Quaternion::euler(euler.x, euler.y, euler.z);
}

Vector3 operator * (const Quaternion &q, const Vector3 &vec)
{
    Quaternion vecAsQuat(vec.x, vec.y, vec.z, 0.0f);
    Quaternion vecRotated = (q * vecAsQuat * q.inverse());
    
    return Vector3(vecRotated.v.x, vecRotated.v.y, vecRotated.v.z);
}

Quaternion operator * (const Quaternion &q, float scalar)
{
    return Quaternion(scalar * q.v, scalar * q.w);
}

Quaternion operator * (float scalar, const Quaternion &q)
{
    return q * scalar;
}

Quaternion operator * (const Quaternion &a, const Quaternion &b)
{
    return Quaternion(
        Vector3::cross(a.v, b.v) + (b.w * a.v) + (a.w * b.v),
        (a.w * b.w) - Vector3::dot(a.v, b.v)
    );
}

Quaternion operator + (const Quaternion &a, const Quaternion &b)
{
    return Quaternion(a.v + b.v, a.w + b.w);
}

ostream& operator << (ostream &os, Quaternion &quat)
{
    os << "( " << quat.v.x << ", " << quat.v.y << ", " << quat.v.z << ", " << quat.w << " )";
    return os;
}

istream& operator >> (istream &is, Quaternion &quat)
{
    is >> quat.v;
    is >> quat.w;
    return is;
}
