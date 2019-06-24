#pragma warning(disable:3861)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct list {
	int number[16];                     //������ �����ϱ� ���� ����
	int bn[4];                        //������ & ���� �����ϱ� ���� ����
	int gr;                           //�׷� �ĺ� ����
	int use;                        //��뿩�� Ȯ�� ����
	struct list* next;                  //���Ḯ��Ʈ ������ ���� ������
};
char c;
int gnum[16];                        //�Է¹��� �� ���� ����S
int snum[16];
int a;//////////////////////////////////////////////scanf�� ����ϱ� ���� �ӽ� ����////////////////////////////////////////////////////////////////
list* point = NULL;
list* head = NULL;
list* head1 = NULL;
list* head2 = NULL;
list* head3 = NULL;


void getdata() {               //�������Է¹޴� �Լ�
	int temp;
	printf("    ABCD\n");
	for (int i = 0; i < 16; i++) {
		printf("%2d  ", i);
		for (int j = 3; j >= 0; j--) printf("%d", (i >> j) & 1);
		printf(" ( )\b\b");
		scanf_s("%d", &temp);
		gnum[i] = temp;
	}
}
int countbit(int num) {            //�Է¹��� ������ 2����ǥ������ 1�� ������ ���� �Լ�
	int count = 0;
	for (int j = 3; j >= 0; j--) if ((num >> j) & 1 == 1) count++;
	return count;
}
void insertdataF(int num) {//ù��° �� �����ϴ� �Լ�
	list* p = (list*)malloc(sizeof(list));
	p->number[0] = num;
	for (int i = 1; i < 16; i++) p->number[i] = 100;            //������� �ʴ� ���� 100���� �ʱ�ȭ
	for (int i = 0; i < 4; i++) p->bn[i] = (num >> i) & 1;
	p->gr = countbit(num);
	p->use = 0;
	p->next = NULL;
	head = p;
}
void insertdata(int num) {				//���Ḯ��Ʈ�� �����͸� �����ϴ� �Լ�
	list* temp = head;
	for (; temp->next != NULL; temp = temp->next);
	list* p = (list*)malloc(sizeof(list));
	p->number[0] = num;
	for (int i = 1; i < 16; i++) p->number[i] = 100;            //������� �ʴ� ���� 100���� �ʱ�ȭ
	for (int i = 0; i < 4; i++) p->bn[i] = (num >> i) & 1;
	p->gr = countbit(num);
	p->use = 0;
	p->next = NULL;
	temp->next = p;
}

