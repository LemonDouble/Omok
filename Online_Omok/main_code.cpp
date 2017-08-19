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

//화살표로 돌 이동, 엔터로 돌 놓기

int main()
{
	int player1_x, player1_y, player2_x, player2_y, who_turn, key, who_win;
	player1_x = 0, player1_y = 0, player2_x = 0, player2_y = 0;
	// 플레이어 1의 X커서, Y커서. 마찬가지로 플레이어 2의 X커서, Y커서, 전부 0,0 (좌측 최상단) 으로 초기화시킴.
	who_turn = 0, key = 0; who_win = -1;
	// 플레이어 1의 차례 : 0, 플레이어 2의 차례 = 1
	// 플레이어 1의 승리 : 0, 플레이어 2의 승리 = 1

	char YN;
	//승리 후 바둑판 재출력시 사용

	int badukpan[19][19];
	// 흰 돌과 검은 돌의 위치를 저장하는 2차원 배열

	clear_badukpan(badukpan);

	draw_badukpan(badukpan);
	gotoxy(0, 0);
	while (who_win == -1)
	{
		key = scan_keyboard();

		if (who_turn == 0) //who_turn이 0이면 1플레이어의 차례
		{
			del_stone(&player1_x, &player1_y, badukpan);
			// 돌을 옮기기 전에 돌을 먼저 지움
			key_handling(&player1_x, &player1_y, badukpan, &who_turn, key, &who_win);
			// 키를 받아옴
			gotoxy((2*player1_x), player1_y);
			// x*2, y 만큼으로 커서를 움직임. (2*x인 이유는, 2*x만큼이 1y의 길이와 같기 때문)
			printf("●");
			// 플레이어 1의 차례니 백돌 출력
		}
		else
		{
			del_stone(&player2_x, &player2_y, badukpan);
			key_handling(&player2_x, &player2_y, badukpan, &who_turn, key, &who_win);
			gotoxy((2 * player2_x), player2_y);
			printf("○");
		}
	}

	if (who_win == 0)
	{
		system("cls");
		printf("백돌의 승리!\n\n\n\n");

		printf("바둑판을 다시 보시겠습니까? (Y/N) >>  ");
		scanf("%c", &YN);

		if (YN == 'y' || YN == 'Y')
		{
			draw_badukpan(badukpan);
		}
	}
	else
	{
		system("cls");
		printf("흑돌의 승리!\n\n\n\n");

		printf("바둑판을 다시 보시겠습니까? (Y/N) >>  ");
		scanf("%c", &YN);

		if (YN == 'y' || YN == 'Y')
		{
			draw_badukpan(badukpan);
		}
	}

}

