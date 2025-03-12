#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "sp3/axes.h"
#include "sp3/rotation.h"

#include <limits>

constexpr auto eps = std::numeric_limits<sp3::real>::epsilon();

TEST_CASE("rotation - rotations around the x, y, and z axes")
{
  SECTION("rotating points 90 degrees clockwise around the given axis")
  {
    const auto& [axis, theta, input, expected] =
        GENERATE( table<sp3::vector, sp3::angle, sp3::point, sp3::point>(
        {
          {sp3::xhat, sp3::angle{sp3::pi/2}, sp3::point{1, 0, 0}, sp3::point{1, 0, 0}},
          {sp3::xhat, sp3::angle{sp3::pi/2}, sp3::point{0, 1, 0}, sp3::point{0, 0, 1}},
          {sp3::xhat, sp3::angle{sp3::pi/2}, sp3::point{0, 0, 1}, sp3::point{0, -1, 0}},
    
          {sp3::yhat, sp3::angle{sp3::pi/2}, sp3::point{1, 0, 0}, sp3::point{0, 0, -1}},
          {sp3::yhat, sp3::angle{sp3::pi/2}, sp3::point{0, 1, 0}, sp3::point{0, 1, 0}},
          {sp3::yhat, sp3::angle{sp3::pi/2}, sp3::point{0, 0, 1}, sp3::point{1, 0, 0}},
    
          {sp3::zhat, sp3::angle{sp3::pi/2}, sp3::point{1, 0, 0}, sp3::point{0, 1, 0}},
          {sp3::zhat, sp3::angle{sp3::pi/2}, sp3::point{0, 1, 0}, sp3::point{-1, 0, 0}},
          {sp3::zhat, sp3::angle{sp3::pi/2}, sp3::point{0, 0, 1}, sp3::point{0, 0, 1}},
        }));

    auto result = sp3::rotation{axis, theta}(input);

    CAPTURE(axis, theta, input);
    
    REQUIRE_THAT(result.x, Catch::Matchers::WithinAbs(expected.x, eps));
    REQUIRE_THAT(result.y, Catch::Matchers::WithinAbs(expected.y, eps));
    REQUIRE_THAT(result.z, Catch::Matchers::WithinAbs(expected.z, eps));
  }
}

#if 0
SCENARIO("rotation - rotations around the x, y, and z axes (explicit)")
{
  GIVEN("a rotation of 90 degrees clockwise around the x-axis")
  {
    const sp3::rotation r{sp3::xhat, sp3::angle{sp3::pi/2}};
    
    WHEN("rotating the point (0, 1, 0) on the y-axis")
    {
      const auto rp = r({0, 1, 0});

      THEN("the resulting point should be (0, 0, 1) on the z-axis")
      {
        REQUIRE_THAT(rp.x, Catch::Matchers::WithinAbs(0, eps));
        REQUIRE_THAT(rp.y, Catch::Matchers::WithinAbs(0, eps));
        REQUIRE_THAT(rp.z, Catch::Matchers::WithinAbs(1, eps));
      }
    }

    WHEN("rotating the point (0, 0, 1) on the z-axis")
    {
      const auto rp = r({0, 0, 1});

      THEN("the resulting point should be (0, -1, 0) on the y-axis")
      {
        REQUIRE_THAT(rp.x, Catch::Matchers::WithinAbs(0, eps));
        REQUIRE_THAT(rp.y, Catch::Matchers::WithinAbs(-1, eps));
        REQUIRE_THAT(rp.z, Catch::Matchers::WithinAbs(0, eps));
      }
    }

    WHEN("rotating the point (1, 0, 0) on the x-axis")
    {
      const auto rp = r({1, 0, 0});

      THEN("the resulting point should be the same as the orignal")
      {
        REQUIRE_THAT(rp.x, Catch::Matchers::WithinAbs(1, eps));
        REQUIRE_THAT(rp.y, Catch::Matchers::WithinAbs(0, eps));
        REQUIRE_THAT(rp.z, Catch::Matchers::WithinAbs(0, eps));
      }
    }
  }

}
#endif
