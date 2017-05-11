#include <cmath> 
#include "Program.h"
#include "conio2.h"



Program::Program()
{
	settitle("Szymon Mroz 165321");
	number_of_pictures = 1;
	x = 0, y = 0, attr = WHITE;
	end = false;
	size_x = 50, size_y = 20;
	picture = new Picture();
}
Program::~Program()
{
	delete picture;
}
bool Program::isEnding()
{
	return end;
}

int Program::display(Picture pictureToShow)
{
	clrscr();
	textcolor(WHITE);
	textbackground(BLACK);
	gotoxy(MENU_POSITION, 1);
	cputs(picture_name);
	gotoxy(MENU_POSITION, 2);
	cputs("tryb: ");
	char* current_mode_to_display = current_mode;
	cputs(current_mode_to_display);
	gotoxy(MENU_POSITION, 3);
	cputs("pozycja kursora:");
	char *a = new char[10];
	cputs(_itoa(x ,a ,10));
	cputs(" ");
	cputs(_itoa(y, a, 10));
	gotoxy(MENU_POSITION, 4);
	cputs("ESC = wyjscie/przerwanie");
	gotoxy(MENU_POSITION, 5);
	cputs("strzalki = poruszanie");
	gotoxy(MENU_POSITION, 6);
	cputs("1234567890qwerty = kolor");
	gotoxy(MENU_POSITION, 7);
	cputs("l = rysowanie prostej");
	gotoxy(MENU_POSITION, 8);
	cputs("k = rysowanie prostokatu");
	gotoxy(MENU_POSITION, 9);
	cputs("n = nowy obrazek");
	gotoxy(MENU_POSITION, 10);
	cputs("s = zapis do pliku");
	gotoxy(MENU_POSITION, 11);
	cputs("o = wczytanie z pliku");
	gotoxy(MENU_POSITION, 12);
	cputs("i = plik domyslny");
	for (int i = 0; i < size_x; i++)
	{
		for (int j = 0; j < size_y; j++)
		{
			if (pictureToShow.getColor_of_Pixel(i, j) != BLACK)
			{
				textbackground(pictureToShow.getColor_of_Pixel(i, j));
				gotoxy(i + DISPLAY_OFFSET + PICTURE_START, j + DISPLAY_OFFSET);
				putch(' ');
			}
			else
				textbackground(BLACK);
		}
	}
	textbackground(BLACK);
	gotoxy(x + DISPLAY_OFFSET + PICTURE_START, y + DISPLAY_OFFSET);
	textcolor(attr);
	putch('*');
	return 0;
}
int Program::savetoFile(char *filename)
{
	current_mode = "zapisywanie obrazka";
	display(picture);
	gotoxy(DISPLAY_OFFSET + PICTURE_START, DISPLAY_OFFSET);
	cputs("Czy chcesz podac nowa nazwe pliku?(Y/N)");
	int zn = getch();
	if (zn == 'Y' || zn == 'y')
	{
		for (int i = 0; i < NAME_SIZE; i++)
		{
			int zn = getche();
			if ((zn >= 64 && zn <= 90) || (zn >= 97 && zn <= 122) || zn == '.' || zn == '_')
				picture_name[i] = zn;
			else i = NAME_SIZE;
		}
		filename = picture_name;
	}
	FILE *opened_file = fopen(filename, "w");
	if (opened_file != NULL)
	{
		char *buffer = new char[100];
		fputs(_itoa(size_x, buffer, 10), opened_file);
		fputs("\n", opened_file);
		fputs(_itoa(size_y, buffer, 10), opened_file);
		fputs("\n", opened_file);
		for (int i = 0; i < size_x; i++)
		{
			for (int j = 0; j < size_y; j++)
			{
				fputs(_itoa(picture->getColor_of_Pixel(i, j), buffer, 10), opened_file);
				fputs("\n", opened_file);
			}
		}
		fclose(opened_file);
	}
	current_mode = "przewijanie";
	return 0;
}
int Program::readfromFile(char* filename)
{
	FILE *opened_file = fopen(filename, "r");
	if (opened_file != NULL)
	{
		for(int i = 0; i < NAME_SIZE; i++)
			picture_name[i] = filename[i];
		char *buffer = new char[100];
		size_x = atoi(fgets(buffer, 100, opened_file));
		size_y = atoi(fgets(buffer, 100, opened_file));
		delete picture;
		*picture = new Picture(size_x, size_y);
		for (int i = 0; i < size_x; i++)
		{
			for (int j = 0; j < size_y; j++)
			{
				picture->colorPixel(i, j, atoi(fgets(buffer, 100, opened_file)));
			}
		}
		fclose(opened_file);
	}
	else
	{
		gotoxy(DISPLAY_OFFSET + PICTURE_START, DISPLAY_OFFSET + 2);
		cputs("Blad wczytywania obrazu");
		getch();
	}
	return 0;

}
int Program::readfromFile()
{
	current_mode = "wczytywanie obrazka";
	display(picture);
	gotoxy(DISPLAY_OFFSET + PICTURE_START, DISPLAY_OFFSET);
	cputs("Podaj nazwe pliku:");
	char new_name[NAME_SIZE] = { '\0' };
	for (int i = 0; i < NAME_SIZE; i++)
	{
		int zn = getche();
		if ((zn >= 64 && zn <= 90) || (zn >= 97 && zn <= 122) || zn == '.' || zn == '_')
			new_name[i] = zn;
		else i = NAME_SIZE;
	}
	readfromFile(new_name);
	current_mode = "przewijanie";
	return 0;
}
int Program::handleInput()
{
	int zn;
	zn = getch();
	if (zn == 0) {//sprawdzenie czy wciœniety klawisz nie odpowiada znakowi alfanumerycznemu
		zn = getch();
		if (zn == 0x48 && y > 0) y--;
		else if (zn == 0x50 && y < size_y - OFFSET) y++;
		else if (zn == 0x4b && x > 0) x--;
		else if (zn == 0x4d && x < size_x - OFFSET) x++;
	}
	else if (zn == 0x1b)
		end = true;
	else if (zn >= '1' && zn <= '9') attr = zn - 49;
	else
	{
		switch (zn)
		{
		case '0':
			attr = 9; break;
		case 'q': case 'Q':
			attr = 10; break;
		case 'w': case 'W':
			attr = 11; break;
		case 'e': case 'E':
			attr = 12; break;
		case 'r': case 'R':
			attr = 13; break;
		case 't': case 'T':
			attr = 14; break;
		case 'y': case 'Y':
			attr = 15; break;
		case 'l': case 'L':
			drawLine(x, y, attr); break;
		case 'k': case 'K':
			drawRectangle(x, y, attr); break;
		case 'f': case 'F':
			picture->bucketFill(x, y, picture->getColor_of_Pixel(x, y), attr); break;
		case 's': case 'S':
			savetoFile(picture_name); break;
		case 'o': case 'O':
			readfromFile(); break;
		case 'i': case 'I':
			readfromFile("default.gmd"); break;
		case 'n': case 'N':
			if(createNewPicture()) current_mode = "przewijanie"; break;
		}
	}
	return 0;
}

