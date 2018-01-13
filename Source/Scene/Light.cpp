#include "Light.hpp"

Light::Light(LightType type, const Color &color, float radius)
    : type_(type),
    color_(color),
    radius_(radius)
{
    
}

void Light::setType(LightType type)
{
    type_ = type;
}

void Light::setColor(Color color)
{
    color_ = color;
}

void Light::setRadius(float radius)
{
    radius_ = radius;
}
