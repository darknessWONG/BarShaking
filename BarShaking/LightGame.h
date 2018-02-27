#pragma once
#include "Canvas.h"
#include "Flashlight.h"
#include "Shadow.h"
#include "config.h"

class LightGame
{
public:
	LightGame();
	~LightGame();

	void start(void);
	void main_loop(void);
private:
	void init_game(void);

	void update_info(void);
	void update_player(void);
	void update_light(void);
	void update_shadow(void);
	void check_win(void);

	void paint(void);
	void paint_light(void);
	void paint_shadow(void);
	void paint_player(void);

	Canvas *canv = 0;

	FlashLight *light = 0;
	double radin;
	double radin_speed;
	int twinkle_interval;
	bool is_display_light;
	
	Shadow *shadow = 0;

	Shape *player = 0;

	Win_status status;
};

