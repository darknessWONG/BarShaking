#pragma once
#include "FlashLight.h"
#include "Shadow.h"
#include "Canvas.h"

class Graph
{
public:
	Graph();
	~Graph();

	Canvas* get_canv(void);
	void set_canv(Canvas*);
	int get_line_num(void);
	void set_line_num(int);
	int get_colum_num(void);
	void set_colum_num(int);
	Shape* get_player(void);
	void set_player(Shape*);
	void clean_player(void);
	FlashLight** get_lights(void);
	void add_light(FlashLight*);
	void clean_lights(void);
	Shadow** get_shadows(void);
	void add_shadow(Shadow*);
	void clean_shadows(void);
	Shape* get_background(void);
	void clean_background(void);

	void clean_shape(void);
	void clean_up(void);

	void cal_background(void);

	void paint(void);
private:

	Intersect_status cal_intersect_status(Point point_left, Point point_right, Line line);
	Position_relation cal_position_relation(Point point, Line line);

	void sort_shadows(void);
	Line** cal_passway(void);

	Canvas *canv = 0;
	int line_num;
	int colum_num;

	Shape *player = 0;
	FlashLight **lights = 0;
	int light_num;
	Shadow **shadows = 0;
	int shadow_num;
	Shape *background = 0;

};

