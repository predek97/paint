#include "picture.h"
#include <cmath>


Picture::Picture()
{
	for (int i = 0; i < size_x; i++)
		for (int j = 0; j < size_y; j++)
			map[i][j].setColor(BLACK);
}

Picture::Picture(int x, int y)
{
	size_x = x;
	size_y = y;
	for (int i = 0; i < size_x; i++)
		for (int j = 0; j < size_y; j++)
			map[i][j].setColor(BLACK);
}

Picture::Picture(Picture *picture_to_copy)
{
	size_x = picture_to_copy->size_x;
	size_y = picture_to_copy->size_y;
	for(int i = 0; i < size_x; i++)
		for (int j = 0; j < size_y; j++)
			map[i][j] = picture_to_copy->map[i][j];
}

Picture & Picture::operator=(Picture picture_to_copy)
{
	size_x = picture_to_copy.size_x;
	size_y = picture_to_copy.size_y;
	for (int i = 0; i < size_x; i++)
		for (int j = 0; j < size_y; j++)
			map[i][j] = picture_to_copy.map[i][j];
	return *this;
}

Picture::~Picture()
{
}

int Picture::drawLine(int start_x, int start_y, int end_x, int end_y, int color)
{
	int dx = abs(start_x - end_x), sx = end_x<start_x ? 1 : -1;
	int dy = abs(start_y - end_y), sy = end_y<start_y ? 1 : -1;
	int err = (dx>dy ? dx : -dy) / 2, e2;

	while(true) {
		colorPixel(end_x, end_y, color);
		if (end_x == start_x && end_y == start_y) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; end_x += sx; }
		if (e2 < dy) { err += dx; end_y += sy; }
	}return 0;
}

int Picture::drawRectangle(int start_x, int start_y, int end_x, int end_y, int color)
{
	drawLine(start_x, start_y, start_x, end_y, color);
	drawLine(start_x, end_y, end_x, end_y, color);
	drawLine(end_x, end_y, end_x, start_y, color);
	drawLine(end_x, start_y, start_x, start_y, color);
	return 0;
}

int Picture::bucketFill(int start_x, int start_y, int target_color, int bucket_color)
{
	if (target_color == bucket_color)
		return 0;
	if (getColor_of_Pixel(start_x, start_y) != target_color)
		return 0;
	colorPixel(start_x, start_y, bucket_color);
	if (start_x > 0)
		bucketFill(start_x - 1, start_y, target_color, bucket_color);
	if(start_x  < size_x - 1)
		bucketFill(start_x + 1, start_y, target_color, bucket_color);
	if(start_y > 0)
		bucketFill(start_x, start_y - 1, target_color, bucket_color);
	if(start_y < size_y - 1)
		bucketFill(start_x , start_y + 1, target_color, bucket_color);
	return 0;
}

int Picture::colorPixel(int x, int y, int color)
{
	map[x][y].setColor(color);
	return 0;
}

int Picture::getColor_of_Pixel(int x, int y)
{
	return map[x][y].getColor();
}