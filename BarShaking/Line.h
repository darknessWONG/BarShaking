#pragma once
#include "Point.h"

class Line
{
public:
	Line();
	Line(int x1, int y1, int x2, int y2);
	Line(int x1, int y1, double radin);
	Line(const Line&);
	~Line();

	double get_a(void);
	void set_a(double);
	double get_b(void);
	void set_b(double);
	int get_x1(void);
	void set_x1(int);
	int get_y1(void);
	void set_y1(int);
	int get_x2(void);
	void set_x2(int);
	int get_y2(void);
	void set_y2(int);
	double get_radin(void);
	void set_radin(double);

	void cal_equations_from_point(void);
	void cal_equations_from_radin(void);
	
	//if the point is under the line return 1
	//if the point is on the line reutrn 0
	//if the point is on the top of the line return -1
	int check_point(double x, double y);
	Point* check_intersect(Line li);
private:
	void init_member(void);

	double a;
	double b;
	int x1;
	int y1;
	int x2;
	int y2;
	double radin;
};

