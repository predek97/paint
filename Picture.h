#pragma once
#include "Pixel.h"
#include "conio2.h"
#define MAX_SIZE_X 50
#define MAX_SIZE_Y 20

class Picture
{
public:
	Picture();
	Picture(int x, int y);
	Picture(Picture *picture_to_copy);
	Picture &operator=(Picture picture_to_copy);
	~Picture();
	int drawLine(int start_x, int start_y, int end_x, int end_y, int color);
	int drawRectangle(int start_x, int start_y, int end_x, int end_y, int color);
	int bucketFill(int start_x, int start_y, int target_color, int bucket_color);
	int colorPixel( int x, int y, int color);
	int getColor_of_Pixel(int x, int y);
private:
	int size_x = MAX_SIZE_X, size_y = MAX_SIZE_Y;
	Pixel map[MAX_SIZE_X][MAX_SIZE_Y];
};