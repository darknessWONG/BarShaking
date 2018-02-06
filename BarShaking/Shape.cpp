#include "stdafx.h"
#include "Shape.h"


Shape::Shape()
{
	set_member();
}

Shape::Shape(int line_num, int colum_num, char* map, short* color_map, int rel_posX, int rel_posY)
{
	set_member(line_num, colum_num, map, color_map, rel_posX, rel_posY);
}

Shape::Shape(const Shape & shape)
{
	this->line_num = shape.line_num;
	this->colum_num = shape.colum_num;
	this->rel_posX = shape.rel_posX;
	this->rel_posY = shape.rel_posY;
	copy_maps(shape.map, shape.color_map);
}


Shape::~Shape()
{
	delete_maps();
}

char * Shape::paint(char * r_map, short * r_color_map, int line_num, int colum_num)
{
	for (int i = 0; i < get_line_num(); i++)
	{
		for (int j = 0; j < get_colum_num(); j++)
		{
			if (color_map[i * get_colum_num() + j] == 255)
			{
				continue;
			}

			int real_x = j + rel_posX;
			int real_y = i + rel_posY;
			r_map[real_y * colum_num + real_x] = map[i * get_colum_num() + j];
			r_color_map[real_y * colum_num + real_x] = color_map[i * get_colum_num() + j];
		}
	}
	return r_map;
}

Shape * Shape::get_shape_next(void)
{
	return shape_next;
}

void Shape::set_shape_next(Shape *prt)
{
	shape_next = prt;
}

int Shape::get_rel_posX(void)
{
	return rel_posX;
}

void Shape::set_rel_posX(int x)
{
	this->rel_posX = x;
}

int Shape::get_rel_posY(void)
{
	return rel_posY;
}

void Shape::set_rel_posY(int y)
{
	this->rel_posY = y;
}

int Shape::get_abs_posX(void)
{
	return abs_posX;
}

void Shape::set_abs_posX(int abs_posX)
{
	this->abs_posX = abs_posX;
}

int Shape::get_abs_posY(void)
{
	return abs_posY;
}

void Shape::set_abs_posY(int abs_posY)
{
	this->abs_posY = abs_posY;
}

int Shape::get_line_num(void)
{
	return line_num;
}

int Shape::get_colum_num(void)
{
	return colum_num;
}

char * Shape::get_map(void)
{
	return map;
}

void Shape::set_map(char* map, short* color_map, int line_num, int colum_num)
{
	this->map = map;
	this->color_map = color_map;
	this->line_num = line_num;
	this->colum_num = colum_num;
}

void Shape::set_map_with_delte(char* map, short* color_map, int line_num, int colum_num)
{
	delete_maps();
	this->map = map;
	this->color_map = color_map;
	this->line_num = line_num;
	this->colum_num = colum_num;
}

short * Shape::get_color_map(void)
{
	return color_map;
}

void Shape::delete_maps(void)
{
	if (map != 0)
	{
		delete map;
		map = 0;
	}
	if (color_map != 0)
	{
		delete[] color_map;
		color_map = 0;
	}
}

void Shape::clean_next(void)
{
	shape_next = 0;
}

void Shape::set_member(int line_num, int colum_num, char * map, short * color_map, int rel_posX, int rel_posY)
{
	this->line_num = line_num;
	this->colum_num = colum_num;
	this->map = map;
	this->color_map = color_map;
	this->rel_posX = rel_posX;
	this->rel_posY;

	shape_next = 0;
}

void Shape::copy_maps(char * map, short * color_map)
{
	delete_maps();
	if (map != 0 && color_map != 0)
	{
		this->map = new char[line_num * colum_num];
		this->color_map = new short[line_num * colum_num];

		for (int i = 0; i < line_num * colum_num; i++)
		{
			this->map[i] = map[i];
			this->color_map[i] = color_map[i];
		}
	}
}
