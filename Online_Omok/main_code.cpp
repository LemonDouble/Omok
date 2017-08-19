#include <stdio.h>
#include <windows.h>
#include <conio.h>

void clear_badukpan(int (*badkupan)[19]);
void draw_badukpan(int (*badukpan)[19]);
void gotoxy(int x, int y);	
int scan_keyboard();
void key_handling(int *x, int*y, int(*badukpan)[19],int *who_turn, int key, int *who_win);
void put_stone(int *x, int *y,int (*badukpan)[19],int *who_turn, int *who_win);
void del_stone(int *x, int *y, int(*badukpan)[19]);
void clear_badukpan(int(*badkupan)[19]);
void draw_badukpan(int(*badukpan)[19]);
int who_wins(int *x, int *y, int(*badukpan)[19], int *who_turn, int *who_win);

//ȭ��ǥ�� �� �̵�, ���ͷ� �� ����

int main()
{
	int player1_x, player1_y, player2_x, player2_y, who_turn, key, who_win;
	player1_x = 0, player1_y = 0, player2_x = 0, player2_y = 0;
	// �÷��̾� 1�� XĿ��, YĿ��. ���������� �÷��̾� 2�� XĿ��, YĿ��, ���� 0,0 (���� �ֻ��) ���� �ʱ�ȭ��Ŵ.
	who_turn = 0, key = 0; who_win = -1;
	// �÷��̾� 1�� ���� : 0, �÷��̾� 2�� ���� = 1
	// �÷��̾� 1�� �¸� : 0, �÷��̾� 2�� �¸� = 1

	char YN;
	//�¸� �� �ٵ��� ����½� ���

	int badukpan[19][19];
	// �� ���� ���� ���� ��ġ�� �����ϴ� 2���� �迭

	clear_badukpan(badukpan);

	draw_badukpan(badukpan);
	gotoxy(0, 0);
	while (who_win == -1)
	{
		key = scan_keyboard();

		if (who_turn == 0) //who_turn�� 0�̸� 1�÷��̾��� ����
		{
			del_stone(&player1_x, &player1_y, badukpan);
			// ���� �ű�� ���� ���� ���� ����
			key_handling(&player1_x, &player1_y, badukpan, &who_turn, key, &who_win);
			// Ű�� �޾ƿ�
			gotoxy((2*player1_x), player1_y);
			// x*2, y ��ŭ���� Ŀ���� ������. (2*x�� ������, 2*x��ŭ�� 1y�� ���̿� ���� ����)
			printf("��");
			// �÷��̾� 1�� ���ʴ� �鵹 ���
		}
		else
		{
			del_stone(&player2_x, &player2_y, badukpan);
			key_handling(&player2_x, &player2_y, badukpan, &who_turn, key, &who_win);
			gotoxy((2 * player2_x), player2_y);
			printf("��");
		}
	}

	if (who_win == 0)
	{
		system("cls");
		printf("�鵹�� �¸�!\n\n\n\n");

		printf("�ٵ����� �ٽ� ���ðڽ��ϱ�? (Y/N) >>  ");
		scanf("%c", &YN);

		if (YN == 'y' || YN == 'Y')
		{
			draw_badukpan(badukpan);
		}
	}
	else
	{
		system("cls");
		printf("�浹�� �¸�!\n\n\n\n");

		printf("�ٵ����� �ٽ� ���ðڽ��ϱ�? (Y/N) >>  ");
		scanf("%c", &YN);

		if (YN == 'y' || YN == 'Y')
		{
			draw_badukpan(badukpan);
		}
	}

}

void clear_badukpan(int(*badukpan)[19])
{
	// �ٵ����� �뱹�� �ϱ� �� �ʱ���·� û���ϴ� �Լ�.

	//����� �ٵ����� 19 * 19���� �����.

	// char�� �迭�� Ư������/�ѱ��� ���� �ʱ� ������, ��� int�� �迭 �ȿ� ��¡ ���ڸ� ����, ����� �� �ٲ� �����.
	// �浹�� 0, �鵹�� 1�� �����.

	//�ܴ̿� ������ ����

	// 10 11 11 ..... 11 12
	// 20 21 21 ..... 21 22
	// 20 21 21 ..... 21 22
	// 30 31 31 ..... 31 32

	// 10�� �ڸ��� ù ���� 1, 2~18° ���� 2, 19��(������ ��)�� 3���� ���.
	// 1�� �ڸ��� 0�� �� ���� ������ ��, 1�Ͻ� 2~18��, 2�� �� 19����.
	badukpan[0][0] = 10;
	badukpan[0][18] = 12;
	badukpan[18][0] = 30;
	badukpan[18][18] = 32;
	// �ٵ����� �� �𼭸��� ������. �迭�� 0���� �����ϹǷ� 18��, ���� ��.

	for (int i = 1; i < 18; i++)
	{
		badukpan[0][i] = 11; //ù �� �����κ� ����
		badukpan[18][i] = 31; // ������ �� �����κ� ����
		badukpan[i][0] = 20; // ù �� �����κ� ����
		badukpan[i][18] = 22; // ������ �� �����κ� ����
	}

	for (int i = 1; i < 18; i++)
	{
		for (int j = 1; j < 18; j++)
		{
			badukpan[i][j] = 21; // ���� �߾Ӻκ� ���ڸ�� ó��.
		}
	}
}
void draw_badukpan(int(*badukpan)[19])
{
	// 2���� �迭�� ���ڸ� �о�, �ٵ��� ������� �ٲ� ����ϴ� �Լ��Դϴ�.

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (badukpan[i][j] == 10)
			{
				printf("��");
			}
			else if (badukpan[i][j] == 11)
			{
				printf("��");
			}
			else if (badukpan[i][j] == 12)
			{
				printf("��");
			} // �ٵ����� ù �ٵ�
			else if (badukpan[i][j] == 20)
			{
				printf("��");
			}
			else if (badukpan[i][j] == 21)
			{
				printf("��");
			}
			else if (badukpan[i][j] == 22)
			{
				printf("��");
			} //�ٵ����� 2~18��
			else if (badukpan[i][j] == 30)
			{
				printf("��");
			}
			else if (badukpan[i][j] == 31)
			{
				printf("��");
			}
			else if (badukpan[i][j] == 32)
			{
				printf("��");
			} //�ٵ����� 19��
			else if (badukpan[i][j] == 0)
			{
				printf("��");
			}
			else if (badukpan[i][j] == 1)
			{
				printf("��");
			} //�鵹�� �浹
		}
		printf("\n");
	}
}

