#ifndef ICARUS_SPHERE_HPP_
#define ICARUS_SPHERE_HPP_

#include "icarus/hit.hpp"

namespace ic {

struct Sphere {
  Vec3 center;
  Vec3::ValueType radius;
};

[[nodiscard]] auto CheckHit(Sphere const& s, Ray const& ray,
                            RayHitBounds const& bounds) noexcept
    -> std::optional<HitRecord>;

}  // namespace ic

#endif /* ICARUS_SPHERE_HPP_ */
