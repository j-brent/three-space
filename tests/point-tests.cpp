#include <catch2/catch_test_macros.hpp>

#include "sp3/point.h"

TEST_CASE("point - default point is the origin")
{
  const sp3::point pt;
  CHECK(pt.x == 0);
  CHECK(pt.y == 0);
  CHECK(pt.z == 0);
}

TEST_CASE("point - construct from coordinates")
{
  const sp3::point pt{-1, 2, 0.3};
  CHECK(pt.x == -1);
  CHECK(pt.y == 2);
  CHECK(pt.z == static_cast<sp3::real>(0.3));
}

TEST_CASE("point - comparison")
{
  const sp3::point pt{-1, 2, 0.3};

  SECTION("equal to self")
  {
    CHECK(pt == pt);
  }

  SECTION("equal to copy of self")
  {
    const auto pt2 = pt;
    CHECK(pt2 == pt);
  }

  SECTION("lexicographical ordering")
  {
    // a < b < c (lexicogpraphically)
    const sp3::point a{1, 2, 3};
    const sp3::point b{1, 2, 4};
    const sp3::point c{2, 2, 3};

    CHECK(a <= a);
    CHECK(a >= a);

    CHECK(a < b);
    CHECK(a <= b);
    CHECK(b > a);
    CHECK(b >= a);

    CHECK(b <= c);
    CHECK(b < c);
    CHECK(c > b);
    CHECK(c >= b);

    CHECK(a < c);
    CHECK(a <= c);
    CHECK(c > a);
    CHECK(c >= a);
  }

  SECTION("negation")
  {
    const sp3::point a{1, 2, 3};
    const sp3::point b{1, 2, 4};
    const sp3::point c{2, 2, 3};

    CHECK(a == a);
    CHECK(!(a != a));

    CHECK(a != b);
    CHECK(!(a == b));

    CHECK(a <= b);
    CHECK(!(b < a));

    CHECK(c >= b);
    CHECK(!(c < b));
  }
}