#include "Bitmap.hpp"

Bitmap::Bitmap()
    : width_(0),
    height_(0),
    pixels_(nullptr),
    pixelsSRGB_(nullptr),
    sampleSums_(nullptr),
    sampleCounts_(nullptr)
{
    
}

Bitmap::~Bitmap()
{
    delete[] pixels_;
    delete[] pixelsSRGB_;
    delete[] sampleSums_;
    delete[] sampleCounts_;
}

const Color* Bitmap::srgbConvert() const
{
    // Update the srgb color buffer
    for(int i = 0; i < width_ * height_; ++i)
    {
        pixelsSRGB_[i] = Color::linearToGamma(pixels_[i]);
    }
    
    // Return the srgb version
    return pixelsSRGB_;
}

void Bitmap::resize(int width, int height)
{
    // Delete any existing buffers
    if(pixels_ != nullptr)
    {
        delete[] pixels_;
        delete[] pixelsSRGB_;
        delete[] sampleSums_;
        delete[] sampleCounts_;
    }
    
    // Allocate new buffers of the correct size.
    pixels_ = new Color[width * height];
    pixelsSRGB_ = new Color[width * height];
    sampleSums_ = new Color[width * height];
    sampleCounts_ = new int[width * height];
    
    // Store the resolution
    width_ = width;
    height_ = height;
}

void Bitmap::clear()
{
    // Set every pixel to black and every count to 0.
    for(int i = 0; i < width_ * height_; ++i)
    {
        sampleSums_[i].r = 0.0f;
        sampleSums_[i].g = 0.0f;
        sampleSums_[i].b = 0.0f;
        sampleCounts_[i] = 0;
    }
}

void Bitmap::addSample(int x, int y, const Color &color)
{
    const int i = y * width_ + x;
    
    // Add to the sample list
    sampleSums_[i] += color;
    sampleCounts_[i] += 1;
    
    // Update the pixel value to be an average of all the values
    pixels_[i] = sampleSums_[i] / (float)sampleCounts_[i];
}
