#include "Rectangle3D.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"

Raytracer::Rectangle3D::Rectangle3D() : origin(-200, -200, -10), leftSide(0, 400, 0), bottomSide(400, 0, 0)
{
}

Math::Point3D Raytracer::Rectangle3D::pointAt(double u, double v)
{
    Math::Vector3D leftVector = leftSide * u;
    Math::Vector3D bottomVector = bottomSide * v;

    return origin + leftVector + bottomVector;
}
