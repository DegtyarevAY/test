#pragma once
#include "Shape.h"

class Ellipse : public Shape
{
private:

	double radius_x;
	double radius_y;

public:

	Ellipse() = default;
	Ellipse(const Point& _center, double _radius_x, double _radius_y) : Shape(_center),
		radius_x(_radius_x), radius_y(_radius_y) {};

	virtual Point get_point(double t) const override
	{
		return Point(radius_x * cos(t), radius_y * sin(t), 0);
	}

	virtual Vector get_derivative(double t) const override
	{
		return Vector(-1 * radius_x * sin(t), radius_y * cos(t), 0);
	}

	double get_radius_x() { return radius_x; }
	double get_radius_y() { return radius_y; }

	virtual ~Ellipse() {};
};
