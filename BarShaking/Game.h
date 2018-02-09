#pragma once
#include "stdafx.h"
#include "Canvas.h"
#include "Bar.h"

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
	void set_radin_speed_random(void);
	double cal_input_value(void);
	void cal_screen(void);
	void bar_status_update(void);

	Canvas *canv = 0;

	Bar *bar = 0;
	double radin_speed;
	double acceleration;

	Win_status status;
	int level;
	int left_time;
	int screen_num;
};

