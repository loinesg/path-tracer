#include "RendererStats.hpp"

RendererStats::RendererStats()
    : timer_(),
    width_(1),
    height_(1),
    samplesCount_(0)
{

}

double RendererStats::currentRenderTime() const
{
    return timer_.elapsed() / 1000.0;
}

uint64_t RendererStats::sampleCount() const
{
    return samplesCount_;
}

uint64_t RendererStats::averageSamplesPerPixel() const
{
    return samplesCount_ / (width_ * height_);
}

uint64_t RendererStats::averageSamplesPerSecond() const
{
    return samplesCount_ / currentRenderTime();
}

void RendererStats::renderStarted(int width, int height)
{
    width_ = width;
    height_ = height;

    // Reset the sample count
    samplesCount_ = 0;

    // Reset the timer
    timer_.restart();
}

void RendererStats::addSample()
{
    // Atomic
    samplesCount_ ++;
}
