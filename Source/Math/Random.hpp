#pragma once

#include "Vector3.hpp"

// Returns a random number between 0 and 1.
float random_float();

// Returns a random number between min and max.
float random_float(float min, float max);

// Returns a random vector in the upper hemisphere.
// Equal probability for each direction.
Vector3 random_hemisphere_ray(const Vector3 &normal);

// Returns a random vector in the upper hemisphere.
// Importance sampling is used - probability of picking
// direction d is d dot normal.
Vector3 random_hemisphere_ray_is(const Vector3 &normal);
