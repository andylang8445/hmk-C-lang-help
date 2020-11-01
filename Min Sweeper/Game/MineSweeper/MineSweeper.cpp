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
#pragma warning(disable : 6385)
#pragma message("This program is designed to run on Windows")

struct coordinate {
	int x = 0, y = 0;
};

CRITICAL_SECTION cs;
struct coordinate user, mine[20];
int map[30][30];
int isRevieled[30][30], mineCnt = 0;


void moveCurser(short x, short y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void mineSeeding(int num) {//항상 num < 20
	mineCnt = num;
	for (int i = 0; i < num; i++) {
		
	}
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
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			map[i][j] = 0;
			isRevieled[i][j] = 0;
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
		Sleep(10);
	}
	moveCurser(0, 0);
	LeaveCriticalSection(&cs);
}

void printMapAgain() {
	system("cls");
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			if (isRevieled[i][j] == 0)//아직 뒤집지 않음
				printf("*");
			else if (isRevieled[i][j] == 2) {//유저가 지뢰로 표시
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("#");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
			}
			if (j < 29)
				printf(" ");
		}
		if (i < 29)
			printf("\n");
	}
}

int main(void) {
	int key;
	srand(time(NULL));
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
				moveCurser(2 * (user.x), user.y);
				if (isRevieled[user.x][user.y] == 0) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
					printf("*");
				}
				else if (isRevieled[user.x][user.y] == 2) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					printf("#");
				}
				switch (key) {
				case 72:
					if (user.y > 0)
						user.y--;
					break;
				case 75:
					if (user.x > 0)
						user.x--;
					break;
				case 77:
					if (user.x < 29)
						user.x++;
					break; 
				case 80:
					if (user.y < 29)
						user.y++;
					//printf("%d", user.y);
					break;
				}
				moveCurser(2 * (user.x), user.y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				if (isRevieled[user.x][user.y] == 0) {
					printf("*");
				}
				else if (isRevieled[user.x][user.y] == 2) {
					printf("#");
				}
				//else if(map[user.x][user.y])

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
				else if (key == 'r') {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
					printMapAgain();
				}
				else if (key == 'x') {//뒤집기
					if (isRevieled[user.x][user.y] == 0) { //공개되지 않은 칸
						isRevieled[user.x][user.y] = 1;
						if (map[user.x][user.y] == -1) {//지뢰
							//Game Over
						}
						else if (map[user.x][user.y] == 0) {//빈칸
							moveCurser(2 * (user.x), user.y);
							printf(" ");
						}
					}
				}
				else if (key == 'c') {//지뢰로 표시 토글
					if (isRevieled[user.x][user.y] == 0) {//표시하기
						isRevieled[user.x][user.y] = 2;
						moveCurser(2 * (user.x), user.y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
						printf("#");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
					}
					else if (isRevieled[user.x][user.y] == 2) {//표시 지우기
						isRevieled[user.x][user.y] = 0;
						moveCurser(2 * (user.x), user.y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
						printf("*");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
					}
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