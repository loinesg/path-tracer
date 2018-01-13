#pragma once

#include "Vector3.hpp"
#include "Color.hpp"

struct SurfaceHit
{
    float distance;
    Vector3 position;
    Vector3 normal;
    Color color;
    Color emission;
    float reflectivity;
};
