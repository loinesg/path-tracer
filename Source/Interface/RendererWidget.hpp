#pragma once

#include <QGLWidget>
#include <QImage>
#include <cstdint>
#include <math.h>

#include "Bitmap.hpp"
#include "Color.hpp"
#include "RendererSettings.hpp"
#include "RendererStats.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"

class RendererWidget : public QGLWidget
{
public:
    RendererWidget();
    
    Scene* scene() { return &scene_; }
    
    // Rendering info
    const RendererStats* stats() const { return renderer_.stats(); }
    
    // Current render settings
    int resolutionX() const { return targetBitmap_.width(); }
    int resolutionY() const { return targetBitmap_.height(); }
    RenderResolution resolutionScale () const { return resolutionScale_; }
    
    // Main scene camera
    Camera* camera() { return scene_.mainCamera(); }
    
    // Changes rendering settings.
    void setResolutionScale(RenderResolution scale);
    void toggleRenderComponent(RenderComponent component);
    void setOverlay(RenderOverlay overlay);
    
    // (Re)starts the rendering process.
    // This should be called whenever the scene / camera is changed.
    void restartRendering();
    
private:
    // The scene that is being rendered.
    // It contains a list of coloured triangles.
    Scene scene_;
    
    // The renderer being used
    Renderer renderer_;
    
    // The image being rendered to
    Bitmap targetBitmap_;
    GLuint targetGPUTexture_;
    
    // Render settings
    int unscaledResolutionX_;
    int unscaledResolutionY_;
    RenderResolution resolutionScale_;
    
    // QGLWidget override methods
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};
