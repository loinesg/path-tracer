#pragma once

#include "Object.hpp"
#include "Ray.hpp"

class Camera : public Object
{
public:
    Camera();
    
    // Camera configuration
    float nearPlane() const { return nearPlaneDistance_; }
    float fov() const { return fov_; }
    
    // Set camera configuration
    void setNearPlane(float nearPlane);
    void setFov(float fov);
    
    // Gets the direction of a ray from the camera and through the view plane,
    // for a normalized [0-1] x/y position on the view plane.
    Vector3 getViewRayDir(float x, float y, float aspect) const;
    
private:
    // Ray directions for the 4 corners of the view frustum
    Vector3 frustumCorners_;
    
    // Distance to the near clipping planes
    float nearPlaneDistance_;
    
    // Vertical fov
    float fov_;
};
