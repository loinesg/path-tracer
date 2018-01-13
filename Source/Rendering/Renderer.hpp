#pragma once

#include <QGLWidget>
#include <QImage>
#include <cstdint>
#include <math.h>
#include <vector>
#include <thread>

#include "Bitmap.hpp"
#include "Color.hpp"
#include "RendererSettings.hpp"
#include "RendererStats.hpp"
#include "Scene.hpp"
#include "SurfaceHit.hpp"

class Renderer
{
public:
    Renderer(const Scene* scene);
    
    // Rendering info
    const RendererStats* stats() const { return &stats_; }
    
    bool running() const { return rendering_; }
    bool componentEnabled(RenderComponent component) const;
    
    // Changes shadow rendering settings.
    void setOverlay(RenderOverlay overlay);
    void toggleComponent(RenderComponent component);
    
    // Starts and stops rendering.
    // Rendering occurs on a background thread.
    void startRender(Bitmap* bitmap);
    void stopRender();
    
private:
    const Scene* scene_;
    
    // Logs rendering stats for display in the UI
    RendererStats stats_;
    
    // Which rendering components are currently enabled.
    RenderComponentList renderComponents_;
    
    // Which rendering overlay is currently being used.
    RenderOverlay renderOverlay_;
    
    // True if a render pass is in progress.
    bool rendering_;
    
    // The worker threads
    std::vector<std::thread> renderThreads_;
    
    // QGLWidget override methods
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    
    void renderWorker(Bitmap* bitmap);
    
    // Computes the radiance for a path traced ray.
    Color pathTrace(const Ray &viewRay, int bounce = 0) const;
    
    // Computes the radiance at a given point from scene area lights
    Color sampleDirectAreaLights(const Ray &viewRay, const SurfaceHit &hit) const;
    
    // Computes the impulse radiance at a given point
    Color sampleImpulseLight(const Ray &viewRay, const SurfaceHit &hit, int bounce) const;
    
    // Computes the indirect radiance at a given point
    Color sampleIndirectLight(const SurfaceHit &hit, int bounce) const;
    
    // Finds the object that a ray hits, if any.
    SurfaceHit testRay(const Ray &ray) const;
    
    // Checks for a line of sight between two points.
    // Returns true if unobstructed.
    bool checkVisibility(const Vector3 &a, const Vector3 &b) const;
    
    // Computes blinnphong radiance for a surface hit.
    Color blinnPhong(const SurfaceHit &surface, const Vector3 &toEye, const Vector3 &toLight) const;
};
