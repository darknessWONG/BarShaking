#pragma once
#include "stdafx.h"

#define DEBUG

#define NAME_LEN 30			//length of name
#define SKILL_NUM 2			//every character's skill num
#define SKILL_TOTAL_NUM 12	//totle skill num
#define CLASS_SKILL_NUM 4	//The maximum number of skills available for all class
#define ATTRIBUTE_SUM 40	//The maximum number of attribute sum
#define CLASS_NUM 3			//num of class
#define TARGET_STRING_LEN 20//The maximum length of target string.
#define RANDOM_NAME_NUM 4	//Num of random name

#define HP_RATE 45
#define MP_RATE 10
#define ATTACK_RATE 3
#define M_ATTACK_RATE 3
#define DEFENSE_RATE 1
#define M_DEFENSE_RATE 2
#define DEFENSE_EFFICIENCY 0.5
#define SKILL_EFFICIENCY 0.23
#define HEAL_EFFICIENCY 0.23

#define STRENGTH_BASE 10
#define INTELLIGENCE_BASE 10
#define MENTALITY_BASE 10
#define SPEED_BASE 10
#define LUCK_BASE 10

extern const int FPS;
extern double NOW_FPS;

extern const double PAI;

extern const int LINE_NUM;
extern const int COLUM_NUM;
extern const int CAV_LINE_NUM;
extern const int CAV_COLUM_NUM;
extern const int TIME_BOX_LINE_NUM;
extern const int TIME_BOX_COLUM_NUM;
extern const int FLASHLIGHT_REL_X;
extern const int FLASHLIGHT_REL_Y;
extern const double FLASHLIGHT_WIDTH;
extern const double FLASHLIGHT_RADIN;
extern const int PLAYER_INITAL_POS_X;
extern const int PLAYER_INITAL_POS_Y;

extern const int LIGHT_COLOR;
extern const int VOID_COLOR;
extern const int SHADOW_COLOR;
extern const int UNCLEAR_COLOR;

extern const int MAP_LINE_NUM;
extern const int MAP_COLUM_NUM;
extern const int TRAVEL_MAP_REAL_POSX;
extern const int TRAVEL_MAP_REAL_POSY;
extern const int PLAYER_MAP_REAL_POSX;
extern const int PLAYER_MAP_REAL_POSY;
extern const int ROLE_LINE_NUM;
extern const int ROLE_COLUM_NUM;

extern const string TIME_BOX_STR;

extern const string MAIN_SOUND_STR;
extern const string TITLE_FILE_STR;
extern const string TITLE_COLOR_FILE_STR;
extern const string FINAL_FILE_STR;
extern const string FINAL_COLOR_FILE_STR;
extern const string BATTLE_SOUND_STR;
extern const string LEVEL_FILE_STR;

string num_to_str(int);
string num_to_str(double);

//create a arrary with [num] element 
//and initialize with [ch]
char* new_map(int num, char ch);

//create a arrary with [num] element 
//and initialize with [ch]
short* new_color_map(int num, short ch);

