#pragma once

#include "Vector3.hpp"
#include "Color.hpp"

// A square, axis-aligned area light
class AreaLight
{
public:
    AreaLight(const Vector3 &min, const Vector3 &max, const Color &emission);
    
    // The emission of the light
    Color emission() const { return emission_; }
    
    // The geometric normal of the area light
    Vector3 normal() const { return normal_; }

    // Gets a random point on the surface of the light
    Vector3 getPoint() const;
    
private:
    Vector3 min_;
    Vector3 size_;
    Vector3 normal_;
    Color emission_;
};
