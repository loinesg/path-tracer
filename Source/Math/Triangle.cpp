#include "Triangle.hpp"

Triangle::Triangle(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Color &color)
    : Triangle(v1, v2, v3, color, Color::black())
{
    
}

Triangle::Triangle(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Color &color, const Color &emission)
{
    vertices[0] = v1;
    vertices[1] = v2;
    vertices[2] = v3;
    
    // Get two vectors in the triangle and use them to
    // compute the triangle's normal.
    const Vector3 vec1 = (v2 - v1).normalized();
    const Vector3 vec2 = (v3 - v1).normalized();
    normal = Vector3::cross(vec1, vec2).normalized();
    
    // Store the triangle color and emission
    this->color = color;
    this->emission = emission;
    this->reflectivity = 0.15f;
}
