#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <process.h>
#include <time.h>
#include <math.h>

int map[10][10] = { 0, };      //��ǻ��1 = 1, ��ǻ��2 = 2, ����� = 3, ������Ѿ� = 4, ��ǻ�� �Ѿ� = 5;
//v��������� �ѹ���
int m1[20] = { 3, 0, 3, 1, 3, 1, 2, 1, 2, 0, 2, 0, 3, 0, 3, 1, 3, 1, 2, 1 };//.�֢�
// �آ�
int m2[20] = { 3, 0, 3, 0, 3, 1, 3, 1, 3, 1, 2, 1, 2, 1, 2, 0, 2, 0, 2, 0 };//.�֡��
// �ء��
//v��������� �ѹ���
int m3[20] = { 0, 2, 0, 2, 1, 2, 1, 3, 1, 3, 0, 3, 0, 2, 0, 2, 1, 2, 1, 3 };// �ע�.
// �٢�
int m4[20] = { 2, 0, 2, 0, 2, 1, 2, 1, 2, 1, 3, 1, 3, 1, 3, 0, 3, 0, 3, 0 };// �ס��.
// �١��
HANDLE hMutex;

int callmenu = 0;//�޴�ȣ��
//���� �����
int cptreset = 0;
int userreset = 0;
int gaming = 0;
int count1;
int count2;
int tcount;
int com1x;
int com1y;
int com1xx;
int com1yy;
int com1xylife;
int com1xxyylife;
int com2x;
int com2y;
int com2xx;
int com2yy;
int com2xylife;
int com2xxyylife;

int com2gogogo;//2��° ���� ��������

