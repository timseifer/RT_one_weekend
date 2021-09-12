#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <math.h> 
#include <iostream>

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

void write_color(color pixel_color, const int samples_per_pixel, int j, int i, char** world){
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);
    //rgb values are correlated to ascii
    r = (int)(256* clamp(r, 0.0, 0.999));
    g = (int)(256 * clamp(g, 0.0, 0.999));
    b = (int)(256 * clamp(b, 0.0, 0.999));
    // get luminance
    int luminance = .3*r+.59*g+.11*b;
    double to_palette = luminance * .075;
    // std::cout << ascii_val << '\n';
    world[j][i] = to_palette;
}

#endif