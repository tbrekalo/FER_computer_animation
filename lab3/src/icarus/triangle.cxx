#include "icarus/triangle.hpp"

#include <numeric>

namespace ic {

namespace detail {

enum class RelPointPos : std::uint8_t { kLeft, kDeadOn, kRight };

auto DetermineRelPos(Vec3 const& ref, Vec3 const& query) -> RelPointPos {
  auto const val = DotProduct(ref, query);
  if (std::abs(val) < 1e-12) {
    return RelPointPos::kDeadOn;
  }

  if (val < 0.) {
    return RelPointPos::kLeft;
  }

  return RelPointPos::kRight;
}

}  // namespace detail
[[nodiscard]] auto CheckHit(Triangle const& trig, Ray const& ray,
                            RayHitBounds const& bounds) noexcept
    -> std::optional<HitRecord> {
  auto const v1 = trig.points[1] - trig.points[0];
  auto const v2 = trig.points[2] - trig.points[0];
  auto const normal = UnitVec3(CrossProduct(v1, v2));

  if (std::abs(DotProduct(ray.dir, normal)) > 1e-12) {
    auto const t = DotProduct((trig.points[0] - ray.origin), normal) /
                   DotProduct(ray.dir, normal);

    if (bounds.lower_bound < t && t < bounds.upper_bound) {
      auto const hit_point = PointAt(ray, t);
      auto const lines = std::array<Vec3, 3U>{trig.points[1] - trig.points[0],
                                              trig.points[2] - trig.points[1],
                                              trig.points[0] - trig.points[2]};

      auto const kSide =
          detail::DetermineRelPos(lines[0], hit_point - trig.points[0]);

      if (kSide == detail::RelPointPos::kDeadOn) {
        return std::nullopt;
      } else {
        for (auto i = 1U; i < lines.size(); ++i) {
          if (detail::DetermineRelPos(lines[i], hit_point - trig.points[i]) !=
              kSide) {
            return std::nullopt;
          }
        }
      }

      auto face = SurfaceFace::kFront;
      if (DotProduct(ray.dir, normal) > 0.0) {
        face = SurfaceFace::kBack;
      }

      return HitRecord{.t = t,
                       .point = hit_point,
                       .normal = normal,
                       .face = face};
    }
  }

  return std::nullopt;
}

};  // namespace ic
