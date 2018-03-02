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
	delete canv;
	delete player;
	/*for (int i = 0; i < line_num; i++)
	{
		delete line[i];
	}
	delete[] line;*/
	clean_light();
	clean_shadow();
	closesound(main_handle);
}

void LightGame::start(void)
{
	init_game();
	playsound(main_handle, 1);
	title_phase();
	main_loop();
	end_phase();
}

void LightGame::main_loop(void)
{
	clock_t current_time, last_time = 0;
	int pass_time;
	frame_num = 0;
	while (status != win && status != lose)
	{
		if (level > level_max)
		{
			status = win;
		}
		else
		{
			init_level(level);
			status = unkwon;
		}
		while (status == unkwon)
		{
			current_time = clock();
			pass_time = current_time - last_time;
			if (pass_time >= (double)1 / FPS * 1000)
			{
				NOW_FPS = 1.0f / ((current_time - last_time) / 1000.0f);

				last_time = current_time;
				frame_num++;


				update_info();
				paint();
				check_win();
			}
		}
		gar->clean_up();
		if (status == level_up)
		{
			level++;
		}
	}

}

void LightGame::init_game(void)
{
	char *main_sound_str = new char[MAIN_SOUND_STR.length()];
	strcpy(main_sound_str, MAIN_SOUND_STR.c_str());
	main_handle = opensound(main_sound_str);

	level = 1;
	level_max = 4;
	canv = new Canvas(CAV_LINE_NUM, CAV_COLUM_NUM, LINE_NUM, COLUM_NUM);
	canv->set_now_display_posX(0);
	canv->set_now_display_posY(0);


	player = new Shape(FileReader::ReadModelFile("player.txt", "player_color.txt"));

	gar = new Graph();
	gar->set_line_num(LINE_NUM);
	gar->set_colum_num(COLUM_NUM);
	gar->set_canv(canv);
	//for (int i = 0; i < light_num; i++)
	//{
	//	gar->add_light(light[i]);
	//}
	//for (int i = 0; i < shadow_num; i++)
	//{
	//	gar->add_shadow(line[i]);
	//}

	//radin = 0;
	status = unkwon;
	//radin_speed = 0.001;
	//twinkle_interval = 0;
	//is_display_light = true;

}

void LightGame::init_level(int level)
{
	clean_light();
	clean_shadow();

	string file_name = LEVEL_FILE_STR;
	file_name = file_name.replace(LEVEL_FILE_STR.find("%d"), 2, num_to_str(level));
	FileReader::ReadLevelFile(file_name, light, light_num, radin_speed, speed, twinkle_interval, shadow, shadow_num);
	//light_num = 2;
	//light = new FlashLight*[light_num];
	//light[0] = new FlashLight(FLASHLIGHT_REL_X, FLASHLIGHT_REL_Y, FLASHLIGHT_WIDTH, FLASHLIGHT_RADIN, LINE_NUM, COLUM_NUM);
	/*light[0] = new FlashLight(19, 0, 0.2, 0.4);
	light[1] = new FlashLight(50, 0, 0.1, 0.6);*/
	for (int i = 0; i < light_num; i++)
	{
		light[i]->cal_shape();
	}
	//radin_speed = new double[light_num];
	//radin_speed[0] = 0.01;
	//radin_speed[1] = 0;
	//twinkle_interval = new int[light_num];
	//twinkle_interval[0] = 0;
	//twinkle_interval[1] = 60;
	is_display_light = new bool[light_num];
	for (int i = 0; i < light_num; i++)
	{
		is_display_light[i] = true;
	}

	//shadow_num = 2;
	//shadow = new Shadow*[shadow_num];
	//shadow[0] = new Shadow(5, 10, 21, 10, LINE_NUM, COLUM_NUM);
	//shadow[0] = new Shadow(0, 10, 20, 10, LINE_NUM, COLUM_NUM);
	/*shadow[1] = new Shadow(28, 10, 40, 10, LINE_NUM, COLUM_NUM);*/
	/*for (int i = 0; i < shadow_num; i++)
	{
	shadow[i]->cal_shape();
	}*/

	/*line_num = 2;
	line = new Line*[line_num];
	line[0] = new Line(0, 10, 20, 10);
	line[1] = new Line(28, 10, 40, 10);*/

	player->set_rel_posX(PLAYER_INITAL_POS_X);
	player->set_rel_posY(PLAYER_INITAL_POS_Y);
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
	for (int i = 0; i < light_num; i++)
	{
		if (twinkle_interval[i] != 0 && frame_num % twinkle_interval[i] == 0)
		{
			is_display_light[i] = !is_display_light[i];
		}
		if (light[i]->get_radin() + light[i]->get_width() + radin_speed[i] >= 1
			|| light[i]->get_radin() + radin_speed[i] <= 0)
		{
			radin_speed[i] = -radin_speed[i];
		}
		light[i]->set_radin(light[i]->get_radin() + radin_speed[i]);
		if (light[i]->get_rel_x() + speed[i] >= gar->get_colum_num()
			|| light[i]->get_rel_x() + speed[i] <= 0)
		{
			speed[i] = -speed[i];
		}
		light[i]->set_rel_x(light[i]->get_rel_x() + speed[i]);
	}
}

