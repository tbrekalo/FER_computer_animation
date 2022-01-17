#ifndef ICARUS_MATERIALS_HPP_
#define ICARUS_MATERIALS_HPP_

#include <concepts>
#include <optional>
#include <random>
#include <type_traits>

#include "icarus/hit.hpp"
#include "icarus/ray.hpp"
#include "icarus/vector.hpp"

namespace ic {

struct ScatterRecord {
  Ray scattered;
  Vec3 attenuation;
};

template <class T>
concept Material = requires(T t, Ray const& ray, HitRecord const& hit_rec) {
  { t(ray, hit_rec) } -> std::same_as<std::optional<ScatterRecord>>;
};

template <class T>
concept MaterialPtr =
    std::is_pointer_v<T> && Material<std::remove_pointer_t<T>>;

class MaterialProxy {
  using IvokerSig = std::optional<ScatterRecord>(void*, Ray const&,
                                                 HitRecord const&);
  using InvokerPtr = std::add_pointer_t<IvokerSig>;

 public:
  template <MaterialPtr T>
  MaterialProxy(T&& t)
      : invoker_([](void* repr, Ray const& ray,
                    HitRecord const& hit_rec) -> std::optional<ScatterRecord> {
          return static_cast<T>(repr)->operator()(ray, hit_rec);
        }),
        obj_ptr_(t) {}

  [[nodiscard]] auto operator()(Ray const& ray,
                                HitRecord const& hit_rec) noexcept {
    return invoker_(obj_ptr_, ray, hit_rec);
  };

 private:
  InvokerPtr invoker_;
  void* obj_ptr_;
};

struct Lambertian {
  auto operator()([[maybe_unused]] Ray const& in_ray,
                  HitRecord const& hit_rec) noexcept
      -> std::optional<ScatterRecord>;

  Vec3 albedo;
  std::mt19937 rng_gen;
};

struct Metal {
  auto operator()(Ray const& in_ray, HitRecord const& hit_rec) noexcept
      -> std::optional<ScatterRecord>;

  Vec3 albedo;
  std::mt19937 rng_gen;
};

}  // namespace ic

#endif /* ICARUS_MATERIALS_HPP_ */