void clear_badukpan(int(*badukpan)[19])
{
	// 바둑판을 대국을 하기 전 초기상태로 청소하는 함수.

	//참고로 바둑판은 19 * 19판을 사용함.

	// char형 배열에 특수문자/한글이 들어가지 않기 떄문에, 대신 int형 배열 안에 상징 숫자를 적고, 출력할 떄 바꿔 출력함.
	// 흑돌은 0, 백돌은 1을 사용함.

	//이외는 다음과 같음

	// 10 11 11 ..... 11 12
	// 20 21 21 ..... 21 22
	// 20 21 21 ..... 21 22
	// 30 31 31 ..... 31 32

	// 10의 자리는 첫 줄은 1, 2~18째 줄은 2, 19행(마지막 줄)은 3으로 사용.
	// 1의 자리는 0일 시 가장 왼쪽의 열, 1일시 2~18열, 2일 시 19열임.
	badukpan[0][0] = 10;
	badukpan[0][18] = 12;
	badukpan[18][0] = 30;
	badukpan[18][18] = 32;
	// 바둑판의 네 모서리를 정리함. 배열은 0부터 시작하므로 18행, 열이 끝.

	for (int i = 1; i < 18; i++)
	{
		badukpan[0][i] = 11; //첫 행 남은부분 정렬
		badukpan[18][i] = 31; // 마지막 행 남은부분 정렬
		badukpan[i][0] = 20; // 첫 열 남은부분 정렬
		badukpan[i][18] = 22; // 마지막 열 남은부분 정렬
	}

	for (int i = 1; i < 18; i++)
	{
		for (int j = 1; j < 18; j++)
		{
			badukpan[i][j] = 21; // 남은 중앙부분 십자모양 처리.
		}
	}
}
void draw_badukpan(int(*badukpan)[19])
{
	// 2차원 배열의 숫자를 읽어, 바둑판 모양으로 바꿔 출력하는 함수입니다.

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (badukpan[i][j] == 10)
			{
				printf("┌");
			}
			else if (badukpan[i][j] == 11)
			{
				printf("┬");
			}
			else if (badukpan[i][j] == 12)
			{
				printf("┐");
			} // 바둑판의 첫 줄들
			else if (badukpan[i][j] == 20)
			{
				printf("├");
			}
			else if (badukpan[i][j] == 21)
			{
				printf("┼");
			}
			else if (badukpan[i][j] == 22)
			{
				printf("┤");
			} //바둑판의 2~18행
			else if (badukpan[i][j] == 30)
			{
				printf("└");
			}
			else if (badukpan[i][j] == 31)
			{
				printf("┴");
			}
			else if (badukpan[i][j] == 32)
			{
				printf("┘");
			} //바둑판의 19행
			else if (badukpan[i][j] == 0)
			{
				printf("●");
			}
			else if (badukpan[i][j] == 1)
			{
				printf("○");
			} //백돌과 흑돌
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
	//화살표를 입력받아 x값, y값을 전달해주는 함수
	//C언어에서 함수는 하나 이상의 값을 return 할 수 없으므로, 포인터를 통해 return 해 준다.

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
		(*y)--; //위쪽
		if ((*y) < 0)
		{
			(*y) = 18;
			// 위쪽 경계선을 넘었다면 가장 아래로 커서를 이동
		}
	}
	else if (key == 80)
	{
		(*y)++; //아래쪽
		if ((*y) > 18)
		{
			(*y) = 0;
		}
	}
	else if (key == 75)
	{
		(*x)--; //왼쪽
		if ((*x) < 0)
		{
			(*x) = 18;
		}
	}
	else if (key == 77)
	{
		(*x)++; // 오른쪽
		if ((*x) > 18)
		{
			(*x) = 0;
		}
	}
	else if (key == 13)
	{
		//엔터, 돌을 놓았으므로 돌을 놓는 함수 호출
		put_stone(x, y, badukpan, who_turn,who_win);
	}
}

void del_stone(int *x, int *y, int(*badukpan)[19])
{
	// 돌을 지우는 함수

	gotoxy((2* (*x)), (*y));

	//위치로 가서
	
	if (badukpan[(*y)][(*x)] == 10)
	{
		printf("┌");
	}
	else if (badukpan[(*y)][(*x)] == 11)
	{
		printf("┬");
	}
	else if (badukpan[(*y)][(*x)] == 12)
	{
		printf("┐");
	} // 바둑판의 첫 줄들
	else if (badukpan[(*y)][(*x)] == 20)
	{
		printf("├");
	}
	else if (badukpan[(*y)][(*x)] == 21)
	{
		printf("┼");
	}
	else if (badukpan[(*y)][(*x)] == 22)
	{
		printf("┤");
	} //바둑판의 2~18행
	else if (badukpan[(*y)][(*x)] == 30)
	{
		printf("└");
	}
	else if (badukpan[(*y)][(*x)] == 31)
	{
		printf("┴");
	}
	else if (badukpan[(*y)][(*x)] == 32)
	{
		printf("┘");
	} //바둑판의 19행
	else if (badukpan[(*y)][(*x)] == 0)
	{
		printf("●");
	}
	else if (badukpan[(*y)][(*x)] == 1)
	{
		printf("○");
	} //흑돌과 백돌

	//이거 함수로 만들면 좋을 것 같은데, 귀찮게 두번 하기 싫어서 복붙함 (..

	//돌을 지우고 원래 그 위치에 있던 걸 출력
}

