#include "Pixel.h"

Pixel::Pixel()
{
	color = 0;
}

Pixel::~Pixel()
{
}

int Pixel::getColor()
{
	return color;
}

int Pixel::setColor(int new_color)
{
	color = new_color;
	return 0;
}