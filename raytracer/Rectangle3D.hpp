#pragma once

#include "Point3D.hpp"
#include "Vector3D.hpp"
namespace Raytracer {
    class Rectangle3D {
        public:
            Rectangle3D();
            ~Rectangle3D() = default;

            Math::Point3D origin;
            Math::Vector3D leftSide;
            Math::Vector3D bottomSide;

            Math::Point3D pointAt(double u, double v);
    };
}
