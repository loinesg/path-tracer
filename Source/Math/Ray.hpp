#pragma once

#include "Vector3.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"

class Ray
{
public:
    Ray(const Vector3 &origin, const Vector3 &direction);
    
    Vector3 origin() const { return origin_; }
    Vector3 direction() const { return direction_; }
    
    // Computes the intersection point between the plane and a ray, if any.
    bool intersectionWithPlane(const Plane &plane, Vector3 &intersection, float &distance) const;
    
    // Computes the intersection between the ray and a triangle.
    // Returns the distance from the ray origin to the intersection.
    // Also outputs the triangle barycentric coords.
    bool intersectionWithTriangle(const Triangle &triangle, float &alpha, float &beta, float &gamma, float &distance) const;
    
    // Computes the intersection between the ray and a sphere.
    // Outputs the distance from the intersection.
    bool intersectionWithSphere(const Sphere &sphere, float &distance) const;

private:
    Vector3 origin_;
    Vector3 direction_;
};
 