void put_stone(int *x, int *y, int(*badukpan)[19], int *who_turn, int *who_win)
{
	//바둑돌을 놓는 함수

	int change = 0;
	
	if (badukpan[(*y)][(*x)] == 0 || badukpan[(*y)][(*x)] == 1)
	{
		//그 위치에 바둑돌이 있을 경우, 아무것도 하지 않음 (== 턴이 바뀌지 않음)
	}
	else
	{
		//그 외의 경우, 배열에 바둑돌 추가
		badukpan[(*y)][(*x)] = (*who_turn);
		
		//배열에 바둑돌 추가했으니, 승리한 사람 있는지 확인
		change = who_wins(x, y, badukpan, who_turn, who_win);

		// 승리한 사람 없음 (change == 0) 이면, 턴을 바꿈
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
		//놓은 돌의 x좌표가 가로 4 이상일때만 검사를 함 (돌의 왼쪽)
		if (badukpan[(*y)][(*x) - 4] == (*who_turn) && badukpan[(*y)][(*x) - 3] == (*who_turn) && badukpan[(*y)][(*x) - 2] == (*who_turn) && badukpan[(*y)][(*x) - 1] == (*who_turn) && badukpan[(*y)][(*x)] == (*who_turn))
		{
			(*who_win) = (*who_turn);
			return 1;
		}
	}
	if ((*x) <= 14)
	{
		//놓은 돌의 x좌표가 가로 14 이하일때만 검사를 함 (돌의 오른쪽)
		if (badukpan[(*y)][(*x) + 4] == (*who_turn) && badukpan[(*y)][(*x) + 3] == (*who_turn) && badukpan[(*y)][(*x) + 2] == (*who_turn) && badukpan[(*y)][(*x) + 1] == (*who_turn) && badukpan[(*y)][(*x)] == (*who_turn))
		{
			(*who_win) = (*who_turn);
			return 1;
		}
	}
	if ((*y) >= 4)
	{
		//놓은 돌의 y좌표가 세로 4 이상일때만 검사를 함 (돌의 위쪽)
		if (badukpan[(*y) - 4][(*x)] == (*who_turn) && badukpan[(*y) - 3][(*x)] == (*who_turn) && badukpan[(*y) - 2][(*x)] == (*who_turn) && badukpan[(*y) - 1][(*x)] == (*who_turn) && badukpan[(*y)][(*x)] == (*who_turn))
		{
			(*who_win) = (*who_turn);
			return 1;
		}
	}
	if ((*y) <= 14)
	{
		//놓은 돌의 y좌표가 세로 14 이하일때만 검사를 함 (돌의 오른쪽)
		if (badukpan[(*y) + 4][(*x)] == (*who_turn) && badukpan[(*y) + 3][(*x)] == (*who_turn) && badukpan[(*y) + 2][(*x)] == (*who_turn) && badukpan[(*y) + 1][(*x)] == (*who_turn) && badukpan[(*y)][(*x)] == (*who_turn))
		{
			(*who_win) = (*who_turn);
			return 1;
		}
	}
	if ((*x) >= 4 && (*y) >= 4)
	{
		//좌상단 모서리의 최저값
		if (badukpan[(*y - 4)][(*x) - 4] == (*who_turn) && badukpan[(*y - 3)][(*x) - 3] == (*who_turn) && badukpan[(*y - 2)][(*x) - 2] == (*who_turn) && badukpan[(*y - 1)][(*x) - 1] == (*who_turn) && badukpan[(*y)][(*x)] == (*who_turn))
		{
			(*who_win) = (*who_turn);
			return 1;
		}
	}
	if ((*x) <= 14 && (*y) >= 4)
	{
		//우상단 모서리의 최저값
		if (badukpan[(*y-4)][(*x) + 4] == (*who_turn) && badukpan[(*y-3)][(*x) + 3] == (*who_turn) && badukpan[(*y-2)][(*x) + 2] == (*who_turn) && badukpan[(*y-1)][(*x) + 1] == (*who_turn) && badukpan[(*y)][(*x)] == (*who_turn))
		{
			(*who_win) = (*who_turn);
			return 1;
		}
	}
	if ((*x) >= 4 && (*y) <= 14)
	{
		//좌하단 모서리의 최저값
		if (badukpan[(*y) + 4][(*x - 4)] == (*who_turn) && badukpan[(*y) + 3][(*x - 3)] == (*who_turn) && badukpan[(*y) + 2][(*x - 2)] == (*who_turn) && badukpan[(*y) + 1][(*x - 1)] == (*who_turn) && badukpan[(*y)][(*x)] == (*who_turn))
		{
			(*who_win) = (*who_turn);
			return 1;
		}
	}
	if ((*x) <= 14 && (*y) <= 14)
	{
		//우하단 모서리의 최저값
		if (badukpan[(*y) + 4][(*x + 4)] == (*who_turn) && badukpan[(*y) + 3][(*x + 3)] == (*who_turn) && badukpan[(*y) + 2][(*x + 2)] == (*who_turn) && badukpan[(*y) + 1][(*x + 1)] == (*who_turn) && badukpan[(*y)][(*x)] == (*who_turn))
		{
			(*who_win) = (*who_turn);
			return 1;
		}
	}

	return 0;
}