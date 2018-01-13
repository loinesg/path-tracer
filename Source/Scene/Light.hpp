#pragma once

#include "Color.hpp"
#include "Object.hpp"

enum class LightType
{
    Directional,
    Point,
};

class Light : public Object
{
public:
    Light(LightType type, const Color &color, float radius);
    
    LightType type() const { return type_; }
    Color color() const { return color_; }
    float radius() const { return radius_; }
    
    void setType(LightType type);
    void setColor(Color color);
    void setRadius(float radius);
    
private:
    LightType type_;
    Color color_;
    float radius_;
};
