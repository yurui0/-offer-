// 29_PrintMatrix.cpp : 定义控制台应用程序的入口点。
//
// 面试题29：顺时针打印矩阵
// 题目：输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

#include "stdafx.h"
#include <cstdio>

void PrintMatrixInCircle(int** numbers, int columns, int rows, int start);
void printNumber(int number);

void PrintMatrixClockwisely(int** numbers, int columns, int rows)//顺时针打印矩阵
{
	if (numbers == nullptr || columns <= 0 || rows <= 0)//边界条件判断
		return;

	int start = 0;//打印的圈数

	while (columns > start * 2 && rows > start * 2)
	{
		PrintMatrixInCircle(numbers, columns, rows, start);//打印一圈矩阵数字的函数

		++start;//打印下一圈
	}
}

void PrintMatrixInCircle(int** numbers, int columns, int rows, int start)//打印一圈矩阵数字的函数
{
	int endX = columns - 1 - start;//X方向的读取数量
	int endY = rows - 1 - start;//Y方向的读取数量

	// 从左到右打印一行，这里没有判断，因为哪怕只有一个数字，也需要跑一步，通过这个方法打印出来
	for (int i = start; i <= endX; ++i)
	{
		int number = numbers[start][i];
		printNumber(number);
	}

	//下面三种情况都要先判断，因为最内圈的不一定需要跑四步，有可能打印最内圈只需要三步/两步/一步，所以加判断以免重复输出或无效输出
	// 从上到下打印一列
	if (start < endY)
	{
		for (int i = start + 1; i <= endY; ++i)
		{
			int number = numbers[i][endX];
			printNumber(number);
		}
	}

	// 从右到左打印一行
	if (start < endX && start < endY)
	{
		for (int i = endX - 1; i >= start; --i)
		{
			int number = numbers[endY][i];
			printNumber(number);
		}
	}

	// 从下到上打印一行
	if (start < endX && start < endY - 1)
	{
		for (int i = endY - 1; i >= start + 1; --i)
		{
			int number = numbers[i][start];
			printNumber(number);
		}
	}
}

void printNumber(int number)
{
	printf("%d\t", number);
}

// ====================测试代码====================
void Test(int columns, int rows)
{
	printf("Test Begin: %d columns, %d rows.\n", columns, rows);

	if (columns < 1 || rows < 1)
		return;

	int** numbers = new int*[rows];
	for (int i = 0; i < rows; ++i)
	{
		numbers[i] = new int[columns];
		for (int j = 0; j < columns; ++j)
		{
			numbers[i][j] = i * columns + j + 1;
		}
	}

	PrintMatrixClockwisely(numbers, columns, rows);
	printf("\n");

	for (int i = 0; i < rows; ++i)
		delete[](int*)numbers[i];

	delete[] numbers;
}



int _tmain(int argc, _TCHAR* argv[])
{
	/*
	1
	*/
	Test(1, 1);

	/*
	1    2
	3    4
	*/
	Test(2, 2);

	/*
	1    2    3    4
	5    6    7    8
	9    10   11   12
	13   14   15   16
	*/
	Test(4, 4);

	/*
	1    2    3    4    5
	6    7    8    9    10
	11   12   13   14   15
	16   17   18   19   20
	21   22   23   24   25
	*/
	Test(5, 5);

	/*
	1
	2
	3
	4
	5
	*/
	Test(1, 5);

	/*
	1    2
	3    4
	5    6
	7    8
	9    10
	*/
	Test(2, 5);

	/*
	1    2    3
	4    5    6
	7    8    9
	10   11   12
	13   14   15
	*/
	Test(3, 5);

	/*
	1    2    3    4
	5    6    7    8
	9    10   11   12
	13   14   15   16
	17   18   19   20
	*/
	Test(4, 5);

	/*
	1    2    3    4    5
	*/
	Test(5, 1);

	/*
	1    2    3    4    5
	6    7    8    9    10
	*/
	Test(5, 2);

	/*
	1    2    3    4    5
	6    7    8    9    10
	11   12   13   14    15
	*/
	Test(5, 3);

	/*
	1    2    3    4    5
	6    7    8    9    10
	11   12   13   14   15
	16   17   18   19   20
	*/
	Test(5, 4);

	return 0;
}

