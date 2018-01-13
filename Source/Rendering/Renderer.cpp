#include "Renderer.hpp"

#include "Random.hpp"

Renderer::Renderer(const Scene* scene)
    : scene_(scene),
    stats_(),
    renderComponents_(~0),
    renderOverlay_(RO_None),
    rendering_(false),
    renderThreads_()
{
    
}

bool Renderer::componentEnabled(RenderComponent component) const
{
    return (renderComponents_ & component) != 0;
}

void Renderer::setOverlay(RenderOverlay overlay)
{
    renderOverlay_ = overlay;
}

void Renderer::toggleComponent(RenderComponent component)
{
    if(componentEnabled(component))
    {
        renderComponents_ &= (~component);
    }
    else
    {
        renderComponents_ |= component;
    }
}

void Renderer::startRender(Bitmap* bitmap)
{
    // Stop any existing render
    stopRender();
    
    // Clear the bitmap prior to starting the new render
    bitmap->clear();
    
    // Start a new render
    rendering_ = true;
    stats_.renderStarted(bitmap->width(), bitmap->height());
    
    // Start multiple worker threads for path tracing
    const int threadCount = 4;
    for(int thread = 0; thread < threadCount; ++thread)
    {
        renderThreads_.push_back(std::thread(&Renderer::renderWorker, this, bitmap));
    }
}

void Renderer::stopRender()
{
    // Mark the renderer as stopped.
    rendering_ = false;
    
    // Wait for rendering threads to finish.
    for(unsigned int i = 0; i < renderThreads_.size(); ++i)
    {
        renderThreads_[i].join();
    }
    
    // Remove all the finished worker threads.
    renderThreads_.clear();
}

void Renderer::renderWorker(Bitmap *bitmap)
{
    const float pixelWidth = 1.0f / (float)bitmap->width();
    const float pixelHeight = 1.0f / (float)bitmap->height();
    const float aspect = pixelWidth / pixelHeight;
    
    // Continually produce more pixel samples until told to stop.
    while(rendering_)
    {
        // Pick a random pixel
        const int x = (rand() % bitmap->width());
        const int y = (rand() % bitmap->height());
        
        // Offset the coordinates to a random point within their pixel
        const float normalizedX = (x / (float)bitmap->width()) + random_float(0.0f, pixelWidth);
        const float normalizedY = (y / (float)bitmap->height()) + random_float(0.0f, pixelHeight);
        
        // Get the viewRay to follow.
        const Vector3 viewRayOrigin = scene_->mainCamera()->position();
        const Vector3 viewRayDir = scene_->mainCamera()->getViewRayDir(normalizedX, normalizedY, aspect);
        const Ray viewRay(viewRayOrigin, viewRayDir);
        
        // Path trace a single sample for the pixel
        bitmap->addSample(x, y, pathTrace(viewRay));
        
        // Keep track of the sample count
        stats_.addSample();
    }
}

Color Renderer::pathTrace(const Ray &viewRay, int bounce) const
{
    // Handle ray directions overlay
    if(renderOverlay_ == RO_PixelRays)
    {
        return viewRay.direction() * 0.5f + 0.5f;
    }
    
    // Find and process the closest surface that the ray intersects.
    const SurfaceHit hit = testRay(viewRay);
    if(hit.distance == INFINITY)
    {
        return Color::black();
    }
    
    // Handle hit information overlays
    if(renderOverlay_ == RO_Distance) return Color::white() * (1.0f - hit.distance * 0.01f);
    if(renderOverlay_ == RO_Position) return hit.position * 0.1f + 0.5f;
    if(renderOverlay_ == RO_Color) return hit.color;
    if(renderOverlay_ == RO_Normals) return hit.normal * 0.5f + 0.5f;
    if(renderOverlay_ == RO_Emission) return hit.emission * 0.0002f;
    
    // Keep a sum of the radiance along the path
    Color radiance = Color::black();

    if(bounce == 0)
    {
        radiance += hit.emission * 0.0005f;
    }
    
    if(componentEnabled(RC_Direct)) radiance += sampleDirectAreaLights(viewRay, hit);
    if(componentEnabled(RC_Impulse) && bounce == 0) radiance += sampleImpulseLight(viewRay, hit, bounce);
    if(componentEnabled(RC_Indirect)) radiance += sampleIndirectLight(hit, bounce);
    return radiance;
}

