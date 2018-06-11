#include "Color.hpp"

#include <string>
#include <math.h>

Color::Color()
: r(0), g(0), b(0)
{
    
}

Color::Color(float r, float g, float b)
: r(r), g(g), b(b)
{
    
}

Color::Color(const Vector3 &v)
    : r(v.x), g(v.y), b(v.z)
{
    
}

Color Color::black()
{
    return Color(0.0f, 0.0f, 0.0f);
}

Color Color::white()
{
    return Color(1.0f, 1.0f, 1.0f);
}

Color Color::grey()
{
    return Color(0.7f, 0.7f, 0.7f);
}

Color Color::red()
{
    return Color(1.0f, 0.0f, 0.0f);
}

Color Color::green()
{
    return Color(0.0f, 1.0f, 0.0f);
}

Color Color::blue()
{
    return Color(0.0f, 0.0f, 1.0f);
}

Color& Color::operator+=(const Color &other)
{
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
}

Color Color::operator/ (float scalar) const
{
    return Color(r / scalar, g / scalar, b / scalar);
}

Color Color::operator+ (Color c) const
{
    return Color(r + c.r, g + c.g, b + c.b);
}

Color Color::operator- (Color c) const
{
    return Color(r - c.r, g - c.g, b - c.b);
}

float Color::gammaToLinear(float srgb)
{
    return srgb < 0.04045f ? srgb / 12.92f : powf((srgb + 0.055f) / 1.055f, 2.4f);
}

float Color::linearToGamma(float linear)
{
    return linear < 0.0031308f ? linear * 12.92f : 1.055f * powf(linear, 1.0f / 2.4f) - 0.055f;
}

Color Color::gammaToLinear(float r, float g, float b)
{
    return gammaToLinear(Color(r, g, b));
}

Color Color::gammaToLinear(const Color& color)
{
    Color c;
    c.r = gammaToLinear(color.r);
    c.g = gammaToLinear(color.g);
    c.b = gammaToLinear(color.b);
    return c;
}

Color Color::linearToGamma(float r, float g, float b)
{
    return linearToGamma(Color(r, g, b));
}

Color Color::linearToGamma(const Color& color)
{
    Color c;
    c.r = linearToGamma(color.r);
    c.g = linearToGamma(color.g);
    c.b = linearToGamma(color.b);
    return c;
}

Color Color::lerp(const Color &a, const Color &b, float t)
{
    return a * (1.0f - t) + b * t;
}

Color operator * (const Color &color, float scalar)
{
    return Color(color.r * scalar, color.g * scalar, color.b * scalar);
}

Color operator * (float scalar, const Color &color)
{
    return color * scalar;
}

Color operator * (const Color &a, const Color &b)
{
    return Color(a.r * b.r, a.g * b.g, a.b * b.b);
}

Color operator + (const Color &color, float scalar)
{
    return Color(color.r + scalar, color.g + scalar, color.b + scalar);
}

ostream& operator<< (ostream &os, const Color &color)
{
    os << std::to_string(color.r)
    << " "
    << std::to_string(color.g)
    << " "
    << std::to_string(color.b);
    
    return os;
}

istream& operator>> (istream &is, Color &color)
{
    is >> color.r;
    is >> color.g;
    is >> color.b;
    return is;
}
