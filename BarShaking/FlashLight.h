#pragma once
#include "Shape.h"
#include "Line.h"

class FlashLight
{
public:
	FlashLight();
	~FlashLight();


private:
	void set_member(int rel_x, int rel_y, double width, double radin);

	Shape *shape = 0;
	Line *line_left = 0;
	Line *line_right = 0;
	double radin;
	double width;
	int rel_x;
	int rel_y;

};

