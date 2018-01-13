#include "Plane.hpp"

Plane::Plane()
    : normal_(Vector3::zero()),
    origin_(Vector3::zero())
{
    
}

Plane::Plane(const Vector3 &normal, const Vector3 &origin)
    : normal_(normal),
    origin_(origin)
{
    
}

Plane Plane::fromTwoVectorsAndPoint(const Vector3 &vec1, const Vector3 &vec2, const Vector3 &point)
{
    // Get the normal of the plane from the vectors
    Vector3 normal = Vector3::cross(vec1, vec2).normalized();
    
    // Create a plane from the normal and the point.
    return Plane(normal, point);
}

Plane Plane::fromThreePoints(const Vector3 &a, const Vector3 &b, const Vector3 &c)
{
    // Get two vectors within the plane
    Vector3 vec1 = b - a;
    Vector3 vec2 = c - a;
    
    // Construct a plane from 2 vectors and a point
    return fromTwoVectorsAndPoint(vec1, vec2, a);
}
