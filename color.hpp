#ifndef COLOR_HPP
#define COLOR_HPP

#include "interval.hpp"
#include "vector.hpp"

using color = vector; // RGB color

void write_color(std::ostream &out, color pcolor)
{
    auto r = pcolor.x();
    auto g = pcolor.y();
    auto b = pcolor.z();

    // Translate [0, 1] -> [0, 255]
    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    out << rbyte << " " << gbyte << " " << bbyte << "\n";
}

#endif