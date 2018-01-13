#include "Sphere.hpp"

Sphere::Sphere(const Color &color, const Vector3 &centre, float radius, float reflectivity)
	: color_(color),
	centre_(centre),
	radius_(radius)
{
    color_ = color_ * (1.0f - reflectivity);
	reflectivity_ = reflectivity;
}
