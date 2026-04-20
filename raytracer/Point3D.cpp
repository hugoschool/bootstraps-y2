#include "Point3D.hpp"
#include "Vector3D.hpp"

Math::Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z)
{
}

Math::Point3D Math::Point3D::operator+(const Point3D &point) const
{
    return Math::Point3D(x + point.x, y + point.y, z + point.z);
}

Math::Vector3D Math::Point3D::operator-(const Point3D &point) const
{
    return Math::Vector3D(x - point.x, y - point.y, z - point.z);
}

Math::Point3D Math::Point3D::operator+(const Vector3D &vec) const
{
    return Math::Point3D(x + vec.x, y + vec.y, z + vec.z);
}
