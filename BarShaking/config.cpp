#include "stdafx.h"
#include "config.h"

const static int FPS = 60;
double NOW_FPS = 1;

const static int CAV_LINE_NUM = 200;
const static int CAV_COLUM_NUM = 640;
const static int LINE_NUM = 50;
const static int COLUM_NUM = 160;
const static int MAP_LINE_NUM = 100;
const static int MAP_COLUM_NUM = 300;
const static int TRAVEL_MAP_REAL_POSX = 43;
const static int TRAVEL_MAP_REAL_POSY = 150;
const static int PLAYER_MAP_REAL_POSX = 15 + TRAVEL_MAP_REAL_POSX;
const static int PLAYER_MAP_REAL_POSY = 85 + TRAVEL_MAP_REAL_POSY;
const static int ROLE_LINE_NUM = 5;
const static int ROLE_COLUM_NUM = 15;

const static int BATTLE_MAIN_MENU_SELECT_NUM = 2;
const static int BATTLE_MAIN_MENU_BOX_LINE_NUM = 10;
const static int BATTLE_MAIN_MENU_BOX_COLUM_NUM = 60;
const static int BATTLE_MAIN_MENU_REAL_POSX = 39;
const static int BATTLE_MAIN_MENU_REAL_POSY = 0;
const static int BATTLE_SUB_MENU_SELECT_NUM = 2;
const static int BATTLE_SUB_MENU_BOX_LINE_NUM = 10;
const static int BATTLE_SUB_MENU_BOX_COLUM_NUM = 50;
const static int BATTLE_SUB_MENU_REAL_POSX = 39;
const static int BATTLE_SUB_MENU_REAL_POSY = 60;
const static int BATTLE_SELECT_MENU_BOX_LINE_NUM = 10;
const static int BATTLE_SELECT_MENU_BOX_COLUM_NUM = 50;
const static int BATTLE_SELECT_MENU_REAL_POSX = 39;
const static int BATTLE_SELECT_MENU_REAL_POSY = 110;
const static int BATTLE_CHARA_REAL_POSX = 5;
const static int BATTLE_CHARA_REAL_POSY = 10;


const static string INPUT_NAME_STR = "カッコイイ名前を入力してください";
const static string SELECT_CLASS_STR = "クラスを選択したください";
const static string STATUS_CHECK_STR = "プレイヤーキャラの情報：";
const static string SELECTING_MARK = "→";
const static string BATTLE_MAIN_MENU_STR = "%nのアクションを選択してください";
const static string BATTLE_TARGET_MENU_STR = "ターゲットを選択してください";
const static string BATTLE_MAIN_MENU_SELECTION_STR[] = { "攻撃", "スキル" };
const static string SKILL_MAIN_MENU_STR = "スキルを選択してください";
const static string DAMAGE_STR = "%nは%sで%pに%dダメージを与える";
const static string HEAL_STR = "%nは%sで%pに%d治療を与える";
const static string INTERLUDE_STR = "これは自身と戦う物語";
const static string ATTACK_STR = "攻撃";
const static string MOSTER_NAME = "雑音";
const static string MP_LESS_STR = "mp値は足りない";

const static string MAIN_SOUND_STR = "./music/miyako-japan3.mp3";
const static string BATTLE_SOUND_STR = "./music/wen-kamuy2.mp3";