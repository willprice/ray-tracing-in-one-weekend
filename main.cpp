#include <iostream>
#include "vec3.hpp"
#include "ray.hpp"

vec3 color_ray(const ray& ray) {
  const vec3 white = vec3(1.0, 1.0, 1.0);
  const vec3 blue = vec3(0.5, 0.7, 1.0);
  vec3 unit_direction = unit_vector(ray.direction());
  float t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * white + t * blue;
}

int main() {
  int nx = 200;
  int ny = 100;
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";
  vec3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);

  for (int j = ny-1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      float u = float(i) / float(nx);
      float v = float(j) / float(ny);
      ray r(origin, lower_left_corner + u*horizontal + v*vertical);
      vec3 color = color_ray(r);
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