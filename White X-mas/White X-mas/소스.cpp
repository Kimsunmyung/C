#include <iostream>
#include <conio.h>
#include <process.h>
#include <Windows.h>
#include <time.h>

using namespace std;

class Number {
private:
	int map[10][10][10];
	int snowmuch;							//눈의 양 설정
	int snowtime;							//눈이 내리는 시간 설정
	int prtmap = 0;
	int x = 5, y = 5;
	int viewnum = 0;						//보는 방향 설정  기본 = 0 = 정면
public:
	void Init();							//각 변수 초기화
	void Tree_Set();						//나무 만들기
	void Print_TMap();						//맵 프린트
	void Tree_View();						//보는 방향 설정
	void Print_FMap();						//앞에서 볼 때
	void Print_LMap();						//왼쪽에서 볼 때
	void Print_RMap();						//오른쪽에서 볼 때
	void Print_BMap();						//뒤에서 볼 때
	void Start_Snow();						//눈내리는 함수
	void Finish_Print();					//보는 방향 설정
};
void gotoxy(char x, char y) {
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
void Number::Init() {
	int key;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			for (int k = 0; k < 10; k++)
				map[i][j][k] = 0;

	cout << "눈 내림의 강도( 1 ~ 4 ) : ";
	cin >> snowmuch;
	cout << "눈 내림 시간 설정(초 단위) : ";
	cin >> snowtime;
	map[0][x][y] = 1;
	system("cls");
	do {
		gotoxy(0, 0);
		Print_TMap();
		key = _getch();
		switch (key) {
		case 72:										//상
			if (x > 2) {
				map[0][x][y] = 0;
				x--;
				map[0][x][y] = 1;
			}
			break;
		case 75:										//하
			if (y > 2) {
				map[0][x][y] = 0;
				y--;
				map[0][x][y] = 1;
			}
			break;
		case 80:										//좌
			if (x < 7) {
				map[0][x][y] = 0;
				x++;
				map[0][x][y] = 1;
			}
			break;
		case 77:										//우
			if (y < 7) {
				map[0][x][y] = 0;
				y++;
				map[0][x][y] = 1;
			}
			break;
		}
	} while (key != 32 && key != 13);					//스페이스바32 혹은 엔터13
	Tree_Set();
}
void Number::Tree_Set() {
	int a = rand() % 2;
	int num = 1;
	if (a == 0) {										//피라미드 2층
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				map[0][x + i][y + j] = num;
				num++;
			}
		}
		map[1][x][y] = num;
	}
	else {												//피라미드 3층
		for (int i = -2; i < 3; i++) {
			for (int j = -2; j < 3; j++) {
				map[0][x + i][y + j] = num;
				num++;
			}
		}
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				map[1][x + i][y + j] = num;
				num++;
				if (num > 25) num = 1;					//A~Z까지만 반복하기 위해 사용
			}
		}
		map[2][x][y] = num;
	}
	Tree_View();
}
void Number::Tree_View() {								//트리 보는 방향 설정
	int key;
	do {
		gotoxy(0, 0);
		Print_TMap();

		switch (viewnum) {
		case 0:
			Print_FMap();
			break;
		case 1:
			Print_RMap();
			break;
		case 2:
			Print_BMap();
			break;
		case 3:
			Print_LMap();
			break;
		}
		key = _getch();
		switch (key) {
		case 75:										//좌
			if (viewnum == 0) {
				viewnum = 3;
			}
			else {
				viewnum--;
			}
			break;
		case 77:										//우
			if (viewnum == 3) {
				viewnum = 0;
			}
			else {
				viewnum++;
			}
			break;
		}
	} while (key != 32 && key != 13);					//스페이스바32 혹은 엔터13
	Start_Snow();
}
void Number::Start_Snow() {
	clock_t start, end;
	start = clock();
	int k;
	int xx, yy;
	do {
		k = snowmuch + rand() % 2 + 1;				//눈의 양 0 = 3~5 1 = 5~7, 2 = 7~9, 3 = 9~11

		for (int i = 0; i < k; i++) {					//눈 만들기
			xx = rand() % 10;
			yy = rand() % 10;
			if (map[9][xx][yy] != 30) {
				map[9][xx][yy] = 30;
			}
			else {
				i--;
			}
		}
		for (int i = 1; i < 10; i++) {					//눈 내리기
			for (int j = 0; j < 10; j++) {
				for (int k = 0; k < 10; k++) {
					if (map[i - 1][j][k] == 0 && map[i][j][k] == 30) {
						map[i - 1][j][k] = 30;
						map[i][j][k] = 0;
					}
				}
			}
		}
		int count;
		for (int i = 0; i < 10; i++) {					//3개만 쌓이도록 하기
			for (int j = 0; j < 10; j++) {
				count = 0;
				for (int k = 0; k < 10; k++) {
					if (map[k][i][j] == 30) {
						count++;
						if (count == 3) {
							map[k + 1][i][j] = 0;
							k = 20;
						}
						if (map[k][i][j] == 0) {
							break;
						}
					}
				}
			}
		}

		gotoxy(0, 0);
		Print_TMap();
		switch (viewnum) {
		case 0:
			Print_FMap();
			break;
		case 1:
			Print_RMap();
			break;
		case 2:
			Print_BMap();
			break;
		case 3:
			Print_LMap();
			break;
		}
		Sleep(500);
		end = clock();
	} while ((end - start) / (double)1000 < snowtime * 2);

	Finish_Print();
}

