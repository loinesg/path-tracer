#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

#include "AreaLight.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Sphere.hpp"
#include "Object.hpp"

class Scene
{
public:
    Scene();
    
    // The viewers camera
    const Camera* mainCamera() const { return &camera_; }
    Camera* mainCamera() { return &camera_; }
    
    // Light settings
    const Color& ambientLight() const { return ambientLight_; }
    const Light& mainLight() const { return lights_[0]; }
    const Light& bigRedLight() const { return lights_[1]; }
    
    // Scene components
    const std::vector<Light>& lights() const { return lights_; }
    const std::vector<AreaLight>& areaLights() const { return areaLights_; }
    const std::vector<Triangle>& triangles() const { return triangles_; }
    const std::vector<Sphere>& spheres() const { return spheres_; }
    
    // Creates the 3 walls of the cornell box.
    void createWalls();
    
    // Creates the cornell box floor
    void createFloor();
    
    // Creates the cornell box ceiling
    void createCeiling();
    
    // Creates the area light at the top of the cornell box
    void createAreaLight();
    
    // Adds a wall with the specified base positions and color
    void addWall(const Vector3 &b1, const Vector3 &b2, const Color &color);
    
    // Adds the specified triangle to the scene.
    void addTriangle(const Triangle &triangle, bool doubleSided = true);
    
    // Adds the specified sphere to the scene.
    void addSphere(const Sphere &sphere);

    // Adds the specified light to the scene.
    void addLight(const Light &light);
    
private:
    // The scene camera.
    Camera camera_;
    
    // The amount of ambient light applied to all objects.
    Color ambientLight_;
    
    // Scene components
    std::vector<Light> lights_;
    std::vector<AreaLight> areaLights_;
    std::vector<Triangle> triangles_;
    std::vector<Sphere> spheres_;
};
