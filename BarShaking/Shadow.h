#pragma once
#include "Line.h"
#include "Shape.h"
#include "config.h"
#include "FlashLight.h"

class Shadow
{
public:
	Shadow(int x1, int y1, int x2, int y2);
	Shadow(int x1, int y1, int x2, int y2, int line_num, int column_num);
	Shadow(const Line&);
	Shadow(const Line&, int line_num, int column_num);
	~Shadow();

	int get_line_num(void);
	void set_line_num(int);
	int get_colum_num(void);
	void get_colum_num(int);
	Line get_line(void);
	Shape* get_shape(void);

	void delete_shape(void);
	void cal_shape(FlashLight *light);
	void cal_shape(void);

private:
	void set_member(int line_num = LINE_NUM, int colum_num = COLUM_NUM);
	Intersect_status cal_intersect_status(Point point_left, Point point_right, Line line);
	Position_relation cal_position_relation(Point point, Line line);

	Shape *shape = 0;
	Line line;
	int line_num;
	int colum_num;


};

