#pragma once
#include "Shape.h"

class Circle : public Shape
{
private:

	double radius;

public:

	Circle() = default;
	Circle(const Point& _center, double _radius) : Shape(_center),
		radius(_radius) {};

	virtual Point get_point(double t) const override
	{
		return Point(radius * cos(t), radius * sin(t), 0);
	}

	virtual Vector get_derivative(double t) const override
	{
		return Vector(-1 * radius * sin(t), radius * cos(t), 0);
	}

	double get_radius() { return radius; }
	virtual ~Circle() {};
};