void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int scan_keyboard()
{
	//ȭ��ǥ�� �Է¹޾� x��, y���� �������ִ� �Լ�
	//C���� �Լ��� �ϳ� �̻��� ���� return �� �� �����Ƿ�, �����͸� ���� return �� �ش�.

	int arrow;

	arrow = getch();
	if (arrow == 0xe0 || arrow == 0)
	{
		arrow = getch();

		if (arrow == 72)
		{
			return 72;
		}
		else if (arrow == 80)
		{
			return 80;
		}
		else if (arrow == 75)
		{
			return 75;
		}
		else if (arrow == 77)
		{
			return 77;
		}
		else if (arrow == 32)
		{
			return 32;
		}
	}
}

void key_handling(int *x, int*y, int(*badukpan)[19], int *who_turn, int key, int *who_win)
{
	if (key == 72)
	{
		(*y)--; //����
		if ((*y) < 0)
		{
			(*y) = 18;
			// ���� ��輱�� �Ѿ��ٸ� ���� �Ʒ��� Ŀ���� �̵�
		}
	}
	else if (key == 80)
	{
		(*y)++; //�Ʒ���
		if ((*y) > 18)
		{
			(*y) = 0;
		}
	}
	else if (key == 75)
	{
		(*x)--; //����
		if ((*x) < 0)
		{
			(*x) = 18;
		}
	}
	else if (key == 77)
	{
		(*x)++; // ������
		if ((*x) > 18)
		{
			(*x) = 0;
		}
	}
	else if (key == 13)
	{
		//����, ���� �������Ƿ� ���� ���� �Լ� ȣ��
		put_stone(x, y, badukpan, who_turn,who_win);
	}
}

void del_stone(int *x, int *y, int(*badukpan)[19])
{
	// ���� ����� �Լ�

	gotoxy((2* (*x)), (*y));

	//��ġ�� ����
	
	if (badukpan[(*y)][(*x)] == 10)
	{
		printf("��");
	}
	else if (badukpan[(*y)][(*x)] == 11)
	{
		printf("��");
	}
	else if (badukpan[(*y)][(*x)] == 12)
	{
		printf("��");
	} // �ٵ����� ù �ٵ�
	else if (badukpan[(*y)][(*x)] == 20)
	{
		printf("��");
	}
	else if (badukpan[(*y)][(*x)] == 21)
	{
		printf("��");
	}
	else if (badukpan[(*y)][(*x)] == 22)
	{
		printf("��");
	} //�ٵ����� 2~18��
	else if (badukpan[(*y)][(*x)] == 30)
	{
		printf("��");
	}
	else if (badukpan[(*y)][(*x)] == 31)
	{
		printf("��");
	}
	else if (badukpan[(*y)][(*x)] == 32)
	{
		printf("��");
	} //�ٵ����� 19��
	else if (badukpan[(*y)][(*x)] == 0)
	{
		printf("��");
	}
	else if (badukpan[(*y)][(*x)] == 1)
	{
		printf("��");
	} //�浹�� �鵹

	//�̰� �Լ��� ����� ���� �� ������, ������ �ι� �ϱ� �Ⱦ ������ (..

	//���� ����� ���� �� ��ġ�� �ִ� �� ���
}

