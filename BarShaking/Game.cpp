#include "stdafx.h"
#include "Game.h"
#include "FileReader.h"
#include <time.h>
#define CONIOEX
#include "conioex.h"
#include <string>

Game::Game()
{
}


Game::~Game()
{
}

void Game::set_canv(Canvas *canv)
{
	this->canv = canv;
}

void Game::set_bar(Bar *bar)
{
	this->bar = bar;
}

int Game::game_start(void)
{
	init_game();
	main_loop();
	return 0;
}

void Game::main_loop(void)
{
	clock_t current_time, last_time = 0;
	int pass_time;
	int a_times, d_time;
	screen_num = 0;
	while (status == unkwon)
	{
		current_time = clock();
		pass_time = current_time - last_time;
		if (pass_time >= (double)1 / FPS * 1000)
		{
			NOW_FPS = 1.0f / ((current_time - last_time) / 1000.0f);

			last_time = current_time;
			left_time -= pass_time;
			screen_num++;

			canv->paint();
			
			status_update();
			
			cal_screen();

			if (left_time <= 0)
			{
				status = win;
			}


			if (bar->get_radin() >= 0.5 || bar->get_radin() <= -0.5)
			{
				status = lost;
			}
		}
	}
}

void Game::init_game(void)
{
	srand(time(0));

	canv = new Canvas(LINE_NUM * 2, COLUM_NUM * 2, LINE_NUM, COLUM_NUM);
	 
	bar = create_bar();
	bar->set_radin(0);
	bar->get_base_shape()->set_rel_posX(20);
	bar->get_base_shape()->set_rel_posY(10);

	radin_speed = 0;
	acceleration = 0.01;

	status = unkwon;
	level = 1;
	left_time = 5000;
	
	create_time_box();
}

Bar * Game::create_bar(void)
{
	Shape *bar_shape = new Shape(FileReader::ReadModelFile("bar.txt", "bar_color.txt"));
	return new Bar(bar_shape, 19, 20);
}

void Game::create_time_box(void)
{
	time_box = new My_diallog_box(TIME_BOX_LINE_NUM, TIME_BOX_COLUM_NUM);
	time_box_status_update();
	time_box->set_rel_posX(20);
	time_box->set_rel_posY(0);
}

void Game::set_radin_speed_random(void)
{

	//int dic = rand() % 2;

	//double speed = (double)(rand() % 100) / 1000;
	/*switch (dic)
	{
	case 0:
		radin_speed = speed;
		break;
	case 1:
		radin_speed = -speed;
		break;
	default:
		break;
	}*/

	if (bar->get_radin() >=  0)
	{
		radin_speed += acceleration;
	}
	else
	{
		radin_speed -= acceleration;
	}

}

double Game::cal_input_value(void)
{
	reinport();
	if (inport(PK_A))
	{
		return -0.02;
	}
	if (inport(PK_D))
	{
		return 0.02;
	}
	return 0;
}

void Game::cal_screen(void)
{
	canv->clean_shap_list();
	
	canv->add_shap(bar->get_now_shape(), 1);

	canv->add_shap(time_box, 2);
}

void Game::status_update(void)
{
	bar_status_update();
	time_box_status_update();
}

void Game::bar_status_update(void)
{

	if (screen_num >= 30)
	{
		set_radin_speed_random();
		screen_num = 0;
	}

	double input = cal_input_value();

	radin_speed += input;

	bar->set_radin(bar->get_radin() + radin_speed);

	bar->cal_now_shape();
}

void Game::time_box_status_update(void)
{
	time_box->set_sentence_with_delete(cal_time_box_sentence());
	time_box->cal_map();
}

string Game::cal_time_box_sentence(void)
{
	string time = num_to_str(left_time);
	string time_str = TIME_BOX_STR;
	return time_str.replace(TIME_BOX_STR.find("%s"), 2, time);
}
