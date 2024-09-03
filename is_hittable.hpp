#ifndef IS_HITTABLE_HPP
#define IS_HITTABLE_HPP

#include "common.hpp"

class hit_record
{
public:
    point3D p;
    vector normal;
    double t;

    bool front_face;

    void set_face_normal(const ray &r, const vector &outward_normal)
    {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class is_hittable
{
public:
    virtual ~is_hittable() = default;

    virtual bool hit(const ray &r, interval ray_t, hit_record &rec) const = 0;
};

#endif