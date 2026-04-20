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

            // TODO: +, +=, -, -=, *, *=, / and /=
            // TODO: *, *=, / and /=
    };
}
