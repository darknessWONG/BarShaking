#include "stdafx.h"
#include "FlashLight.h"
#include "config.h"


FlashLight::FlashLight()
{
	set_member();
}

FlashLight::FlashLight(int rel_x, int rel_y, double width, double radin)
{
	set_member(rel_x, rel_y, width, radin);
}

FlashLight::FlashLight(int rel_x, int rel_y, double width, double radin, int line_num, int colum_num)
{
	set_member(rel_x, rel_y, width, radin, line_num, colum_num);
}


FlashLight::~FlashLight()
{
}

Line * FlashLight::get_line_left(void)
{
	return line_left;
}

Line * FlashLight::get_line_right(void)
{
	return line_right;
}

double FlashLight::get_radin(void)
{
	return radin;
}

void FlashLight::set_radin(double radin)
{
	this->radin = radin;
}

double FlashLight::get_width(void)
{
	return width;
}

void FlashLight::set_width(double width)
{
	this->width = width;
}

int FlashLight::get_rel_x(void)
{
	return rel_x;
}

void FlashLight::set_rel_x(int rel_x)
{
	this->rel_x = rel_x;
}

int FlashLight::get_rel_y(void)
{
	return rel_y;
}

void FlashLight::set_rel_y(int rel_y)
{
	this->rel_y = rel_y;
}

int FlashLight::get_line_num(void)
{
	return line_num;
}

void FlashLight::set_line_num(int line_num)
{
	this->line_num = line_num;
}

int FlashLight::get_colum_num(void)
{
	return colum_num;
}

void FlashLight::set_colum_num(int colum_num)
{
	this->colum_num = colum_num;
}

Shape * FlashLight::get_shape(void)
{
	return shape;
}

void FlashLight::cal_lines(void)
{
	delete_line_left();
	delete_line_right();

	line_left = new Line(rel_x, rel_y, radin);
	line_left->cal_equations_from_radin();
	line_right = new Line(rel_x, rel_y, radin + width);
	line_right->cal_equations_from_radin();

}

void FlashLight::cal_shape(void)
{
	cal_lines();

	delete_shape();
	
	char *map = new_map(line_num * colum_num, ' ');
	short *color_map = new_color_map(line_num * colum_num, 255);

	for (int i = 0; i < line_num; i++)
	{
		for (int j = 0; j < colum_num; j++)
		{
			if(check_point_in_area(j, i))
			{
				color_map[i * colum_num + j] = 7;
			}
		}
	}

	shape = new Shape(line_num, colum_num, map, color_map, 0, 0);
}

void FlashLight::set_member(int rel_x, int rel_y, double width, double radin, int line_num, int colum_num)
{
	this->rel_x = rel_x;
	this->rel_y = rel_y;
	this->width = width;
	this->radin = radin;

	this->line_num = line_num;
	this->colum_num = colum_num;
}

bool FlashLight::check_point_in_area(int x, int y)
{
	if ((line_left->get_a() < 0 && line_left->check_point(x, y) >= 0)
		|| (line_left->get_a() > 0 && line_left->check_point(x, y) <= 0))
	{
		if ((line_right->get_a() < 0 && line_right->check_point(x, y) <= 0)
			|| (line_right->get_a() > 0 && line_right->check_point(x, y) >= 0))
		{
			return true;
		}
	}
	return false;
}

void FlashLight::delete_shape(void)
{
	if (shape != 0)
	{
		delete shape;
		shape = 0;
	}
}

void FlashLight::delete_line_left(void)
{
	if (line_left != 0)
	{
		delete line_left;
		line_left = 0;
	}
}

void FlashLight::delete_line_right(void)
{
	if (line_right != 0)
	{
		delete line_right;
		line_right = 0;
	}
}
