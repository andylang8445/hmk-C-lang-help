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
struct coordinate user;
int map[30][30];
int isRevieled[30][30], mineCnt = 0, isInitial = 1;
int mineAddrArray[2][30];


void moveCurser(short x, short y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void mineSeeding(int num) {
	//printf("aa\n");
	srand(time(NULL));
	int x, y, tmpChk;
	for (int i = 0; i < num; i++) {
		while (1) {
			tmpChk = 0;
			x = rand() % 30;
			y = rand() % 30;
			if (abs((user.x - x)) < 2 || abs((user.y - y)) < 2) {
				tmpChk = 1;
			}
			if (map[x][y] == 0 && tmpChk != 1) {
				map[x][y] = -1;
				mineAddrArray[0][mineCnt] = x;
				mineAddrArray[1][mineCnt] = y;
				mineCnt++;
				break;
			}
		}
		//printf("%d, %d\n", x, y);
	}
}

void calculateNumbersAroundMines() {
    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
            if(map[i][j]==-1){
                for(int m=i-1;m<i+2;m++){
                    if(m>=0&&m<30){
                        for(int n=j-1;n<j+2;n++){
                            if(n>=0&&n<30&&map[m][n]>=0){
                                map[m][n]++;
                            }
                        }
                    }
                }
            }
        }
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
	moveCurser(65,3);
	printf("Mine Left: %03d",mineCnt);
	moveCurser(0, 0);
	LeaveCriticalSection(&cs);
}

void printMapAgain() {
	system("cls");
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			if (isRevieled[i][j] == 0&& map[i][j] ==0)//아직 뒤집지 않음
				printf("*");
			else if (isRevieled[i][j] == 2) {//유저가 지뢰로 표시
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("#");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
			}
			else if (map[i][j] == -1) {//지뢰
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("@");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
			}
			else if (map[i][j] > 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
				printf("%d", map[i][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
			}
			if (j < 29)
				printf(" ");
		}
		if (i < 29)
			printf("\n");
	}
}

void printRawValues() {
	system("cls");
	for (int i = 0; i < 30; i++) {
        for(int j=0;j<30;j++){
			printf("%d ", map[i][j]);
        }
		if (i < 29)
			printf("\n");
    }
}

void addMineToTheMap(int mineCntPar) {
	mineSeeding(mineCntPar);
	calculateNumbersAroundMines();
}

void flipGivenAddressCell(int x, int y){//지뢰가 있는 칸을 제외하고 주어진 주소의 칸을 알맞은 형태로 뒤집기
	if (map[x][y] == 0) {//빈칸
		moveCurser(2 * (x), y);
		printf(" ");
		isRevieled[x][y]=1;
	}
	else if (map[x][y] > 0) {//숫자
		moveCurser(2 * (x), y);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		printf("%d",map[x][y]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		isRevieled[x][y]=1;
	}
	return;
}

void flipNeighborCells(int x, int y) {//start working from here
	for (int i = -1; i <= 1; i += 2) {
		if ((x + i) >= 0 && (x + i) < 30) {
			for (int j = -1; j <= 1; j += 2) {
				if ((y + j) >= 0 && (y + j) < 30) {
					if (map[x][j] != -1 && isRevieled[x][y] == 0) {
						flipGivenAddressCell((x + i), (y + j));
						flipNeighborCells((x + i), (y + j));
					}
				}
			}
		}
	}
	return;
}

int main(void) {
	int key;
	srand(time(NULL));
	InitializeCriticalSection(&cs);
	system("title Mine Sweeper");
	//system("mode con: cols=60 lines=30");
	CursorView(0);
	initialize();
	//_beginthreadex(NULL, 0, (_beginthreadex_proc_type)initialize, NULL, 0, NULL);
	PlaySound(TEXT("NationalAnt.wav"), NULL, SND_ASYNC | SND_LOOP);
	while (1) {
		Sleep(1);
		if (mineCnt == 0 && isInitial == 0) {
			int chkTmp = 1;
			for (int i = 0; i < 30; i++) {
				for (int j = 0; j < 30; j++) {
					if (isRevieled[i][j] == 2 && map[i][j] != -1) {
						chkTmp = 0;
					}
				}
			}
			if (chkTmp == 1) {
				system("cls");
				moveCurser(8, 10);
				printf("Game Cleared!");
				break;
			}
		}
		if (_kbhit()) {
			moveCurser(76, 3);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
			printf("%03d", mineCnt);
			moveCurser(2 * (user.x), user.y);
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
				else if (key == 'p') {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
					printRawValues();
				}
				else if (key == 'x') {//뒤집기
					if (isInitial == 1) {
						isInitial = 0;
						addMineToTheMap(150);
					}
					if (isRevieled[user.x][user.y] == 0) { //공개되지 않은 칸
						isRevieled[user.x][user.y] = 1;
						if (map[user.x][user.y] == -1) {//지뢰
							moveCurser(2 * (user.x), user.y);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
							printf("@");
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
							Sleep(1000);
							system("cls");
							//printf("aa");
							return 0;
						}
						else if(map[user.x][user.y]>=0){
							flipNeighborCells(user.x, user.y);
							flipGivenAddressCell(user.x,user.y);
						}
					}
				}
				else if (key == 'c') {//지뢰로 표시 토글
					if (isRevieled[user.x][user.y] == 0 && mineCnt > 0) {//표시하기
						mineCnt--;
						isRevieled[user.x][user.y] = 2;
						moveCurser(2 * (user.x), user.y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
						printf("#");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
					}
					else if (isRevieled[user.x][user.y] == 2) {//표시 지우기
						mineCnt++;
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