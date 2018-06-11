#pragma once

#include <iostream>
#include <cstdint>

#include "Vector3.hpp"

using namespace std;

struct Color
{
    float r;
    float g;
    float b;
    
    Color();
    Color(float r, float g, float b);
    Color(const Vector3 &v);
    
    static Color black();
    static Color white();
    static Color grey();
    static Color red();
    static Color green();
    static Color blue();
    
    Color& operator+=(const Color &other);
    
    Color operator/ (float scalar) const;
    Color operator+ (Color c) const;
    Color operator- (Color c) const;
    
    // Converts a single scalar value from srgb to linear
    static float gammaToLinear(float srgb);
    static float linearToGamma(float linear);
    
    // Converts a color from gamma to linear space
    // The alpha (if provided) is unchanged, and 1 if not provided
    static Color gammaToLinear(float r, float g, float b);
    static Color gammaToLinear(const Color& color);
    
    // Converts a color from linear to gamma space
    // The alpha unchanged if provided, and 1 if not provided
    static Color linearToGamma(float r, float g, float b);
    static Color linearToGamma(const Color& color);
    
    // Performs linear interpolation from a to b
    static Color lerp(const Color &a, const Color &b, float t);
};

Color operator * (const Color &color, float scalar);
Color operator * (float scalar, const Color &color);
Color operator * (const Color &a, const Color &b);
Color operator + (const Color &color, float scalar);

ostream& operator<< (ostream &os, const Color &color);
istream& operator>> (istream &is, Color &color);
