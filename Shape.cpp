#include "Shape.h"


Rectangle::Rectangle(double length, double width) :length_{ length }, width_{ width }
{area_ = length_ * width_; }

Circle::Circle(double radius) : radius_{ radius }
{area_ = 3.1415926535 * radius_ * radius_;}