#include "icarus/sphere.hpp"

#include <cmath>

namespace ic {

auto CheckHit(Sphere const& s, Ray const& ray,
              RayHitBounds const& bounds) noexcept -> std::optional<HitRecord> {
  auto const oc = ray.origin - s.center;
  auto const a = DotProduct(ray.dir, ray.dir);
  auto const h = DotProduct(oc, ray.dir);
  auto const c = DotProduct(oc, oc) - s.radius * s.radius;

  auto const determinant = h * h - a * c;
  if (determinant >= 0) {
    auto t = (-h - std::sqrt(determinant)) / a;
    if (t < bounds.lower_bound || bounds.upper_bound < t) {
      t = (-h + std::sqrt(determinant)) / a;
      if (t < bounds.lower_bound || bounds.upper_bound < t) {
        return std::nullopt;
      }
    }

    auto const point = PointAt(ray, t);

    auto face = SurfaceFace();
    auto outward_normal = UnitVec3(point - s.center);
    if (DotProduct(ray.dir, outward_normal) >= 0) {
      face = SurfaceFace::kBack;
      outward_normal *= -1;
    } else {
      face = SurfaceFace::kFront;
    }

    return HitRecord{
        .t = t, .point = point, .normal = outward_normal, .face = face};
  }

  return std::nullopt;
}

}  // namespace ic
