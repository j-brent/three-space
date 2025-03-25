#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "sp3/real.h"
#include "sp3/vector.h"

constexpr auto eps = std::numeric_limits<sp3::real>::epsilon();

TEST_CASE("vector - default vector is the origin")
{
  const sp3::vector v;
  CHECK(v.x == 0);
  CHECK(v.y == 0);
  CHECK(v.z == 0);
}

TEST_CASE("vector - construct from coordinates")
{
  const sp3::vector v{-1, 2, 0.3};
  CHECK(v.x == -1);
  CHECK(v.y == 2);
  CHECK(v.z == static_cast<sp3::real>(0.3));
}

TEST_CASE("vector - equality comparison")
{
  const sp3::vector v{-1, 2, 0.3};
  
  SECTION("equal to self")
  {
    CHECK(v == v);
  }
  
  SECTION("equal to copy of self")
  {
    const auto v2 = v;
    CHECK(v2 == v);
  }
  
  SECTION("not equal ")
  {
    const sp3::vector u{1, 2, 0.3};

    CHECK(v != u);
    CHECK(!(v == u));

    CHECK(u == u);
    CHECK(!(u != u));
  }
}

TEST_CASE("vector - vector arithmetic")
{
  SECTION("addition and subtraction")
  {

    const sp3::vector a{-1, 2, 0};
    const sp3::vector b{11, 8, 10};
    const sp3::vector c{10, 10, 10};
    
    CHECK(a + b == c);
    CHECK(c - b == a);
  }

  SECTION("the origin is the identity element")
  {
    const sp3::vector O{0, 0, 0};
    const sp3::vector a{1, -2, 0.3};
    const sp3::vector minus_a{-1, 2, -0.3};

    CHECK(O + a == a);
    CHECK(O - a == minus_a);
  }

  SECTION("unary minus")
  {
    const sp3::vector a{1, -2, 0.3};
    const sp3::vector minus_a{-1, 2, -0.3};
    CHECK(-a == minus_a);
  }

  SECTION("scalar multiplication and division")
  {
    const sp3::vector a{1, -2, 0.3};
    const sp3::vector minus_a{-1, 2, -0.3};
    const sp3::vector two_a{2, -4, 0.6};

    CHECK(1*a == a);
    CHECK(-1*a == minus_a);
    CHECK(2*a == two_a);
    CHECK(two_a/2 == a);
  }
}

TEST_CASE("vector - dot product and norm")
{
  SECTION("dot product")
  {
    const sp3::vector v{1, 2, 3};
    const sp3::vector u{3, 2, 1};
    const sp3::real v_dot_u{3 + 4 + 3};
    
    CHECK(sp3::dot(v,u) == v_dot_u);
    CHECK(sp3::dot(v,u) == sp3::dot(u,v));
  }
  
  SECTION("norm")
  {
    const sp3::vector v{1, 2, 3};
    const sp3::real norm_v = std::sqrt(14); 

    constexpr float eps = std::numeric_limits<float>::epsilon();
    REQUIRE_THAT(sp3::norm(v), Catch::Matchers::WithinRel(norm_v, eps));
    
    CHECK(norm(v) == norm(-v));
    
    const auto dot_norm = std::sqrt(dot(v, v));
    REQUIRE_THAT(sp3::norm(v), Catch::Matchers::WithinRel(dot_norm, eps));
  }
}

TEST_CASE("vector - cross product")
{
  SECTION("canonincal basis vectors")
  {
    const auto i = sp3::vector{1, 0, 0};
    const auto j = sp3::vector{0, 1, 0};
    const auto k = sp3::vector{0, 0, 1};
    
    CHECK(sp3::cross(i, j) == k);
    CHECK(sp3::cross(j, k) == i);
    CHECK(sp3::cross(k, i) == j);
    
    CHECK(sp3::cross(j, i) == -k);
    CHECK(sp3::cross(k, j) == -i);
    CHECK(sp3::cross(i, k) == -j);
  }

  SECTION("non-zero, non-canonical vectors")
  {
    const auto a = sp3::vector{1, -2, 3};
    const auto axa = sp3::cross(a, a);
    
    CHECK_THAT(axa.x, Catch::Matchers::WithinAbs(0, eps));
    CHECK_THAT(axa.y, Catch::Matchers::WithinAbs(0, eps));
    CHECK_THAT(axa.z, Catch::Matchers::WithinAbs(0, eps));
    
    const auto b = sp3::vector{4, -5, -6};
    const auto axb = sp3::cross(a, b);
    const auto bxa = sp3::cross(b, a);

    CHECK(axb == sp3::vector{27, 18, 3});
    CHECK(axb == -bxa);
  }
}