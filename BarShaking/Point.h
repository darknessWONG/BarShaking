#pragma once
class Point
{
public:
	Point();
	Point(double x, double y);
	~Point();

	double get_x(void);
	void set_x(double);
	double get_y(void);
	void set_y(double);


private:
	void set_member(double x = 0, double y = 0);

	double x;
	double y;
};

