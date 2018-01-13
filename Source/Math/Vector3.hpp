#pragma once

#include <iostream>

using namespace std;

struct Vector3
{
    float x;
    float y;
    float z;

    Vector3();
    Vector3(float x, float y, float z);
    
    static Vector3 zero();
    static Vector3 one();
    static Vector3 up();
    static Vector3 down();
    static Vector3 forwards();

    float maxComponent() const;
    float sqrMagnitude() const;
    float magnitude() const;

    Vector3 normalized() const;

    static float dot(const Vector3 &a, const Vector3 &b);
    static Vector3 cross(const Vector3 &a, const Vector3 &b);
    static Vector3 lerp(const Vector3 &a, const Vector3 &b, float t);
};

Vector3 operator / (const Vector3 &v, float scalar);
Vector3 operator / (float scalar, const Vector3 &v);
Vector3 operator * (const Vector3 &v, float scalar);
Vector3 operator * (float scalar, const Vector3 &v);
Vector3 operator + (const Vector3 &v, float scalar);
Vector3 operator + (float scalar, const Vector3 &v);
Vector3 operator - (const Vector3 &v, float scalar);
Vector3 operator - (float scalar, const Vector3 &v);
Vector3 operator + (const Vector3 &a, const Vector3 &b);
Vector3 operator - (const Vector3 &a, const Vector3 &b);

ostream& operator << (ostream &os, Vector3 &vec);
istream& operator >> (istream &is, Vector3 &vec);
