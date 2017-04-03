#include <iostream>
#include <values.h>
#include "vec3.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "hitable_list.hpp"
#include "camera.hpp"

vec3 random_in_unit_sphere() {
  vec3 p;
  // Generate vectors in unit cube and test if they're in the unit sphere
  do {
    p = vec3(drand48(), drand48(), drand48());
  } while (p.squared_length() >= 1.0);
  return p;
}
vec3 color_ray(const ray& r, hitable *world) {
  const vec3 white = vec3(1.0, 1.0, 1.0);
  const vec3 blue = vec3(0.5, 0.7, 1.0);

  hit_record record;
  // Without t_min = 0.001 (i.e. t_min = 0.0) we get shadow acne
  if (world->hit(r, 0.001, MAXFLOAT, record)) {
    vec3 target = record.p + record.normal + random_in_unit_sphere();
    return 0.5 * color_ray(ray(record.p, target - record.p), world);
  } else {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * white + t * blue;
  }
}

int main() {
  int nx = 200;
  int ny = 100;
  int ns = 16;
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  hitable *list[2];
  list[0] = new sphere(vec3(0, 0, -1), 0.5);
  list[1] = new sphere(vec3(0, -100.5, -1), 100);
  hitable *world = new hitable_list(list, 2);
  camera cam;

  for (int j = ny-1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 color(0, 0, 0);
      for (int s = 0; s < ns; s++) {
        float u = float(i + drand48()) / float(nx);
        float v = float(j + drand48()) / float(ny);
        ray r = cam.get_ray(u, v);
        color += color_ray(r, world);
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