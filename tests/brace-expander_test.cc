#include "gtest/gtest.h"
#include "src/lib/brace-expander.h"
#include <string>

// BEGIN INVALID INPUT --------------------

// INVALID: A disallowed character in input
TEST(TestInputValidation, DetectsBadInputChar) {
  bool did_throw = false;

  try {
    BraceExpandr be("A%F");
  } catch(std::exception& e) {
    did_throw = true;
  }

  ASSERT_EQ(did_throw, true);
}

// INVALID: Opens with closing brace
TEST(TestInputValidation, DetectsInvalidClosingBrace) {
  bool did_throw = false;

  try {
    BraceExpandr be("}ABC");
  } catch(std::exception& e) {
    did_throw = true;
  }

  ASSERT_EQ(did_throw, true);
}

// INVALID: Empty braces in input
TEST(TestInputValidation, DetectsEmptyBraces) {
  bool did_throw = false;

  try {
    BraceExpandr be("{}");
  } catch(std::exception& e) {
    did_throw = true;
  }

  ASSERT_EQ(did_throw, true);
}

// INVALID: Braces close then open
TEST(TestInputValidation, DetectsMalformedBraces) {
  bool did_throw = false;

  try {
    BraceExpandr be("}{");
  } catch(std::exception& e) {
    did_throw = true;
  }

  ASSERT_EQ(did_throw, true);
}

// INVALID: Commas present outside of braces
TEST(TestInputValidation, DetectsCommaOutsideBraces) {
  bool did_throw = false;

  try {
    BraceExpandr be("A,B,C");
  } catch(std::exception& e) {
    did_throw = true;
  }

  ASSERT_EQ(did_throw, true);
}

// INVALID: First opening brace not closed in statement
TEST(TestInputValidation, DetectsUnclosedBrace) {
  bool did_throw = false;

  try {
    BraceExpandr be("{A{B,C}");
  } catch(std::exception& e) {
    did_throw = true;
  }

  ASSERT_EQ(did_throw, true);
}

// INVALID: Comma followed by non letter character
TEST(TestInputValidation, DetectsCommaWithNoFollowingLetter) {
  bool did_throw = false;

  try {
    BraceExpandr be("{A,}");
  } catch(std::exception& e) {
    did_throw = true;
  }

  ASSERT_EQ(did_throw, true);
}

// BEGIN VALID INPUT ----------------------

// VALID: A simple valid input test case
TEST(TestInputValidation, DetectsValidInput) {
  bool did_throw = false;

  try {
    BraceExpandr be("AF");
  } catch(std::exception& e) {
    did_throw = true;
  }

  ASSERT_EQ(did_throw, false);
}

std::string results_tests[6][2] = {
  {"{A,B}{C,D}", "AC AD BC BD"},
  {"{A,B}{C,D}{E,F}", "ACE ACF ADE ADF BCE BCF BDE BDF"},
  {"{{A,B}C,D}", "AC BC D"},
  {"{A,B{C,D}}", "A BC BD"},
  {"{{A,B}C{D,E}}", "ACD ACE BCD BCE"},
  {"{X,F{A,B}X{C,D}}", "X FAXC FAXD FBXC FBXD"}
};

// VALID: Tests the results of the first test case in results_tests
TEST(TestResultValues, ProducesCorrectValueForTest1) {
  bool did_throw = false;
  std::string result;

  try {
    BraceExpandr be(results_tests[0][0]);
    result = be.getExpandedStatement();
  } catch(std::exception& e) {
    did_throw = true;
  }

  ASSERT_EQ(did_throw, false);
  ASSERT_EQ(result, results_tests[0][1]);
}

// VALID: Tests the results of the first test case in results_tests
TEST(TestResultValues, ProducesCorrectValueForTest2) {
  bool did_throw = false;
  std::string result;

  try {
    BraceExpandr be(results_tests[1][0]);
    result = be.getExpandedStatement();
  } catch(std::exception& e) {
    did_throw = true;
  }

  ASSERT_EQ(did_throw, false);
  ASSERT_EQ(result, results_tests[1][1]);
}

// VALID: Tests the results of the first test case in results_tests
TEST(TestResultValues, ProducesCorrectValueForTest3) {
  bool did_throw = false;
  std::string result;

  try {
    BraceExpandr be(results_tests[2][0]);
    result = be.getExpandedStatement();
  } catch(std::exception& e) {
    did_throw = true;
  }

  ASSERT_EQ(did_throw, false);
  ASSERT_EQ(result, results_tests[2][1]);
}

// VALID: Tests the results of the first test case in results_tests
TEST(TestResultValues, ProducesCorrectValueForTest4) {
  bool did_throw = false;
  std::string result;

  try {
    BraceExpandr be(results_tests[3][0]);
    result = be.getExpandedStatement();
  } catch(std::exception& e) {
    did_throw = true;
  }

  ASSERT_EQ(did_throw, false);
  ASSERT_EQ(result, results_tests[3][1]);
}

// VALID: Tests the results of the first test case in results_tests
TEST(TestResultValues, ProducesCorrectValueForTest5) {
  bool did_throw = false;
  std::string result;

  try {
    BraceExpandr be(results_tests[4][0]);
    result = be.getExpandedStatement();
  } catch(std::exception& e) {
    did_throw = true;
  }

  ASSERT_EQ(did_throw, false);
  ASSERT_EQ(result, results_tests[4][1]);
}

// VALID: Tests the results of the first test case in results_tests
TEST(TestResultValues, ProducesCorrectValueForTest6) {
  bool did_throw = false;
  std::string result;

  try {
    BraceExpandr be(results_tests[5][0]);
    result = be.getExpandedStatement();
  } catch(std::exception& e) {
    did_throw = true;
  }

  ASSERT_EQ(did_throw, false);
  ASSERT_EQ(result, results_tests[5][1]);
}
