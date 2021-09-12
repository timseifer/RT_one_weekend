#include "camera.h"

#include "utils.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"

#include <iostream>



 const char palette[9] = {'.',',','^',';','-','+','a','b','c'};


color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);
    vec3 obj = vec3();
    if (world.hit(r, .001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

hittable_list random_scene() {
    hittable_list world;
    auto material_center = make_shared<lambertian>(color(3.8, 3.8, 3.8));
   auto material_right  = make_shared<lambertian>(color(3, 0, 0));
    world.add(make_shared<sphere>(point3(0, 0.0, -1.0),   2, material_center));
    world.add(make_shared<sphere>(point3( -2, 1.0, 0),   2,material_right));
    // world.add(make_shared<sphere>(point3( 10, 3, 0),   2,material_right));
    auto ground_material = make_shared<metal>(color(0.8, 0.6, 0.2));
    world.add(make_shared<sphere>(point3(0,-1010,-10), 1000, ground_material));


    return world;
}

void ClearScreen()
    {
      int n;
    for (n = 0; n < 2; n++){
      printf( "\n\n\n\n" );
    }
}

void print_world(int image_height, int image_width, char** world_ascii){
    int ascii_val = 0;
    int ascii_val_two = 0;
    for(int i =image_height-8; i>=0 ; i-=8){
        for(int j =0; j< image_width-8; j+=8){
            ascii_val = 0;
            ascii_val_two = 0;
            for(int block_row = i; block_row < i+4; block_row++){
                for(int block_col = j; block_col < j+4; block_col++){
                    ascii_val += (int)(world_ascii[block_row][block_col]);
                    ascii_val_two += (int)(world_ascii[block_row+4][block_col+4]);
                }
            }
            int max = (ascii_val < ascii_val_two) ? ascii_val : ascii_val_two;
            std::cout << palette[(max/16)];
        }
        std::cout << '\n';
    }
}

void print_world_debug(int image_height, int image_width, char** world_ascii){
    int ascii_val = 0;
    for(int i =0; i< image_height-8; i++){
        for(int j =0; j< image_width-8; j++){
                    std::cout <<  (int)(world_ascii[i][j]);
        }
        std::cout << '\n';
    }
}


int main() {

    // Image

    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 300;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 5;
    const int max_depth = 5;

    // World

    auto world = random_scene();

    // Camera

    point3 lookfrom(13,2,3);
    point3 lookat(0,0,0);
    vec3 vup(0,1,0);
    auto dist_to_focus = 10;
    auto aperture = 0.1;

    // make the ascii world

	char **world_ascii = 0;// no need to be global variable
	world_ascii = new char *[image_height];
	int i;
	for (i=0; i < image_height; i++)
		world_ascii[i] = new char [image_width];

    //inialize
    // std::cout << "INITIALIZING THE WORLD" << "\n";
    for(int i =0; i< image_height; i ++){
        for(int j = 0; j < image_width-1; j ++){
            world_ascii[i][j] = 0;
            // std::cout << world_ascii[i][j];
        }
        // std::cout << '\n';
    }


// camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
    // Render

    // std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
for(int camera_move_x = 0; camera_move_x < 1000; camera_move_x++){
auto material_right  = make_shared<lambertian>(color(3.8, 3.8, 3.8));
if(camera_move_x % 10 == 0){
world.add(make_shared<sphere>(point3(10+(camera_move_x*1.2), 1, 0),   1.0,material_right));
}
point3 lookfrom(camera_move_x+5, 2, 3);
camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    for (int j = image_height-1; j >= 0; --j) {
        // std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(pixel_color, samples_per_pixel, j, i, world_ascii);
            //  write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
        print_world(image_height, image_width, world_ascii);
        // ClearScreen();
}

    // std::cerr << "\nDone.\n";
    // print_world_debug(image_height, image_width, world_ascii);
}