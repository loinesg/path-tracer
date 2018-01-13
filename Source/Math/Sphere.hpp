#pragma once

#include "Color.hpp"
#include "Vector3.hpp"

class Sphere
{
public:
    Sphere(const Color &color, const Vector3 &centre, float radius, float reflectivity = 0.7f);

    const Color& color() const { return color_; }
    const Vector3& centre() const { return centre_; }
    float radius() const { return radius_; }
    float reflectivity() const { return reflectivity_; }

private:
    Color color_;
    Vector3 centre_;
    float radius_;
    float reflectivity_;
};
