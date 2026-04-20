#pragma once

#include "Point3D.hpp"
#include "Ray.hpp"
#include "Rectangle3D.hpp"

namespace Raytracer {
    class Camera {
        public:
            Camera();
            ~Camera() = default;

            Math::Point3D origin;
            Raytracer::Rectangle3D screen;

            Raytracer::Ray ray(double u, double v);
    };
}
