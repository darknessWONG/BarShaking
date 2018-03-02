#pragma once
#include "Canvas.h"
#include "Flashlight.h"
#include "Shadow.h"
#include "config.h"
#include "graph.h"

class LightGame
{
public:
	LightGame();
	~LightGame();

	void start(void);
	void main_loop(void);
private:
	void init_game(void);
	void init_level(int);

	void update_info(void);
	void update_player(void);
	void update_light(void);
	void update_shadow(void);
	void check_win(void);

	void paint(void);
	void paint_light(void);
	void paint_shadow(void);
	void paint_player(void);

	void title_phase(void);
	void end_phase(void);

	void clean_light(void);
	void clean_shadow(void);


	Canvas *canv = 0;

	int level;
	int level_max;

	FlashLight **light = 0;
	int light_num;
	double *speed = 0;
	double *radin_speed = 0;
	int *twinkle_interval = 0;
	int frame_num;
	bool *is_display_light = 0;
	
	Shadow **shadow = 0;
	int shadow_num;
	//Line **line = 0;
	//int line_num;

	int main_handle;

	Shape *player = 0;

	Graph *gar = 0;
	Win_status status;
};

