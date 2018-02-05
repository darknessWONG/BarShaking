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

extern const int CAV_LINE_NUM;
extern const int CAV_COLUM_NUM;
extern const int LINE_NUM;
extern const int COLUM_NUM;
extern const int MAP_LINE_NUM;
extern const int MAP_COLUM_NUM;
extern const int TRAVEL_MAP_REAL_POSX;
extern const int TRAVEL_MAP_REAL_POSY;
extern const int PLAYER_MAP_REAL_POSX;
extern const int PLAYER_MAP_REAL_POSY;
extern const int ROLE_LINE_NUM;
extern const int ROLE_COLUM_NUM;

extern const int BATTLE_MAIN_MENU_SELECT_NUM;
extern const int BATTLE_MAIN_MENU_BOX_LINE_NUM;
extern const int BATTLE_MAIN_MENU_BOX_COLUM_NUM;
extern const int BATTLE_MAIN_MENU_REAL_POSX;
extern const int BATTLE_MAIN_MENU_REAL_POSY;
extern const int BATTLE_SUB_MENU_SELECT_NUM;
extern const int BATTLE_SUB_MENU_BOX_LINE_NUM;
extern const int BATTLE_SUB_MENU_BOX_COLUM_NUM;
extern const int BATTLE_SUB_MENU_REAL_POSX;
extern const int BATTLE_SUB_MENU_REAL_POSY;
extern const int BATTLE_SELECT_MENU_BOX_LINE_NUM;
extern const int BATTLE_SELECT_MENU_BOX_COLUM_NUM;
extern const int BATTLE_SELECT_MENU_REAL_POSX;
extern const int BATTLE_SELECT_MENU_REAL_POSY;
extern const int BATTLE_CHARA_REAL_POSX;
extern const int BATTLE_CHARA_REAL_POSY;

extern const string INPUT_NAME_STR;
extern const string SELECT_CLASS_STR;
extern const string STATUS_CHECK_STR;
extern const string SELECTING_MARK;
extern const string BATTLE_MAIN_MENU_STR;
extern const string BATTLE_TARGET_MENU_STR;
extern const string BATTLE_MAIN_MENU_SELECTION_STR[];
extern const string SKILL_MAIN_MENU_STR;
extern const string DAMAGE_STR;
extern const string HEAL_STR;
extern const string INTERLUDE_STR;
extern const string ATTACK_STR;
extern const string MOSTER_NAME;
extern const string MP_LESS_STR;

extern const string MAIN_SOUND_STR;
extern const string BATTLE_SOUND_STR;