#include "MainWindow.hpp"

#include <QVariant>
#include <QScrollArea>
#include <QCheckBox>

MainWindow::MainWindow()
{
    // Create main renderer
    rendererWidget_ = new RendererWidget();
    
    // Create groups
    statsGroupBox_ = new QGroupBox("Stats");
    resolutionScaleRadios_ = new QGroupBox("Resolution Scale");
    renderComponentToggles_ = new QGroupBox("Render Components");
    overlayRadios_ = new QGroupBox("Debug Overlay");
    
    // Use a vertical layout for all groups
    statsGroupBox_->setLayout(new QBoxLayout(QBoxLayout::TopToBottom));
    resolutionScaleRadios_->setLayout(new QBoxLayout(QBoxLayout::TopToBottom));
    renderComponentToggles_->setLayout(new QBoxLayout(QBoxLayout::TopToBottom));
    overlayRadios_->setLayout(new QBoxLayout(QBoxLayout::TopToBottom));

    // Create stats widgets
    resolutionLabel_ = createStatsLabel();
    renderTimeLabel_ = createStatsLabel();
    sampleCountLabel_ = createStatsLabel();
    samplesPerSecondLabel_ = createStatsLabel();
    samplesPerPixelLabel_ = createStatsLabel();
    
    // Create resolution scale radios
    createResolutionScaleRadio(RS_FullRes, "Native (Very Slow)");
    createResolutionScaleRadio(RS_HalfRes, "1/2 Res");
    createResolutionScaleRadio(RS_QuarterRes, "1/4 Res");
    createResolutionScaleRadio(RS_EighthRes, "1/8 Resolution")->setChecked(true); // Default
    createResolutionScaleRadio(RS_SixteenthRes, "1/16 Resolution");
    
    // Create render component toggles
    createRenderComponentToggle(RC_Direct, "Direct Light");
    createRenderComponentToggle(RC_Impulse, "Impulse Light");
    createRenderComponentToggle(RC_Indirect, "Indirect Light");
    createRenderComponentToggle(RC_Shadows, "Shadows");
    createRenderComponentToggle(RC_Spheres, "Spheres");
    
    // Create overlay radios
    createOverlayRadio(RO_None, "No Overlay")->setChecked(true); // Default = No Overlay
    createOverlayRadio(RO_PixelRays, "Pixel Rays");
    createOverlayRadio(RO_Distance, "Hit Distance");
    createOverlayRadio(RO_Position, "Hit Position");
    createOverlayRadio(RO_Color, "Surface Color");
    createOverlayRadio(RO_Normals, "Surface Normals");
    createOverlayRadio(RO_Emission, "Surface Emission");
    
    // Add widgets to side panel
    QBoxLayout* sidePanelLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    sidePanelLayout->addWidget(statsGroupBox_);
    sidePanelLayout->addWidget(resolutionScaleRadios_);
    sidePanelLayout->addWidget(renderComponentToggles_);
    sidePanelLayout->addWidget(overlayRadios_);
    sidePanelLayout->setSpacing(20);
    sidePanelLayout->addStretch();
    
    QWidget* sidePanel = new QWidget();
    sidePanel->setFixedWidth(240);
    sidePanel->setLayout(sidePanelLayout);
    
    // Create the scroll area for the side panel
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setMaximumWidth(260);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    scrollArea->setWidget(sidePanel);
    scrollArea->setWidgetResizable(false);
    scrollArea->setFrameShape(QFrame::NoFrame);
    sidePanelWidget_ = scrollArea;
    
    // Add widgets to main layout
    QBoxLayout* mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    mainLayout->addWidget(rendererWidget_);
    mainLayout->addWidget(sidePanelWidget_);
}

QLabel* MainWindow::createStatsLabel()
{
    QLabel* label = new QLabel();
    statsGroupBox_->layout()->addWidget(label);
    return label;
}

QRadioButton* MainWindow::createResolutionScaleRadio(RenderResolution scale, const char* label)
{
    QRadioButton* radio = new QRadioButton(label);
    radio->setProperty("scale", (int)scale);
    
    resolutionScaleRadios_->layout()->addWidget(radio);
    return radio;
}

QCheckBox* MainWindow::createRenderComponentToggle(RenderComponent component, const char* label)
{
    QCheckBox* checkBox = new QCheckBox(label);
    checkBox->setProperty("component", (int)component);
    checkBox->setChecked(true);
    
    renderComponentToggles_->layout()->addWidget(checkBox);
    return checkBox;
}

QRadioButton* MainWindow::createOverlayRadio(RenderOverlay overlay, const char* label)
{
    // Creat the radio button
    QRadioButton* radio = new QRadioButton(label);
    radio->setProperty("overlay", (int)overlay);
    
    // Add to the overlay radios group
    overlayRadios_->layout()->addWidget(radio);
    
    return radio;
}

QSlider* MainWindow::createSlider(QGroupBox* parent, float value, float min, float max)
{
    QSlider* slider = new QSlider();
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum((int)(min * 1000.0f));
    slider->setMaximum((int)(max * 1000.0f));
    slider->setValue((int)(value * 1000.0f));
    parent->layout()->addWidget(slider);
    return slider;
}
