#pragma once

#include <QElapsedTimer>
#include <atomic>

class RendererStats
{
public:
    RendererStats();
    
    // Gets the amount of time the render has been running for.
    double currentRenderTime() const;

    // Gets the total number of processed samples.
    uint64_t sampleCount() const;

    // Gets the average samples per pixel
    uint64_t averageSamplesPerPixel() const;
    
    // Gets the average samples performed per second.
    uint64_t averageSamplesPerSecond() const;

    // Restarts the stats for a new render.
    void renderStarted(int width, int height);

    // Adds a new sample to the count
    void addSample();
    
private:
    
    // The timer used for measuring rendering times
    QElapsedTimer timer_;
    
    // The resolution of the image
    int width_;
    int height_;

    // The number of finished samples.
    std::atomic<std::uint64_t> samplesCount_;
};
