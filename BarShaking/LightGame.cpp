#include "stdafx.h"
#include "LightGame.h"
#include "FileReader.h"
#define CONIOEX
#include "conioex.h"


LightGame::LightGame()
{
}

LightGame::~LightGame()
{
}

void LightGame::start(void)
{
	init_game();
	main_loop();
}

void LightGame::main_loop(void)
{
	clock_t current_time, last_time = 0;
	int pass_time;
	while (status == unkwon)
	{
		current_time = clock();
		pass_time = current_time - last_time;
		if (pass_time >= (double)1 / FPS * 1000)
		{
			NOW_FPS = 1.0f / ((current_time - last_time) / 1000.0f);

			last_time = current_time;



			update_info();
			paint();
			check_win();
		}
	}

}

void LightGame::init_game(void)
{
	canv = new Canvas(CAV_LINE_NUM, CAV_COLUM_NUM, LINE_NUM, COLUM_NUM);
	canv->set_now_display_posX(0);
	canv->set_now_display_posY(0);

	light = new FlashLight(FLASHLIGHT_REL_X, FLASHLIGHT_REL_Y, FLASHLIGHT_WIDTH, FLASHLIGHT_RADIN, LINE_NUM, COLUM_NUM);
	light->cal_shape();

	shadow = new Shadow (5, 10, 21, 10, LINE_NUM, COLUM_NUM);
	shadow->cal_shape();

	player = new Shape(FileReader::ReadModelFile("player.txt", "player_color.txt"));
	player->set_rel_posX(PLAYER_INITAL_POS_X);
	player->set_rel_posY(PLAYER_INITAL_POS_Y);


	radin = 0;
	status = unkwon;
	radin_speed = 0.001;
	twinkle_interval = 0;
	is_display_light = true;

}

void LightGame::update_info(void)
{
	update_player();
	update_light();
	update_shadow();
	//check_win();
}

void LightGame::update_player(void)
{
	reinport();
	if (inport(PK_A))
	{
		player->set_rel_posX(player->get_rel_posX() - 1 < 0 ? 0 : player->get_rel_posX() - 1);
	}
	if (inport(PK_D))
	{
		player->set_rel_posX(player->get_rel_posX() + 1 > COLUM_NUM ? COLUM_NUM : player->get_rel_posX() + 1);
	}
}

void LightGame::update_light(void)
{
	if (light->get_radin() + light->get_width() + radin_speed >= 1
		|| light->get_radin() + radin_speed <= 0)
	{
		radin_speed = -radin_speed;
	}
	light->set_radin(light->get_radin() + radin_speed);
}

void LightGame::update_shadow(void)
{

}

void LightGame::check_win(void)
{
	for (int i = 0; i < player->get_line_num(); i++)
	{
		for (int j = 0; j < player->get_colum_num(); j++)
		{
			int real_pos = (i + player->get_rel_posY()) * shadow->get_colum_num() + (j + player->get_rel_posX());
			if (light->get_shape()->get_color_map()[real_pos] == LIGHT_COLOR
				&& shadow->get_shape()->get_color_map()[real_pos] == VOID_COLOR)
			{
				status = Win_status::lost;
				return;
			}
		}
	}
	if (player->get_rel_posX() + player->get_colum_num() >= COLUM_NUM)
	{
		status = Win_status::win;
	}
}

void LightGame::paint(void)
{
	canv->clean_shap_list();
	canv->clean_map();
	paint_light();
	paint_shadow();
	paint_player();

	canv->paint();
}

void LightGame::paint_light(void)
{
	light->cal_shape();
	canv->add_shap(light->get_shape(), 1);
}

void LightGame::paint_shadow(void)
{
	if (is_display_light)
	{
		shadow->cal_shape(light);
	}
	else
	{
		shadow->cal_shape();
	}
	canv->add_shap(shadow->get_shape(), 2);
}

void LightGame::paint_player(void)
{
	canv->add_shap(player, 3);
}
