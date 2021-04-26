// 60_DicesProbability.cpp : 定义控制台应用程序的入口点。
 //

// 面试题60：n个骰子的点数
// 题目：把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s
// 的所有可能的值出现的概率。

#include "stdafx.h"

#include <cstdio>
#include <math.h>

int g_maxValue = 6;

// ====================方法一==================== //运用递归的思路完成
void Probability(int number, int* pProbabilities);
void Probability(int original, int current, int sum, int* pProbabilities);

void PrintProbability_Solution1(int number)//主函数，参数number表示n个骰子
{
	if (number < 1)//输入是否合法
		return;

	int maxSum = number * g_maxValue;//因为一个骰子的值范围为[1,6]，因此n个骰子的和最大位6n
	int* pProbabilities = new int[maxSum - number + 1];//创建存储向上的n个骰子的和sum的数组，数组的范围是6n-n+1，因为sum最小为n，最大位6n，
														// 至于“+1”是因为两个数相减后表示的两者之间的数的个数要比两数相减值少一
	for (int i = number; i <= maxSum; ++i)
		pProbabilities[i - number] = 0;//初始化，给sum范围为[n,6n]之间的赋值，对应到数组中就是[0,6n-n]

	Probability(number, pProbabilities);//计算n个骰子可能出现的sum的次数，为后面计算概率做铺垫

	int total = pow((double)g_maxValue, number); //pow是幂函数，即pow(x,y)表示x^y，x的y次幂，这里是计算6^n次，因为n个骰子的所有点数排列为6x6x6...x6，也就是6^n
	for (int i = number; i <= maxSum; ++i)
	{
		double ratio = (double)pProbabilities[i - number] / total;//计算每一种可能的结果出现的概率
		printf("%d: %e\n", i, ratio);
	}

	delete[] pProbabilities;
}

void Probability(int number, int* pProbabilities)
{
	//这里是将n个骰子分为两堆，一堆一个骰子，另一堆n-1个，这里是第一个骰子的值从[1,6]开始分别计算剩余n-1堆的可能的sum和
	for (int i = 1; i <= g_maxValue; ++i) 
		Probability(number, number, i, pProbabilities);
}

void Probability(int original, int current, int sum,int* pProbabilities)// original表示骰子数n，current表示划分为两堆后第二堆的数量，
															// sum表示对应current划分的堆的情况下，前面一个堆的骰子和sum，pProbabilities存储不同骰子对应点数的数组
{
	if (current == 1)
	{
		pProbabilities[sum - original]++;
	}
	else
	{
		for (int i = 1; i <= g_maxValue; ++i)
		{
			Probability(original, current - 1, i + sum, pProbabilities);
		}
	}
}

// ====================方法二====================
void PrintProbability_Solution2(int number) //这一个思路是：基于循环求骰子点数
{
	if (number < 1)//输入是否合法
		return;

	int* pProbabilities[2];//创建两个数组，第一个数组的第n项等于骰子和为n出现的次数，另一个数组的第n个数字表示前一个数组对应的第[n-1,n-6]个数字之和
	pProbabilities[0] = new int[g_maxValue * number + 1];
	pProbabilities[1] = new int[g_maxValue * number + 1];
	for (int i = 0; i < g_maxValue * number + 1; ++i)
	{
		pProbabilities[0][i] = 0;
		pProbabilities[1][i] = 0;
	}

	int flag = 0;
	for (int i = 1; i <= g_maxValue; ++i)
		pProbabilities[flag][i] = 1;

	for (int k = 2; k <= number; ++k)
	{
		for (int i = 0; i < k; ++i)
			pProbabilities[1 - flag][i] = 0;

		for (int i = k; i <= g_maxValue * k; ++i)
		{
			pProbabilities[1 - flag][i] = 0;
			for (int j = 1; j <= i && j <= g_maxValue; ++j)
				pProbabilities[1 - flag][i] += pProbabilities[flag][i - j]; //另一个数组的第n个数字表示前一个数组对应的第[n - 1, n - 6]个数字之和
		}

		flag = 1 - flag;//在下一轮循环中交换这两个数组代表的意义
	}

	double total = pow((double)g_maxValue, number);//pow是幂函数，即pow(x,y)表示x^y，x的y次幂，这里是计算6^n次，因为n个骰子的所有点数排列为6x6x6...x6，也就是6^n
	for (int i = number; i <= g_maxValue * number; ++i)
	{
		double ratio = (double)pProbabilities[flag][i] / total;//计算每一种可能的结果出现的概率
		printf("%d: %e\n", i, ratio);
	}

	delete[] pProbabilities[0];
	delete[] pProbabilities[1];
}

// ====================测试代码====================
void Test(int n)
{
	printf("Test for %d begins:\n", n);

	printf("Test for solution1\n");
	PrintProbability_Solution1(n);

	printf("Test for solution2\n");
	PrintProbability_Solution2(n);

	printf("\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test(1);
	Test(2);
	Test(3);
	Test(4);

	Test(11);

	Test(0);

	return 0;
}

