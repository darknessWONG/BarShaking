// BarShaking.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Canvas.h"
#include "Shape.h"
#include "FileReader.h"
#include <math.h>
#include "config.h"
#include "Bar.h"
#include "Game.h"
#include "FlashLight.h"
#include "Shadow.h"
#include "LightGame.h"

int main()
{


	//Game gg;
	//gg.game_start();
	LightGame gg;
	gg.start();

	//Canvas canv(LINE_NUM * 2, COLUM_NUM * 2, LINE_NUM, COLUM_NUM);
	//canv.set_now_display_posX(0);
	//canv.set_now_display_posY(0);
	//FlashLight light(20, 0, 0.6, 0.2);
	//light.cal_shape();
	//Shadow sha(0, 10, 21, 10);
	//sha.cal_shape(&light);
	//Shadow sha1(10, 10, 22, 10);
	//sha1.cal_shape(&light);


	//canv.add_shap(light.get_shape(), 1);
	//canv.add_shap(sha.get_shape(), 2);
	//canv.add_shap(sha1.get_shape(), 2);
	//canv.paint();


	system("pause");
    return 0;
}

