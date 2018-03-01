#include "stdafx.h"
#include "Shadow.h"

Shadow::Shadow(int x1, int y1, int x2, int y2)
	:line(x1, y1, x2, y2)
{
	set_member();
}

Shadow::Shadow(int x1, int y1, int x2, int y2, int line_num, int column_num)
	:line(x1, y1, x2, y2)
{
	set_member(line_num, column_num);
}

Shadow::Shadow(const Line &li)
	: line(li)
{
	set_member();
}

Shadow::Shadow(const Line &li, int line_num, int column_num)
	:line(li)
{
	set_member(line_num, column_num);
}


Shadow::~Shadow()
{
	delete_shape();
}

int Shadow::get_line_num(void)
{
	return line_num;
}

void Shadow::set_line_num(int line_num)
{
	this->line_num = line_num;
}

int Shadow::get_colum_num(void)
{
	return colum_num;
}

void Shadow::get_colum_num(int colum_num)
{
	this->colum_num = colum_num;
}

Line Shadow::get_line(void)
{
	return line;
}

Shape * Shadow::get_shape(void)
{
	//cal_final();
	return shape;
}

void Shadow::delete_shape(void)
{
	if (shape != 0)
	{
		delete shape;
		shape = 0;
	}
}

void Shadow::cal_shape(FlashLight * light)
{
	line.cal_equations_from_point();
	//delete_shape();
	

	char *map = new_map(line_num * colum_num, ' ');
	short *color_map = new_color_map(line_num * colum_num, 255);
	if (shape != 0)
	{
		for (int i = 0; i < line_num * colum_num; i++)
		{
			map[i] = shape->get_map()[i];
			color_map[i] = shape->get_color_map()[i];
		}
	}

	Point* point_left = line.check_intersect(*light->get_line_left());
	Point* point_right = line.check_intersect(*light->get_line_right());

	Intersect_status intersect_status = cal_intersect_status(*point_left, *point_right, line);
	Point light_point(light->get_rel_x(), light->get_rel_y());
	Position_relation position_relation = cal_position_relation(light_point, line);

	Line tangent_left(light->get_rel_x(), light->get_rel_y(), line.get_x1(), line.get_y1());
	tangent_left.cal_equations_from_point();
	Line tangent_right(light->get_rel_x(), light->get_rel_y(), line.get_x2(), line.get_y2());
	tangent_right.cal_equations_from_point();

	bool is_shadow = false;

	for (int i = line.get_y2(); i < line_num; i++)
	{
		for (int j = 0; j < colum_num; j++)
		{
			is_shadow = false;
			if (j >= line.get_x1() && j <= line.get_x2() && i == line.get_y1())
			{
				color_map[i * colum_num + j] = 4;
			}
			else if(light->get_shape()->get_color_map()[i * colum_num + j] == LIGHT_COLOR)
			{
				//shape->get_color_map()[i * colum_num + j] = UNCLEAR_COLOR;
				if (intersect_status == Intersect_status::cover)
				{
					if (position_relation == Position_relation::outside_right 
						&& tangent_left.check_point(j, i) > 0 && tangent_right.check_point(j, i) < 0)
					{
						is_shadow = true;
					}
					else if (position_relation == Position_relation::outside_left
						&& tangent_left.check_point(j, i) < 0 && tangent_right.check_point(j, i) > 0)
					{
						is_shadow = true;
					}
					else if (position_relation == Position_relation::middle
						&& tangent_left.check_point(j, i) > 0 && tangent_right.check_point(j, i) > 0)
					{
						is_shadow = true;
					}
				}
				else if (intersect_status == Intersect_status::right_half_block)
				{
					if (position_relation == Position_relation::outside_left
						&& tangent_left.check_point(j, i) < 0 && i > line.get_y1())
					{
						is_shadow = true;
					}
					else if((position_relation == Position_relation::outside_right || position_relation == Position_relation::middle)
						&& tangent_left.check_point(j, i) > 0 && i > line.get_y1())
					{
						is_shadow = true;
					}
				}
				else if (intersect_status == Intersect_status::left_half_block)
				{
					if (position_relation == Position_relation::outside_right
						&& tangent_right.check_point(j, i) < 0 && i > line.get_y1())
					{
						is_shadow = true;
					}
					else if ((position_relation == Position_relation::outside_left || position_relation == Position_relation::middle)
						&& tangent_right.check_point(j, i) > 0 && i > line.get_y1())
					{
						is_shadow = true;
					}
				}
				else if (intersect_status == Intersect_status::blocked)
				{
					if (i > line.get_y1())
					{
						is_shadow = true;
					}
				}
				if (!is_shadow)
				{
					color_map[i * colum_num + j] = UNCLEAR_COLOR;
				}
				else
				{
					if (shape == 0 || shape->get_color_map()[i * colum_num + j] != UNCLEAR_COLOR)
					{
						color_map[i * colum_num + j] = SHADOW_COLOR;
					}
				}
			}
		}
	}

	if (shape == 0)
	{
		shape = new Shape(line_num, colum_num, map, color_map, 0, 0);
	}
	else
	{
		shape->set_map_with_delte(map, color_map, line_num, colum_num);
	}

	delete point_left;
	delete point_right;
}

void Shadow::cal_shape(void)
{
	char *map = new_map(line.get_x2() - line.get_x1() + 1, ' ');
	short *color_map = new_color_map(line.get_x2() - line.get_x1() + 1, 4);
	if (shape == 0)
	{
		shape = new Shape(1, line.get_x2() - line.get_x1() + 1, map, color_map, line.get_x1(), line.get_y1());
	}
	else
	{
		shape->set_map_with_delte(map, color_map, 1, line.get_x2() - line.get_x1() + 1);
		shape->set_rel_posX(line.get_x1());
		shape->set_rel_posY(line.get_y2());
	}
}

