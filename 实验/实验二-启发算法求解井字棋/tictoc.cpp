#include <stdio.h>
#include<conio.h> 
#define COM -1 
#define MAN 1
#define STEP 9 
#define DRAW 0 
#define ROW 3 
#define COL 3
#define MAX_NUM 1000;
 
 
struct Move
{
	int x;
	int y;
 
};
 
//����
int board[3][3] = { { 0,0,0 },
					{ 0,0,0 },
					{ 0,0,0 }
};
int tempBoard[3][3] = { { 0,0,0 },
						{ 0,0,0 },
						{ 0,0,0 }
};
//���
int player = MAN;
//��õ�һ��
Move bestMove;
//��ǰ���
int currentDepth;
//˭����
bool MAN_first = true;
 
 
//�ж���Ӯ
int isWin() {
	int i, j;
 
	for (int i = 0; i < 3; i++)
	{
		if (board[i][0] + board[i][1] + board[i][2] == 3)
			return 1;
		else if (board[i][0] + board[i][1] + board[i][2] == -3)
			return -1;
	}
	for (int j = 0; j < 3; j++)
	{
		if (board[0][j] + board[1][j] + board[2][j] == 3)
			return 1;
		else if (board[0][j] + board[1][j] + board[2][j] == -3)
			return -1;
	}
	if (board[0][0] + board[1][1] + board[2][2] == 3 || board[0][2] + board[1][1] + board[2][0] == 3)
		return 1;
	else if (board[0][0] + board[1][1] + board[2][2] == -3 || board[0][2] + board[1][1] + board[2][0] == -3)
		return -1;
	else  return 0;
 
}
 
//��������
int evaluteMap() {
 
	bool flag = true;
	int i, j;
 
	if (isWin() == COM)
		return MAX_NUM;//��������Ӯ�ˣ��������ֵ 
	if (isWin() == MAN)
		return -MAX_NUM;//�����������ˣ�������Сֵ 
	//for (i = 0; i < 3; i++)
	//	for (j = 0; j < 3; j++)
	//		if (board[i][j] == 0)
	//		{
	//			flag = false;
	//			break;
	//		}
	//if (flag)  //���FlagΪ��  �� ���̶�����  ���˳�  
	//	return 0;
 
 
	int count = 0;//�ñ���������ʾ����������ֵ
				  //�������еĿո������Լ������ӣ��Ƚ����������е�0��Ϊ1
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			if (board[i][j] == 0)
				tempBoard[i][j] = COM;
			else
				tempBoard[i][j] = board[i][j];
		}
	//����һ��
	//����ÿһ�����ж����е���������3����
	for (i = 0; i < 3; i++)
		count += (tempBoard[i][0] + tempBoard[i][1] + tempBoard[i][2]) / 3;
	for (i = 0; i < 3; i++)
		count += (tempBoard[0][i] + tempBoard[1][i] + tempBoard[2][i]) / 3;
	count += (tempBoard[0][0] + tempBoard[1][1] + tempBoard[2][2]) / 3;
	count += (tempBoard[2][0] + tempBoard[1][1] + tempBoard[0][2]) / 3;
 
 
 
	//�������еĿո������Է������ӣ��Ƚ����������е�0��Ϊ-1
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			if (board[i][j] == 0)
				tempBoard[i][j] = MAN;
			else tempBoard[i][j] = board[i][j];
		}
	//�Է�
	//����ÿһ�����ж����е���������3����
	for (i = 0; i < 3; i++)
		count += (tempBoard[i][0] + tempBoard[i][1] + tempBoard[i][2]) / 3;
	for (i = 0; i < 3; i++)
		count += (tempBoard[0][i] + tempBoard[1][i] + tempBoard[2][i]) / 3;
	count += (tempBoard[0][0] + tempBoard[1][1] + tempBoard[2][2]) / 3;
	count += (tempBoard[2][0] + tempBoard[1][1] + tempBoard[0][2]) / 3;
 
 
 
 
	return count;
}
 
 
void makeMove(Move curMove)
{
	board[curMove.x][curMove.y] = player;
	player = (player == COM) ? MAN : COM;
}
 
void unMakeMove(Move curMove) {
	board[curMove.x][curMove.y] = 0;
	player = (player == COM) ? MAN : COM;
}
 
