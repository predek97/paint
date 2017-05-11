#pragma once
#include "Picture.h"
#include <stdio.h>


#define OFFSET 1
#define DISPLAY_OFFSET 1
#define MENU_POSITION 55 //0-L 55-R
#define PICTURE_START 0  //0-L 30-R
#define NAME_SIZE 20
class Program
{
public:
	Program();
	~Program();
	bool isEnding();
	int display(Picture pictureToShow);
	int savetoFile(char * filename);
	int readfromFile(char * filename);
	int readfromFile();
	int handleInput();
	Picture *picture;
	char picture_name[NAME_SIZE] = "\0";
	char *current_mode = "przewijanie";
private:
	int drawLine(int start_x, int start_y, int color);
	int drawRectangle (int start_x, int start_y, int color);
	int createNewPicture();
	bool end;
	int number_of_pictures;
	int x, y, attr;
	int size_x, size_y;
	const int number_of_colors = 2;
};