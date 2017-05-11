#include <iostream>
#include "Program.h"

int main(int argc, char* argv[])
{
	Program program1;
	if (argc > 1)
	{
		program1.readfromFile(argv[1]);
	}
	do {
		program1.display(*program1.picture);
		program1.handleInput();
	} while (!program1.isEnding());

	return 0;
}