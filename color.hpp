#ifndef COLOR_HPP
#define COLOR_HPP

#include "vector.hpp"

using color = vector; // RGB color

void write_color(std::ostream &out, color pcolor)
{
    auto r = pcolor.x();
    auto g = pcolor.y();
    auto b = pcolor.z();

    // Translate [0, 1] -> [0, 255]
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    out << rbyte << " " << gbyte << " " << bbyte << "\n";
}

#endif