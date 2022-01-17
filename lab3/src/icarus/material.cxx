#include "icarus/material.hpp"

#include <cmath>
#include <functional>
#include <numeric>

namespace ic {

namespace detail {

auto NearZero(Vec3 const& vec) -> bool {
  return std::transform_reduce(
      vec.begin(), vec.end(), true, std::logical_and<bool>(),
      [](Vec3::ValueType const val) -> bool { return std::fabs(val) < 1e-8; });
}

auto Reflect(Vec3 const& vec, Vec3 const& normal) -> Vec3 {
  return vec - 2 * DotProduct(vec, normal) * normal;
};

}  // namespace detail

auto Lambertian::operator()([[maybe_unused]] Ray const& in_ray,
                            HitRecord const& hit_rec) noexcept
    -> std::optional<ScatterRecord> {
  auto unit_sphere_vec = RngVec(0.0, 1.0, rng_gen);
  while (DotProduct(unit_sphere_vec, unit_sphere_vec) > 1.0) {
    unit_sphere_vec = RngVec(0.0, 1.0, rng_gen);
  }

  auto scatter_dir = UnitVec3(hit_rec.normal + unit_sphere_vec);
  if (detail::NearZero(scatter_dir)) {
    scatter_dir = hit_rec.normal;
  }

  return ScatterRecord{
      .scattered = Ray{.origin = hit_rec.point, .dir = scatter_dir},
      .attenuation = albedo};
};

auto Metal::operator()(Ray const& in_ray, HitRecord const& hit_rec) noexcept
    -> std::optional<ScatterRecord> {
  auto const reflected_dir =
      UnitVec3(detail::Reflect(in_ray.dir, hit_rec.normal));
  if (DotProduct(reflected_dir, hit_rec.normal) < 0) {
    return std::nullopt;
  }

  return ScatterRecord{
      .scattered = Ray{.origin = hit_rec.point, .dir = reflected_dir},
      .attenuation = albedo};
}

}  // namespace ic
