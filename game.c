#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
void InitBoard(char board[ROWS][COLS], int rows, int cols,char set)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows;i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}


}

void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	printf("-------扫雷--------\n");
	for (j = 0; j <= col; j++)
	{
		printf("%d ",j);
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d ", i);
		for (j = 1; j <=col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("-------扫雷--------\n");

}

void SetMine(char board[ROWS][COLS], int row, int col)
{
	int count = EASY_COUNT;//10个雷
	//1-9
	//1-9
	while (count)
	{
		int x = rand() % row + 1;//1-9
		int y = rand() % col + 1;//1-9
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;

		}
	}
	
}

int get_mine_count(char board[ROWS][COLS], int x, int y)
{
	return (board[x - 1][y] + board[x - 1][y - 1] +
		board[x][y - 1] + board[x + 1][y - 1] +
		board[x + 1][y] + board[x + 1][y + 1] +
		board[x][y + 1] + board[x - 1][y + 1]-8*'0');
}

void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int win=0;//找到不是雷的个数
	while (win < row * col-EASY_COUNT)
	{
		printf("请输入要排查的坐标：>");
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (show[x][y] != '*')
			{
				printf("该位置坐标已经排过，请勿重复排雷\n");

			}
			else
			{
				//如果是雷
				if (mine[x][y] == '1')
				{
					printf("抱歉，你被炸死了！\n");
					DisplayBoard(mine, ROW, COL);
					break;
				}
				//不是雷，判断周围雷的个数
				else
				{
					win++;
					//统计mine[x][y]周围雷的个数
					int count = get_mine_count(mine, x, y);
					show[x][y] = count + '0';//转换成数字字符
					DisplayBoard(show, ROW, COL);

				}

			}
			
		}
		else
		{
			printf("输入坐标非法，请重新输入\n");
		}
	}
	if (win == row * col - EASY_COUNT)
	{
		printf("恭喜你，排雷成功！\n");
		DisplayBoard(show, ROW, COL);

	}
	
}
