#pragma once

#include "Vector3.hpp"

class Plane
{
public:
    Plane();
    Plane(const Vector3 &normal, const Vector3 &origin);
    
    // Gets the normal and point that represent the plane
    Vector3 normal() const { return normal_; }
    Vector3 origin() const { return origin_; }
    
    // Constructs a plane from two vectors and a point within it.
    static Plane fromTwoVectorsAndPoint(const Vector3 &vec1, const Vector3 &vec2, const Vector3 &point);
    
    // Constructs a plane from three points within it.
    static Plane fromThreePoints(const Vector3 &a, const Vector3 &b, const Vector3 &c);
    
private:
    Vector3 normal_;
    Vector3 origin_;
};
