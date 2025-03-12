#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "sp3/angle.h"

TEST_CASE("angle - default angle is zero")
{
  const sp3::angle theta;
  CHECK(theta.rad() == 0);
  CHECK(theta.deg() == 0);
}

TEST_CASE("angle - angles of integer fractions and multiples of pi")
{
  SECTION("pi")
  {
    const auto theta = sp3::angle{sp3::pi};
    CHECK(theta.rad() == sp3::pi);
    CHECK(theta.deg() == sp3::real{180});
  }

  SECTION("pi over two")
  {
    const auto theta = sp3::angle{sp3::pi / 2};
    CHECK(theta.rad() == sp3::pi / 2);
    CHECK(theta.deg() == sp3::real{90});
  }

  SECTION("pi over four")
  {
    const auto theta = sp3::angle{sp3::pi / 4};
    CHECK(theta.rad() == sp3::pi / 4);
    CHECK(theta.deg() == sp3::real{45});
  }

  SECTION("pi over three")
  {
    const auto theta = sp3::angle{sp3::pi / 3};
    CHECK(theta.rad() == sp3::pi / 3);
    CHECK(theta.deg() == sp3::real{60});
  }

  SECTION("pi over six")
  {
    const auto theta = sp3::angle{sp3::pi / 6};
    CHECK(theta.rad() == sp3::pi / 6);
    CHECK(theta.deg() == sp3::real{30});
  }

  SECTION("pi over five")
  {
    const auto theta = sp3::angle{sp3::pi / 5};
    CHECK(theta.rad() == sp3::pi / 5);
    CHECK(theta.deg() == sp3::real{36});
  }

  SECTION("pi over ten")
  {
    const auto theta = sp3::angle{sp3::pi / 10};
    CHECK(theta.rad() == sp3::pi / 10);
    CHECK(theta.deg() == sp3::real{18});
  }

  SECTION("two pi")
  {
    const auto theta = sp3::angle{2 * sp3::pi};
    CHECK(theta.rad() == 2 * sp3::pi);
    CHECK(theta.deg() == sp3::real{360});
  }

  SECTION("three pi over two")
  {
    const auto theta = sp3::angle{3 * sp3::pi / 2};
    CHECK(theta.rad() == 3 * sp3::pi / 2);
    CHECK(theta.deg() == sp3::real{270});
  }
}

TEST_CASE("angle - constructing angle from degrees")
{
  using namespace sp3::literals;

  {
    const auto theta = sp3::angle{90_degrees};
    CHECK(theta.rad() == sp3::pi / 2);
    CHECK(theta.deg() == sp3::real{90});
  }

  {
    const auto theta = sp3::angle{0_degrees};
    CHECK(theta.rad() == 0);
    CHECK(theta.deg() == 0);
  }

  {
    const auto theta = sp3::angle{45.0_degrees};
    CHECK(theta.rad() == sp3::pi / 4);
    CHECK(theta.deg() == 45);
  }

  {
    const auto theta = sp3::angle{720_degrees};
    CHECK(theta.rad() == 4 * sp3::pi);
    CHECK(theta.deg() == 720);
  }

  {
    const auto theta = sp3::angle{-90_degrees};
    CHECK(theta.rad() == -sp3::pi / 2);
    CHECK(theta.deg() == sp3::real{-90});
  }
}