void Shadow::cal_shape_with_delete(FlashLight * light)
{
	//line.cal_equations_from_point();
	delete_shape();

	cal_shape(light);
	//char *map = new_map(line_num * colum_num, ' ');
	//short *color_map = new_color_map(line_num * colum_num, 255);

	//Point* point_left = line.check_intersect(*light->get_line_left());
	//Point* point_right = line.check_intersect(*light->get_line_right());

	//Intersect_status intersect_status = cal_intersect_status(*point_left, *point_right, line);
	//Point light_point(light->get_rel_x(), light->get_rel_y());
	//Position_relation position_relation = cal_position_relation(light_point, line);

	//Line tangent_left(light->get_rel_x(), light->get_rel_y(), line.get_x1(), line.get_y1());
	//tangent_left.cal_equations_from_point();
	//Line tangent_right(light->get_rel_x(), light->get_rel_y(), line.get_x2(), line.get_y2());
	//tangent_right.cal_equations_from_point();

	//bool is_shadow = false;

	//for (int i = line.get_y2(); i < line_num; i++)
	//{
	//	for (int j = 0; j < colum_num; j++)
	//	{
	//		is_shadow = false;
	//		if (j >= line.get_x1() && j <= line.get_x2() && i == line.get_y1())
	//		{
	//			color_map[i * colum_num + j] = 4;
	//		}
	//		else if (light->get_shape()->get_color_map()[i * colum_num + j] == LIGHT_COLOR)
	//		{

	//			if (intersect_status == Intersect_status::cover)
	//			{
	//				if (position_relation == Position_relation::outside_right
	//					&& tangent_left.check_point(j, i) > 0 && tangent_right.check_point(j, i) < 0)
	//				{
	//					//color_map[i * colum_num + j] = 0;
	//					is_shadow = true;
	//				}
	//				else if (position_relation == Position_relation::outside_left
	//					&& tangent_left.check_point(j, i) < 0 && tangent_right.check_point(j, i) > 0)
	//				{
	//					is_shadow = true;
	//				}
	//				else if (position_relation == Position_relation::middle
	//					&& tangent_left.check_point(j, i) > 0 && tangent_right.check_point(j, i) > 0)
	//				{
	//					is_shadow = true;
	//				}
	//			}
	//			if (intersect_status == Intersect_status::right_half_block)
	//			{
	//				if (position_relation == Position_relation::outside_left
	//					&& tangent_left.check_point(j, i) < 0 && i > line.get_y1())
	//				{
	//					is_shadow = true;
	//				}
	//				else if ((position_relation == Position_relation::outside_right || position_relation == Position_relation::middle)
	//					&& tangent_left.check_point(j, i) > 0 && i > line.get_y1())
	//				{
	//					is_shadow = true;
	//				}
	//			}
	//			if (intersect_status == Intersect_status::left_half_block)
	//			{
	//				if (position_relation == Position_relation::outside_right
	//					&& tangent_right.check_point(j, i) < 0 && i > line.get_y1())
	//				{
	//					is_shadow = true;
	//				}
	//				else if ((position_relation == Position_relation::outside_left || position_relation == Position_relation::middle)
	//					&& tangent_right.check_point(j, i) > 0 && i > line.get_y1())
	//				{
	//					is_shadow = true;
	//				}
	//			}
	//			if (intersect_status == Intersect_status::blocked)
	//			{
	//				if (i > line.get_y1())
	//				{
	//					is_shadow = true;
	//				}
	//			}
	//			if (!is_shadow)
	//			{
	//				color_map[i * colum_num + j] = UNCLEAR_COLOR;
	//			}
	//			else
	//			{

	//				color_map[i * colum_num + j] = SHADOW_COLOR;
	//			}
	//		}
	//	}
	//}

	//shape = new Shape(line_num, colum_num, map, color_map, 0, 0);

	//delete point_left;
	//delete point_right;
}

void Shadow::cal_final(void)
{
	for (int i = 0; i < line_num * colum_num; i++)
	{
		if (shape->get_color_map()[i] == UNCLEAR_COLOR)
		{
			shape->get_color_map()[i] = VOID_COLOR;
		}
	}
}

void Shadow::set_member(int line_num, int colum_num)
{
	this->line_num = line_num;
	this->colum_num = colum_num;
}

Intersect_status Shadow::cal_intersect_status(Point point_left, Point point_right, Line line)
{
	if (point_left.get_x() >= line.get_x1() && point_right.get_x() <= line.get_x2())
	{
		return Intersect_status::blocked;
	}
	if ((point_left.get_x() < line.get_x1() && point_right.get_x() < line.get_x1())
		|| (point_left.get_x() > line.get_x2() && point_right.get_x() > line.get_x2()))
	{
		return Intersect_status::no_intersect;
	}
	if (point_left.get_x() < line.get_x1() && point_right.get_x() > line.get_x2())
	{
		return Intersect_status::cover;
	}
	if (point_left.get_x() < line.get_x1() && point_right.get_x() >= line.get_x1() && point_right.get_x() <= line.get_x2())
	{
		return Intersect_status::right_half_block;
	}
	if (point_right.get_x() > line.get_x2() && point_left.get_x() >= line.get_x1() && point_left.get_x() <= line.get_x2())
	{
		return Intersect_status::left_half_block;
	}
}

Position_relation Shadow::cal_position_relation(Point point, Line line)
{
	if (point.get_x() >= line.get_x1() && point.get_x() <= line.get_x2())
	{
		return Position_relation::middle;
	}
	if (point.get_x() < line.get_x1())
	{
		return Position_relation::outside_left;
	}
	if (point.get_x() > line.get_x2())
	{
		return Position_relation::outside_right;
	}
}
