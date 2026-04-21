#pragma once

namespace Math {
    class Vector3D {
        public:
            Vector3D() = default;
            Vector3D(double x, double y, double z);
            ~Vector3D() = default;

            double x;
            double y;
            double z;

            double length();
            double dot(Vector3D &vector);

            Vector3D operator+(const Vector3D &vector) const;
            Vector3D operator-(const Vector3D &vector) const;
            Vector3D operator*(const Vector3D &vector) const;

            Math::Vector3D operator*(const double nb) const;

            Math::Vector3D rotateX(double degree) const;
            Math::Vector3D rotateY(double degree) const;
            Math::Vector3D rotateZ(double degree) const;

            // TODO: +=, -=, *=, / and /=
    };
}
