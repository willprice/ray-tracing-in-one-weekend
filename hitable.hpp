#ifndef RAYTRACER_IN_ONE_WEEKEND_HITABLE_HPP
#define RAYTRACER_IN_ONE_WEEKEND_HITABLE_HPP

#include "ray.hpp"

class hit_record {
public:
  float t;
  vec3 p;
  vec3 normal;
};

class hitable {
public:
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& record) const = 0;
};


#endif //RAYTRACER_IN_ONE_WEEKEND_HITABLE_HPP
