// 53_03_IntegerIdenticalToIndex.cpp : 定义控制台应用程序的入口点。
//

// 面试题53（三）：数组中数值和下标相等的元素
// 题目：假设一个单调递增的数组里的每个元素都是整数并且是唯一的。请编程实
// 现一个函数找出数组中任意一个数值等于其下标的元素。例如，在数组{-3, -1,
// 1, 3, 5}中，数字3和它的下标相等。

#include "stdafx.h"

#include <cstdio>

int GetNumberSameAsIndex(const int* numbers, int length)//运用递增队列（排好序）的特点，使用二分查找，将时间复杂度o(n)->o(logn)
{
	if (numbers == nullptr || length <= 0)//判断输入是否合理
		return -1;

	int left = 0;
	int right = length - 1;
	while (left <= right) //缩小范围进行判断，直到前后相遇了
	{
		int middle = left + ((right - left) >> 1);//计算中间的下标
		if (numbers[middle] == middle)//此时满足条件找到了
			return middle;

		if (numbers[middle] > middle)//如果数字的值大于他的下标，则其右边的数字都大于对应的下标
			// 思路是：当前数字值m，下标i，m>i,从i开始，任意一个大于0的k，由于数组是递增的因此下标i+k的数字的值一定大于m+k（假设都是加一增长）,又有m+k>i+k，故得到上面结论
			right = middle - 1;
		else //如果不满足，则下一轮我们只需要从其左边的数字中查找
			left = middle + 1;
	}

	return -1;
}

// ====================测试代码====================
void Test(const char* testName, int numbers[], int length, int expected)
{
	if (GetNumberSameAsIndex(numbers, length) == expected)
		printf("%s passed.\n", testName);
	else
		printf("%s FAILED.\n", testName);
}

void Test1()
{
	int numbers[] = { -3, -1, 1, 3, 5 };
	int expected = 3;
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test2()
{
	int numbers[] = { 0, 1, 3, 5, 6 };
	int expected = 0;
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test3()
{
	int numbers[] = { -1, 0, 1, 2, 4 };
	int expected = 4;
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test4()
{
	int numbers[] = { -1, 0, 1, 2, 5 };
	int expected = -1;
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test5()
{
	int numbers[] = { 0 };
	int expected = 0;
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test6()
{
	int numbers[] = { 10 };
	int expected = -1;
	Test("Test6", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test7()
{
	Test("Test7", nullptr, 0, -1);
}


int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	return 0;
}

