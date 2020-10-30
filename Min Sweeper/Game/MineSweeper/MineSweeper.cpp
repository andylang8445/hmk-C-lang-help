#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#include <process.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#pragma comment(lib, "winmm.lib")
#pragma warning(disable : 4996)
#pragma message("This program is designed to run on Windows")

struct coordinate {
	int x = 0, y = 0;
};

CRITICAL_SECTION cs;
struct coordinate user;
int map[60][30];


void moveCurser(short x, short y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CursorView(char show)//0: 커서숨기기, 1: 커서 보이기
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void initialize() {
	EnterCriticalSection(&cs);
	user.x = 0;
	user.y = 0;
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 30; j++) {
			map[i][j] = 1;
		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			printf("*");
			if (j < 29)
				printf(" ");
		}
		if(i<29)
			printf("\n");
		Sleep(100);
	}
	moveCurser(0, 0);
	LeaveCriticalSection(&cs);
}

int main(void) {
	int key;
	InitializeCriticalSection(&cs);
	system("title Mine Sweeper");
	system("mode con: cols=60 lines=30");
	CursorView(0);
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)initialize, NULL, 0, NULL);
	PlaySound(TEXT("NationalAnt.wav"), NULL, SND_ASYNC | SND_LOOP);
	while (1) {
		Sleep(1);
		if (_kbhit()) {
			key = _getch();
			if (key == 224 || key == 0) {
				key = _getch();
				moveCurser(user.x, user.y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				if (map[user.x][user.y] == 1) {
					printf("*");
				}
				switch (key) {
				case 72:
					if (user.y > 0)
						user.y--;
					break;
				case 75:
					if (user.x > 0)
						user.x-=2;
					break;
				case 77:
					if (user.x < 59)
						user.x+=2;
					break;
				case 80:
					if (user.y < 29)
						user.y++;
					//printf("%d", user.y);
					break;
				}
				moveCurser(user.x, user.y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				if (map[user.x][user.y] == 1) {
					printf("*");
				}
			}
			else {
				if (key == 'a') {
					PlaySound(TEXT("NationalAnt.wav"), NULL, SND_ASYNC | SND_LOOP);
					//moveCurser(0, 1);
				}
				else if (key == 'b') {
					PlaySound(TEXT("Music.wav"), NULL, SND_ASYNC | SND_LOOP);
					//moveCurser(0, 0);
				}
				else if (key == 'c')
					break;
				else if (key == 'm') {
					PlaySound(NULL, NULL, 0);
				}
			}
		}
		
	}
	return 0;
}