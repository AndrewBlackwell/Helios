#ifndef VEC_HPP
#define VEC_HPP

#include <cmath>
#include <iostream>

class vector
{
public:
    double e[3];
    vector() : e{0, 0, 0} {}
    vector(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vector operator-() const { return vector(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double &operator[](int i) { return e[i]; }

    vector &operator+=(const vector &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vector &operator*=(double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vector &operator/=(double t)
    {
        return *this *= 1 / t;
    }

    double length() const
    {
        return std::sqrt(length_squared());
    }

    double length_squared() const
    {
        return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    }
};

#endif