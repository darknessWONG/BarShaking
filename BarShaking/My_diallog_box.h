#pragma once
#include "Shape.h"
class My_diallog_box : public Shape
{
public:
	My_diallog_box();
	My_diallog_box(int line_num, int colum_num);
	My_diallog_box(char tran, char por,int line_num, int colum_num);
	~My_diallog_box();

	char* get_sentence(void);
	void set_sentence(char*);
	void set_sentence_with_delete(char*);
	void set_sentence_with_delete(string);
	int get_line_num(void);
	void set_line_num(int);
	int get_colum_num(void);
	void set_colum_num(int);

	void change_frame_color(int color);

	void reset_map(void);
	void cal_map(void);
	//char* paint(char* r_map, short* r_color_map, int line_num, int colum_num);
private:
	void set_member(char tran_frame = '-', char por_frame = '|', int line_num = 0, int colum_num = 0);

	char *sentence;
	int colum_num;
	int line_num;
	char diallog_box_tran_frame;
	char diallog_box_por_frame;
};

