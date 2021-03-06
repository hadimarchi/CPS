#include "../headers/consts.h"
using cps::RADIAN;
#include "../headers/shape.h"
using cps::Shape;
#include "../headers/polygon.h"
using cps::Polygon;
#include "../headers/consts.h"
using cps::DRAW_POLYGON;
#include <initializer_list>
using std::initializer_list;
#include <string>
using std::string;
using std::to_string;
#include <utility>
using std::make_pair;
using std::pair;
#include <math.h> // sin and ceil

#define PI 3.14159265

Polygon::Polygon(BoundBoxType bound_box, PointType current_point,
                 int number_sides, int side_length)
    : number_sides(number_sides), side_length(side_length),
      Shape(bound_box, current_point) {
  setStartingPoint();
}

void Polygon::rotate(int rotation_angle) {
  rotateStartingPoint(rotation_angle);
  rotateBoundBox(rotation_angle);
}

void Polygon::horizontal() {}

void Polygon::vertical(const initializer_list<Shape> &list) {}

string Polygon::toPostScript() {
  string ps_polygon = DRAW_POLYGON;
  ps_polygon.replace(ps_polygon.find(x_coord_str), x_coord_str.length(),
                     to_string(starting_point.first));
  ps_polygon.replace(ps_polygon.find(y_coord_str), y_coord_str.length(),
                     to_string(starting_point.second));
  ps_polygon.replace(ps_polygon.find(number_sides_str),
                     number_sides_str.length(), to_string(number_sides));
  ps_polygon.replace(ps_polygon.find(side_length_str), side_length_str.length(),
                     to_string(side_length));
  return ps_polygon;
}

bool Polygon::operator==(const Polygon &rhs) const {
  if (bound_box != rhs.bound_box || current_point != rhs.current_point ||
      number_sides != rhs.number_sides || side_length != rhs.side_length) {
    return false;
  }
  return true;
}

int Polygon::getNumberOfSides() { return number_sides; }
int Polygon::getSideLength() { return side_length; }

/* This function Takes the current_point and returns the Point from which to
   start drawing the Regular Polygon so that A side is always centered
   horizontally below the current point This Only works for non-Rotated Shapes*/
void Polygon::setStartingPoint() {
  double pi = 3.14159265;
  double apothem = (side_length / 2.0) / tan(pi / number_sides);

  starting_point.first = (int)(current_point.first - (side_length / 2.0));
  starting_point.second = (int)(current_point.second - apothem);
}
void Polygon::setCurrentPoint(PointType new_point) {
  current_point = new_point;
  setStartingPoint();
}
void Polygon::rotateStartingPoint(int angle) {
  double xs = starting_point.first;
  double ys = starting_point.second;

  double x = current_point.first;
  double y = current_point.second;

  double apothem = y - ys;
	double halfSide = x - xs;

	if (angle == 90) {
		starting_point.first = x + apothem;
		starting_point.second = y - halfSide;
	}
	else if (angle == 180) {
		starting_point.first = x - apothem;
		starting_point.second = y + halfSide;
	}
	else if (angle == 270) {
		starting_point.first = x + halfSide;
		starting_point.second = y + apothem;
	}
}

/*Polygon cps::getPolygon(Shape::PointType current_point,
                        int number_sides, int side_length) {
  auto denominator = sin(PI / double(number_sides));
  int radius = abs(ceil(double(side_length) / denominator));
  auto bound_box = make_pair(radius, radius);
  return Polygon(bound_box, current_point, number_sides, side_length);
}*/

/* This provide the correct Bounding Box for Regular Polygons that are not
rotated. I have tested this with drawing works in all cases (When the Bounding
Box is allowed to be a double) It comes from his hint in the assingments. Again
this may not match perfectly with an integer bounding box */
Shape::BoundBoxType cps::make_Bounding_Box(int number_sides, int side_length) {

  double pi = 3.14159265;
  double height;
  double width;

  if (number_sides % 2 == 1) {
    height = side_length * (1 + cos(pi / number_sides)) /
             (2 * sin(pi / number_sides));
    width = side_length * sin(pi * (number_sides) / (2 * number_sides)) /
            sin(pi / number_sides);
  }

  else if (number_sides % 2 == 0 && number_sides % 4 != 0) {
    height = side_length * cos(pi / number_sides) / sin(pi / number_sides);
    width = side_length / sin(pi / number_sides);
  }

  else {
    height = side_length * cos(pi / number_sides) / sin(pi / number_sides);
    width = side_length * cos(pi / number_sides) / sin(pi / number_sides);
  }
  auto box = make_pair(width, height);
  return box;
}

Polygon cps::getPolygon(Shape::PointType current_point, int number_sides,
                        int side_length) {

  auto bound_box = make_Bounding_Box(number_sides, side_length);
  return Polygon(bound_box, current_point, number_sides, side_length);
}
