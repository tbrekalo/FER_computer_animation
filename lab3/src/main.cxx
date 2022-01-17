#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>

#include "icarus/camera.hpp"
#include "icarus/hit.hpp"
#include "icarus/image.hpp"
#include "icarus/material.hpp"
#include "icarus/ray.hpp"
#include "icarus/sphere.hpp"
#include "icarus/triangle.hpp"
#include "icarus/vector.hpp"

int main(void) {
  constexpr auto kAspectRation = 16.f / 9.f;

  constexpr auto kImageHeight = 720;
  constexpr auto kImageWidth =
      static_cast<std::int32_t>(kAspectRation * kImageHeight);

  auto metal1 = ic::Metal{.albedo = ic::Vec3{0.8, 0.8, 0.8}};
  auto metal2 = ic::Metal{.albedo = ic::Vec3{0.32, 0.34, 0.2}};
  auto lam1 = ic::Lambertian{.albedo = ic::Vec3{0.82, 0.31, 0.19}};
  auto lam2 = ic::Lambertian{.albedo = ic::Vec3{0.16, 0.08, 0.08}};

  auto const spheres = std::vector<ic::Sphere>{
      ic::Sphere{.center = ic::Vec3{0.0, 0.0, -1.0}, .radius = 0.5},
      ic::Sphere{.center = ic::Vec3{0.0, -100.5, -1.0}, .radius = 100}};

  auto const trigs = std::vector<ic::Triangle>{ic::Triangle{
      .points = {ic::Vec3{0.0, -2.0, -2.0}, ic::Vec3{2.0, 0.0, -2.0},
                 ic::Vec3{0.0, 2.0, -2.0}}}};

  auto world = std::vector<std::pair<ic::HittableProxy, ic::MaterialProxy>>{
      std::make_pair(ic::HittableProxy(&spheres[0]),
                     ic::MaterialProxy(&metal2)),
      std::make_pair(ic::HittableProxy(&spheres[1]), ic::MaterialProxy(&lam2)),
      std::make_pair(ic::HittableProxy(&trigs[0]), ic::MaterialProxy(&metal1)),
  };

  auto const kImgDims =
      ic::ImageDims{.width = kImageWidth, .height = kImageHeight};
  auto const camera =
      ic::Camera(ic::Vec3{0.0, 0.0, 1.0}, ic::Vec3{0.0, 0.0, -1.0});

  std::cout << camera.Render(world, kImgDims);

  return EXIT_SUCCESS;
}
