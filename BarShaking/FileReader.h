#pragma once
#include "stdafx.h"
#include "Shape.h"
#include <fstream>


static class FileReader
{
public:
	FileReader();
	~FileReader();

	static Shape ReadModelFile(string fileNmae, string color_flieName);
	static int* ReadConfigFile(string fileName);

private:
	static int get_int_from_letter(char);
};
