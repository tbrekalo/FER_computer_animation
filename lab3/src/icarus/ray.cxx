#include "icarus/ray.hpp"

namespace ic {

auto PointAt(Ray const& ray, Vec3::ValueType const t) noexcept -> Vec3 {
  return ray.origin + t * ray.dir;
}

}  // namespace ic
