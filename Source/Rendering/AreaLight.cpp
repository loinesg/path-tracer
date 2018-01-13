#include "AreaLight.hpp"

AreaLight::AreaLight(const Vector3 &min, const Vector3 &max, const Color &emission)
    : min_(min), size_(max - min), emission_(emission)
{
    // Get two vectors within the area light
    const Vector3 v1 = (max - min).normalized();
    const Vector3 v2 = (Vector3(min.x, min.y, max.z) - min).normalized();

    // Use the vectors to get the normal
    normal_ = Vector3::cross(v1, v2).normalized();
}

Vector3 AreaLight::getPoint() const
{
    // Compute random offsets in all 3 directions
    const float xOffset = (rand() / (float)RAND_MAX) * size_.x;
    const float yOffset = (rand() / (float)RAND_MAX) * size_.y;
    const float zOffset = (rand() / (float)RAND_MAX) * size_.z;
    
    // Return the point at the specified offset
    return min_ + Vector3(xOffset, yOffset, zOffset);
}
