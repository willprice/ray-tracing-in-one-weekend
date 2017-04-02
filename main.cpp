#include <iostream>
#include "vec3.hpp"

int main() {
  int nx = 200;
  int ny = 100;
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";
  for (int j = ny-1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 color(float(i) / float(nx), float(j) / float(ny), 0.2);
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