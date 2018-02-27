#include "stdafx.h"
#include "Canvas.h"

#include "conioex.h"

Canvas::Canvas(int cav_line_num, int cav_colum_num, int display_line_num, int display_colum_num)
{
	set_member(cav_line_num, cav_colum_num, display_line_num, display_colum_num);
}


Canvas::~Canvas()
{
	if (map != 0)
	{
		delete[] map;
	}
}

Shape * Canvas::GetShapList(int priority)
{
	if (priority <= layer_num)
	{
		return shape_list[priority - 1];
	}
	return NULL;
}

void Canvas::add_shap(Shape* shape, int priority)
{
	if (shape_list == 0)
	{
		shape_list = new Shape*[priority] {0};
		layer_num = priority;
		shape_list[priority - 1] = shape;
	}
	else
	{
		if (layer_num < priority)
		{
			Shape **tmp = new Shape*[priority] {0};
			for (int i = 0; i < layer_num; i++)
			{
				tmp[i] = shape_list[i];
			}
			delete[] shape_list;
			shape_list = tmp;
			layer_num = priority;
		}
		if (shape_list[priority - 1] == 0)
		{
			shape_list[priority - 1] = shape;
		}
		else
		{
			Shape *tmp = shape_list[priority - 1];
			while (tmp->get_shape_next() != 0)
			{
				tmp = tmp->get_shape_next();
			}
			tmp->set_shape_next(shape);
			shape->set_shape_next(0);
		}
		
		
	}
}

int Canvas::get_cav_line_num(void)
{
	return cav_line_num;
}

void Canvas::set_cav_line_num(int cav_line_num)
{
	this->cav_line_num = cav_line_num;
}

int Canvas::get_cav_colum_num(void)
{
	return cav_colum_num;
}

void Canvas::set_cav_colum_num(int cav_colum_num)
{
	this->cav_colum_num = cav_colum_num;
}

int Canvas::get_display_line_num(void)
{
	return display_line_num;
}

void Canvas::set_display_line_num(int display_line_num)
{
	this->display_line_num = display_line_num;
}

int Canvas::get_display_colum_num(void)
{
	return display_colum_num;
}

void Canvas::set_display_colum_num(int display_colum_num)
{
	this->display_colum_num = display_colum_num;
}

int Canvas::get_now_display_posX(void)
{
	return now_display_posX;
}

void Canvas::set_now_display_posX(int now_display_posX)
{
	this->now_display_posX = now_display_posX;
}

int Canvas::get_now_display_posY(void)
{
	return now_display_posY;
}

void Canvas::set_now_display_posY(int now_display_posY)
{
	this->now_display_posY = now_display_posY;
}

int Canvas::get_fps(void)
{
	return fps;
}

void Canvas::set_fps(int fps)
{
	this->fps = fps;
}

void Canvas::clean_map(void)
{
	for (int i = 0; i < CAV_LINE_NUM * CAV_COLUM_NUM; i++)
	{
		map[i] = ' ';
		color_map[i] = 255;
	}
}

void Canvas::clean_shap_list(void)
{
	if (shape_list != 0)
	{
		for (int i = 0; i < layer_num; i++)
		{
			try 
			{
				Shape *tmp = shape_list[i];
				while (tmp != 0)
				{
					Shape *ptr = tmp->get_shape_next();
					tmp->set_shape_next(0);
					tmp = ptr;
				}
			}
			catch (exception e)
			{
				exception_parser(e);
			}
		}
		delete[] shape_list;
		shape_list = 0;
		layer_num = 0;
	}
}

void Canvas::set_windows_size(int line_num, int columns_num)
{
	string cmd = "mode con cols=";
	stringstream ss;
	string tmp;
	ss << columns_num;
	ss >> tmp;
	cmd += tmp;
	cmd += " lines=";
	ss.clear();
	ss << line_num;
	ss >> tmp;
	cmd += tmp;
	system(cmd.c_str());
}

void Canvas::paint(void)
{
	for (int i = 0; i < layer_num; i++)
	{
		paint_list(shape_list[i]);
	}

	refreash();

}

void Canvas::refreash(void)
{	
	gotoxy(1, 1);
	char* tmp_map = new char[(display_colum_num + 1) * display_line_num + 1];
	int num = 0, now_color = 255;
	for (int i = now_display_posY; i < now_display_posY + display_line_num; i++)
	{
		for (int j = now_display_posX; j < now_display_posX + display_colum_num; j++)
		{
			if (num == 0)
			{
				tmp_map[num++] = map[i * cav_colum_num + j];
				now_color = color_map[i * cav_colum_num + j];
			}
			else if (color_map[i * cav_colum_num + j] != now_color)
			{
				tmp_map[num] = '\0';
				if (now_color != 255)
				{
					textbackground(now_color);
				}
				else
				{
					textbackground(0);
				}
				printf("%s", tmp_map);
				num = 0;
				tmp_map[num++] = map[i * cav_colum_num + j];
				now_color = color_map[i * cav_colum_num + j];
			}
			else
			{
				tmp_map[num++] = map[i * cav_colum_num + j];
				now_color = color_map[i * cav_colum_num + j];
			}
		}
		tmp_map[num++] = '\n';

	}
	if (num != 0)
	{
		tmp_map[num] = '\0';
		if (now_color != 255)
		{
			textbackground(now_color);
		}
		else
		{
			textbackground(0);
		}
		printf("%s", tmp_map);
		num = 0;
	}
	delete[] tmp_map;

#ifdef DEBUG
	gotoxy(1, 1);
	printf("FPS:%lf", NOW_FPS);
#endif
}

void Canvas::set_member(int cav_line_num, int cav_colum_num, int display_line_num, int display_colum_num, int now_display_posX, int now_display_posY, int fps)
{
	this->cav_line_num = cav_line_num;
	this->cav_colum_num = cav_colum_num;
	this->display_line_num = display_line_num;
	this->display_colum_num = display_colum_num;
	this->now_display_posX = now_display_posX;
	this->now_display_posY = now_display_posY;
	this->fps = fps;
	

	map = new char[cav_line_num * cav_colum_num];
	color_map = new short[cav_line_num * cav_colum_num];
	for (int i = 0; i < cav_line_num * cav_colum_num; i++)
	{
		map[i] = ' ';
		color_map[i] = 255;
	}


	shape_list = 0;
	layer_num = 0;

	set_windows_size(display_line_num + 1, display_colum_num + 1);

	setcursortype(NOCURSOR);
}

void Canvas::paint_list(Shape* list)
{
	Shape *prt = list;
	while (prt != 0)
	{
		map = prt->paint(map, color_map, cav_line_num, cav_colum_num);
		prt = prt->get_shape_next();
	}
}

void Canvas::exception_parser(exception e)
{
	//do something
	cout << "aaa" << endl;
}
