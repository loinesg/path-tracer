#pragma once

#include "Vector3.hpp"
#include "Color.hpp"

struct Triangle
{
    Vector3 vertices[3];
    Vector3 normal;
    Color color;
    Color emission;
    float reflectivity;
    
    Triangle(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Color &color);
    Triangle(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Color &color, const Color &emission);
};
