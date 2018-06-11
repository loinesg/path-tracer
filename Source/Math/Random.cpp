#include "Random.hpp"

#include <cstdlib>
#include <math.h>

float random_float()
{
    return drand48();
}

float random_float(float min, float max)
{
    return min + (random_float() * (max - min));
}

Vector3 random_hemisphere_ray(const Vector3& normal)
{
    Vector3 dir;
    float sqrMagnitude;
    do
    {
        dir.x = random_float(-1.0f, 1.0f);
        dir.y = random_float(-1.0f, 1.0f);
        dir.z = random_float(-1.0f, 1.0f);
        sqrMagnitude = dir.sqrMagnitude();
    }
    while(sqrMagnitude < 0.1f || sqrMagnitude > 1.0f);
    
    // Normalise the vector
    dir = dir / sqrtf(sqrMagnitude);
    
    // Check the vector is in the hemisphere,
    // if not, negate it.
    if(Vector3::dot(dir, normal) < 0.0f)
    {
        dir = dir * -1.0f;
    }
    
    return dir;
}

Vector3 random_hemisphere_ray_is(const Vector3& normal)
{
    Vector3 dir;
    while(1)
    {
        dir.x = random_float(-1.0f, 1.0f);
        dir.y = random_float(-1.0f, 1.0f);
        dir.z = random_float(-1.0f, 1.0f);
        float magnitude = dir.magnitude();
        if(magnitude < 0.1f || magnitude > 1.0f)
        {
            continue;
        }
        
        dir = dir / magnitude;
        if(Vector3::dot(dir, normal) > 0.0f)
        {
            break;
        }
    }
    
    return dir;
}
