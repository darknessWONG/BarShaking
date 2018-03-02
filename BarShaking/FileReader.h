#pragma once
#include "stdafx.h"
#include "Shape.h"
#include "Shadow.h"
#include "FlashLight.h"
#include <fstream>


static class FileReader
{
public:
	FileReader();
	~FileReader();

	static Shape ReadModelFile(string fileNmae, string color_flieName);
	static int* ReadConfigFile(string fileName);
	static void ReadLevelFile(string fileName, FlashLight**& lights, int& light_num, double*& radin_speed, double*& speed, int*& fream, Shadow**& shadow, int& shadow_num);
private:
	static int get_int_from_letter(char);
};
