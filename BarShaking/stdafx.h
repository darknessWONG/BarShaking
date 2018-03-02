// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>

using namespace std;


// TODO:  在此处引用程序需要的其他头文件
enum Win_status
{
	unkwon,
	win,
	lose,
	level_up
};

enum Intersect_status
{
	no_intersect,
	blocked,
	cover,
	left_half_block,
	right_half_block
};

enum Position_relation
{
	outside_left,
	outside_right,
	middle
};

enum Point_status
{
	light,
	shadow,
	normal
};