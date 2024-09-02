#include "color.hpp"
#include "vector.hpp"

#include <iostream>

int main()
{
    int width = 256;
    int height = 256;

    std::cout << "P3\n"
              << width << " " << height << "\ns255\n";

    for (int i = 0; i < height; i++)
    {
        std::clog << "\rLines remaining: " << (height - i) << ' ' << std::flush;
        for (int j = 0; j < width; j++)
        {
            // Normalize coordinates to range [0, 1]
            double x = double(i) / (width - 1);
            double y = double(j) / (height - 1);

            // Calculate the angle of the point in polar coordinates
            double angle = std::atan2(y - 0.5, x - 0.5) + M_PI;

            // Map angle to a color: 0 to 2π maps to 0 to 1 (normalized)
            double r = 0.5 + 0.5 * std::cos(angle);
            double g = 0.5 + 0.5 * std::cos(angle - 2.0 * M_PI / 3.0);
            double b = 0.5 + 0.5 * std::cos(angle - 4.0 * M_PI / 3.0);

            // Create a color object from these values
            auto pixel_color = color(r, g, b);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone!                 \n";
    return 0;
}