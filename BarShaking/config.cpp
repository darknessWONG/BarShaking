#include "stdafx.h"
#include "config.h"
#include <sstream>

const static int FPS = 60;
double NOW_FPS = 1;

const static double PAI = 3.1415926;


const static int LINE_NUM = 25;
const static int COLUM_NUM = 80;
const static int CAV_LINE_NUM = LINE_NUM * 2;
const static int CAV_COLUM_NUM = COLUM_NUM * 2;
const static int TIME_BOX_LINE_NUM = 3;
const static int TIME_BOX_COLUM_NUM = 15;
const static int FLASHLIGHT_REL_X = 10;
const static int FLASHLIGHT_REL_Y = 0;
const static double FLASHLIGHT_WIDTH = 0.201;
const static double FLASHLIGHT_RADIN = 0.251;
const static int PLAYER_INITAL_POS_X = 0;
const static int PLAYER_INITAL_POS_Y = LINE_NUM - 1;

const static int LIGHT_COLOR = 7;
const static int VOID_COLOR = 255;

const static int MAP_LINE_NUM = 100;
const static int MAP_COLUM_NUM = 300;
const static int TRAVEL_MAP_REAL_POSX = 43;
const static int TRAVEL_MAP_REAL_POSY = 150;
const static int PLAYER_MAP_REAL_POSX = 15 + TRAVEL_MAP_REAL_POSX;
const static int PLAYER_MAP_REAL_POSY = 85 + TRAVEL_MAP_REAL_POSY;
const static int ROLE_LINE_NUM = 5;
const static int ROLE_COLUM_NUM = 15;


const static string TIME_BOX_STR = "time: %s";


const static string MAIN_SOUND_STR = "./music/miyako-japan3.mp3";
const static string BATTLE_SOUND_STR = "./music/wen-kamuy2.mp3";

string num_to_str(int num)
{
	string str;
	stringstream sst;
	sst << num;
	sst >> str;
	return str;
}

string num_to_str(double num)
{
	string str;
	stringstream sst;
	sst << num;
	sst >> str;
	return str;
}

char* new_map(int num, char ch)
{
	char *map = new char[num];
	for (int i = 0; i < num; i++)
	{
		map[i] = ch;
	}
	return map;
}

short* new_color_map(int num, short ch)
{
	short *map = new short[num];
	for (int i = 0; i < num; i++)
	{
		map[i] = ch;
	}
	return map;
}