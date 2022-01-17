#ifndef ICARUS_IMAGE_HPP_
#define ICARUS_IMAGE_HPP_

#include <cstdint>
#include <ostream>
#include <vector>

#include "icarus/vector.hpp"

namespace ic {

struct ImageDims {
  std::uint32_t width;
  std::uint32_t height;
};

struct PpmImage {
  ImageDims dims;
  std::vector<Vec3> rgb_pixels;
};

auto operator<<(std::ostream& ostrm, PpmImage const& img) -> std::ostream&;

}  // namespace ic

#endif /* ICARUS_IMAGE_HPP_ */
