#include "Ray.hpp"

#include <math.h>

Ray::Ray(const Vector3 &origin, const Vector3 &direction)
    : origin_(origin), direction_(direction.normalized())
{
    
}

bool Ray::intersectionWithPlane(const Plane &plane, Vector3 &intersection, float &distance) const
{
    // Get a vector from the ray origin to the plane
    Vector3 rayToPlane = plane.origin() - origin_;
    
    // Use this to find the distance we need to move along the ray direction.
    float t = Vector3::dot(rayToPlane, plane.normal()) / Vector3::dot(direction_, plane.normal());
    
    // Check if there is no intersection.
    // This happens when the ray and plane are parallel, or the ray is
    // travelling away from the plane.
    if(t < 0.0f || t > 10000000.0f)
    {
        return false;
    }
    
    // Otherwise, return the correct point on the ray.
    intersection = origin_ + t * direction_;
    distance = t;
    return true;
}

bool Ray::intersectionWithTriangle(const Triangle &triangle, float &alpha, float &beta, float &gamma, float &distance) const
{
    // Adapted from "Computer Graphics: Principles and Practise"
    // page 410
    Vector3 e1 = triangle.vertices[1] - triangle.vertices[0];
    Vector3 e2 = triangle.vertices[2] - triangle.vertices[0];
    Vector3 q = Vector3::cross(direction_, e2);
    float a = Vector3::dot(e1, q);
    Vector3 s = origin_ - triangle.vertices[0];
    Vector3 r = Vector3::cross(s, e1);
    
    // Compute barycentric coordinates
    beta = Vector3::dot(s, q) / a;
    gamma = Vector3::dot(direction_, r) / a;
    alpha = 1.0f - (beta + gamma);
    
    // Compute the distance to the triangle from the ray origin
    distance = Vector3::dot(e2, r) / a;
    
    // Check if the ray enters the triangle
    if(a < 0.000001f || alpha < 0.0f || beta < 0.0f || gamma < 0.0f || distance < 0.000001f)
    {
        // Ray did not enter the triangle
        return false;
    }
    else
    {
        // Ray did enter the triangle.
        return true;
    }
}

bool Ray::intersectionWithSphere(const Sphere &sphere, float &distance) const
{
    // Adapted from lecture 16 slide 20 + 21
    const Vector3 v = direction_;
    const Vector3 u = origin_ - sphere.centre();
    const float A = Vector3::dot(direction_, direction_);
    const float B = 2.0f * Vector3::dot(u, v);
    const float C = Vector3::dot(u, u) - sphere.radius() * sphere.radius();

    const float t1 = (-B + sqrtf(B*B - 4.0f*A*C)) / (2.0f * A);
    const float t2 = (-B - sqrtf(B*B - 4.0f*A*C)) / (2.0f * A); 

    // If both values are negative or infinity, there is no intersection.
    if((t1 < 0.0f || t1 > 1000000.0f) && (t2 < 0.0f || t2 > 1000000.0f))
    {
        return false;
    }

    // Otherwise use the smallest positive value
    if(t1 < 0.0f) distance = t2;
    if(t2 < 0.0f) distance = t1;
    distance = (t1 < t2) ? t1 : t2;
    return true;
}
