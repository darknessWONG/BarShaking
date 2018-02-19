#include "stdafx.h"
#include "My_diallog_box.h"


My_diallog_box::My_diallog_box()
{
	set_member();
}

My_diallog_box::My_diallog_box(int line_num, int colum_num)
{
	set_member('-', '|', line_num, colum_num);
}

My_diallog_box::My_diallog_box(char tran, char por, int line_num, int colum_num)
{
	set_member(tran, por, line_num, colum_num);
}



My_diallog_box::~My_diallog_box()
{
}


char * My_diallog_box::get_sentence(void)
{
	return sentence;
}

void My_diallog_box::set_sentence(char *sen)
{
	sentence = new char[strlen(sen) + 1];
	strcpy(sentence, sen);
}

void My_diallog_box::set_sentence_with_delete(char *sen)
{
	if (sentence != 0)
	{
		delete[] sentence;
		sentence = 0;
	}
	set_sentence(sen);
}

void My_diallog_box::set_sentence_with_delete(string sent)
{
	char *c_str = new char[sent.length() + 1];
	strcpy(c_str, sent.c_str());
	set_sentence_with_delete(c_str);
}

int My_diallog_box::get_line_num(void)
{
	return line_num;
}

void My_diallog_box::set_line_num(int line_num)
{
	this->line_num = line_num;
}

int My_diallog_box::get_colum_num(void)
{
	return colum_num;
}

void My_diallog_box::set_colum_num(int colum_num)
{
	this->colum_num = colum_num;
}

void My_diallog_box::change_frame_color(int color)
{
}

void My_diallog_box::reset_map(void)
{
	char *map = new char[line_num * colum_num];
	short *color_map = new short[line_num * colum_num];
	for (int i = 0; i < line_num; i++)
	{
		for (int j = 0; j < colum_num; j++)
		{
			if (i == 0 || i == line_num - 1)
			{
				map[i * colum_num + j] = diallog_box_tran_frame;
				color_map[i * colum_num + j] = 0;
			}
			else if (j == 0 || j == colum_num - 2)
			{
				map[i * colum_num + j] = diallog_box_por_frame;
				color_map[i * colum_num + j] = 0;
			}
			else
			{
				map[i * colum_num + j] = ' ';
				color_map[i * colum_num + j] = 0;
			}
		}
	}
	set_map_with_delte(map, color_map, line_num, colum_num);
}

void My_diallog_box::cal_map(void)
{
	reset_map();
	for (int i = 1, k = 0; i < get_line_num(); i++)
	{
		for (int j = 1; j < get_colum_num() - 3; j++, k++)
		{
			if (sentence[k] == '\0')
			{
				break;
			}
			else if (sentence[k] == '\n')
			{
				k++;
				break;
			}
			get_map()[i * get_colum_num() + j] = sentence[k];
		}
	}
}

void My_diallog_box::set_member(char tran_frame, char por_frame, int line_num, int colum_num)
{
	this->line_num = line_num;
	this->colum_num = colum_num;
	diallog_box_tran_frame = tran_frame;
	diallog_box_por_frame = por_frame;

	reset_map();
	sentence = new char[1] {'\0'};
}
