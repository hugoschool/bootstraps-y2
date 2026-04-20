#include "Vector3D.hpp"
#include <cmath>

Math::Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z)
{
}

double Math::Vector3D::length()
{
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
}

double Math::Vector3D::dot(Vector3D &vector)
{
    return x * vector.x + y * vector.y + z * vector.z;
}

Math::Vector3D Math::Vector3D::operator+(const Math::Vector3D &vector) const
{
    return Math::Vector3D(x + vector.x, y + vector.y, z + vector.z);
}

Math::Vector3D Math::Vector3D::operator-(const Math::Vector3D &vector) const
{
    return Math::Vector3D(x - vector.x, y - vector.y, z - vector.z);
}

Math::Vector3D Math::Vector3D::operator*(const Math::Vector3D &vector) const
{
    return Math::Vector3D(x * vector.x, y * vector.y, z * vector.z);
}

Math::Vector3D Math::Vector3D::operator*(const double nb) const
{
    return Math::Vector3D(x * nb, y * nb, z * nb);
}
