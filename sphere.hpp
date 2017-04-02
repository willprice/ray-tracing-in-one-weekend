#ifndef RAYTRACER_IN_ONE_WEEKEND_SPHERE_HPP
#define RAYTRACER_IN_ONE_WEEKEND_SPHERE_HPP

#include "hitable.hpp"

class sphere: public hitable {
public:
  vec3 _center;
  float _radius;

  sphere() {}
  sphere(vec3 center, float radius) : _center(center), _radius(radius) {}
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& record) const;
};

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &record) const {
  // This is derived from finding the point p, along the ray r
  // (parameterised by t) such that p is on the surface of the sphere
  // This forms a quadratic equation and we check the discriminant
  // to determine whether there are solutions to the equation or not
  // if so, then there is a point at which the ray intersects the sphere
  vec3 origin_to_center = r.origin() - _center;
  float a = dot(r.direction(), r.direction());
  float b = dot(origin_to_center, r.direction());
  float c = dot(origin_to_center, origin_to_center) - _radius * _radius;
  float discriminant = b * b - a * c;
  if (discriminant > 0) {
    float temp = -(b + sqrt(b * b - a * c))/a;
    if (temp < t_max && temp > t_min) {
      record.t = temp;
      record.p = r.point_at_parameter(temp);
      record.normal = (record.p - _center) / _radius;
    }
    temp = (-b + sqrt(b * b - a * c)) / a;
    if (temp < t_max && temp > t_min){
      record.t = temp;
      record.p = r.point_at_parameter(temp);
      return true;
    }
  }
  return false;
}
#endif //RAYTRACER_IN_ONE_WEEKEND_SPHERE_HPP
