#include "MainWindowController.hpp"

#include <cstdint>

MainWindowController::MainWindowController(MainWindow* window)
    : window_(window),
    inputManager_(),
    mouseDragging_(false),
    mousePosition_(Vector2(0, 0))
{
    // Resolution scale toggle signals
    for(int i = 1; i < window_->resolutionScaleRadios().size(); ++i)
    {
        connect(window_->resolutionScaleRadios()[i], SIGNAL(toggled(bool)), this, SLOT(resolutionScaleToggled()));
    }
    
    // Render component toggle signals
    for(int i = 1; i < window_->renderComponentToggles().size(); ++i)
    {
        connect(window_->renderComponentToggles()[i], SIGNAL(stateChanged(int)), this, SLOT(renderComponentToggled()));
    }
    
    // Debug overlay radio button signals
    for(int i = 1; i < window_->overlayRadios().size(); ++i)
    {
        connect(window_->overlayRadios()[i], SIGNAL(toggled(bool)), this, SLOT(overlayToggled()));
    }
}

bool MainWindowController::eventFilter(QObject* obj, QEvent* event)
{
    if(event->type() == QEvent::Paint)
    {
        update((1.0 / 60.0));
    }
    else if(event->type() == QEvent::MouseButtonPress && obj == window_->rendererWidget())
    {
        mousePressEvent(static_cast<QMouseEvent*>(event));
    }
    else if(event->type() == QEvent::MouseButtonRelease && obj == window_->rendererWidget())
    {
        mouseReleaseEvent(static_cast<QMouseEvent*>(event));
    }
    else if(event->type() == QEvent::MouseMove && obj == window_->rendererWidget())
    {
        mouseMoveEvent(static_cast<QMouseEvent*>(event));
    }
    
    // InputManager handles key press / release events
    if(event->type() == QEvent::KeyPress)
    {
        inputManager_.keyPressed((InputKey)static_cast<QKeyEvent*>(event)->key());
    }
    else if(event->type() == QEvent::KeyRelease)
    {
        inputManager_.keyReleased((InputKey)static_cast<QKeyEvent*>(event)->key());
    }
    
    // Unhandled events are passed back to Qt
    return QObject::eventFilter(obj, event);
}

void MainWindowController::resolutionScaleToggled()
{
    // The sender is a resolution scale radio button
    QRadioButton* sender = (QRadioButton*)QObject::sender();
    RenderResolution scale = (RenderResolution)sender->property("scale").toInt();
    
    // Update the shadow method
    window_->rendererWidget()->setResolutionScale(scale);
}

void MainWindowController::renderComponentToggled()
{
    // The sender is a render component checkbox
    QCheckBox* checkbox = (QCheckBox*)QObject::sender();
    RenderComponent component = (RenderComponent)checkbox->property("component").toInt();
    
    // Update the renderer widget
    window_->rendererWidget()->toggleRenderComponent(component);
}

void MainWindowController::overlayToggled()
{
    // The sender is a overlay radio button
    QRadioButton* radio = (QRadioButton*)QObject::sender();
    RenderOverlay overlay = (RenderOverlay)radio->property("overlay").toInt();
    
    // Update the overlay index
    window_->rendererWidget()->setOverlay(overlay);
}

void MainWindowController::update(float deltaTime)
{
    // Move the camera with user input
    applyCameraMovement(deltaTime);
    
    // Update the statistics ui
    updateStatsUI();
}

void MainWindowController::applyCameraMovement(float deltaTime)
{
    Camera* camera = window_->rendererWidget()->camera();

    // Calculate movement from inputs
    Vector3 movement;
    movement.x = inputManager_.getSidewaysMovement();
    movement.z = inputManager_.getForwardsMovement();
    movement.y = inputManager_.getVerticalMovement();
    movement = movement * inputManager_.getMovementSpeed();
    movement = camera->localToWorldVector(movement);
    
    // Apply movement to camera (frame rate independent)
    camera->translate(movement * deltaTime);
    
    // Restart the rendering if the camera moved
    if(movement.sqrMagnitude() > 0.0001f)
    {
        window_->rendererWidget()->restartRendering();
    }
}

void MainWindowController::updateStatsUI()
{
    // Get the render resolution
    int resX = window_->rendererWidget()->resolutionX();
    int resY = window_->rendererWidget()->resolutionY();
    
    // Get the performance stats
    const RendererStats* stats = window_->rendererWidget()->stats();
    double renderTime = stats->currentRenderTime();
    uint64_t sampleCount = stats->sampleCount();
    uint64_t samplesPerSecond = stats->averageSamplesPerSecond();
    uint64_t samplesPerPixel = stats->averageSamplesPerPixel();

    // Create the text for each label
    QString resolutionText = QString("%1 x %2").arg(resX).arg(resY);
    QString renderTimeText = QString("Render Time: %1").arg(renderTime);
    QString sampleCountText = QString("Total Samples: %1").arg(sampleCount);
    QString samplesPerSecondText = QString("Samples/s: %1").arg(samplesPerSecond);
    QString samplesPerPixelText = QString("Avg Samples: %1").arg(samplesPerPixel);

    // Update the stats labels
    window_->resolutionLabel()->setText(resolutionText);
    window_->renderTimeLabel()->setText(renderTimeText);
    window_->sampleCountLabel()->setText(sampleCountText);
    window_->samplesPerSecondLabel()->setText(samplesPerSecondText);
    window_->samplesPerPixelLabel()->setText(samplesPerPixelText);
}

void MainWindowController::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        mouseDragging_ = true;
        mousePosition_ = Vector2(event->pos().x(), event->pos().y());
    }
}

void MainWindowController::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        mouseDragging_ = false;
    }
}

void MainWindowController::mouseMoveEvent(QMouseEvent *event)
{
    if(mouseDragging_)
    {
        Camera* camera = window_->rendererWidget()->camera();
        
        // Determine mouse movement
        Vector2 oldPosition = mousePosition_;
        Vector2 newPosition = Vector2 (event->pos().x(), event->pos().y());
        Vector2 deltaPosition = newPosition - oldPosition;
        mousePosition_ = newPosition;
        
        // Apply horizontal rotation
        Quaternion horizontal = Quaternion::rotation(deltaPosition.x * 0.5, Vector3::up());

        // Calculate vertical rotation
        Vector3 upAxis = camera->up();
        Vector3 forwardAxis = camera->forward();
        Vector3 sidewaysAxis = Vector3::cross(upAxis, forwardAxis);
        Quaternion vertical = Quaternion::rotation(deltaPosition.y * 0.5, sidewaysAxis);
    
        // Apply rotation, vertical first
        camera->setRotation(horizontal * vertical * camera->rotation());
        
        // Restart the rendering while rotating the camera
        window_->rendererWidget()->restartRendering();
    }
}
