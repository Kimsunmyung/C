#include <iostream>
#include <conio.h>
#include <process.h>
#include <Windows.h>
#include <time.h>

using namespace std;

class Number {
private:
	int map[10][10][10];
	int snowmuch;							//���� �� ����
	int snowtime;							//���� ������ �ð� ����
	int prtmap = 0;
	int x = 5, y = 5;
	int viewnum = 0;						//���� ���� ����  �⺻ = 0 = ����
public:
	void Init();							//�� ���� �ʱ�ȭ
	void Tree_Set();						//���� �����
	void Print_TMap();						//�� ����Ʈ
	void Tree_View();						//���� ���� ����
	void Print_FMap();						//�տ��� �� ��
	void Print_LMap();						//���ʿ��� �� ��
	void Print_RMap();						//�����ʿ��� �� ��
	void Print_BMap();						//�ڿ��� �� ��
	void Start_Snow();						//�������� �Լ�
	void Finish_Print();					//���� ���� ����
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

	cout << "�� ������ ����( 1 ~ 4 ) : ";
	cin >> snowmuch;
	cout << "�� ���� �ð� ����(�� ����) : ";
	cin >> snowtime;
	map[0][x][y] = 1;
	system("cls");
	do {
		gotoxy(0, 0);
		Print_TMap();
		key = _getch();
		switch (key) {
		case 72:										//��
			if (x > 2) {
				map[0][x][y] = 0;
				x--;
				map[0][x][y] = 1;
			}
			break;
		case 75:										//��
			if (y > 2) {
				map[0][x][y] = 0;
				y--;
				map[0][x][y] = 1;
			}
			break;
		case 80:										//��
			if (x < 7) {
				map[0][x][y] = 0;
				x++;
				map[0][x][y] = 1;
			}
			break;
		case 77:										//��
			if (y < 7) {
				map[0][x][y] = 0;
				y++;
				map[0][x][y] = 1;
			}
			break;
		}
	} while (key != 32 && key != 13);					//�����̽���32 Ȥ�� ����13
	Tree_Set();
}
void Number::Tree_Set() {
	int a = rand() % 2;
	int num = 1;
	if (a == 0) {										//�Ƕ�̵� 2��
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				map[0][x + i][y + j] = num;
				num++;
			}
		}
		map[1][x][y] = num;
	}
	else {												//�Ƕ�̵� 3��
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
				if (num > 25) num = 1;					//A~Z������ �ݺ��ϱ� ���� ���
			}
		}
		map[2][x][y] = num;
	}
	Tree_View();
}
void Number::Tree_View() {								//Ʈ�� ���� ���� ����
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
		case 75:										//��
			if (viewnum == 0) {
				viewnum = 3;
			}
			else {
				viewnum--;
			}
			break;
		case 77:										//��
			if (viewnum == 3) {
				viewnum = 0;
			}
			else {
				viewnum++;
			}
			break;
		}
	} while (key != 32 && key != 13);					//�����̽���32 Ȥ�� ����13
	Start_Snow();
}
void Number::Start_Snow() {
	clock_t start, end;
	start = clock();
	int k;
	int xx, yy;
	do {
		k = snowmuch + rand() % 2 + 1;				//���� �� 0 = 3~5 1 = 5~7, 2 = 7~9, 3 = 9~11

		for (int i = 0; i < k; i++) {					//�� �����
			xx = rand() % 10;
			yy = rand() % 10;
			if (map[9][xx][yy] != 30) {
				map[9][xx][yy] = 30;
			}
			else {
				i--;
			}
		}
		for (int i = 1; i < 10; i++) {					//�� ������
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
		for (int i = 0; i < 10; i++) {					//3���� ���̵��� �ϱ�
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

void Number::Finish_Print() {						//���� ���� �� ���� ���� ���� �ϴ� �Լ�
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
		case 75:										//��
			if (viewnum == 0) {
				viewnum = 3;
			}
			else {
				viewnum--;
			}
			break;
		case 77:										//��
			if (viewnum == 3) {
				viewnum = 0;
			}
			else {
				viewnum++;
			}
			break;
		}
	} while (key != 32 && key != 13);					//�����̽���32 Ȥ�� ����13

}
void Number::Print_TMap() {								//������ �� view
	int p;
	cout << "��";
	for (int i = 0; i < 20; i++) cout << "��";
	cout << "��\n";
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (j == 0) cout << "��";
			for (int k = 9; k >= 0; k--) {
				if (map[k][i][j] != 0) {
					p = map[k][i][j];
					if (p != 30) {
						cout << (char)(64 + p) << (char)(64 + p);
					}
					else {
						cout << "��";
					}
					break;
				}
				else if (k == 0) {
					cout << "  ";
				}
			}
			if (j == 9) cout << "��";
		}
		cout << endl;
	}
	cout << "��";
	for (int i = 0; i < 20; i++) cout << "��";
	cout << "��\n";
}
void Number::Print_FMap() {							//���� z = 0 x = 9` y = 0
													//�տ��� �� view
	int p;
	cout << "��";
	for (int i = 0; i < 20; i++) cout << "��";
	cout << "��\n";
	for (int i = 9; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			if (j == 0) cout << "��";
			for (int k = 9; k >= 0; k--) {
				if (map[i][k][j] != 0) {
					p = map[i][k][j];
					if (p != 30) {
						cout << (char)(64 + p) << (char)(64 + p);
					}
					else {
						cout << "��";
					}
					break;
				}
				else if (k == 0) {
					cout << "  ";
				}
			}
			if (j == 9) cout << "��";
		}
		cout << endl;
	}
	cout << "��";
	for (int i = 0; i < 20; i++) cout << "��";
	cout << "��\n";
}
void Number::Print_BMap() {							//�޸� z = 0 x = 0` y = 9
													//�ڿ��� �� view
	int p;
	cout << "��";
	for (int i = 0; i < 20; i++) cout << "��";
	cout << "��\n";
	for (int i = 9; i >= 0; i--) {
		for (int j = 9; j >= 0; j--) {
			if (j == 9) cout << "��";
			for (int k = 0; k < 10; k++) {
				if (map[i][k][j] != 0) {
					p = map[i][k][j];
					if (p != 30) {
						cout << (char)(64 + p) << (char)(64 + p);
					}
					else {
						cout << "��";
					}
					break;
				}
				else if (k == 9) {
					cout << "  ";
				}
			}
			if (j == 0) cout << "��";
		}
		cout << endl;
	}
	cout << "��";
	for (int i = 0; i < 20; i++) cout << "��";
	cout << "��\n";
}
void Number::Print_RMap() {								//�����ʿ��� �� view
	int p;
	cout << "��";
	for (int i = 0; i < 20; i++) cout << "��";
	cout << "��\n";
	for (int i = 9; i >= 0; i--) {
		for (int j = 9; j >= 0; j--) {
			if (j == 9) cout << "��";
			for (int k = 9; k >= 0; k--) {
				if (map[i][j][k] != 0) {
					p = map[i][j][k];
					if (p != 30) {
						cout << (char)(64 + p) << (char)(64 + p);
					}
					else {
						cout << "��";
					}
					break;
				}
				else if (k == 0) {
					cout << "  ";
				}
			}
			if (j == 0) cout << "��";
		}
		cout << endl;
	}
	cout << "��";
	for (int i = 0; i < 20; i++) cout << "��";
	cout << "��\n";
}
void Number::Print_LMap() {								//���ʿ��� �� view
	int p;
	cout << "��";
	for (int i = 0; i < 20; i++) cout << "��";
	cout << "��\n";
	for (int i = 9; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			if (j == 0) cout << "��";
			for (int k = 0; k < 10; k++) {
				if (map[i][j][k] != 0) {
					p = map[i][j][k];
					if (p != 30) {
						cout << (char)(64 + p) << (char)(64 + p);
						break;
					}
					else {
						cout << "��";
					}
					break;
				}
				else if (k == 9) {
					cout << "  ";
				}
			}
			if (j == 9) cout << "��";
		}
		cout << endl;
	}
	cout << "��";
	for (int i = 0; i < 20; i++) cout << "��";
	cout << "��\n";
}
void main() {

	CONSOLE_CURSOR_INFO Curinfo;																	//Ŀ�� ������ ���ִ� �Լ�
	Curinfo.dwSize = 1;
	Curinfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Curinfo);

	srand(time(NULL));																				//�õ尪 �ð����� �ʱ�ȭ

	Number nm;
	nm.Init();
}