//�õ��п�λ�ļ���
int getMoveList(Move moveList[]) {
	int moveCount = 0;
	int i, j;
	for (i = 0; i < COL; i++)
	{
		for (j = 0; j < ROW; j++)
		{
			if (board[i][j] == 0)
			{
				moveList[moveCount].x = i;
				moveList[moveCount].y = j;
				moveCount++;
			}
 
		}
	}
	return moveCount; //����һ�����ٸ��յ�λ�� 
}
 
 
int miniMaxsearch(int depth)
{
	int value;  //��ֵ 
	int bestValue = 0; //��õĹ�ֵ
	int moveCount = 0;
	int i; int m, n;
	Move moveList[9];//����������ӵ�λ��
	if (isWin() == COM || isWin() == MAN)
	{
		return evaluteMap();  //һ���Ƿ��ؼ���Сֵ
	}
	//���������Ⱥľ� �� ���ع�ֵ 
	if (depth == 0)
	{
		return evaluteMap();
	}
 
 
	//���ݲ�ͬ����� ���и�ֵ 
	if (COM == player) {
		bestValue = -MAX_NUM;
	}
	else if (MAN == player)
	{
		bestValue = MAX_NUM;
	}
 
	//һ�����ٲ�
	moveCount = getMoveList(moveList);
 
	for (i = 0; i < moveCount; i++)
	{
		Move curMove = moveList[i];
 
		makeMove(curMove);
		value = miniMaxsearch(depth - 1);
		unMakeMove(curMove);
 
		if (player == COM)
		{
			if (value > bestValue)
			{
				bestValue = value;
				if (depth == currentDepth)
				{
					bestMove = curMove;
				}
			}
		}
		else if (player == MAN)
		{
			if (value < bestValue)
			{
				bestValue = value;
				if (depth == currentDepth)
				{
					bestMove = curMove;
				}
			}
		}
 
	}
	 
	return bestValue;
}
 
 
//��ӡ���� ����X  �����O 
void printBoard() {
	int i, j;
	for (i = 0; i < COL; i++)
	{
		printf("-------------\n");
		for (j = 0; j < ROW; j++)
		{
			if (board[i][j] == COM)
			{
				printf("| X ");
			}
			else if (board[i][j] == MAN)
			{
				printf("| O ");
			}
			else
			{
				printf("|   ");
			}
 
		}
		printf("|\n");
	}
	printf("-------------\n");
 
}
 
 
 
void com_play() {
	miniMaxsearch(currentDepth);
	board[bestMove.x][bestMove.y] = COM;
 
}
 
void man_play() {
	int x, y;
	printf("������λ������  e.g ����0 0��Ϊ���Ͻ� ��2��2��Ϊ���½� \n");
	scanf("%d", &x);
	scanf("%d", &y);
 
	while (x < 0 || x > 2 || y < 0 || y > 2)
	{
		printf("������������������������:x:(0~2) , y:(0~2)\n");
		scanf("%d", &x);
		scanf("%d", &y);
	}
	while (board[x][y] != 0)
	{
		printf("��λ�������壬����������:\n");
		scanf("%d", &x);
		scanf("%d", &y);
	}
 
	board[x][y] = MAN;
 
}
 
 
 
 
 
 
void setFirst() {
	char c;
	printf("\nDo you want to play first? y -������  , n-��������");
	for (c = getche(); c != 'Y'&&c != 'y'&&c != 'N'&&c != 'n'; c = getche());
	if (c == 'n' || c == 'N') {
		MAN_first = false;
	}
	printf("\n");
}
 
 
void main()
{
	currentDepth = 9;
	int step = 1;
	setFirst();
	printBoard();
 
	if (MAN_first) {
		player = MAN;
		for (step = 1; step <= STEP; )
		{
			man_play();
			printBoard();
			if (player == isWin()) {
				printf("����ʤ�ˣ���");
				break;
			}
			step++;
			currentDepth--;
			if (step == 10) {
				printf("ƽ�� ~~~");
				break;
			}
			player = (player == COM) ? MAN : COM;
			com_play();
			printBoard();
			if (player == isWin()) {
				printf("���ź�������Ӯ��������");
				break;
			}
			step++;
			currentDepth--;
			player = (player == COM) ? MAN : COM;
		}
	}
 
	else
	{
		player = COM;
		for (step = 1; step <= STEP; )
		{
			com_play();
 
			printBoard();
			if (player == isWin()) {
				printf("���ź�������Ӯ��������");
				break;
			}
			step++;
			currentDepth--;
			if (step == 10) {
				printf("ƽ�� ~~~");
				break;
			}
			player = (player == COM) ? MAN : COM;
			man_play();
			printBoard();
			if (player == isWin()) {
				printf("����ʤ�ˣ���");
				break;
			}
			step++;
			currentDepth--;
			player = (player == COM) ? MAN : COM;
		}
	}
	getch();
}