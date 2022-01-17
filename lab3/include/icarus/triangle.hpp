#ifndef ICARUS_TRIANGLE_HPP_
#define ICARUS_TRIANGLE_HPP_

#include <array>

#include "icarus/hit.hpp"
#include "icarus/ray.hpp"
#include "icarus/vector.hpp"

namespace ic {

struct Triangle {
  std::array<Vec3, 3U> points;
};

[[nodiscard]] auto CheckHit(Triangle const& plane, Ray const& ray,
                            RayHitBounds const& bounds) noexcept
    -> std::optional<HitRecord>;

}  // namespace ic

#endif /* ICARUS_TRIANGLE_HPP_ */
