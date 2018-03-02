#include "stdafx.h"
#include "FileReader.h"



FileReader::FileReader()
{
}


FileReader::~FileReader()
{
}

Shape FileReader::ReadModelFile(string fileName, string color_flieName)
{
	fstream file(fileName, ios::in), color_file(color_flieName, ios::in);
	int len = 0;
	string tmp;

	//ƒtƒ@ƒCƒ‹‚Ì
	while (getline(file, tmp, '\n'))
	{
		len++;
	}

	file.clear();
	file.seekg(0, ios::beg);

	string *tmp_prt = new string[len];
	string *color_prt = new string[len];
	int colum_max = 0;
	for (int i = 0; i < len; i++)
	{
		int colum_num = 0;
		while(1)
		{
			char ch = file.get();
			char color_ch = color_file.get();
			if (ch != '\n' && ch != EOF)
			{
				tmp_prt[i] += ch;
				color_prt[i] += color_ch;
			}
			else
			{
				break;
			}
			colum_num++;
		}
		if (colum_num > colum_max)
		{
			colum_max = colum_num;
		}
	}
	char* map = new char[len * colum_max]{' '};
	short* color_map = new short[len * colum_max]{255};
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < colum_max; j++)
		{
			if (j < tmp_prt[i].length())
			{
				map[i * colum_max + j] = tmp_prt[i][j];
				color_map[i * colum_max + j] = get_int_from_letter(color_prt[i][j]);
			}
			else
			{
				map[i * colum_max + j] = ' ';
				color_map[i * colum_max + j] = 255;
			}
		}
	}
	
	Shape shape(len, colum_max, map, color_map);

	file.close();
	color_file.close();
	return shape;
}

int * FileReader::ReadConfigFile(string fileName)
{
	fstream wfile(fileName, ios::in);
	wfile.seekg(0, ios::end);
	int len = wfile.tellg();
	wfile.seekg(0, ios::beg);

	int *prt = new int[len];
	for (int i = 0; i < len; i++)
	{
		wfile >> prt[i];
	}

	return prt;
}

void FileReader::ReadLevelFile(string fileName, FlashLight **& lights, int & light_num, double *& radin_speed, double *& speed, int *& fream, Shadow **& shadow, int & shadow_num)
{
	fstream file(fileName, ios::in);

	file >> light_num;
	lights = new FlashLight*[light_num];
	radin_speed = new double[light_num];
	speed = new double[light_num];
	fream = new int[light_num];

	for (int i = 0; i < light_num; i++)
	{
		int x, y;
		double width, radin;
		file >> x >> y >> width >> radin;
		lights[i] = new FlashLight(x, y, width, radin);
	}
	for (int i = 0; i < light_num; i++)
	{
		file >> radin_speed[i];
	}
	for (int i = 0; i < light_num; i++)
	{
		file >> fream[i];
	}
	for (int i = 0; i < light_num; i++)
	{
		file >> speed[i];
	}

	file >> shadow_num;
	shadow = new Shadow*[shadow_num];
	for (int i = 0; i < shadow_num; i++)
	{
		int x1, y1, x2, y2;
		file >> x1 >> y1 >> x2 >> y2;
		shadow[i] = new Shadow(x1, y1, x2, y2, LINE_NUM, COLUM_NUM);
	}

}

int FileReader::get_int_from_letter(char c)
{
	if (c >= '0' && c <= '9')
	{
		return c - '0';
	}
	else if (c >= 'a' && c <= 'z')
	{
		return c - 'a' + 10;
	}
	else
	{
		return 255;
	}
}