void LightGame::update_shadow(void)
{

}

void LightGame::check_win(void)
{
	bool is_lose = false;
	for (int i = 0; i < player->get_line_num(); i++)
	{
		for (int j = 0; j < player->get_colum_num(); j++)
		{
			int real_pos = (i + player->get_rel_posY()) * COLUM_NUM + (j + player->get_rel_posX());
			if (gar->get_background()->get_color_map()[real_pos] == LIGHT_COLOR)
			{
				is_lose = true;
			}
			//for (int l = 0; l < light_num; l++)
			//{
			//	if (!is_display_light[l])
			//	{
			//		continue;
			//	}
			//	if (light[l]->get_shape()->get_color_map()[real_pos] == LIGHT_COLOR)
			//	{
			//		is_lose = true;
			//	}
			//}
			//for (int k = 0; k < shadow_num; k++)
			//{
			//	if (shadow[k]->get_shape()->get_color_map()[real_pos] != VOID_COLOR)
			//	{
			//		is_lose = false;
			//	}
			//}

			if (is_lose)
			{
				//status = Win_status::lose;
				return;
			}
			//if (light->get_shape()->get_color_map()[real_pos] == LIGHT_COLOR
			//	&& shadow->get_shape()->get_color_map()[real_pos] == VOID_COLOR)
			//{
			//	status = Win_status::lost;
			//	return;
			//}
		}
	}
	if (player->get_rel_posX() + player->get_colum_num() >= COLUM_NUM)
	{
		status = Win_status::level_up;
	}
}

void LightGame::paint(void)
{
	//canv->clean_shap_list();
	//canv->clean_map();
	gar->clean_shape();


	paint_light();
	paint_shadow();
	paint_player();

	//gar->cal_background();
	//canv->paint();
	gar->paint();
}

void LightGame::paint_light(void)
{
	for (int i = 0; i < light_num; i++)
	{
		if (is_display_light[i])
		{
			//light[i]->cal_shape();
			//canv->add_shap(light[i]->get_shape(), 1);
			gar->add_light(light[i]);
		}
	}
}

void LightGame::paint_shadow(void)
{

	//for (int i = 0; i < shadow_num; i++)
	//{
	//	shadow[i]->delete_shape();
	//	for (int j = 0; j < light_num; j++)
	//	{
	//		if (is_display_light[j])
	//		{
	//			shadow[i]->cal_shape(light[j]);
	//		}
	//	}
	//}
	//for (int i = 0; i < shadow_num; i++)
	//{
	//	canv->add_shap(shadow[1]->get_shape(), 2);
	//}

	for (int i = 0; i < shadow_num; i++)
	{
		gar->add_shadow(shadow[i]);
	}
}

void LightGame::paint_player(void)
{
	//canv->add_shap(player, 3);
	gar->set_player(player);
}

void LightGame::title_phase(void)
{
	Shape gg = FileReader::ReadModelFile(TITLE_FILE_STR, TITLE_COLOR_FILE_STR);
	gg.set_shape_next(0);

	canv->clean_map();
	canv->clean_shap_list();
	canv->add_shap(&gg, 1);
	canv->paint();

	while (!inport(PK_SP))
	{
	}

	canv->clean_map();
	canv->clean_shap_list();
}

void LightGame::end_phase(void)
{
	Shape gg = FileReader::ReadModelFile(FINAL_FILE_STR, FINAL_COLOR_FILE_STR);
	gg.set_shape_next(0);

	canv->clean_map();
	canv->clean_shap_list();
	canv->add_shap(&gg, 1);
	canv->paint();

	while (!inport(PK_SP))
	{
	}

	canv->clean_map();
	canv->clean_shap_list();
}

void LightGame::clean_light(void)
{
	if (light != 0)
	{
		for (int i = 0; i < light_num; i++)
		{
			delete light[i];
		}
		delete[] light;
		delete[] radin_speed;
		delete[] twinkle_interval;
		delete[] is_display_light;
	}
}

void LightGame::clean_shadow(void)
{
	if (shadow != 0)
	{
		for (int i = 0; i < shadow_num; i++)
		{
			delete shadow[i];
		}
		delete[] shadow;
	}
}
