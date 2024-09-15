#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "common.hpp"

#include "is_hittable.hpp"

class camera
{
public:
    double aspect_ratio = 1.0;  // Ratio of image width over height
    int width = 100;            // Rendered image width in pixel count
    int samples_per_pixel = 10; // Count of random samples for each pixel
    int max_depth = 10;         // Maximum number of ray bounces into scene

    void render(const is_hittable &world)
    {
        initialize();

        std::cout << "P3\n"
                  << width << ' ' << height << "\n255\n";

        for (int j = 0; j < height; j++)
        {
            std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
            for (int i = 0; i < width; i++)
            {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; sample++)
                {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";
    }

private:
    int height;                 // Rendered image height
    double pixel_samples_scale; // Color scale factor for a sum of pixel samples
    point3D center;             // Camera center
    point3D pixel00_loc;        // Location of pixel 0, 0
    vector pixel_delta_u;       // Offset to pixel to the right
    vector pixel_delta_v;       // Offset to pixel below

    void initialize()
    {
        height = int(width / aspect_ratio);
        height = (height < 1) ? 1 : height;
        pixel_samples_scale = 1.0 / samples_per_pixel;

        center = point3D(0, 0, 0);

        // Determine viewport dimensions.
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(width) / height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = vector(viewport_width, 0, 0);
        auto viewport_v = vector(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / width;
        pixel_delta_v = viewport_v / height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            center - vector(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    ray get_ray(int i, int j) const
    {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j.

        auto offset = sample_square();
        auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vector sample_square() const
    {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vector(random_double() - 0.5, random_double() - 0.5, 0);
    }

    color ray_color(const ray &r, int depth, const is_hittable &world) const
    {
        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return color(0, 0, 0);

        hit_record rec;

        if (world.hit(r, interval(0, infinity), rec))
        {
            vector direction = random_on_hemisphere(rec.normal);
            return 0.5 * ray_color(ray(rec.p, direction), depth - 1, world);
        }

        vector unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
};

#endif