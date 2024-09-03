#ifndef RAY_HPP
#define RAY_HPP

#include "vector.hpp"

class ray
{
public:
    ray() {}

    ray(const point3D &origin, const vector &direction)
        : orig(origin), dir(direction)
    {
    }

    const point3D &origin() const { return orig; }
    const vector &direction() const { return dir; }

    point3D at(double t) const
    {
        return orig + t * dir;
    }

private:
    point3D orig;
    vector dir;
};

#endif