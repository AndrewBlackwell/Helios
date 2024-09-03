#include "common.hpp"

#include "is_hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

color ray_color(const ray &r, const is_hittable &world)
{
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec))
    {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    vector unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int height = int(width / aspect_ratio);
    height = (height < 1) ? 1 : height;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3D(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3D(0, -100.5, -1), 100));

    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(width) / height);
    auto camera_center = point3D(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vector(viewport_width, 0, 0);
    auto viewport_v = vector(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / width;
    auto pixel_delta_v = viewport_v / height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center - vector(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    std::cout << "P3\n"
              << width << " " << height << "\ns255\n";

    for (int i = 0; i < height; i++)
    {
        std::clog << "\rLines remaining: " << (height - i) << ' ' << std::flush;
        for (int j = 0; j < width; j++)
        {
            auto pixel_center = pixel00_loc + (j * pixel_delta_u) + (i * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone!                 \n";
    return 0;
}