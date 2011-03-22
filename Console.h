#include <Windows.h>

class Console
{
private:
	Console() {};

public:
	static void to(int column, int line)
	{
		COORD cord = {column, line};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	}

	static COORD get()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
			return COORD();
		return csbi.dwCursorPosition;
	}
};
