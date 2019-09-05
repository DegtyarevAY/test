#pragma once
#include "Shape.h"

class Helix : public Shape
{
private:

	double radius;
	double step;

public:

	Helix() = default;
	Helix(const Point& _center, double _radius, double _step) : Shape(_center),
		radius(_radius), step(_step) {};

	virtual Point get_point(double t) const override
	{
		return Point(radius * t * cos(t), radius * t * sin(t), step * t);
	}

	virtual Vector get_derivative(double t) const override
	{
		return Vector(radius*(cos(t) - t * sin(t)), radius*(sin(t) + t * cos(t)), step);
	}

	double get_radius() { return radius; }
	double get_step() { return step; }

	virtual ~Helix() {};
};