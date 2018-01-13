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
};

Color operator * (const Color &color, float scalar);
Color operator * (float scalar, const Color &color);
Color operator * (const Color &a, const Color &b);
Color operator + (const Color &color, float scalar);

ostream& operator<< (ostream &os, const Color &color);
istream& operator>> (istream &is, Color &color);
