// 49_UglyNumber.cpp : 定义控制台应用程序的入口点。
//

// 面试题49：丑数
// 题目：我们把只包含因子2、3和5的数称作丑数（Ugly Number）。求按从小到
// 大的顺序的第1500个丑数。例如6、8都是丑数，但14不是，因为它包含因子7。
// 习惯上我们把1当做第一个丑数。

#include "stdafx.h"
#include <cstdio>

// ====================算法1的代码====================  比较粗暴的解法
bool IsUgly(int number)//该函数是用来计算一个数是不是丑数，即要都能被2,3,5整除，除完这几个数之后，最终会得到1
{
	while (number % 2 == 0)
		number /= 2;
	while (number % 3 == 0)
		number /= 3;
	while (number % 5 == 0)
		number /= 5;

	return (number == 1) ? true : false;
}

int GetUglyNumber_Solution1(int index) //这个函数中传入从小到大顺序的第index个丑数
{
	if (index <= 0)
		return 0;

	int number = 0;//进行测试的数量
	int uglyFound = 0;//统计到number数的时候，已经有多少个丑数
	while (uglyFound < index)
	{
		++number;

		if (IsUgly(number))
			++uglyFound;
	}

	return number;
}

// ====================算法2的代码====================
int Min(int number1, int number2, int number3);

int GetUglyNumber_Solution2(int index)
{
	if (index <= 0)
		return 0;

	int *pUglyNumbers = new int[index];//一个辅助数组，用来存储从小到大排列的丑数
	pUglyNumbers[0] = 1;//第一个丑数为1
	int nextUglyIndex = 1;//记录当前存储丑数的数组中有多少个丑数

	int *pMultiply2 = pUglyNumbers;
	int *pMultiply3 = pUglyNumbers;
	int *pMultiply5 = pUglyNumbers;

	while (nextUglyIndex < index)
	{
		int min = Min(*pMultiply2 * 2, *pMultiply3 * 3, *pMultiply5 * 5);
		pUglyNumbers[nextUglyIndex] = min;

		while (*pMultiply2 * 2 <= pUglyNumbers[nextUglyIndex])
			++pMultiply2;//在数组中后移一位
		while (*pMultiply3 * 3 <= pUglyNumbers[nextUglyIndex])
			++pMultiply3;
		while (*pMultiply5 * 5 <= pUglyNumbers[nextUglyIndex])
			++pMultiply5;

		++nextUglyIndex;
	}

	int ugly = pUglyNumbers[nextUglyIndex - 1];
	delete[] pUglyNumbers;
	return ugly;
}

int Min(int number1, int number2, int number3)//这个是得到三个数中的最小值
{
	int min = (number1 < number2) ? number1 : number2;
	min = (min < number3) ? min : number3;

	return min;
}

// ====================测试代码====================
void Test(int index, int expected)
{
	if (GetUglyNumber_Solution1(index) == expected)
		printf("solution1 passed\n");
	else
		printf("solution1 failed\n");

	if (GetUglyNumber_Solution2(index) == expected)
		printf("solution2 passed\n");
	else
		printf("solution2 failed\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test(1, 1);

	Test(2, 2);
	Test(3, 3);
	Test(4, 4);
	Test(5, 5);
	Test(6, 6);
	Test(7, 8);
	Test(8, 9);
	Test(9, 10);
	Test(10, 12);
	Test(11, 15);

	Test(1500, 859963392);

	Test(0, 0);

	return 0;
}