int userx;
int usery;
int userxylife;
int userxx;
int useryy;
int userxxyylife;
void gotoxy(char x, char y) {
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

unsigned _stdcall cptmove(void* arg) {
	char a;
	srand(time(NULL));
	count1 = 1;
	count2 = 1;

	int tempfirst = 0;         //�ι�° ���� �ʱ�ȭ �ϱ� ���� ����
	com1x = rand() % 4;
	com1y = rand() % 10;
	com1xx = com1x + 1;
	com1yy = com1y;
	com1xylife = 1;
	com1xxyylife = 1;

	com2xylife = 1;
	com2xxyylife = 1;
	com2gogogo = 0;            //�ι�° ���� ���� Ȯ�� ����

	int speed = 10;
	int sspeed = 100;
	int rndmoving1 = 0;            //�迭�� ����
	int rndcount1 = 0;         //�迭 ������ �Ҳ���?!
	int ai1;               //� �ڷḦ �����ΰ�?!
	int rndmoving2 = 0;            //�迭�� ����
	int rndcount2 = 0;         //�迭 ������ �Ҳ���?!
	int ai2;               //� �ڷḦ �����ΰ�?!
	int k = 0;
	int l = 0;
	while (1) {
		if (cptreset == 1) {
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					map[i][j] = 0;
			com2gogogo = 0;            //�ι�° ���� ���� Ȯ�� ����
			count1 = 1;
			count2 = 1;
			tcount = 1;
			tempfirst = 0;         //�ι�° ���� �ʱ�ȭ �ϱ� ���� ����
			com1x = rand() % 4;
			com1y = rand() % 10;
			com1xx = com1x + 1;
			com1yy = com1y;
			com1xylife = 1;
			com1xxyylife = 1;
			com2xylife = 1;
			com2xxyylife = 1;
			rndmoving1 = 0;            //�迭�� ����
			rndcount1 = 0;         //�迭 ������ �Ҳ���?!
			ai1;               //� �ڷḦ �����ΰ�?!
			rndmoving2 = 0;            //�迭�� ����
			rndcount2 = 0;         //�迭 ������ �Ҳ���?!
			ai2;               //� �ڷḦ �����ΰ�?!
			k = 0;
			l = 0;
			speed = 10;
			cptreset = 0;
		}
		else {
			if (callmenu == 0) {
				if (count1 % 2 == 1) {
					if (rndmoving1 == rndcount1) {
						rndcount1 = rand() % 5 + 15;
						rndmoving1 = 0;
						ai1 = rand() % 4;
					}
					switch (ai1) {
					case 0:
						k = m1[rndmoving1];
						break;
					case 1:
						k = m2[rndmoving1];
						break;
					case 2:
						k = m3[rndmoving1];
						break;
					case 3:
						k = m4[rndmoving1];
						break;
					}
					rndmoving1++;

					if (k == 0) {//��
						if (com1x != 0) {
							if (map[com1x - 1][com1y] == 4 && com1xylife == 1) {
								com1xylife = 0;
								map[com1x][com1y] = 0;
							}
							if (map[com1xx - 1][com1yy] == 4 && com1xxyylife == 1) {
								com1xxyylife = 0;
								map[com1xx][com1yy] = 0;
							}
							map[com1x][com1y] = 0;
							map[com1xx][com1yy] = 0;
							if (com1xylife == 1) {
								map[com1x - 1][com1y] = 1;
							}
							if (com1xxyylife == 1) {
								map[com1xx - 1][com1yy] = 1;
							}
							com1x--;
							com1xx--;
						}
					}
					else if (k == 1) {//��
						if (com1x != 3) {
							if (map[com1x + 1][com1y] == 4 && com1xylife == 1) {
								com1xylife = 0;
								map[com1x][com1y] = 0;
							}
							if (map[com1xx + 1][com1yy] == 4 && com1xxyylife == 1) {
								com1xxyylife = 0;
								map[com1xx][com1yy] = 0;
							}
							map[com1x][com1y] = 0;
							map[com1xx][com1yy] = 0;
							if (com1xylife == 1) {
								map[com1x + 1][com1y] = 1;
							}
							if (com1xxyylife == 1) {
								map[com1xx + 1][com1yy] = 1;
							}
							com1x++;
							com1xx++;
						}
					}
					else if (k == 2) {//��
						if (com1y != 0) {
							if (map[com1x][com1y - 1] == 4 && com1xylife == 1) {
								com1xylife = 0;
								map[com1x][com1y] = 0;
							}
							if (map[com1xx][com1yy - 1] == 4 && com1xxyylife == 1) {
								com1xxyylife = 0;
								map[com1xx][com1yy] = 0;
							}
							if (com1xylife == 1) {
								map[com1x][com1y - 1] = 1;
							}
							if (com1xxyylife == 1) {
								map[com1xx][com1yy - 1] = 1;
							}
							map[com1xx][com1yy] = 0;
							com1yy--;
							map[com1x][com1y] = 0;
							com1y--;
						}
					}
					else if (k == 3) {//��
						if (com1y != 9) {
							if (map[com1x][com1y + 1] == 4 && com1xylife == 1) {
								com1xylife = 0;
								map[com1x][com1y] = 0;
							}
							if (map[com1xx][com1yy + 1] == 4 && com1xxyylife == 1) {
								com1xxyylife = 0;
								map[com1xx][com1yy] = 0;
							}
							if (com1xylife == 1) {
								map[com1x][com1y + 1] = 1;
							}
							if (com1xxyylife == 1) {
								map[com1xx][com1yy + 1] = 1;
							}
							map[com1x][com1y] = 0;
							map[com1xx][com1yy] = 0;
							com1y++;
							com1yy++;
						}
					}




					if (com2gogogo == 1) {
						if (rndmoving2 == rndcount2) {
							rndcount2 = rand() % 5 + 15;
							rndmoving2 = 0;
							ai2 = rand() % 4;
						}
						switch (ai2) {
						case 0:
							l = m1[rndmoving2];
							break;
						case 1:
							l = m2[rndmoving2];
							break;
						case 2:
							l = m3[rndmoving2];
							break;
						case 3:
							l = m4[rndmoving2];
							break;
						}
						rndmoving2++;

						if (l == 0) {//��
							if (com2x != 0) {
								if (map[com2x - 1][com2y] == 4 && com2xylife == 1) {
									com2xylife = 0;
									map[com2x][com2y] = 0;
								}
								if (map[com2xx - 1][com2yy] == 4 && com2xxyylife == 1) {
									com2xxyylife = 0;
									map[com2xx][com2yy] = 0;
								}
								map[com2x][com2y] = 0;
								map[com2xx][com2yy] = 0;
								if (com2xylife == 1) {
									map[com2x - 1][com2y] = 2;
								}
								if (com2xxyylife == 1) {
									map[com2xx - 1][com2yy] = 2;
								}
								com2x--;
								com2xx--;
							}
						}
						else if (l == 1) {//��
							if (com2x != 3) {
								if (map[com2x + 1][com2y] == 4 && com2xylife == 1) {
									com2xylife = 0;
									map[com2x][com2y] = 0;
								}
								if (map[com2xx + 1][com2yy] == 4 && com2xxyylife == 1) {
									com2xxyylife = 0;
									map[com2xx][com2yy] = 0;
								}
								map[com2x][com2y] = 0;
								map[com2xx][com2yy] = 0;
								if (com2xylife == 1) {
									map[com2x + 1][com2y] = 2;
								}
								if (com2xxyylife == 1) {
									map[com2xx + 1][com2yy] = 2;
								}
								com2x++;
								com2xx++;
							}
						}
						else if (l == 2) {//��
							if (com2y != 0) {
								if (map[com2x][com2y - 1] == 4 && com2xylife == 1) {
									com2xylife = 0;
									map[com2x][com2y] = 0;
								}
								if (map[com2xx][com2yy - 1] == 4 && com2xxyylife == 1) {
									com2xxyylife = 0;
									map[com2xx][com2yy] = 0;
								}
								map[com2xx][com2yy] = 0;
								map[com2x][com2y] = 0;
								if (com2xylife == 1) {
									map[com2x][com2y - 1] = 2;
								}
								if (com2xxyylife == 1) {
									map[com2xx][com2yy - 1] = 2;
								}
								com2yy--;
								com2y--;
							}
						}
						else if (l == 3) {//��
							if (com2y != 9) {
								if (map[com2x][com2y + 1] == 4 && com2xylife == 1) {
									com2xylife = 0;
									map[com2x][com2y] = 0;
								}
								if (map[com2xx][com2yy + 1] == 4 && com2xxyylife == 1) {
									com2xxyylife = 0;
									map[com2xx][com2yy] = 0;
								}
								map[com2x][com2y] = 0;
								map[com2xx][com2yy] = 0;
								if (com2xylife == 1) {
									map[com2x][com2y + 1] = 2;
								}
								if (com2xxyylife == 1) {
									map[com2xx][com2yy + 1] = 2;
								}
								com2y++;
								com2yy++;
							}
						}

					}

				}
				else {                                 //�Ѿ� �����̴� �Լ�
					for (int i = 0; i < 10; i++) {
						if (map[9][i] == 5) map[9][i] = 0;
					}
					for (int i = 8; i >= 0; i--) {
						for (int j = 0; j < 10; j++) {
							if (map[i][j] == 5) {
								if (i + 1 == userx && j == usery && userxylife == 1) {
									userxylife = 0;
									map[i][j] = 0;
									map[i + 1][j] = 0;
								}
								else if ((i + 1 == userxx && j == useryy && userxxyylife == 1)) {
									userxxyylife = 0;
									map[i][j] = 0;
									map[i + 1][j] = 0;
								}
								else {
									map[i][j] = 0;
									map[i + 1][j] = 5;
								}
							}
						}
					}
					for (int i = 0; i < 9; i++) {
						for (int j = 0; j < 10; j++) {
							if (map[i][j] == 4) {
								if (i - 1 == com1x && j == com1y && com1xylife == 1) {
									com1xylife = 0;
									map[i][j] = 0;
									map[i - 1][j] = 0;
								}
								else if ((i - 1 == com1xx && j == com1yy && com1xxyylife == 1)) {
									com1xxyylife = 0;
									map[i][j] = 0;
									map[i - 1][j] = 0;
								}
								else {
									map[i][j] = 0;
									map[i - 1][j] = 4;
								}
							}
						}
					}
				}
				if (tcount >= 100) {                              //2��° ����� ���� ����
					if (tempfirst == 0) {                           //2��° ����� �ʱ�ȭ
						com2x = rand() % 4;
						com2y = rand() % 10;
						if (com1y < 5) com2y += 5;
						com2xx = com2x + 1;
						com2yy = com2y;
						map[com2x][com2y] = 2;
						map[com2xx][com2yy] = 2;
						tempfirst = 1;
					}
					com2gogogo = 1;
				}
				if (sspeed == 0) {
					sspeed = 100;
					if (speed >= 5)speed--;
				}
				else {
					sspeed--;
				}
				if (count1 >= speed) {
					if (com1xylife == 1 || com1xxyylife == 1) {
						if (abs(com1y - usery) <= 1) {
							count1 = 0;
							map[com1x + 2][com1y] = 5;
						}
					}
				}
				if (count2 >= speed && com2gogogo == 1) {
					if (com2xylife == 1 || com2xxyylife == 1) {
						if (abs(com2y - usery) <= 1) {
							count2 = 0;
							map[com2x + 2][com2y] = 5;
						}
					}
				}
				Sleep(100);
				count1++;
				count2++;
				tcount++;
				if (com1xylife == 0 && com1xxyylife == 0 && com2gogogo == 0) {
					callmenu = 1;
					system("cls");
					gotoxy(10, 5);
					printf("���� �¸�\n");
					Sleep(1000);
					gotoxy(10, 5);
					printf("1. ���ӽ���");
					gotoxy(10, 7);
					printf("2. ���Ӱ��");
					gotoxy(10, 9);
					printf("3. ��������");
				}
				if (com1xylife == 0 && com1xxyylife == 0 && com2xylife == 0 && com2xxyylife == 0) {
					callmenu = 1;
					system("cls");
					gotoxy(10, 5);
					printf("���� �¸�\n");
					Sleep(1000);
					gotoxy(10, 5);
					printf("1. ���ӽ���");
					gotoxy(10, 7);
					printf("2. ���Ӱ��");
					gotoxy(10, 9);
					printf("3. ��������");
				}
				if (userxylife == 0 && userxxyylife == 0) {
					callmenu = 1;
					system("cls");
					gotoxy(10, 5);
					printf("���� ����");
					Sleep(1000);
					gotoxy(10, 5);
					printf("1. ���ӽ���");
					gotoxy(10, 7);
					printf("2. ���Ӱ��");
					gotoxy(10, 9);
					printf("3. ��������");
				}
			}
		}
	}
	return 0;
}

unsigned _stdcall usermove(void* arg) {

	clock_t start, end;
	clock_t timetime = 2;

	userx = 7;
	usery = 5;
	userxx = 8;
	useryy = 5;
	userxylife = 1;
	userxxyylife = 1;
	map[userx][usery] = 3;
	map[userxx][useryy] = 3;

	int key;
	start = clock();
	while (1) {
		if (userreset == 1) {
			userx = 7;
			usery = 5;
			userxx = 8;
			useryy = 5;
			userxylife = 1;
			userxxyylife = 1;
			map[userx][usery] = 3;
			map[userxx][useryy] = 3;
			userreset = 0;
		}
		else {
			key = _getch();
			if (callmenu == 0) {
				switch (key) {
				case 72:   //��
					if (userx != 5) {
						if (map[userx - 1][usery] == 5 && userxylife == 1) {
							userxylife = 0;
							map[userx][usery] = 0;
						}
						map[userx - 1][usery] = map[userx][usery];
						map[userx][usery] = 0;
						if (map[userxx - 1][useryy] == 5 && userxxyylife == 1) {
							userxxyylife = 0;
							map[userxx][useryy] = 0;
						}
						map[userxx - 1][useryy] = map[userxx][useryy];
						map[userxx][useryy] = 0;
						userx--;
						userxx--;
					}
					break;
				case 80:   //��
					if (userx != 8) {
						if (map[userxx + 1][useryy] == 5 && userxylife == 1) {
							userxxyylife = 0;
							map[userxx][useryy] = 0;
						}
						map[userxx + 1][useryy] = map[userxx][useryy];
						map[userxx][useryy] = 0;
						if (map[userx + 1][usery] == 5 && userxxyylife == 1) {
							userxylife = 0;
							map[userx][usery] = 0;
						}
						map[userx + 1][usery] = map[userx][usery];
						map[userx][usery] = 0;
						userx++;
						userxx++;
					}

					break;
				case 75://��
					if (usery != 0) {
						if (map[userx][usery - 1] == 5 && userxylife == 1) {
							userxylife = 0;
							map[userx][usery] = 0;
						}
						if (map[userxx][useryy - 1] == 5 && userxxyylife == 1) {
							userxxyylife = 0;
							map[userxx][useryy] = 0;
						}
						map[userx][usery - 1] = map[userx][usery];
						map[userxx][useryy - 1] = map[userxx][useryy];
						map[userx][usery] = 0;
						map[userxx][useryy] = 0;
						usery--;
						useryy--;
					}
					break;
				case 77://��
					if (usery != 9) {
						if (map[userx][usery + 1] == 5 && userxylife == 1) {
							userxylife = 0;
							map[userx][usery] = 0;
						}
						if (map[userxx][useryy + 1] == 5 && userxxyylife == 1) {
							userxxyylife = 0;
							map[userxx][useryy] = 0;
						}
						map[userx][usery + 1] = map[userx][usery];
						map[userxx][useryy + 1] = map[userxx][useryy];
						map[userx][usery] = 0;
						map[userxx][useryy] = 0;
						usery++;
						useryy++;
					}
					break;
				case 32:   //�����̽���
					end = clock();
					if ((end - start) / (double)1000 > timetime) {
						map[userx - 1][usery] = 4;
						start = clock();
					}
					break;
				case 224:
					break;
				default:
					callmenu = 1;
					gaming = 1;
					Sleep(100);
					system("cls");
					gotoxy(10, 5);
					printf("1. ���ӽ���");
					gotoxy(10, 7);
					printf("2. ���Ӱ��");
					gotoxy(10, 9);
					printf("3. ��������");
					break;
				}
			}
			else if (callmenu == 1) {
				switch (key) {
				case 49:
					gaming = 0;
					for (int i = 0; i < 10; i++)
						for (int j = 0; j < 10; j++)
							map[i][j] = 0;
					cptreset = 1;
					userreset = 1;
					Sleep(100);
					callmenu = 0;
					break;
				case 50:
					if (gaming == 1) {
						callmenu = 0;
						gaming = 0;
					}
					break;

				case 51:
					return 0;
					break;
				}
			}
		}
	}
	return 0;
}
unsigned _stdcall printmap(void* arg) {
	while (1) {
		if (callmenu == 0) {
			gotoxy(0, 0);
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (map[i][j] == 1 || map[i][j] == 2) {
						printf("��");
					}
					else if (map[i][j] == 3) {
						printf("��");
					}
					else if (map[i][j] == 4) {
						printf("��");
					}
					else if (map[i][j] == 5) {
						printf("��");
					}
					else {
						printf("  ");
					}
				}
				printf("\n");
			}
			if (tcount < 100) printf("\n���� �������� = %2d", 99 - tcount);
			Sleep(10);
		}
	}
}
void main() {
	CONSOLE_CURSOR_INFO Curinfo;
	Curinfo.dwSize = 1;
	Curinfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Curinfo);
	gotoxy(10, 5);
	printf("1. ���ӽ���");
	gotoxy(10, 7);
	printf("2. ���Ӱ��");
	gotoxy(10, 9);
	printf("3. ��������");
	int key;
	do {
		key = _getch();
		if (key == 51) return;
	} while (key != 49);
	HANDLE hThread[3];      //������ �Լ� �̸� ���� �迭
	unsigned Threadld1;
	hMutex = CreateMutex(NULL, FALSE, NULL);
	unsigned long hThread1 = _beginthreadex(NULL, 0, cptmove, NULL, 0, &Threadld1);
	unsigned long hThread2 = _beginthreadex(NULL, 0, usermove, NULL, 0, &Threadld1);
	unsigned long hThread3 = _beginthreadex(NULL, 0, printmap, NULL, 0, &Threadld1);
	hThread[0] = (HANDLE)hThread1;
	hThread[1] = (HANDLE)hThread2;
	hThread[2] = (HANDLE)hThread3;
	WaitForMultipleObjects(3, hThread, FALSE, INFINITE);
}