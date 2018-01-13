#include "Scene.hpp"

#include <cstdio>
#include <assert.h>

Scene::Scene()
    : camera_(),
    ambientLight_(Color(0.8245026f, 0.8790448f, 0.8970588f)),
    lights_(),
    areaLights_(),
    triangles_(),
    spheres_()
{
    // Position the camera at a hand-picked location
    camera_.setPosition(Vector3(0.0f, 5.0f, -15.0f));
    camera_.setRotation(Quaternion::identity());
    
    // Create the lights and geometry
    createWalls();
    createFloor();
    createCeiling();
    createAreaLight();
    
    // Make some spheres in the middle of the scene.
    addSphere(Sphere(Color::white(), Vector3(-2.2f, 2.0f, 0.0f), 2.0f));
    addSphere(Sphere(Color::white(), Vector3(2.2f, 2.0f, 0.0f), 2.0f));
    addSphere(Sphere(Color::blue(), Vector3(-1.5f, 1.2f, -3.0f), 1.2f, 0.1f));
    addSphere(Sphere(Color::blue(), Vector3(1.5f, 1.2f, -3.0f), 1.2f, 0.1f));
    addSphere(Sphere(Color::blue(), Vector3(0.0f, 1.2f, 3.0f), 1.2f, 0.1f));
}

void Scene::createWalls()
{
    // Left wall (red)
    const Vector3 left1 = Vector3(-5.0f, 0.0f, 5.0f);
    const Vector3 left2 = Vector3(-5.0f, 0.0f, -5.0f);
    const Color leftColor = Color::red();
    addWall(left1, left2, leftColor);
    
    // Right wall (green)
    const Vector3 right1 = Vector3(5.0f, 0.0f, -5.0f);
    const Vector3 right2 = Vector3(5.0f, 0.0f, 5.0f);
    const Color rightColor(0.7f, 1.0f, 0.85f);
    addWall(right1, right2, rightColor);
    
    // Front wall (gray)
    const Vector3 front1 = Vector3(-5.0f, 0.0f, -5.0f);
    const Vector3 front2 = Vector3(5.0f, 0.0f, -5.0f);
    const Color frontColor = Color::grey();
    addWall(front1, front2, frontColor);
    
    // Back wall (gray)
    const Vector3 back1 = Vector3(5.0f, 0.0f, 5.0f);
    const Vector3 back2 = Vector3(-5.0f, 0.0f, 5.0f);
    const Color backColor = Color::grey();
    addWall(back1, back2, backColor);
}

void Scene::createFloor()
{
    // The floor is gray
    const Color color = Color::grey();
    
    // The floor is a quad with 4 vertices
    const Vector3 p1 = Vector3(-5.0f, 0.0f, 5.0f);
    const Vector3 p2 = Vector3(5.0f, 0.0f, 5.0f);
    const Vector3 p3 = Vector3(5.0f, 0.0f, -5.0f);
    const Vector3 p4 = Vector3(-5.0f, 0.0f, -5.0f);
    
    // Make the floor from 2 triangles
    addTriangle(Triangle(p1, p2, p3, color), false);
    addTriangle(Triangle(p1, p3, p4, color), false);
}

void Scene::createCeiling()
{
    // The ceiling is gray
    const Color color = Color::grey();
    
    // The ceiling is a quad with 4 vertices
    const Vector3 p1 = Vector3(-5.0f, 10.0f, -5.0f);
    const Vector3 p2 = Vector3(5.0f, 10.0f, -5.0f);
    const Vector3 p3 = Vector3(5.0f, 10.0f, 5.0f);
    const Vector3 p4 = Vector3(-5.0f, 10.0f, 5.0f);
    
    // Make the ceiling from 2 triangles
    addTriangle(Triangle(p1, p2, p3, color), false);
    addTriangle(Triangle(p1, p3, p4, color), false);
}

void Scene::createAreaLight()
{
    // The light is black, with a white emission
    const Color color = Color::black();
    const Color emission(2000.0f, 2000.0f, 2000.0f);
    
    // The area light is a quad
    // Offset is slightly below the ceiling
    const float eps = 0.000001f;
    const Vector3 p1 = Vector3(-1.0f, 10.0f - eps, -1.0f);
    const Vector3 p2 = Vector3(1.0f, 10.0f - eps, -1.0f);
    const Vector3 p3 = Vector3(1.0f, 10.0f - eps, 1.0f);
    const Vector3 p4 = Vector3(-1.0f, 10.0f - eps, 1.0f);
    
    // Make the area light from 2 triangles
    addTriangle(Triangle(p1, p2, p3, color, emission), false);
    addTriangle(Triangle(p1, p3, p4, color, emission), false);
    
    // Create a light source corresponding to the triangles
    areaLights_.push_back(AreaLight(p1, p3, emission));
}

void Scene::addWall(const Vector3 &b1, const Vector3 &b2, const Color &color)
{
    // A wall is a quad with 4 vertices
    const Vector3 p1 = Vector3(b1.x, 0.0f, b1.z);
    const Vector3 p2 = Vector3(b2.x, 0.0f, b2.z);
    const Vector3 p3 = Vector3(b2.x, 10.0f, b2.z);
    const Vector3 p4 = Vector3(b1.x, 10.0f, b1.z);
    
    // Make the wall from 2 triangles
    addTriangle(Triangle(p1, p2, p3, color), false);
    addTriangle(Triangle(p1, p3, p4, color), false);
}

void Scene::addTriangle(const Triangle &triangle, bool doubleSided)
{
    // Add the triangle to the scene.
    triangles_.push_back(triangle);

    if(doubleSided)
    {
        // Reverse the triangle winding and add it again to
        // form the back of the triangle.
        Triangle reversed(triangle.vertices[2], triangle.vertices[1], triangle.vertices[0], triangle.color);
        
        // Add the reversed triangle to the triangles list.
        triangles_.push_back(reversed);
    }
}

void Scene::addSphere(const Sphere &sphere)
{
    spheres_.push_back(sphere);
}

void Scene::addLight(const Light &light)
{
    // Add the light to the scene.
    lights_.push_back(light);
}