Color Renderer::sampleDirectAreaLights(const Ray &viewRay, const SurfaceHit &hit) const
{
    Color radiance = Color::black();
    
    // Sum the radiance from each area light source
    auto areaLights = scene_->areaLights();
    for(auto areaLight = areaLights.begin(); areaLight != areaLights.end(); areaLight++)
    {
        const Vector3 lightPoint = areaLight->getPoint();
        const Vector3 toLight = lightPoint - hit.position;
        
        if(componentEnabled(RC_Shadows) == false || checkVisibility(hit.position + hit.normal * 0.0001f, lightPoint - toLight * 0.0001f))
        {
            // Compute the incoming light direction and intensity
            const Color lightRadiance = areaLight->emission() / (4.0f * M_PI * toLight.sqrMagnitude());
            
            // Use blinnphong bsdf
            float ndotl = Vector3::dot(hit.normal, toLight.normalized());
            float lightndotl = Vector3::dot(areaLight->normal(), toLight.normalized() * -1.0f);
            if(ndotl > 0.0f && lightndotl > 0.0f)
            {
                const Vector3 toEye = viewRay.direction() * -1.0f;
                radiance += blinnPhong(hit, toEye, toLight.normalized()) * lightRadiance * ndotl * lightndotl;
            }
        }
    }

    return radiance;
}

Color Renderer::sampleImpulseLight(const Ray &viewRay, const SurfaceHit &hit, int bounce) const
{
    // Find the reflection vector
    const Vector3 refl = viewRay.direction() - 2.0f * Vector3::dot(viewRay.direction(), hit.normal) * hit.normal;

    // Path trace to find the impulse from the reflection direction
    return pathTrace(Ray(hit.position, refl), bounce + 1) * hit.reflectivity;
}

Color Renderer::sampleIndirectLight(const SurfaceHit &hit, int bounce) const
{
    if(random_float() > 0.5f) return Color::black();

    // Construct a random ray in the surface's hemisphere
    // and trace a ray in that direction
    const Vector3 dir = random_hemisphere_ray(hit.normal);
    return pathTrace(Ray(hit.position, dir), bounce + 1);
}

SurfaceHit Renderer::testRay(const Ray &ray) const
{
    // Keep track of the closest surface that the ray intersects.
    SurfaceHit hit;
    hit.distance = INFINITY;
    
    // Check for intersection against each triangle in the scene
    for(unsigned int i = 0; i < scene_->triangles().size(); ++i)
    {
        // Get the triangle
        const Triangle triangle = scene_->triangles()[i];
        
        // Check for an intersection with the ray
        float alpha, beta, gamma, triangleDistance;
        if(ray.intersectionWithTriangle(triangle, alpha, beta, gamma, triangleDistance)
           && triangleDistance < hit.distance)
        {
            // Record details of the hit.
            hit.distance = triangleDistance;
            hit.position = ray.origin() + ray.direction() * triangleDistance;
            hit.normal = triangle.normal;
            hit.color = triangle.color;
            hit.emission = triangle.emission;
            hit.reflectivity = triangle.reflectivity;
        }
    }

    if(componentEnabled(RC_Spheres))
    {
        // Check for intersection against each sphere in the scene
        for(unsigned int i = 0; i < scene_->spheres().size(); ++i)
        {
            // Get the sphere
            const Sphere sphere = scene_->spheres()[i];

            // Check for intersection with the ray
            float distance;
            if(ray.intersectionWithSphere(sphere, distance)
                && distance < hit.distance)
            {
                // Record details of the hit.
                hit.distance = distance;
                hit.position = ray.origin() + ray.direction() * distance;
                hit.normal = (hit.position - sphere.centre()).normalized();
                hit.color = sphere.color();
                hit.emission = Color::black();
                hit.reflectivity = sphere.reflectivity();
            }
        }
    }
    
    // Return the hit details.
    // If no hit occurred, the hit distance will be INFINITY
    return hit;
}

bool Renderer::checkVisibility(const Vector3 &a, const Vector3 &b) const
{
    // Find the direction and distance from a to b
    const Vector3 direction = b - a;
    const float sqrDistance = direction.sqrMagnitude();
    
    // Find how far a ray from a to b gets
    const float hitDistance = testRay(Ray(a, direction)).distance;
    const float hitDistanceSqr = hitDistance * hitDistance;
    
    // Check if the ray hits something before reaching b
    return (hitDistanceSqr >= sqrDistance) ? 1.0f : 0.0f;
}

Color Renderer::blinnPhong(const SurfaceHit &surface, const Vector3 &toEye, const Vector3 &toLight) const
{
    Vector3 h = (toLight + toEye).normalized();
    float ndoth = std::max(0.0f, Vector3::dot(surface.normal, h));
    float spec = powf(ndoth, 25.0f) * 0.15f;
    return (surface.color + spec) / M_PI;
}
