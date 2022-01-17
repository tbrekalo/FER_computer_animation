#include "icarus/image.hpp"

#include <algorithm>
#include <cmath>

namespace ic {

namespace detail {

[[maybe_unused]] auto WriteColor(std::ostream& ostrm, Vec3 const& color)
    -> std::ostream& {
  ostrm << static_cast<std::uint32_t>(
               std::ceil(255 * std::clamp(std::sqrt(color[0]), 0., .999)))
        << ' ';

  ostrm << static_cast<std::uint32_t>(
               std::ceil(255 * std::clamp(std::sqrt(color[1]), 0., .999)))
        << ' ';

  ostrm << static_cast<std::uint32_t>(
               std::ceil(255 * std::clamp(std::sqrt(color[2]), 0., .999)))
        << '\n';

  return ostrm;
}

}  // namespace detail

auto operator<<(std::ostream& ostrm, PpmImage const& img) -> std::ostream& {
  ostrm << "P3\n" << img.dims.width << ' ' << img.dims.height << "\n255\n";
  for (auto const& it : img.rgb_pixels) {
    detail::WriteColor(ostrm, it);
  }

  return ostrm;
}

}  // namespace ic
