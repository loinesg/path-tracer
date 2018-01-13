#include "RendererWidget.hpp"

RendererWidget::RendererWidget()
    : QGLWidget(),
    scene_(),
    renderer_(&scene_),
    targetBitmap_()
{
    // Start with 1/8 downsampling by default
    resolutionScale_ = RS_EighthRes;
}

void RendererWidget::setResolutionScale(RenderResolution scale)
{
    resolutionScale_ = scale;
    
    // Recalculate resolution-related values
    resizeGL(unscaledResolutionX_, unscaledResolutionY_);
}

void RendererWidget::toggleRenderComponent(RenderComponent component)
{
    renderer_.toggleComponent(component);
    
    // Restart the rendering process using the new setting.
    restartRendering();
}

void RendererWidget::setOverlay(RenderOverlay overlay)
{
    renderer_.setOverlay(overlay);
    
    // Restart the rendering process using the new overlay setting.
    restartRendering();
}

void RendererWidget::restartRendering()
{
    // Stop any existing rendering.
    renderer_.stopRender();
    
    // Start a new render
    renderer_.startRender(&targetBitmap_);
}

void RendererWidget::initializeGL()
{
    // Set up opengl for rendering the image quad
    glDisable(GL_DEPTH_TEST);
    
    // Create the image to copy the raytraced mage into
    glGenTextures(1, &targetGPUTexture_);
}

void RendererWidget::resizeGL(int w, int h)
{
    unscaledResolutionX_ = w;
    unscaledResolutionY_ = h;
    
    // Apply downsampling to the screen w and h
    const int scaledWidth = w >> (int)resolutionScale_;
    const int scaledHeight = h >> (int)resolutionScale_;
    
    // We need to stop the renderer before resizing the bitmap.
    renderer_.stopRender();
    
    // Allocate memory for the pixels
    targetBitmap_.resize(scaledWidth, scaledHeight);
    
    // Start a new render
    restartRendering();
}

void RendererWidget::paintGL()
{
    // Load the computed image into an opengl texture
    glBindTexture(GL_TEXTURE_2D, targetGPUTexture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, targetBitmap_.width(), targetBitmap_.height(), 0, GL_RGB, GL_FLOAT, targetBitmap_.buffer());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    // Bind the image to GL_TEXTURE_2D
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, targetGPUTexture_);
    
    // Draw to the entire screen
    if(contentsRect().width() > unscaledResolutionX_)
    {
        glViewport(0, 0, contentsRect().width(), contentsRect().height());
    }
    else
    {
        glViewport(0, 0, unscaledResolutionX_, unscaledResolutionY_);
    }

    // Draw a full screen quad containing the image
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glEnd();
    
    // Schedule a redraw immediately
    update();
}
