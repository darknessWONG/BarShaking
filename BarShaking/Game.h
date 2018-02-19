#pragma once
#include "stdafx.h"
#include "Canvas.h"
#include "Bar.h"
#include "My_diallog_box.h"

class Game
{
public:
	Game();
	~Game();

	void set_canv(Canvas*);
	void set_bar(Bar*);

	int game_start(void);
	void main_loop(void);
private:
	void init_game(void);

	Bar* create_bar(void);
	void create_time_box(void);

	void set_radin_speed_random(void);
	double cal_input_value(void);
	void cal_screen(void);

	void status_update(void);
	void bar_status_update(void);
	void time_box_status_update(void);

	string cal_time_box_sentence(void);

	Canvas *canv = 0;

	Bar *bar = 0;
	double radin_speed;
	double acceleration;

	My_diallog_box *time_box;

	Win_status status;
	int level;
	int left_time;
	int screen_num;
};