void put_stone(int *x, int *y, int(*badukpan)[19], int *who_turn, int *who_win)
{
	//�ٵϵ��� ���� �Լ�

	int change = 0;
	
	if (badukpan[(*y)][(*x)] == 0 || badukpan[(*y)][(*x)] == 1)
	{
		//�� ��ġ�� �ٵϵ��� ���� ���, �ƹ��͵� ���� ���� (== ���� �ٲ��� ����)
	}
	else
	{
		//�� ���� ���, �迭�� �ٵϵ� �߰�
		badukpan[(*y)][(*x)] = (*who_turn);
		
		//�迭�� �ٵϵ� �߰�������, �¸��� ��� �ִ��� Ȯ��
		change = who_wins(x, y, badukpan, who_turn, who_win);

		// �¸��� ��� ���� (change == 0) �̸�, ���� �ٲ�
		if (change == 0)
		{
			if ((*who_turn) == 0)
			{
				(*who_turn) = 1;
			}
			else
			{
				(*who_turn) = 0;
			}
		}
	}
}

int who_wins(int *x, int *y, int(*badukpan)[19], int *who_turn, int *who_win)
{
	if ((*x) >= 4)
	{
		//���� ���� x��ǥ�� ���� 4 �̻��϶��� �˻縦 �� (���� ����)
		if (badukpan[(*y)][(*x) - 4] == (*who_turn) && badukpan[(*y)][(*x) - 3] == (*who_turn) && badukpan[(*y)][(*x) - 2] == (*who_turn) && badukpan[(*y)][(*x) - 1] == (*who_turn) && badukpan[(*y)][(*x)] == (*who_turn))
		{
			(*who_win) = (*who_turn);
			return 1;
		}
	}
	if ((*x) <= 14)
	{
		//���� ���� x��ǥ�� ���� 14 �����϶��� �˻縦 �� (���� ������)
		if (badukpan[(*y)][(*x) + 4] == (*who_turn) && badukpan[(*y)][(*x) + 3] == (*who_turn) && badukpan[(*y)][(*x) + 2] == (*who_turn) && badukpan[(*y)][(*x) + 1] == (*who_turn) && badukpan[(*y)][(*x)] == (*who_turn))
		{
			(*who_win) = (*who_turn);
			return 1;
		}
	}
	if ((*y) >= 4)
	{
		//���� ���� y��ǥ�� ���� 4 �̻��϶��� �˻縦 �� (���� ����)
		if (badukpan[(*y) - 4][(*x)] == (*who_turn) && badukpan[(*y) - 3][(*x)] == (*who_turn) && badukpan[(*y) - 2][(*x)] == (*who_turn) && badukpan[(*y) - 1][(*x)] == (*who_turn) && badukpan[(*y)][(*x)] == (*who_turn))
		{
			(*who_win) = (*who_turn);
			return 1;
		}
	}
	if ((*y) <= 14)
	{
		//���� ���� y��ǥ�� ���� 14 �����϶��� �˻縦 �� (���� ������)
		if (badukpan[(*y) + 4][(*x)] == (*who_turn) && badukpan[(*y) + 3][(*x)] == (*who_turn) && badukpan[(*y) + 2][(*x)] == (*who_turn) && badukpan[(*y) + 1][(*x)] == (*who_turn) && badukpan[(*y)][(*x)] == (*who_turn))
		{
			(*who_win) = (*who_turn);
			return 1;
		}
	}
	if ((*x) >= 4 && (*y) >= 4)
	{
		//�»�� �𼭸��� ������
		if (badukpan[(*y - 4)][(*x) - 4] == (*who_turn) && badukpan[(*y - 3)][(*x) - 3] == (*who_turn) && badukpan[(*y - 2)][(*x) - 2] == (*who_turn) && badukpan[(*y - 1)][(*x) - 1] == (*who_turn) && badukpan[(*y)][(*x)] == (*who_turn))
		{
			(*who_win) = (*who_turn);
			return 1;
		}
	}
	if ((*x) <= 14 && (*y) >= 4)
	{
		//���� �𼭸��� ������
		if (badukpan[(*y-4)][(*x) + 4] == (*who_turn) && badukpan[(*y-3)][(*x) + 3] == (*who_turn) && badukpan[(*y-2)][(*x) + 2] == (*who_turn) && badukpan[(*y-1)][(*x) + 1] == (*who_turn) && badukpan[(*y)][(*x)] == (*who_turn))
		{
			(*who_win) = (*who_turn);
			return 1;
		}
	}
	if ((*x) >= 4 && (*y) <= 14)
	{
		//���ϴ� �𼭸��� ������
		if (badukpan[(*y) + 4][(*x - 4)] == (*who_turn) && badukpan[(*y) + 3][(*x - 3)] == (*who_turn) && badukpan[(*y) + 2][(*x - 2)] == (*who_turn) && badukpan[(*y) + 1][(*x - 1)] == (*who_turn) && badukpan[(*y)][(*x)] == (*who_turn))
		{
			(*who_win) = (*who_turn);
			return 1;
		}
	}
	if ((*x) <= 14 && (*y) <= 14)
	{
		//���ϴ� �𼭸��� ������
		if (badukpan[(*y) + 4][(*x + 4)] == (*who_turn) && badukpan[(*y) + 3][(*x + 3)] == (*who_turn) && badukpan[(*y) + 2][(*x + 2)] == (*who_turn) && badukpan[(*y) + 1][(*x + 1)] == (*who_turn) && badukpan[(*y)][(*x)] == (*who_turn))
		{
			(*who_win) = (*who_turn);
			return 1;
		}
	}

	return 0;
}