#pragma once

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "MathUtils.h"

namespace raytracing_1
{
    class Vector3 {

    public:

        double x;
        double y;
        double z;

        Vector3() :x(0), y(0), z(0) {}
        Vector3(double x0, double y0, double z0) :x(x0), y(y0), z(z0) {}

        static const Vector3 Zero;
        static const Vector3 One;
        static const Vector3 PositiveX;
        static const Vector3 PositiveY;
        static const Vector3 PositiveZ;
        static const Vector3 NegtiveX;
        static const Vector3 NegtiveY;
        static const Vector3 NegtiveZ;

        inline const Vector3& operator+() const { return *this; }
        inline Vector3 operator-() const { return Vector3(-x, -y, -z); }
        inline double operator[](int i) const;
        inline double& operator[](int i);

        inline bool operator==(const Vector3& v) const;
        inline bool operator!=(const Vector3& v) const;
        inline Vector3& operator+=(const Vector3 &v2);
        inline Vector3& operator-=(const Vector3 &v2);
        inline Vector3& operator*=(const double t);
        inline Vector3& operator/=(const double t);

        inline double length() const { return sqrt(x * x + y * y + z * z); }
        inline double squaredLength() const { return x * x + y * y + z * z; }
        inline void normalize();
    };

    inline double Vector3::operator[](int i) const
    {
        switch (i)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            break;
        }
        throw "invalid index";
    }

    inline double & Vector3::operator[](int i)
    {
        switch (i)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            break;
        }
        throw "invalid index";
    }


    inline void Vector3::normalize() {
        double k = 1.0 / sqrt(x * x + y * y + z * z);
        x *= k; y *= k; z *= k;
    }
    inline bool Vector3::operator==(const Vector3& v2) const
    {
        return x == v2.x && y == v2.y && z == v2.z;
    }

    inline bool Vector3::operator!=(const Vector3& v2) const
    {
        return x != v2.x || y != v2.y || z != v2.z;
    }

    inline std::istream& operator>>(std::istream &is, Vector3 &t) {
        is >> t.x >> t.y >> t.z;
        return is;
    }

    inline std::ostream& operator<<(std::ostream &os, const Vector3 &t) {
        os << t.x << " " << t.y << " " << t.z;
        return os;
    }

    inline Vector3 operator+(const Vector3 &v1, const Vector3 &v2) {
        return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    }

    inline Vector3 operator-(const Vector3 &v1, const Vector3 &v2) {
        return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    }

    inline Vector3 operator*(const Vector3 &v1, const Vector3 &v2) {
        return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
    }

    inline Vector3 operator/(const Vector3 &v1, const Vector3 &v2) {
        return Vector3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
    }

    inline Vector3 operator*(double t, const Vector3 &v) {
        return Vector3(t*v.x, t*v.y, t*v.z);
    }

    inline Vector3 operator/(Vector3 v, float t) {
        return Vector3(v.x / t, v.y / t, v.z / t);
    }

    inline Vector3 operator*(const Vector3 &v, double t) {
        return Vector3(t*v.x, t*v.y, t*v.z);
    }

    inline double dot(const Vector3 &v1, const Vector3 &v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    inline Vector3 cross(const Vector3 &v1, const Vector3 &v2) {
        return Vector3((v1.y * v2.z - v1.z * v2.y),
            (-(v1.x * v2.z - v1.z * v2.x)),
            (v1.x * v2.y - v1.y * v2.x));
    }

    inline Vector3& Vector3::operator+=(const Vector3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    inline Vector3& Vector3::operator-=(const Vector3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    inline Vector3& Vector3::operator*=(const double t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    inline Vector3& Vector3::operator/=(const double t) {
        double k = 1.0 / t;
        x *= k;
        y *= k;
        z *= k;
        return *this;
    }

    inline Vector3 normalize(const Vector3 &v) {
        return v / v.length();
    }

    inline Vector3 lerp(const Vector3 &v1, const Vector3 &v2, double t) {
        return Vector3(v1.x + t * v2.x,
            v1.y + t * v2.y,
            v1.z + t * v2.z);
    }

    inline double squaredDistance(const Vector3 &v1, const Vector3 &v2)
    {
        return (v1.x - v2.x) * (v1.x - v2.x)
            + (v1.y - v2.y) * (v1.y - v2.y)
            + (v1.z - v2.z) * (v1.z - v2.z);
    }

    inline double distance(const Vector3 &v1, const Vector3 &v2)
    {
        return sqrt(squaredDistance(v1, v2));
    }

    inline Vector3 max(const Vector3& v1, const Vector3& v2)
    {
        return Vector3(
            MathUtils::max(v1.x, v2.x),
            MathUtils::max(v1.y, v2.y),
            MathUtils::max(v1.z, v2.z)
        );
    }

    inline Vector3 min(const Vector3& v1, const Vector3& v2)
    {
        return Vector3(
            MathUtils::min(v1.x, v2.x),
            MathUtils::min(v1.y, v2.y),
            MathUtils::min(v1.z, v2.z)
        );
    }

    inline Vector3 clamp(const Vector3& value, const Vector3& min, const Vector3& max)
    {
        return Vector3(
            MathUtils::clamp(value.x, min.x, max.x),
            MathUtils::clamp(value.y, min.y, max.y),
            MathUtils::clamp(value.z, min.z, max.z)
        );
    }
}
