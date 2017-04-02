#ifndef RAYTRACER_IN_ONE_WEEKEND_RAY_HPP
#define RAYTRACER_IN_ONE_WEEKEND_RAY_HPP
#include "vec3.hpp"

class ray {
public:
  vec3 _origin;
  vec3 _direction;
  ray() {}
  ray(const vec3& origin, const vec3& direction) : _origin(origin), _direction(direction) { }
  vec3 origin() const { return _origin; }
  vec3 direction() const { return _direction; }
  vec3 point_at_parameter(float t) const {
    return _origin + _direction * t;
  }
};

#endif //RAYTRACER_IN_ONE_WEEKEND_RAY_HPP
