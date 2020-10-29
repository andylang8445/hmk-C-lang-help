#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#include <process.h>

#pragma comment(lib, "winmm.lib")
#pragma warning(disable : 4996)
#pragma message("This program is designed to run on Windows")

CRITICAL_SECTION cs;

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
	LeaveCriticalSection(&cs);
}

int main(void) {
	char tmp;
	InitializeCriticalSection(&cs);
	system("title Mine Sweeper");
	system("mode con: cols=60 lines=30");
	CursorView(0);
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)initialize, NULL, 0, NULL);
	PlaySound(TEXT("Music.wav"), NULL, SND_ASYNC | SND_LOOP);
	while (1) {
		scanf("%c", &tmp);
		if (tmp == 'a') {
			PlaySound(TEXT("NationalAnt.wav"), NULL, SND_ASYNC | SND_LOOP);
			moveCurser(0, 0);
		}
		else if (tmp == 'b') {
			PlaySound(TEXT("Music.wav"), NULL, SND_ASYNC | SND_LOOP);
			moveCurser(0, 0);
		}
		else if (tmp == 'c')
			break;
	}
	return 0;
}