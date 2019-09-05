#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <algorithm>
#include <typeinfo>
#include <typeindex>
#include <memory>

struct Point
{
	double x, y, z;
	Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};
};

struct Vector
{
	double x, y, z;
	Vector(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};
};


class Shape
{
private:

	Point center;

public:
	Shape(const Point& _center) : center(_center) {};

	virtual Point get_point(double t) const = 0;
	virtual Vector get_derivative(double t) const = 0;

	virtual ~Shape() {};
};