#include "Camera.hpp"
#include "Point3D.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"

Raytracer::Camera::Camera() : origin(0, 0, 0), screen()
{
}

Raytracer::Ray Raytracer::Camera::ray(double u, double v)
{
    Math::Point3D point = screen.pointAt(u, v);
    Math::Vector3D direction = point - origin;

    return Raytracer::Ray(origin, direction);
}
