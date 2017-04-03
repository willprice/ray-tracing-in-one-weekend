#include <iostream>
#include <values.h>
#include "vec3.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "sphere.hpp"
#include "hitable_list.hpp"
#include "camera.hpp"

vec3 color_ray(const ray& r, hitable *world, int depth) {
  const vec3 white = vec3(1.0, 1.0, 1.0);
  const vec3 blue = vec3(0.5, 0.7, 1.0);

  hit_record record;
  // Without t_min = 0.001 (i.e. t_min = 0.0) we get shadow acne
  if (world->hit(r, 0.000001, MAXFLOAT, record)) {
    ray scattered;
    vec3 attenuation;
    if (depth < 50 && record.mat != nullptr && record.mat->scatter(r, record, attenuation, scattered)) {
      return attenuation * color_ray(scattered, world, depth + 1);
    } else {
      return vec3(0, 0, 0);
    }
  } else {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * white + t * blue;
  }
}

int main() {
  int nx = 400;
  int ny = 200;
  int ns = 32;
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  hitable *list[4];
  list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
  list[1] = new sphere(vec3(0, -100.5f, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
  list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.1));
  list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8), 0.7));
  hitable *world = new hitable_list(list, 4);
  camera cam;

  for (int j = ny-1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 color(0, 0, 0);
      for (int s = 0; s < ns; s++) {
        float u = float(i + drand48()) / float(nx);
        float v = float(j + drand48()) / float(ny);
        ray r = cam.get_ray(u, v);
        color += color_ray(r, world, 0);
      }
      color /= float(ns);
      // Gamma correct with gamma = 2
      color = vec3(sqrt(color.r()), sqrt(color.g()), sqrt(color.b()));
      // I believe 255.99 is used instead of 255 since we're using the `int` constructor on floats, so we'll truncate the results
      //     0 <= r <= 1
      // =>  0 <= 255.99 * r <= 255.99
      // =>  0 <= int(255.99 * r) <= 255
      // It's a nasty way of rounding really, biasing towards rounding down.
      int ir = int(255.99*color.r());
      int ig = int(255.99*color.g());
      int ib = int(255.99*color.b());
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
  return 0;
}