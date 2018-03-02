#include "stdafx.h"
#include "graph.h"


Graph::Graph()
{
}


Graph::~Graph()
{
}

Canvas * Graph::get_canv(void)
{
	return canv;
}

void Graph::set_canv(Canvas *canv)
{
	this->canv = canv;
}

int Graph::get_line_num(void)
{
	return line_num;
}

void Graph::set_line_num(int line_num)
{
	this->line_num = line_num;
}

int Graph::get_colum_num(void)
{
	return colum_num;
}

void Graph::set_colum_num(int colum_num)
{
	this->colum_num = colum_num;
}

Shape * Graph::get_player(void)
{
	return player;
}

void Graph::set_player(Shape *player)
{
	this->player = player;
}

void Graph::clean_player(void)
{
	if (player != 0)
	{
		player = 0;
	}
}

FlashLight ** Graph::get_lights(void)
{
	return lights;
}

void Graph::add_light(FlashLight *light)
{
	FlashLight **tmp = new FlashLight*[++light_num];
	for (int i = 0; i < light_num - 1; i++)
	{
		tmp[i] = lights[i];
	}
	tmp[light_num - 1] = light;
	delete[] lights;
	lights = tmp;
}

void Graph::clean_lights(void)
{
	if (lights != 0)
	{
		delete[] lights;
		lights = 0;
		light_num = 0;
	}
}

Shadow ** Graph::get_shadows(void)
{
	return shadows;
}

void Graph::add_shadow(Shadow *shadow)
{
	Shadow **tmp = new Shadow*[++shadow_num];
	
	for (int i = 0; i < shadow_num - 1; i++)
	{
		tmp[i] = shadows[i];
	}
	tmp[shadow_num - 1] = shadow;
	delete[] shadows;
	shadows = tmp;
}

void Graph::clean_shadows(void)
{
	if (shadows != 0)
	{
		delete[] shadows;
		shadows = 0;
		shadow_num = 0;
	}
}

Shape * Graph::get_background(void)
{
	return background;
}

void Graph::clean_background(void)
{
	if (background != 0)
	{
		delete background;
		background = 0;
	}
}

void Graph::clean_shape(void)
{
	clean_lights();
	clean_shadows();
	clean_player();
}

void Graph::clean_up(void)
{
	canv->clean_shap_list();
	canv->clean_map();

	clean_shape();
	clean_background();
}

void Graph::cal_background(void)
{
	clean_background();

	int passageway_num = shadow_num + 1;
	if (shadows[0]->get_line().get_x1() <= 0)
	{
		passageway_num--;
	}
	if (shadows[shadow_num - 1]->get_line().get_x2() >= colum_num)
	{
		passageway_num--;
	}
	Line **passageway = cal_passway();

	char* map = new_map(line_num * colum_num, ' ');
	short* color_map = new_color_map(line_num * colum_num, 255);

	int top_line_y = 10000;
	for (int i = 0; i < shadow_num; i++)
	{
		shadows[i]->get_line().cal_equations_from_point();
		if (shadows[i]->get_line().get_y2() < top_line_y)
		{
			top_line_y = shadows[i]->get_line().get_y2();
		}
	}
	for (int i = 0; i < light_num; i++)
	{
		lights[i]->cal_lines();
	}

	for (int i = 0; i < line_num; i++)
	{
		for (int j = 0; j < colum_num; j++)
		{
			Point_status p_status = Point_status::normal;
			for (int k = 0; k < light_num; k++)
			{
				if (lights[k]->check_point_in_area(j, i))
				{
					if (i <= top_line_y)
					{
						p_status = Point_status::light;
						break;
					}
					else
					{

						Line tmp_line(lights[k]->get_rel_x(), lights[k]->get_rel_y(), j, i);
						//for (int l = 0; l < shadow_num; l++)
						for (int l = 0; l < passageway_num; l++)
						{
							if (tmp_line.get_a() == passageway[l]->get_a())
							{
								continue;
							}
							Point *tmp_point = passageway[l]->check_intersect(tmp_line);
							if (cal_position_relation(*tmp_point, *passageway[l]) == Position_relation::middle)
							{
								p_status = Point_status::light;
								delete tmp_point;
								break;
							}
							delete tmp_point;
						}
					}
				}
				if (p_status == Point_status::light)
				{
					break;
				}
			}
			if (p_status == Point_status::light)
			{
				color_map[i * colum_num + j] = LIGHT_COLOR;
			}
			else if(p_status == Point_status::shadow)
			{
				color_map[i * colum_num + j] = SHADOW_COLOR;
			}
		}
	}

	background = new Shape(line_num, colum_num, map, color_map, 0, 0);

	for (int i = 0; i < passageway_num; i++)
	{
		delete passageway[i];
	}
	delete passageway;
}

