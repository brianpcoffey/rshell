#include "gtest/gtest.h"

//#include "append_test.hpp"
#include "bracket_parse_test.hpp"
//#include "input_parse_test.hpp"
//#include "output_parse_test.hpp"
#include "paren_parse_test.hpp"
#include "parse_test.hpp"
//#include "pipes_test.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}