#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "sp3/real.h"
#include "sp3/unit_vector.h"

constexpr auto eps = std::numeric_limits<sp3::real>::epsilon();

TEST_CASE("unit_vector - initialization from elements")
{
  {
    const auto u = sp3::unit_vector{1, 1, 1};
    CHECK_THAT(length(u), Catch::Matchers::WithinRel(sp3::real{1}, eps));
    CHECK(u.x == u.y);
    CHECK(u.y == u.z);
  }
  
  {
    const auto u = sp3::unit_vector{-1, -1, -1};
    CHECK_THAT(length(u), Catch::Matchers::WithinRel(sp3::real{1}, eps));
    CHECK(u.x == u.y);
    CHECK(u.y == u.z);
  }
}

TEST_CASE("unit_vector - initialization from the zero vector")
{
  const auto u = sp3::unit_vector{0, 0, 0};
  CHECK(length(u) == 0);
  CHECK(u.x == 0);
  CHECK(u.y == 0);
  CHECK(u.z == 0);
}

TEST_CASE("unit_vector - orientation")
{
  const auto u = sp3::unit_vector{1, -1, 1};
  const auto mu = sp3::unit_vector{-1, 1, -1};
  CHECK(mu == -u);
}

TEST_CASE("unit_vector - adding unit vectors")
{
  {
    const auto u1 = sp3::unit_vector{1, 0, 0};
    const auto u2 = sp3::unit_vector{0, 1, 0};
    const auto v = u1 + u2;
    static_assert(std::is_same_v<decltype(v), const sp3::vector>);
    CHECK(v.x == sp3::real{1});
    CHECK(v.y == sp3::real{1});
    CHECK(v.z == sp3::real{0});
  }
}

TEST_CASE("unit_vector - scaling a unit vector")
{
  {
    const auto u = sp3::unit_vector{1, 1, 1};
    const auto v = u / (1/std::sqrt(3));
    static_assert(std::is_same_v<decltype(v), const sp3::vector>);
    CHECK_THAT(v.x, Catch::Matchers::WithinRel(sp3::real{1}, eps));
    CHECK_THAT(v.y, Catch::Matchers::WithinRel(sp3::real{1}, eps));
    CHECK_THAT(v.z, Catch::Matchers::WithinRel(sp3::real{1}, eps));
  }
  {
    const auto u = sp3::unit_vector{1, 1, 1};
    const auto v = u * std::sqrt(3);
    static_assert(std::is_same_v<decltype(v), const sp3::vector>);
    CHECK_THAT(v.x, Catch::Matchers::WithinRel(sp3::real{1}, eps));
    CHECK_THAT(v.y, Catch::Matchers::WithinRel(sp3::real{1}, eps));
    CHECK_THAT(v.z, Catch::Matchers::WithinRel(sp3::real{1}, eps));
  }
}
