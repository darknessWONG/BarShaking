#include "stdafx.h"
#include "Bar.h"


Bar::Bar(Shape * base_shape)
{
	set_member(base_shape);
}

Bar::Bar(Shape * base_shape, int center_x, int center_y)
{
	set_member(base_shape, center_x, center_y);
}

Bar::~Bar()
{
}

int Bar::get_center_x(void)
{
	return center_x;
}

void Bar::set_center_x(int center_x)
{
	this->center_x = center_x;
}

int Bar::get_center_y(void)
{
	return center_y;
}

void Bar::set_center_y(int center_y)
{
	this->center_y = center_y;
}

double Bar::get_radin(void)
{
	return radin;
}

void Bar::set_radin(double radin)
{
	this->radin = radin;
}

Shape * Bar::get_now_shape(void)
{
	return now_shape;
}

Shape * Bar::get_base_shape(void)
{
	return base_shape;
}

void Bar::cal_now_shape(void)
{
	if (now_shape != 0)
	{
		delete now_shape;
		now_shape = 0;
	}

	char *map = new char[base_shape->get_line_num() * base_shape->get_colum_num()]{ ' ' };
	short *color_map = new short[base_shape->get_line_num() * base_shape->get_colum_num()]{ 4 };
	for (int i = 0; i < base_shape->get_line_num() * base_shape->get_colum_num(); i++)
	{
		map[i] = ' ';
		color_map[i] = 4;
	}
	for (int i = 0; i < base_shape->get_line_num(); i++)
	{
		for (int j = 0; j < base_shape->get_colum_num(); j++)
		{
			if (base_shape->get_map()[i * base_shape->get_colum_num() + j] != ' ')
			{
				double longg = sqrt(pow(i - center_x, 2) + pow(j - center_y, 2));
				double new_x = longg * sin(radin * 3.1415926) + j;
				double new_y = center_y - longg * cos(radin * 3.1415926);

				if ((new_x < 0 || new_x > base_shape->get_colum_num() - 1) || (new_y < 0 || new_y > base_shape->get_line_num()))
				{
					continue;
				}


				map[(int)new_y * base_shape->get_colum_num() + (int)new_x] = base_shape->get_map()[i * base_shape->get_colum_num() + j];
				color_map[(int)new_y * base_shape->get_colum_num() + (int)new_x] = base_shape->get_color_map()[i * base_shape->get_colum_num() + j];
			}
			/*	else
			{
			map[i * bar.get_colum_num() + j] = bar.get_map()[i * bar.get_colum_num() + j];
			color_map[i * bar.get_colum_num() + j] = bar.get_color_map()[i * bar.get_colum_num() + j];
			}*/
		}
	}

	now_shape = new Shape(base_shape->get_line_num(), base_shape->get_colum_num(), map, color_map, base_shape->get_rel_posX(), base_shape->get_rel_posY());

}

void Bar::set_member(Shape * base_shape, int center_x, int center_y, double radin)
{
	this->base_shape = base_shape;
	this->center_x = center_x;
	this->center_y = center_y;
	this->radin = radin;
}
