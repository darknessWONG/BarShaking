#include "stdafx.h"
#include "FlashLight.h"


FlashLight::FlashLight()
{
}


FlashLight::~FlashLight()
{
}

void FlashLight::set_member(int rel_x, int rel_y, double width, double radin)
{
	this->rel_x = rel_x;
	this->rel_y = rel_y;
	this->width = width;
	this->radin = radin;
}
