#include "gtest/gtest.h"
#include "src/lib/brace-expander.h"

TEST(BraceExpandrWithBadInput, ShouldThrow) {
  bool did_throw = false;

  try {
    BraceExpandr be("A%F");
  } catch(std::exception& e) {
    did_throw = true;
  }

  ASSERT_EQ(did_throw, true);
}

TEST(BraceExpandrWithValidInput, ShouldNotThrow) {
  bool did_throw = false;

  try {
    BraceExpandr be("AF");
  } catch(std::exception& e) {
    did_throw = true;
  }

  ASSERT_EQ(did_throw, false);
}