void Graph::paint(void)
{
	canv->clean_shap_list();
	canv->clean_map();

	cal_background();
	canv->add_shap(background, 1);
	for (int i = 0; i < shadow_num; i++)
	{
		shadows[i]->cal_shape();
		canv->add_shap(shadows[i]->get_shape(), 2);
	}
	canv->add_shap(player, 2);

	canv->paint();
}

Intersect_status Graph::cal_intersect_status(Point point_left, Point point_right, Line line)
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

Position_relation Graph::cal_position_relation(Point point, Line line)
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

void Graph::sort_shadows(void)
{
	for (int i = 0; i < shadow_num; i++)
	{
		for (int j = i + 1; j < shadow_num - 1; j++)
		{
			if (shadows[i]->get_line().get_x1() > shadows[j]->get_line().get_x1())
			{
				Shadow *tmp = shadows[i];
				shadows[i] = shadows[j];
				shadows[j] = tmp;
			}
		}
	}
}

Line ** Graph::cal_passway(void)
{
	sort_shadows();

	int passageway_num = shadow_num + 1;
	if (shadows[0]->get_line().get_x1() <= 0)
	{
		passageway_num--;
	}
	if (shadows[shadow_num - 1]->get_line().get_x2() >= colum_num)
	{
		passageway_num--;
	}

	Line **passageway = new Line*[passageway_num];

	if (passageway_num > shadow_num)
	{
		for (int i = 0; i < passageway_num; i++)
		{
			int x1, y1, x2, y2;
			if (i == 0)
			{
				x1 = 0;
				y1 = shadows[i]->get_line().get_y1();
				x2 = shadows[i]->get_line().get_x1();
				y2 = shadows[i]->get_line().get_y1();
			}
			else if (i == passageway_num - 1)
			{
				x1 = shadows[i - 1]->get_line().get_x2();
				y1 = shadows[i - 1]->get_line().get_y2();
				x2 = colum_num;
				y2 = shadows[i - 1]->get_line().get_y2();
			}
			else
			{
				x1 = shadows[i - 1]->get_line().get_x2();
				y1 = shadows[i - 1]->get_line().get_y2();
				x2 = shadows[i]->get_line().get_x1();
				y2 = shadows[i]->get_line().get_y1();
			}
			passageway[i] = new Line(x1, y1, x2, y2);
			passageway[i]->cal_equations_from_point();
		}
	}
	else if(passageway_num < shadow_num)
	{
		for (int i = 0; i < passageway_num; i++)
		{
			int x1, y1, x2, y2;
			x1 = shadows[i]->get_line().get_x2();
			y1 = shadows[i]->get_line().get_y2();
			x2 = shadows[i + 1]->get_line().get_x1();
			y2 = shadows[i + 1]->get_line().get_y1();

			passageway[i] = new Line(x1, y1, x2, y2);
			passageway[i]->cal_equations_from_point();
		}
	}
	else if (shadows[0]->get_line().get_x1() <= 0)
	{
		for (int i = 0; i < passageway_num; i++)
		{
			int x1, y1, x2, y2;
			if (i == passageway_num - 1)
			{
				x1 = shadows[i]->get_line().get_x2();
				y1 = shadows[i]->get_line().get_y2();
				x2 = colum_num;
				y2 = shadows[i]->get_line().get_y2();
			}
			else
			{
				x1 = shadows[i]->get_line().get_x2();
				y1 = shadows[i]->get_line().get_y2();
				x2 = shadows[i + 1]->get_line().get_x1();
				y2 = shadows[i + 1]->get_line().get_y1();
			}
			passageway[i] = new Line(x1, y1, x2, y2);
			passageway[i]->cal_equations_from_point();
		}
	}
	else
	{
		for (int i = 0; i < passageway_num; i++)
		{
			int x1, y1, x2, y2;
			if (i == 0)
			{
				x1 = 0;
				y1 = shadows[i]->get_line().get_y1();
				x2 = shadows[i]->get_line().get_x1();
				y2 = shadows[i]->get_line().get_y1();
			}
			else
			{
				x1 = shadows[i - 1]->get_line().get_x2();
				y1 = shadows[i - 1]->get_line().get_y2();
				x2 = shadows[i]->get_line().get_x1();
				y2 = shadows[i]->get_line().get_y1();
			}
			passageway[i] = new Line(x1, y1, x2, y2);
			passageway[i]->cal_equations_from_point();
		}
	}
	return passageway;
}
