#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#include <process.h>

#pragma comment(lib, "winmm.lib")
#pragma warning(disable : 4996)

void moveCurser(short x, short y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main(void) {
	char tmp;
	system("title Mine Sweeper");
	PlaySound(TEXT("Music.wav"), NULL, SND_ASYNC | SND_LOOP);
	while (scanf("%c",&tmp) != EOF);
	return 0;
}