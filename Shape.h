#ifndef _SHAPE_H_
#define _SHAPE_H_

class Shape
{
protected:
	double area_;
};

class Rectangle : public Shape
{
public:
	Rectangle(double length, double width);
	double GetArea() { return area_; }
protected:
	double width_, length_;
};

class Circle :public Shape
{
public:
	Circle(double radius);
	double GetArea() { return area_; }
protected:
	double radius_;

};

class Square :public Rectangle
{
public:
	Square(double length) :Rectangle(length, length) {}
};
#endif