void insertLL() {						//���Ḯ��Ʈ�� �����͸� �����ϴ� �Լ�
	list* body;
	for (int j = 0; j <= 4; j++) {               //1�� ������ �׷���
		for (int i = 0; i < 16; i++) {            //ó������ ������ Ȯ��
			body = head;                     //ó������ Ȯ���ϱ� ����
			if (gnum[i] == 1 & head == NULL & countbit(i) == j) {
				insertdataF(i);
			}
			else if (gnum[i] == 1 & countbit(i) == j) {
				insertdata(i);
			}
		}
	}
}
void printgroup() {						//1�� ������ŭ �׷��� ���� �׷캰�� ����ϴ� �Լ�
	list* temp = head;
	int count = 0;
	for (; temp != NULL; temp = temp->next) {
		if (count == temp->gr) {
			printf("\n---------------------------------------(%d)\n", count);
			count++;
		}
		printf("%2d\t", temp->number[0]);
		for (int i = 3; i >= 0; i--) {
			if (temp->bn[i] == 2) {
				printf("-");
			}
			else {
				printf("%d", temp->bn[i]);
			}
		}

		printf("\n");
	}
}
list* printLLdata(list* foot) {				//��ũ����Ʈ �����͸� ����ϴ� �Լ�
	list* temp = foot;
	int count = 0;
	for (; temp != NULL; temp = temp->next) {
		if (count == temp->gr) {
			printf("\n---------------------------------------(%d)\n", count);
			count++;
		}
		for (int i = 0; i < 16; i++)
			if (temp->number[i] >= 0 & temp->number[i] <= 15) printf("%2d ", temp->number[i]);
		printf("\t");
		for (int i = 3; i >= 0; i--) {
			if (temp->bn[i] == 2) {
				printf("-");
			}
			else {
				printf("%d", temp->bn[i]);
			}
		}
		printf("\n");
	}
	gets_s(&c,sizeof(c));
	return temp;
}
list* printnusedata(list* foot) {			// changing bit üũ�� ���ؼ� ���� pi�� ����ϴ� �Լ�
	printf("\n�̻�� ������");
	list* temp = foot;
	int count = 0;
	for (; temp != NULL; temp = temp->next) {
		if (count == temp->gr) {
			printf("\n---------------------------------------(%d)\n", count);
			count++;
		}
		for (int i = 0; i < 16; i++)
			if (temp->number[i] >= 0 & temp->number[i] <= 15 & temp->use == 0) printf("%2d ", temp->number[i]);

		if (temp->use == 0) {
			for (int i = 3; i >= 0; i--) {
				if (temp->bn[i] == 2) {
					printf("-");
				}
				else {
					printf("%d", temp->bn[i]);
				}
			}
			printf("\n");
		}
	}
	return temp;
}
list* delLL(list* tail, list* btail) {				//����Ʈ �����ϴ� �Լ�
	btail->next = tail->next;
	free(tail);
	return btail;
}
void printpi() {					//pi ����ϴ� �Լ�
	list* temp1 = head;
	list* temp2 = head1;
	list* temp3 = head2;
	list* temp4 = head3;



	temp1 = head;
	int count = 0;
	for (; temp1 != NULL; temp1 = temp1->next) {

		if (temp1->use == 0) {
			printf("PI : ");
			for (int i = 3; i >= 0; i--) {
				if (temp1->bn[i] == 2) {
					printf("-");
				}
				else {
					printf("%d", temp1->bn[i]);
				}
			}
			printf("\n");
		}
	}
	count = 0;
	for (; temp2 != NULL; temp2 = temp2->next) {

		if (temp2->use == 0) {
			printf("PI : ");
			for (int i = 3; i >= 0; i--) {
				if (temp2->bn[i] == 2) {
					printf("-");
				}
				else {
					printf("%d", temp2->bn[i]);
				}
			}
			printf("\n");
		}
	}
	count = 0;
	for (; temp3 != NULL; temp3 = temp3->next) {

		if (temp3->use == 0) {
			printf("PI : ");
			for (int i = 3; i >= 0; i--) {
				if (temp3->bn[i] == 2) {
					printf("-");
				}
				else {
					printf("%d", temp3->bn[i]);
				}
			}
			printf("\n");
		}
	}
	count = 0;
	for (; temp4 != NULL; temp4 = temp4->next) {

		if (temp4->use == 0) {
			printf("PI : ");
			for (int i = 3; i >= 0; i--) {
				if (temp4->bn[i] == 2) {
					printf("-");
				}
				else {
					printf("%d", temp4->bn[i]);
				}
			}
			printf("\n");
		}
	}
}
void getpi() {							//pi ���ϴ� �Լ�
	list* body;
	list* tail;
	list* taill;
	int temp;
	for (int i = 0; i < 4; i++) {
		body = head;
		tail = body->next;
		for (; body != NULL; body = body->next) {
			if (body->gr == i) {                        //�׷� �� ������ ��
				tail = body->next;
				for (; tail != NULL; tail = tail->next) {
					if (tail->gr == i + 1) {               //�׷�+1 �� �� �ϱ� ����
						temp = 0;
						for (int j = 0; j < 4; j++) {
							if (body->bn[j] == tail->bn[j]) temp++;
						}
						if (temp == 3) {
							if (head1 == NULL) {
								list* p = (list*)malloc(sizeof(list));
								body->use = 1;
								tail->use = 1;
								p->number[0] = body->number[0];
								p->number[1] = tail->number[0];
								for (int k = 0; k < 4; k++) {
									if (body->bn[k] == tail->bn[k]) {
										p->bn[k] = body->bn[k];
									}
									else {
										p->bn[k] = 2;
									}
								}
								p->gr = i;
								p->use = 0;
								p->next = NULL;
								head1 = p;
							}
							else {
								taill = head1;
								for (; taill->next != NULL; taill = taill->next);
								list* p = (list*)malloc(sizeof(list));
								body->use = 1;
								tail->use = 1;
								p->number[0] = body->number[0];
								p->number[1] = tail->number[0];
								for (int k = 0; k < 4; k++) {
									if (body->bn[k] == tail->bn[k]) {
										p->bn[k] = body->bn[k];
									}
									else {
										p->bn[k] = 2;
									}
								}
								p->gr = i;
								p->use = 0;
								p->next = NULL;
								taill->next = p;
							}
						}
					}
				}
			}
		}

	}
	printLLdata(head1);
	for (int i = 0; i < 4; i++) {
		body = head1;
		tail = body->next;
		for (; body != NULL; body = body->next) {
			if (body->gr == i) {                        //�׷� �� ������ ��
				tail = body->next;
				for (; tail != NULL; tail = tail->next) {
					if (tail->gr == i + 1) {               //�׷�+1 �� �� �ϱ� ����
						temp = 0;
						for (int j = 0; j < 4; j++) {
							if (body->bn[j] == tail->bn[j]) temp++;
						}
						if (temp == 3) {
							if (head2 == NULL) {
								list* p = (list*)malloc(sizeof(list));
								body->use = 1;
								tail->use = 1;
								p->number[0] = body->number[0];
								p->number[1] = body->number[1];
								p->number[2] = tail->number[0];
								p->number[3] = tail->number[1];
								for (int k = 0; k < 4; k++) {
									if (body->bn[k] == tail->bn[k]) {
										p->bn[k] = body->bn[k];
									}
									else {
										p->bn[k] = 2;
									}
								}
								p->gr = i;
								p->use = 0;
								p->next = NULL;
								head2 = p;
							}
							else {
								taill = head2;
								for (; taill->next != NULL; taill = taill->next);
								list* p = (list*)malloc(sizeof(list));
								body->use = 1;
								tail->use = 1;
								p->number[0] = body->number[0];
								p->number[1] = body->number[1];
								p->number[2] = tail->number[0];
								p->number[3] = tail->number[1];
								for (int k = 0; k < 4; k++) {
									if (body->bn[k] == tail->bn[k]) {
										p->bn[k] = body->bn[k];
									}
									else {
										p->bn[k] = 2;
									}
								}
								p->gr = i;
								p->use = 0;
								p->next = NULL;
								taill->next = p;
							}
						}
					}
				}
			}
		}
	}
	printLLdata(head2);

	body = head2;
	for (; body != NULL; body = body->next) {
		tail = body->next;
		taill = body;
		for (; tail != NULL; tail = tail->next) {
			if (taill->next != tail) taill = taill->next;
			if (body->bn[0] == tail->bn[0] & body->bn[1] == tail->bn[1] & body->bn[2] == tail->bn[2] & body->bn[3] == tail->bn[3]) {
				//            printf("delete\t\t\t\t\t\t%d\n", tail->number[0]);
				delLL(tail, taill);
				tail = taill;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		body = head2;
		tail = body->next;
		for (; body != NULL; body = body->next) {
			if (body->gr == i) {                        //�׷� �� ������ ��
				tail = body->next;
				for (; tail != NULL; tail = tail->next) {
					if (tail->gr == i + 1) {               //�׷�+1 �� �� �ϱ� ����
						temp = 0;
						for (int j = 0; j < 4; j++) {
							if (body->bn[j] == tail->bn[j]) temp++;
						}
						if (temp == 3) {
							if (head3 == NULL) {
								list* p = (list*)malloc(sizeof(list));
								body->use = 1;
								tail->use = 1;
								p->number[0] = body->number[0];
								p->number[1] = body->number[1];
								p->number[2] = body->number[2];
								p->number[3] = body->number[3];
								p->number[4] = tail->number[0];
								p->number[5] = tail->number[1];
								p->number[6] = tail->number[2];
								p->number[7] = tail->number[3];
								for (int k = 0; k < 4; k++) {
									if (body->bn[k] == tail->bn[k]) {
										p->bn[k] = body->bn[k];
									}
									else {
										p->bn[k] = 2;
									}
								}
								p->gr = i;
								p->use = 0;
								p->next = NULL;
								head3 = p;
							}
							else {
								taill = head3;
								for (; taill->next != NULL; taill = taill->next);
								list* p = (list*)malloc(sizeof(list));
								body->use = 1;
								tail->use = 1;
								p->number[0] = body->number[0];
								p->number[1] = body->number[1];
								p->number[2] = body->number[2];
								p->number[3] = body->number[3];
								p->number[4] = tail->number[0];
								p->number[5] = tail->number[1];
								p->number[6] = tail->number[2];
								p->number[7] = tail->number[3];
								for (int k = 0; k < 4; k++) {
									if (body->bn[k] == tail->bn[k]) {
										p->bn[k] = body->bn[k];
									}
									else {
										p->bn[k] = 2;
									}
								}
								p->gr = i;
								p->use = 0;
								p->next = NULL;
								taill->next = p;
							}
						}
					}
				}
			}
		}
	}
	printLLdata(head3);
	body = head3;
	for (; body != NULL; body = body->next) {					//�ߺ��� �� �����ϱ�
		tail = body->next;
		taill = body;
		for (; tail != NULL; tail = tail->next) {
			if (taill->next != tail) taill = taill->next;
			if (body->bn[0] == tail->bn[0] & body->bn[1] == tail->bn[1] & body->bn[2] == tail->bn[2] & body->bn[3] == tail->bn[3]) {
				//            printf("delete\t\t\t\t\t\t%d\n", tail->number[0]);
				delLL(tail, taill);
				tail = taill;
			}
		}
	}
	printpi();
}
void printfx() {							//���� ����ϴ� �Լ�
	printf("\n\n  F=");

	int counta, llll;

	list* temp2 = head;
	for (; temp2 != NULL; temp2 = temp2->next) {
		counta = 0;
		for (int i = 0; i < 16; i++) {
			if (temp2->number[i] >= 0 & temp2->number[i] <= 15) {
				llll = temp2->number[i];
				if (snum[llll] != 1) counta++;
			}
		}
		if (counta == 0) {
			if (temp2->use == 0) {
				for (int i = 3; i >= 0; i--) {
					switch (i) {
					case 3:
						if (temp2->bn[i] == 0) printf("A`");
						if (temp2->bn[i] == 1) printf("A");
						break;
					case 2:
						if (temp2->bn[i] == 0) printf("B`");
						if (temp2->bn[i] == 1) printf("B");
						break;
					case 1:
						if (temp2->bn[i] == 0) printf("C`");
						if (temp2->bn[i] == 1) printf("C");
						break;
					case 0:
						if (temp2->bn[i] == 0) printf("D`");
						if (temp2->bn[i] == 1) printf("D");
						break;
					}
				}
				printf("+");
			}
		}
	}



	list* temp1 = head;
	list* tempp = head;
	int countt;


	for (; temp1 != NULL; temp1 = temp1->next) {
		if (temp1->use == 0) {

			for (int i = 0; i < 16; i++) {
				if (gnum[i] == 1) {
					for (int j = 0; j < 16; j++) {
						if (temp1->number[j] == i) {
							tempp = head;
							countt = 0;
							for (; tempp != NULL; tempp = tempp->next) {
								for (int k = 0; k < 16; k++) {
									if (tempp->number[k] == i & tempp->use == 0) countt++;
								}
							}
							if (countt == 1) {
								for (int i = 3; i >= 0; i--) {
									switch (i) {
									case 3:
										if (temp1->bn[i] == 0) printf("A`");
										if (temp1->bn[i] == 1) printf("A");
										break;
									case 2:
										if (temp1->bn[i] == 0) printf("B`");
										if (temp1->bn[i] == 1) printf("B");
										break;
									case 1:
										if (temp1->bn[i] == 0) printf("C`");
										if (temp1->bn[i] == 1) printf("C");
										break;
									case 0:
										if (temp1->bn[i] == 0) printf("D`");
										if (temp1->bn[i] == 1) printf("D");
										break;
									}


								}
								printf("+");
							}
						}
					}
				}
			}
		}
	}

	printf("\b ");


	/*

		temp2 = head;
		for (; temp2 != NULL; temp2 = temp2->next){
			counta = 0;
			for (int i = 0; i < 16; i++){
				if (temp2->number[i] >= 0 & temp2->number[i] <= 15){
					llll = temp2->number[i];
					if (snum[llll] != 1) counta++;
				}
			}
			if (counta == 0){
				if (temp2->use == 0) {
					for (int i = 3; i >= 0; i--) {
						switch (i){
						case 3:
							if (temp2->bn[i] == 0) printf("A`");
							if (temp2->bn[i] == 1) printf("A");
							break;
						case 2:
							if (temp2->bn[i] == 0) printf("B`");
							if (temp2->bn[i] == 1) printf("B");
							break;
						case 1:
							if (temp2->bn[i] == 0) printf("C`");
							if (temp2->bn[i] == 1) printf("C");
							break;
						case 0:
							if (temp2->bn[i] == 0) printf("D`");
							if (temp2->bn[i] == 1) printf("D");
							break;
						}
					}
					printf("+");
				}
			}
		}
	*/
}
void printmap() {			//����ǥ ����ȭ �ϴ� �Լ�

	list* tttt;
	list* temp1 = head;
	list* temp2 = head1;
	list* temp3 = head2;
	list* temp4 = head3;

	point = temp1;
	for (; temp1->next != NULL; temp1 = temp1->next);

	if (point == NULL) {
		point = temp2;
	}
	else {
		temp1->next = temp2;
	}
	for (; temp2->next != NULL; temp2 = temp2->next);
	if (point == NULL) {
		point = temp3;
	}
	else {
		temp2->next = temp3;
	}
	for (; temp3->next != NULL; temp3 = temp3->next);
	if (point == NULL) {
		point = temp4;
	}
	else {
		temp3->next = temp4;
	}

	printf("                         ");
	for (int i = 0; i < 16; i++) {
		if (gnum[i] == 1) printf("%3d ", i);
	}
	printf("\n");

	temp1 = head;
	int count, textcount;
	for (; temp1 != NULL; temp1 = temp1->next) {
		textcount = 0;
		if (temp1->use == 0) {
			printf("(");
			textcount += 1;

			for (int i = 0; i < 16; i++) {
				if (temp1->number[i] >= 0 & temp1->number[i] <= 15) {
					printf("%2d,", temp1->number[i]);
					textcount += 3;
				}
			}
			printf("\b)");
			for (int i = textcount; i <= 25; i++) printf(" ");

			for (int i = 0; i < 16; i++) {
				if (gnum[i] == 1) {
					count = 0;
					for (int j = 0; j < 16; j++) {
						if (temp1->number[j] == i) {
							printf(" X  ");
							count++;
						}
					}
					if (count == 0) {
						printf("    ");
					}
				}
			}
			printf("\n");
		}
	}

	printf("\n\n");

	gets_s(&c,sizeof(c));

	int countt;
	list* tempp = head;


	printf("                         ");
	for (int i = 0; i < 16; i++) {
		if (gnum[i] == 1) printf("%3d ", i);
	}
	printf("\n");

	temp1 = head;
	for (; temp1 != NULL; temp1 = temp1->next) {
		textcount = 0;
		if (temp1->use == 0) {
			printf("(");
			textcount += 1;

			for (int i = 0; i < 16; i++) {
				if (temp1->number[i] >= 0 & temp1->number[i] <= 15) {
					printf("%2d,", temp1->number[i]);
					textcount += 3;
				}
			}
			printf("\b)");
			for (int i = textcount; i <= 25; i++) printf(" ");

			for (int i = 0; i < 16; i++) {
				if (gnum[i] == 1) {
					count = 0;
					for (int j = 0; j < 16; j++) {
						if (temp1->number[j] == i) {
							tempp = head;
							countt = 0;
							for (; tempp != NULL; tempp = tempp->next) {
								for (int k = 0; k < 16; k++) {
									if (tempp->number[k] == i & tempp->use == 0) countt++;
								}
							}
							if (countt == 1) {
								printf(" O  ");
							}
							else {
								printf(" X  ");
							}
							count++;
						}
					}
					if (count == 0) {
						printf("    ");
					}
				}
			}
			printf("\n");
		}
	}
	temp1 = head;
	for (; temp1 != NULL; temp1 = temp1->next) {
		if (temp1->use == 1) {
			for (int i = 0; i < 16; i++) {
				for (int j = 0; j < 16; j++) {
					if (temp1->number[i] == j) {
						snum[j] += 1;
					}
				}
			}
		}
	}
}
void main() {
	getdata();                           //�� �Է��ϴ� �Լ�
	insertLL();                           //LL�� 1�� ���� ������ ����
	printgroup();                        //�׷�ȭ �� ���
	gets_s(&c,sizeof(c));
	getpi();                           //pi�����ϴ� �Լ�
	gets_s(&c, sizeof(c));
	printmap();							//ǥ ����ϴ� �Լ�
	gets_s(&c, sizeof(c));
	printfx();							//���� ����ϴ� �Լ�
	gets_s(&c, sizeof(c));
}