#include "stdafx.h"
#include "Point.h"


Point::Point()
{
	set_member();
}

Point::Point(double x, double y)
{
	set_member(x, y);
}


Point::~Point()
{
}

double Point::get_x(void)
{
	return x;
}

void Point::set_x(double x)
{
	this->x = x;
}

double Point::get_y(void)
{
	return y;
}

void Point::set_y(double y)
{
	this->y = y;
}

void Point::set_member(double x, double y)
{
	this->x = x;
	this->y = y;
}
