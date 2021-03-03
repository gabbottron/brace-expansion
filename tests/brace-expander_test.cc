#include "gtest/gtest.h"
#include "src/lib/brace-expander.h"

TEST(AdderShould, ReturnReturnSum) {
  int expected = 13;
  int actual = add(7, 6);
  ASSERT_EQ(expected, actual);
}
