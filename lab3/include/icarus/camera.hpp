#ifndef ICARUS_CAMERA_HPP_
#define ICARUS_CAMERA_HPP_

#include <span>
#include <vector>

#include "icarus/hit.hpp"
#include "icarus/image.hpp"
#include "icarus/material.hpp"
#include "icarus/vector.hpp"

namespace ic {

struct Viewport {
  Vec3 horizonal;
  Vec3 vertical;
};

class Camera {
 public:
  Camera(Vec3 const position, Vec3 const target) noexcept;

  [[nodiscard]] auto Render(
      std::span<std::pair<HittableProxy, MaterialProxy>> hittables,
      ImageDims const img_dims) const -> PpmImage;

 private:
  Vec3 position_;
  Vec3 direction_;
};

}  // namespace ic

#endif /* ICARUS_CAMERA_HPP_ */
