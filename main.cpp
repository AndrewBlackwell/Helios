#include <iostream>

int main()
{
    int width = 256;
    int height = 256;

    std::cout << "P3\n"
              << width << " " << height << "\ns255\n";

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            auto red = double(j) / (height - 1);
            auto green = double(i) / (width - 1);
            auto blue = 0.0;

            int ired = int(255.999 * red);
            int igreen = int(255.999 * green);
            int iblue = int(255.999 * blue);

            std::cout << ired << " " << igreen << " " << iblue << "\n";
        }
    }
    return 0;
}