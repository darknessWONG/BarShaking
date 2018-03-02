#pragma once
#include "Shape.h"
#include "Line.h"
#include "config.h"

class FlashLight
{
public:
	FlashLight();
	FlashLight(int rel_x, int rel_y, double width, double radin);
	FlashLight(int rel_x, int rel_y, double width, double radin, int line_num, int colum_num);
	~FlashLight();

	Line* get_line_left(void);
	Line* get_line_right(void);
	double get_radin(void);
	void set_radin(double);
	double get_width(void);
	void set_width(double);
	double get_rel_x(void);
	void set_rel_x(double);
	int get_rel_y(void);
	void set_rel_y(int);
	int get_line_num(void);
	void set_line_num(int);
	int get_colum_num(void);
	void set_colum_num(int);
	Shape* get_shape(void);

	void cal_lines(void);
	void cal_shape(void);

	bool check_point_in_area(int x, int y);
private:
	void set_member(int rel_x = 0, int rel_y = 0, double width = 0, double radin = 0, int line_num = LINE_NUM, int colum_num = COLUM_NUM);

	void delete_shape(void);
	void delete_line_left(void);
	void delete_line_right(void);

	Shape *shape = 0;
	Line *line_left = 0;
	Line *line_right = 0;
	double radin;
	double width;
	double rel_x;
	int rel_y;
	int line_num;
	int colum_num;

};

