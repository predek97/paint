#pragma once
class Pixel
{
public:
	Pixel();
	~Pixel();
	int getColor();
	int setColor(int new_color);
private:
	int color;
};