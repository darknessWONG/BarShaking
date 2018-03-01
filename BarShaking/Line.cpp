#include "stdafx.h"
#include "Line.h"
#include "config.h"


Line::Line()
{
	init_member();
}

Line::Line(int x1, int y1, int x2, int y2)
{
	init_member();
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;

	cal_equations_from_point();
}

Line::Line(int x1, int y1, double radin)
{
	init_member();
	this->x1 = x1;
	this->y1 = y1;
	this->radin = radin;

	cal_equations_from_radin();
}

Line::Line(const Line & li)
{
	a = li.a;
	b = li.b;
	x1 = li.x1;
	y1 = li.y1;
	x2 = li.x2;
	y2 = li.y2;
	radin = li.radin;
}


Line::~Line()
{
}

double Line::get_a(void)
{
	return a;
}

void Line::set_a(double a)
{
	this->a = a;
}

double Line::get_b(void)
{
	return b;
}

void Line::set_b(double b)
{
	this->b = b;
}

int Line::get_x1(void)
{
	return x1;
}

void Line::set_x1(int x1)
{
	this->x1 = x1;
}

int Line::get_y1(void)
{
	return y1;
}

void Line::set_y1(int y1)
{
	this->y1 = y1;
}

int Line::get_x2(void)
{
	return x2;
}

void Line::set_x2(int x2)
{
	this->x2 = x2;
}

int Line::get_y2(void)
{
	return y2;
}

void Line::set_y2(int y2)
{
	this->y2 = y2;
}

double Line::get_radin(void)
{
	return radin;
}

void Line::set_radin(double radin)
{
	this->radin = radin;
}

void Line::cal_equations_from_point()
{
	a = (double)(y1 - y2) / (x1 - x2);
	b = y2 - a * x2;
}

void Line::cal_equations_from_radin(void)
{
	//double new_radin = radin > 0.5 ? 1- radin : radin;
	double new_radin = radin;
	int symbol = radin > 0.5 ? -1 : 1;
	a = sin(new_radin * PAI) / cos(new_radin * PAI) * -1;
	b = abs(a) * x1 * symbol;
}

int Line::check_point(double x, double y)
{
	double new_y = a * x + b;
	if (y > new_y) return 1;
	if (y == new_y) return 0;
	if (y < new_y) return -1;
}

Point* Line::check_intersect(Line li)
{
	if (a == li.a)
	{
		return 0;
	}
	double new_x = (li.b - b) / (a - li.a);
	double new_y = a * new_x + b;


	return new Point(new_x, new_y);
}


void Line::init_member(void)
{
	a = 0.0f;
	b = 0.0f;
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
	radin = 0.0f;
}
