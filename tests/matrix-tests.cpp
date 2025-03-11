#include <catch2/catch_test_macros.hpp>

#include "sp3/matrix.h"

TEST_CASE("matrix - default matrix all zeros")
{
  const sp3::matrix m;
  CHECK(m(0, 0) == sp3::real{0});
  CHECK(m(0, 1) == sp3::real{0});
  CHECK(m(0, 2) == sp3::real{0});
  CHECK(m(1, 0) == sp3::real{0});
  CHECK(m(1, 1) == sp3::real{0});
  CHECK(m(1, 2) == sp3::real{0});
  CHECK(m(2, 0) == sp3::real{0});
  CHECK(m(2, 1) == sp3::real{0});
  CHECK(m(2, 2) == sp3::real{0});
}

TEST_CASE("matrix - construct with values")
{
  const sp3::matrix m{{{
    {{1, 2, 3}},
    {{4, 5, 6}},
    {{7, 8, 9}}
  }}};

  CHECK(m(0, 0) == sp3::real{1});
  CHECK(m(0, 1) == sp3::real{2});
  CHECK(m(0, 2) == sp3::real{3});

  CHECK(m(1, 0) == sp3::real{4});
  CHECK(m(1, 1) == sp3::real{5});
  CHECK(m(1, 2) == sp3::real{6});
  
  CHECK(m(2, 0) == sp3::real{7});
  CHECK(m(2, 1) == sp3::real{8});
  CHECK(m(2, 2) == sp3::real{9});
}

TEST_CASE("matrix - the identity matrix")
{
  const auto I = sp3::matrix::identity();

  CHECK(I(0, 0) == sp3::real{1});
  CHECK(I(0, 1) == sp3::real{0});
  CHECK(I(0, 2) == sp3::real{0});

  CHECK(I(1, 0) == sp3::real{0});
  CHECK(I(1, 1) == sp3::real{1});
  CHECK(I(1, 2) == sp3::real{0});
  
  CHECK(I(2, 0) == sp3::real{0});
  CHECK(I(2, 1) == sp3::real{0});
  CHECK(I(2, 2) == sp3::real{1});
}

TEST_CASE("matrix - matrix addition and subtraction")
{
  const sp3::matrix m{{{
    {{1, 2, 3}},
    {{4, 5, 6}},
    {{7, 8, 9}}
  }}};

  const sp3::matrix two_m{{{
    {{2, 4, 6}},
    {{8, 10, 12}},
    {{14, 16, 18}}
  }}};

  SECTION("addition")
  {
    const auto m_plus_m = m + m;

    CHECK(m_plus_m == two_m);
  }

  SECTION("subtraction")
  {
    const auto two_m_minus_m = two_m - m;
    CHECK(two_m_minus_m == m);
  }
}


TEST_CASE("matrix - matrix multiplication")
{
  const sp3::matrix m{{{
    {{1, 2, 3}},
    {{4, 5, 6}},
    {{7, 8, 9}}
  }}};

  const sp3::matrix m_times_m{{{
    {{30, 36, 42}},
    {{66, 81, 96}},
    {{102, 126, 150}}
  }}};

  CHECK(m*m == m_times_m);
}

TEST_CASE("matrix - scalar multiplication and division")
{
  const sp3::matrix m{{{
    {{1, 2, 3}},
    {{4, 5, 6}},
    {{7, 8, 9}}
  }}};

  const sp3::real s = 3;

  SECTION("multiplication")
  {
    const auto sm = s*m;

    CHECK(sm(0, 0) == s*1);
    CHECK(sm(0, 1) == s*2);
    CHECK(sm(0, 2) == s*3);

    CHECK(sm(1, 0) == s*4);
    CHECK(sm(1, 1) == s*5);
    CHECK(sm(1, 2) == s*6);

    CHECK(sm(2, 0) == s*7);
    CHECK(sm(2, 1) == s*8);
    CHECK(sm(2, 2) == s*9);
  }

  SECTION("division")
  {
    const auto ms = m / s;
    CHECK(ms(0, 0) == 1 / s);
    CHECK(ms(0, 1) == 2 / s);
    CHECK(ms(0, 2) == 3 / s);

    CHECK(ms(1, 0) == 4 / s);
    CHECK(ms(1, 1) == 5 / s);
    CHECK(ms(1, 2) == 6 / s);

    CHECK(ms(2, 0) == 7 / s);
    CHECK(ms(2, 1) == 8 / s);
    CHECK(ms(2, 2) == 9 / s);
  }
}

TEST_CASE("matrix - matrix transpose")
{
  const sp3::matrix m{{{
    {{1, 2, 3}},
    {{4, 5, 6}},
    {{7, 8, 9}}
  }}};

  const auto mT = sp3::transposed(m);

  CHECK(mT(0, 0) == sp3::real{1});
  CHECK(mT(0, 1) == sp3::real{4});
  CHECK(mT(0, 2) == sp3::real{7});

  CHECK(mT(1, 0) == sp3::real{2});
  CHECK(mT(1, 1) == sp3::real{5});
  CHECK(mT(1, 2) == sp3::real{8});
  
  CHECK(mT(2, 0) == sp3::real{3});
  CHECK(mT(2, 1) == sp3::real{6});
  CHECK(mT(2, 2) == sp3::real{9});
}