#include <catch2/catch_test_macros.hpp>

#include "sp3/axes.h"
#include "sp3/transform.h"

TEST_CASE("transform - the default transform is the identity transform")
{
  const auto T = sp3::transform{};
  const auto p = sp3::point{-1, 2, 0.3};
  CHECK(T(p) == p);
}

TEST_CASE("transform - scale-only transform")
{
  const auto p = sp3::point{-1, 2, 0.3};
  {
    const sp3::real scale = 2;
    const auto T = sp3::transform{{}, {}, scale};
    const auto two_p = sp3::point{-2, 4, 0.6};
    CHECK(T(p) == two_p);
  }

  {
    const sp3::real scale = -1;
    const auto T = sp3::transform{{}, {}, scale};
    const auto minus_p = sp3::point{1, -2, -0.3};
    CHECK(T(p) == minus_p);
  }
}

TEST_CASE("transform - translation-only transform")
{
  const auto p = sp3::point{-1, 2, 0.3};
  {
    const auto t = sp3::vector{1, -2, 3};
    const auto T = sp3::transform{t, {}};
    CHECK(T(p) == p+t);
  }

  SECTION("transform - composition of translation-only transforms")
  {
    const auto t1 = sp3::vector{1, -2, 3};
    const auto T1 = sp3::transform{t1, {}};

    const auto t2 = sp3::vector{-12, 17, 0.01};
    const auto T2 = sp3::transform{t2, {}};

    const auto O = sp3::point{0, 0, 0};

    const auto result = (T1*T2)(O);
    const auto expected = O + (t1 + t2);

    CHECK(result == expected);
  }
}

TEST_CASE("transform - translation, rotation, and scale transform")
{
  const auto t = sp3::vector{-1, -1, 1};
  const auto r = sp3::rotation{sp3::yhat, sp3::angle{-sp3::pi/3}}; // 60 degree ccw rotation about y_hat
  const auto s = sp3::real{1.7};

  const auto T = sp3::transform{t, r, s};

  {
    // see Listing 10.4 in Computer Graphics from Scratch
    const auto p = sp3::point{1, -2, 0.3};

    const auto scaled = s * p;
    const auto rotated = r(scaled);
    const auto translated = rotated + t;

    CHECK(T(p) == translated);
  }
}