int Program::drawLine(int start_x, int start_y, int color)
{
	current_mode = "rysowanie linii";
	int zn;
	do
	{
		Picture interactive = *picture;
		interactive.drawLine(start_x, start_y, x, y, color);
		display(interactive);
		zn = getch();
		if (zn == 0) {//sprawdzenie czy wciœniety klawisz nie odpowiada znakowi alfanumerycznemu
			zn = getch();
			if (zn == 0x48 && y > 0) y--;
			else if (zn == 0x50 && y < size_y - OFFSET) y++;
			else if (zn == 0x4b && x > 0) x--;
			else if (zn == 0x4d && x < size_x - OFFSET) x++;
		}
		else if (zn == 0x1b)
			return 1;
	} while (zn != 'l' && zn != 'L');
	picture->drawLine(start_x, start_y, x, y, color);
	current_mode = "przewijanie";
	return 0;
}
int Program::drawRectangle(int start_x, int start_y, int color)
{
	current_mode = "rysowanie prostokatu";
	int zn;
	do
	{
		Picture interactive = *picture;
		interactive.drawRectangle(start_x, start_y, x, y, color);
		display(interactive);
		zn = getch();
		if (zn == 0) {//sprawdzenie czy wciœniety klawisz nie odpowiada znakowi alfanumerycznemu
			zn = getch();
			if (zn == 27)
				break;
			else if (zn == 0x48 && y > 0) y--;
			else if (zn == 0x50 && y < size_y - OFFSET) y++;
			else if (zn == 0x4b && x > 0) x--;
			else if (zn == 0x4d && x < size_x - OFFSET) x++;
		}
		else if (zn == 0x1b)
			return 1;
	} while (zn != 'k' && zn != 'K');
	picture->drawRectangle(start_x, start_y, x, y, color);
	current_mode = "przewijanie";
	return 0;
}

int Program::createNewPicture()
{
	current_mode = "tworzenie obrazka";
	display(picture);
	int zn = 0;
	int size_of_x = 0;
	int size_of_y = 0;
	gotoxy(PICTURE_START, 1);
	zn = getche();
	if (zn < '0' || zn > '9')
		return -1;
	size_of_x += (zn - 48) * 10;
	zn = getche();
	if (zn < '0' || zn > '9')
		return -1;
	size_of_x += (zn - 48);
	cputs("x");
	zn = getche();
	if (zn < '0' || zn > '9')
		return -1;
	size_of_y += (zn - 48) * 10;
	zn = getche();
	if (zn < '0' || zn > '9')
		return -1;
	size_of_y += (zn - 48);
	bool allowed_x_size = (size_of_x > 0 && size_of_x <= MAX_SIZE_X);
	bool allowed_y_size = (size_of_y > 0 && size_of_y <= MAX_SIZE_Y);
	if (allowed_x_size && allowed_y_size)
	{
			size_x = size_of_x;
			size_y = size_of_y;
		delete picture;
		*picture = new Picture(size_x, size_y);
		x = 0;
		y = 0;
		gotoxy(PICTURE_START, y + 1);
		for (int i = 0; i < NAME_SIZE; i++)
		{
			int zn = getche();
			if ((zn >= 64 && zn <= 90) || (zn >= 97 && zn <= 122) || zn == '.' || zn == '_')
				picture_name[i] = zn;
			else
			{
				for (int j = i; j < NAME_SIZE; j++)
					picture_name[j] = '\0';
				i = NAME_SIZE;
			}
		}
	}
	current_mode = "przewijanie";
	return 0;
}
