// 47_MaxValueOfGifts.cpp : 定义控制台应用程序的入口点。
//
// 面试题47：礼物的最大价值
// 题目：在一个m×n的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值
// （价值大于0）。你可以从棋盘的左上角开始拿格子里的礼物，并每次向左或
// 者向下移动一格直到到达棋盘的右下角。给定一个棋盘及其上面的礼物，请计
// 算你最多能拿到多少价值的礼物？
#include "stdafx.h"

#include <algorithm>
#include <iostream>

int getMaxValue_solution1(const int* values, int rows, int cols)
{
	if (values == nullptr || rows <= 0 || cols <= 0)//判断输入是否合法
		return 0;

	int** maxValues = new int*[rows];//创建一个二维数组存储(i,j)格子里礼物的价值
	for (int i = 0; i < rows; ++i)
		maxValues[i] = new int[cols];

	for (int i = 0; i < rows; ++i) //这里的二层循环是为了计算从矩阵左上角开始，到每个(i,j)时候的最大价值，这样当整个循环完成之后，最后（len-1,len-1）就是最终的结果
	{
		for (int j = 0; j < cols; ++j)
		{
			int left = 0;
			int up = 0;

			if (i > 0)//不是第一行的话，就可以看其上一行，当前列所对应的值
				up = maxValues[i - 1][j];

			if (j > 0)//不是第一列的话，就可以看其左边一列，当前行对应的值
				left = maxValues[i][j - 1];

			maxValues[i][j] = std::max(left, up) + values[i * cols + j];//从左边和上方找到一个最大的值之后，加上当前的位置，即是当前位置最大的礼物数。
		}
	}

	int maxValue = maxValues[rows - 1][cols - 1];

	for (int i = 0; i < rows; ++i)
		delete[] maxValues[i];
	delete[] maxValues;

	return maxValue;
}

int getMaxValue_solution2(const int* values, int rows, int cols)//这种是对上一种的优化，这个一维数组前面j个数字分布式当前第i行前面j个格子的最大价值
{
	if (values == nullptr || rows <= 0 || cols <= 0)
		return 0;

	int* maxValues = new int[cols]; //这是个一维数组，其中存储的是当前列j下，前面i行中最大的价值数
	for (int i = 0; i < rows; ++i)//
	{
		for (int j = 0; j < cols; ++j)
		{
			int left = 0;
			int up = 0;

			if (i > 0)
				up = maxValues[j];

			if (j > 0)
				left = maxValues[j - 1];

			maxValues[j] = std::max(left, up) + values[i * cols + j];
		}
	}

	int maxValue = maxValues[cols - 1];

	delete[] maxValues;

	return maxValue;
}

// ====================测试代码====================
void test(const char* testName, const int* values, int rows, int cols, int expected)
{
	if (getMaxValue_solution1(values, rows, cols) == expected)
		std::cout << testName << ": solution1 passed." << std::endl;
	else
		std::cout << testName << ": solution1 FAILED." << std::endl;

	if (getMaxValue_solution2(values, rows, cols) == expected)
		std::cout << testName << ": solution2 passed." << std::endl;
	else
		std::cout << testName << ": solution2 FAILED." << std::endl;
}

void test1()
{
	// 三行三列
	int values[][3] = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 }
	};
	int expected = 29;
	test("test1", (const int*)values, 3, 3, expected);
}

void test2()
{
	//四行四列
	int values[][4] = {
		{ 1, 10, 3, 8 },
		{ 12, 2, 9, 6 },
		{ 5, 7, 4, 11 },
		{ 3, 7, 16, 5 }
	};
	int expected = 53;
	test("test2", (const int*)values, 4, 4, expected);
}

void test3()
{
	// 一行四列
	int values[][4] = {
		{ 1, 10, 3, 8 }
	};
	int expected = 22;
	test("test3", (const int*)values, 1, 4, expected);
}

void test4()
{
	int values[4][1] = {
		{ 1 },
		{ 12 },
		{ 5 },
		{ 3 }
	};
	int expected = 21;
	test("test4", (const int*)values, 4, 1, expected);
}

void test5()
{
	// 一行一列
	int values[][1] = {
		{ 3 }
	};
	int expected = 3;
	test("test5", (const int*)values, 1, 1, expected);
}

void test6()
{
	// 空指针
	int expected = 0;
	test("test6", nullptr, 0, 0, expected);
}


int _tmain(int argc, _TCHAR* argv[])
{
	test1();
	test2();
	test3();
	test4();
	test5();

	return 0;
}

