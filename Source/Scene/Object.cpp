#include "Object.hpp"

Object::Object()
    : position_(Vector3::zero()),
    rotation_(Quaternion::identity()),
    scale_(Vector3::one()),
    worldToLocal_(Matrix4x4::identity()),
    localToWorld_(Matrix4x4::identity())
{
    
}

Vector3 Object::forward() const
{
    return rotation_ * Vector3::forwards();
}

Vector3 Object::up() const
{
    return rotation_ * Vector3::up();
}

Vector3 Object::right() const
{
    return rotation_ * Vector3(1.0f, 0.0f, 0.0f);
}

Vector3 Object::localToWorldVector(const Vector3 &v) const
{
    Vector4 worldV4 = localToWorld() * Vector4(v, 0.0);
    return Vector3(worldV4.x, worldV4.y, worldV4.z);
}

void Object::setPosition(const Vector3 &pos)
{
    position_ = pos;
    recreateTransformation();
}

void Object::setRotation(const Quaternion &rot)
{
    rotation_ = rot;
    recreateTransformation();
}

void Object::setScale(const Vector3 &scale)
{
    scale_ = scale;
    recreateTransformation();
}

void Object::translate(const Vector3 &translation)
{
    setPosition(position_ + translation);
}

void Object::rotate(float angle, const Vector3 &axis)
{
    // Construct the delta quaternion
    Quaternion rotationChange = Quaternion::rotation(angle, axis);
    
    // Apply to the current rotation
    Quaternion newRotation = rotationChange * rotation_;
    
    // Set the rotation and update the transformation matrices
    setRotation(newRotation);
}

void Object::recreateTransformation()
{
    localToWorld_ = Matrix4x4::trs(position_, rotation_, scale_);
    worldToLocal_ = Matrix4x4::trsInverse(position_, rotation_, scale_);
}
