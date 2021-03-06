#include "../headers/shape.h"
using cps::Shape;
#include "../headers/spacer.h"
using cps::Spacer;
#include "catch.hpp"

#include <utility>
using std::make_pair;
using std::pair;

TEST_CASE(" testing spacer shape ") {
  auto current_point = make_pair(200, 200);
  double width = 100.0;
  double height = 110.0;
  auto correct_bound_box = pair<double, double>(width, height);
  SECTION(" testing constructors ") {
    auto test_spacer = Spacer(current_point, width, height);
    REQUIRE(correct_bound_box == test_spacer.getBoundBox());
  }
}
