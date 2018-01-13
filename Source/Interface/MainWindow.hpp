#pragma once

#include <QWidget>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>

#include "RendererWidget.hpp"

class MainWindow : public QWidget
{
public:
    MainWindow();

    // Renderer and side panel
    RendererWidget* rendererWidget() const { return rendererWidget_; }
    QWidget* sidePanelWidget() const { return sidePanelWidget_; }

    // Stats widgets
    QLabel* resolutionLabel() const { return resolutionLabel_; }
    QLabel* renderTimeLabel() const { return renderTimeLabel_; }
    QLabel* sampleCountLabel() const { return sampleCountLabel_; }
    QLabel* samplesPerSecondLabel() const { return samplesPerSecondLabel_; }
    QLabel* samplesPerPixelLabel() const { return samplesPerPixelLabel_; }

    // Render setting widget lists
    QObjectList resolutionScaleRadios() { return resolutionScaleRadios_->children(); }
    QObjectList renderComponentToggles() { return renderComponentToggles_->children(); }
    QObjectList overlayRadios() { return overlayRadios_->children(); }
    
private:
    
    // Main renderer widget
    RendererWidget* rendererWidget_;
    
    // Side panel widget
    QWidget* sidePanelWidget_;
    
    // Stats labels
    QGroupBox* statsGroupBox_;
    QLabel* resolutionLabel_;
    QLabel* renderTimeLabel_;
    QLabel* sampleCountLabel_;
    QLabel* samplesPerSecondLabel_;
    QLabel* samplesPerPixelLabel_;
    
    // Render setting widget groups
    QGroupBox* resolutionScaleRadios_;
    QGroupBox* renderComponentToggles_;
    QGroupBox* overlayRadios_;
    
    QLabel* createStatsLabel();
    QRadioButton* createResolutionScaleRadio(RenderResolution scale, const char* label);
    QCheckBox* createRenderComponentToggle(RenderComponent component, const char* label);
    QRadioButton* createOverlayRadio(RenderOverlay overlay, const char* label);
    QSlider* createSlider(QGroupBox* parent, float value, float min, float max);
};
