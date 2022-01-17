#ifndef ICARUS_RAY_HPP_
#define ICARUS_RAY_HPP_

#include <limits>

#include "icarus/vector.hpp"

namespace ic {

struct Ray {
  Vec3 origin;
  Vec3 dir;
};

struct RayHitBounds {
  Vec3::ValueType lower_bound = 0.0;
  Vec3::ValueType upper_bound = std::numeric_limits<Vec3::ValueType>::max();
};

auto PointAt(Ray const& ray, Vec3::ValueType const t) noexcept -> Vec3;

}  // namespace ic

#endif /* ICARUS_RAY_HPP_ */
