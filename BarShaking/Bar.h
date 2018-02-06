#pragma once
#include "Shape.h"

class Bar
{
public:
	Bar(Shape* base_shape);
	Bar(Shape* base_shape, int center_x, int center_y);
	~Bar();


	int get_center_x(void);
	void set_center_x(int);
	int get_center_y(void);
	void set_center_y(int);
	double get_radin(void);
	void set_radin(double);
	Shape *get_now_shape(void);

	void cal_now_shape(void);
private:
	void set_member(Shape *base_shape, int center_x = 0, int center_y = 0, double radin = 0);

	Shape *base_shape = 0;
	Shape *now_shape = 0;

	int center_x;
	int center_y;
	double radin; //ƒÎ‚Ì”{”‚¾‚¯‚Å‚¢‚¢

};

