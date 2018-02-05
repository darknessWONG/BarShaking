#pragma once
class Shape
{
public:
	Shape();
	Shape(int line_num, int colum_num, char* map, short* color_map, int rel_posX = 0, int rel_posY = 0);
	Shape(const Shape& shape);
	virtual ~Shape();

	virtual char* paint(char* r_map, short* r_color_map, int line_num, int colum_num);

	Shape* get_shape_next(void);
	void set_shape_next(Shape*);
	int get_rel_posX(void);
	void set_rel_posX(int x);
	int get_rel_posY(void);
	void set_rel_posY(int y);
	int get_abs_posX(void);
	void set_abs_posX(int);
	int get_abs_posY(void);
	void set_abs_posY(int);
	virtual int get_line_num(void);
	virtual int get_colum_num(void);
	char* get_map(void);
	short* get_color_map(void);
	void set_map(char* map, short* color_map, int line_num, int colum_num);
	void set_map_with_delte(char* map, short* color_map, int line_num, int colum_num);

	void delete_maps(void);
	void clean_next(void);
private:
	void set_member(int line_num = 0, int colum_num = 0, char* map = 0, short* color_map = 0, int rel_posX = 0, int rel_posY = 0);
	void copy_maps(char* map, short* color_map);

	Shape *shape_next;
	int rel_posX;
	int rel_posY;
	int abs_posX;
	int abs_posY;
	int line_num;
	int colum_num;
	char* map = 0;
	short* color_map = 0;
};