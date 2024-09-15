#ifndef VEC_HPP
#define VEC_HPP

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

    bool near_zero() const
    {
        // Return true if the vector is close to zero in all dimensions.
        auto s = 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
    }

    static vector random()
    {
        return vector(random_double(), random_double(), random_double());
    }

    static vector random(double min, double max)
    {
        return vector(random_double(min, max), random_double(min, max), random_double(min, max));
    }
};

// create some type aliases for vector
using point3D = vector; // 3D point

// utilities
inline std::ostream &operator<<(std::ostream &out, const vector &v)
{
    return out << v.e[0] << " " << v.e[1] << " " << v.e[2];
}

inline vector operator+(const vector &u, const vector &v)
{
    return vector(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
inline vector operator-(const vector &u, const vector &v)
{
    return vector(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vector operator*(const vector &u, const vector &v)
{
    return vector(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vector operator*(double t, const vector &v)
{
    return vector(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vector operator*(const vector &v, double t)
{
    return t * v;
}

inline vector operator/(const vector &v, double t)
{
    return (1 / t) * v;
}

inline double dot(const vector &u, const vector &v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vector cross(const vector &u, const vector &v)
{
    return vector(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                  u.e[2] * v.e[0] - u.e[0] * v.e[2],
                  u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vector unit_vector(const vector &v)
{
    return v / v.length();
}

inline vector random_in_unit_disk()
{
    while (true)
    {
        auto p = vector(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() < 1)
            return p;
    }
}

inline vector random_unit_vector()
{
    while (true)
    {
        auto p = vector::random(-1, 1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}

inline vector random_on_hemisphere(const vector &normal)
{
    vector on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

inline vector reflect(const vector &v, const vector &n)
{
    return v - 2 * dot(v, n) * n;
}

inline vector refract(const vector &uv, const vector &n, double etai_over_etat)
{
    auto cos_theta = std::fmin(dot(-uv, n), 1.0);
    vector r_out_perp = etai_over_etat * (uv + cos_theta * n);
    vector r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

#endif