void Number::Finish_Print() {						//눈이 내린 후 보는 방향 설정 하는 함수
	int key;
	do {
		gotoxy(0, 0);
		Print_TMap();

		switch (viewnum) {
		case 0:
			Print_FMap();
			break;
		case 1:
			Print_RMap();
			break;
		case 2:
			Print_BMap();
			break;
		case 3:
			Print_LMap();
			break;
		}
		key = _getch();
		switch (key) {
		case 75:										//좌
			if (viewnum == 0) {
				viewnum = 3;
			}
			else {
				viewnum--;
			}
			break;
		case 77:										//우
			if (viewnum == 3) {
				viewnum = 0;
			}
			else {
				viewnum++;
			}
			break;
		}
	} while (key != 32 && key != 13);					//스페이스바32 혹은 엔터13

}
void Number::Print_TMap() {								//위에서 본 view
	int p;
	cout << "┌";
	for (int i = 0; i < 20; i++) cout << "─";
	cout << "┐\n";
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (j == 0) cout << "│";
			for (int k = 9; k >= 0; k--) {
				if (map[k][i][j] != 0) {
					p = map[k][i][j];
					if (p != 30) {
						cout << (char)(64 + p) << (char)(64 + p);
					}
					else {
						cout << "＊";
					}
					break;
				}
				else if (k == 0) {
					cout << "  ";
				}
			}
			if (j == 9) cout << "│";
		}
		cout << endl;
	}
	cout << "└";
	for (int i = 0; i < 20; i++) cout << "─";
	cout << "┘\n";
}
void Number::Print_FMap() {							//정면 z = 0 x = 9` y = 0
													//앞에서 본 view
	int p;
	cout << "┌";
	for (int i = 0; i < 20; i++) cout << "─";
	cout << "┐\n";
	for (int i = 9; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			if (j == 0) cout << "│";
			for (int k = 9; k >= 0; k--) {
				if (map[i][k][j] != 0) {
					p = map[i][k][j];
					if (p != 30) {
						cout << (char)(64 + p) << (char)(64 + p);
					}
					else {
						cout << "＊";
					}
					break;
				}
				else if (k == 0) {
					cout << "  ";
				}
			}
			if (j == 9) cout << "│";
		}
		cout << endl;
	}
	cout << "└";
	for (int i = 0; i < 20; i++) cout << "─";
	cout << "┘\n";
}
void Number::Print_BMap() {							//뒷면 z = 0 x = 0` y = 9
													//뒤에서 본 view
	int p;
	cout << "┌";
	for (int i = 0; i < 20; i++) cout << "─";
	cout << "┐\n";
	for (int i = 9; i >= 0; i--) {
		for (int j = 9; j >= 0; j--) {
			if (j == 9) cout << "│";
			for (int k = 0; k < 10; k++) {
				if (map[i][k][j] != 0) {
					p = map[i][k][j];
					if (p != 30) {
						cout << (char)(64 + p) << (char)(64 + p);
					}
					else {
						cout << "＊";
					}
					break;
				}
				else if (k == 9) {
					cout << "  ";
				}
			}
			if (j == 0) cout << "│";
		}
		cout << endl;
	}
	cout << "└";
	for (int i = 0; i < 20; i++) cout << "─";
	cout << "┘\n";
}
void Number::Print_RMap() {								//오른쪽에서 본 view
	int p;
	cout << "┌";
	for (int i = 0; i < 20; i++) cout << "─";
	cout << "┐\n";
	for (int i = 9; i >= 0; i--) {
		for (int j = 9; j >= 0; j--) {
			if (j == 9) cout << "│";
			for (int k = 9; k >= 0; k--) {
				if (map[i][j][k] != 0) {
					p = map[i][j][k];
					if (p != 30) {
						cout << (char)(64 + p) << (char)(64 + p);
					}
					else {
						cout << "＊";
					}
					break;
				}
				else if (k == 0) {
					cout << "  ";
				}
			}
			if (j == 0) cout << "│";
		}
		cout << endl;
	}
	cout << "└";
	for (int i = 0; i < 20; i++) cout << "─";
	cout << "┘\n";
}
void Number::Print_LMap() {								//왼쪽에서 본 view
	int p;
	cout << "┌";
	for (int i = 0; i < 20; i++) cout << "─";
	cout << "┐\n";
	for (int i = 9; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			if (j == 0) cout << "│";
			for (int k = 0; k < 10; k++) {
				if (map[i][j][k] != 0) {
					p = map[i][j][k];
					if (p != 30) {
						cout << (char)(64 + p) << (char)(64 + p);
						break;
					}
					else {
						cout << "＊";
					}
					break;
				}
				else if (k == 9) {
					cout << "  ";
				}
			}
			if (j == 9) cout << "│";
		}
		cout << endl;
	}
	cout << "└";
	for (int i = 0; i < 20; i++) cout << "─";
	cout << "┘\n";
}
void main() {

	CONSOLE_CURSOR_INFO Curinfo;																	//커서 깜빡임 없애는 함수
	Curinfo.dwSize = 1;
	Curinfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Curinfo);

	srand(time(NULL));																				//시드값 시간으로 초기화

	Number nm;
	nm.Init();
}
