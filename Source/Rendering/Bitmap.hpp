#pragma once

#include "Color.hpp"

class Bitmap
{
public:
    Bitmap();
    ~Bitmap();
    
    // Prevent bitmaps from being copied
    Bitmap(const Bitmap&) = delete;
    Bitmap& operator=(const Bitmap&) = delete;
    
    int width() const { return width_; }
    int height() const { return height_; }
    const Color* buffer() { return pixels_; }
    
    // Returns a version of the bitmap encoded as srgb values
    const Color* srgbConvert() const;
    
    // Resizes and clears the image
    void resize(int width, int height);
    
    // Removes all samples and sets every pixel to black.
    void clear();
    
    // Adds an additional sample to the specified location
    void addSample(int x, int y, const Color &color);
    
private:
    int width_;
    int height_;
    Color* pixels_;
    Color* pixelsSRGB_;
    Color* sampleSums_;
    int* sampleCounts_;
};
