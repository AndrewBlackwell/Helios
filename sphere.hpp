#ifndef SPHERE_H
#define SPHERE_H

#include "is_hittable.hpp"

class sphere : public is_hittable
{
public:
    sphere(const point3D &center, double radius) : center(center), radius(std::fmax(0, radius)) {}

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {
        vector oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius * radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0)
        {
            return false;
        }

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;

        if (!ray_t.surrounds(root))
        {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root))
            {
                return false;
            }
        }
        rec.t = root;
        rec.p = r.at(rec.t);
        vector outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }

private:
    point3D center;
    double radius;
};
#endif