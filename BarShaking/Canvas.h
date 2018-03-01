#pragma once
#include "stdafx.h"
#include "Shape.h"
#include "config.h"

//画面コントローラーである
//レイヤーで画面をレンダリングする
//レイヤーは番号を小さい順でレンダリングするので、上の画像を大きい番号のレイヤーに保存してください
class Canvas
{
public:
	Canvas(int cav_line_num, int cav_colum_num, int display_line_num, int display_colum_num);
	virtual ~Canvas();

	Shape *GetShapList(int priority);
	void add_shap(Shape* shap, int priority);

	int get_cav_line_num(void);
	void set_cav_line_num(int);
	int get_cav_colum_num(void);
	void set_cav_colum_num(int);
	int get_display_line_num(void);
	void set_display_line_num(int);
	int get_display_colum_num(void);
	void set_display_colum_num(int);
	int get_now_display_posX(void);
	void set_now_display_posX(int);
	int get_now_display_posY(void);
	void set_now_display_posY(int);
	int get_fps(void);
	void set_fps(int);
	
	void clean_map(void);
	void clean_shap_list(void);

	void set_windows_size(int line_num, int columns_num);

	void paint(void);
	void refreash(void);
private:
	void set_member(int cav_line_num, int cav_colum_num, int display_line_num, int display_colum_num, int now_display_posX = 0, int now_display_posY = 0, int fps = 60);
	void paint_list(Shape*);

	void exception_parser();

	int cav_line_num;
	int cav_colum_num;
	int display_line_num;
	int display_colum_num;
	int now_display_posX;
	int now_display_posY;

	Shape **shape_list = 0;
	int layer_num;

	char* map;
	short* color_map;

	int fps;
};

