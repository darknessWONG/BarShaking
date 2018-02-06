// BarShaking.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Canvas.h"
#include "Shape.h"
#include "FileReader.h"
#include <math.h>
#include "config.h"

int main()
{
	Canvas *canv = new Canvas(25, 80, 25, 80);
	Shape bar = FileReader::ReadModelFile("bar.txt", "bar_color.txt");
	bar.set_rel_posX(35);
	bar.set_rel_posY(5);
	
	char *map = new char[bar.get_line_num() * bar.get_colum_num()]{' '};
	short *color_map = new short[bar.get_line_num() * bar.get_colum_num()]{4};
	for (int i = 0; i < bar.get_line_num() * bar.get_colum_num(); i++)
	{
		map[i] = ' ';
		color_map[i] = 4;
	}
	for (int i = 0; i < bar.get_line_num(); i++)
	{
		for (int j = 0; j < bar.get_colum_num(); j++)
		{
			if (bar.get_map()[i * bar.get_colum_num() + j] != ' ')
			{
				double longg = sqrt(pow(i - 9, 2) + pow(j - 10, 2));
				double new_x = longg * sin(0.1 * 3.1415926) + j;
				double new_y = 9 - longg * cos(0.1 * 3.1415926);
				
				if ((new_x < 0 || new_x > bar.get_colum_num() - 1) || (new_y < 0 || new_y > bar.get_line_num()))
				{
					continue;
				}


				map[(int)new_y * bar.get_colum_num() + (int)new_x] = bar.get_map()[i * bar.get_colum_num() + j];
				color_map[(int)new_y * bar.get_colum_num() + (int)new_x] = bar.get_color_map()[i * bar.get_colum_num() + j];
			}
		/*	else
			{
				map[i * bar.get_colum_num() + j] = bar.get_map()[i * bar.get_colum_num() + j];
				color_map[i * bar.get_colum_num() + j] = bar.get_color_map()[i * bar.get_colum_num() + j];
			}*/
		}
	}
	bar.set_map(map, color_map, bar.get_line_num(), bar.get_colum_num());
	
	canv->add_shap(&bar, 1);
	canv->paint();
	canv->refreash();

	system("pause");
	delete canv;
	//delete[] map;
	//delete[] color_map;
    return 0;
}

