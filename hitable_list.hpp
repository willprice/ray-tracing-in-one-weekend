#ifndef RAYTRACER_IN_ONE_WEEKEND_HITABLE_LIST_HPP
#define RAYTRACER_IN_ONE_WEEKEND_HITABLE_LIST_HPP

#include "hitable.hpp"

class hitable_list : public hitable {
public:
  hitable **_list;
  int _size;

  hitable_list() {}
  hitable_list(hitable **list, int size) : _list(list), _size(size) { }
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record &record) const;
};

bool hitable_list::hit(const ray &r, float t_min, float t_max, hit_record &record) const {
  hit_record temp_record;
  bool hit_anything = false;
  double closest_so_far = t_max;
  for (int i = 0; i < _size; ++i) {
    if (_list[i]->hit(r, t_min, closest_so_far, temp_record)) {
      hit_anything = true;
      closest_so_far = temp_record.t;
      record = temp_record;
    }
  }
  return hit_anything;
}

#endif //RAYTRACER_IN_ONE_WEEKEND_HITABLE_LIST_HPP
