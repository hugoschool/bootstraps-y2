#include "Sphere.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"
#include <cmath>

Raytracer::Sphere::Sphere(const Math::Point3D &center, double radius) :
    center(center.x, center.y, center.z), radius(radius)
{
}

// From the bootstrap:
//
// Not explained in the bootstrap:
// a, b, c comes from the "written down" / "expanded" version of the quadratic equation.
//
// x^2 = (OxK) ^ 2 + 2OxKDxK + DxK^2
// Same for y^2 and z^2 (https://en.wikipedia.org/wiki/Quadratic_equation)
//
// a * k^2 = (OxK) ^ 2 + (OyK) ^ 2 + (OzK) ^ 2
// b * k = 2DxKOx + 2DyOy + 2DzKOz
// c (the rest) = Ox^2 + Oy^2 + Oz^2 - R^2
//
// Remove the all references to k
//
// This only works for a Sphere who's origin is 0, 0, 0
// To remedy this:
// O = Sphere Center - Ray Origin
//
bool Raytracer::Sphere::hits(Raytracer::Ray &ray)
{
    Math::Vector3D centerOffset(center.x - ray.origin.x, center.y - ray.origin.y, center.z - ray.origin.z);
    double a = std::pow(ray.direction.x, 2) + std::pow(ray.direction.y, 2) + std::pow(ray.direction.z, 2);
    double b = 2 * ray.direction.x * centerOffset.x + 2 * ray.direction.y * centerOffset.y + 2 * ray.direction.z * centerOffset.z;
    double c = std::pow(centerOffset.x, 2) + std::pow(centerOffset.y, 2) + std::pow(centerOffset.z, 2) - std::pow(radius, 2);
    double d = std::pow(b, 2) - 4 * a * c;

    return d >= 0;
}
