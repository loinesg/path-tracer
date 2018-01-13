#include "Camera.hpp"

#include <assert.h>
#include <math.h>

Camera::Camera()
    : nearPlaneDistance_(0.1),
    fov_(60.0)
{
    
}

void Camera::setNearPlane(float nearPlane)
{
    nearPlaneDistance_ = nearPlane;
}

void Camera::setFov(float fov)
{
    fov_ = fov;
}

Vector3 Camera::getViewRayDir(float x, float y, float aspect) const
{
    // Calculate the view plane width and height at the near plane distance
    float halfFov = (fov_ / 2.0) * (M_PI / 180.0);
    float planeWidth = nearPlaneDistance_ * tan(halfFov) * 2.0f;
    float planeHeight = planeWidth * aspect;
    
    // Determine the centre of the view plane at the near plane distance
    Vector3 origin = position();
    Vector3 planeCentre = origin + (forward() * nearPlaneDistance_);
    
    // Offset to the correct location inside the plane
    Vector3 xOffset = right() * (x - 0.5f) * planeWidth;
    Vector3 yOffset = up() * (y - 0.5f) * planeHeight;
    
    // Offset the plane centre to get the point in the plane on the view ray
    Vector3 planeRayIntersection = planeCentre + xOffset + yOffset;
    
    // Return the position to near plane direction
    return (planeRayIntersection - origin).normalized();
}
