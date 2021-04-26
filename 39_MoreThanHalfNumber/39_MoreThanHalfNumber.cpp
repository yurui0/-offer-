// 39_MoreThanHalfNumber.cpp : 定义控制台应用程序的入口点。
//

// 面试题39：数组中出现次数超过一半的数字
// 题目：数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例
// 如输入一个长度为9的数组{1, 2, 3, 2, 2, 2, 5, 4, 2}。由于数字2在数组中
// 出现了5次，超过数组长度的一半，因此输出2。

#include "stdafx.h"

#include <cstdio>
#include "Array.h"

bool g_bInputInvalid = false;

bool CheckInvalidArray(int* numbers, int length)//判断输入的数组和其他参数是否合法
{
	g_bInputInvalid = false;
	if (numbers == nullptr && length <= 0)
		g_bInputInvalid = true;

	return g_bInputInvalid;
}

bool CheckMoreThanHalf(int* numbers, int length, int number)//判断找到的中位数，其数据出现次数是否占据了数组长度的一般
{
	int times = 0;
	for (int i = 0; i < length; ++i)//统计该数字出现的次数
	{
		if (numbers[i] == number)
			times++;
	}

	bool isMoreThanHalf = true;
	if (times * 2 <= length)
	{
		g_bInputInvalid = true;
		isMoreThanHalf = false;
	}

	return isMoreThanHalf;
}

// ====================方法1====================
////思路是：找到数组中数据排序后的中位数，因为如果满足条件，则该数字必定是中位数（中位数就是长度为n的数组中第2/n大的数字）
int MoreThanHalfNum_Solution1(int* numbers, int length)//这个函数是希望找到数组中所有数字的中位数
{
	if (CheckInvalidArray(numbers, length))//判断输入的数组是否是有效的
		return 0;

	int middle = length >> 1;
	int start = 0;
	int end = length - 1;
	int index = Partition(numbers, length, start, end);//这个函数的意义是：随机选择一个数字，然后基于这个数字将数组分为两段，左边都小于这个数字，右边都大于这个数字
	while (index != middle)//得到排序完后的数字所在的序号后，和2/n相比较
	{
		if (index > middle)//如果其比2 / n大，则要找的中位数应该在index左边
		{
			end = index - 1;
			index = Partition(numbers, length, start, end);
		}
		else//否则，要找的数字应该在index右边
		{
			start = index + 1;
			index = Partition(numbers, length, start, end);
		}
	}

	int result = numbers[middle];
	if (!CheckMoreThanHalf(numbers, length, result))//判断找到的数组的中位数其是否在数组中的出现次数是否超过数组长度的一半
		result = 0;

	return result;
}

// ====================方法2====================
//思路是：记录下数组中出现次数最高的数据，然后将其出现的次数与2/n相比较
int MoreThanHalfNum_Solution2(int* numbers, int length) //这个函数的目的是，找出出现次数最高的数据，随后在CheckMoreThanHalf中判断他出现的次数是否超过2/n
{
	if (CheckInvalidArray(numbers, length))
		return 0;

	int result = numbers[0];
	int times = 1;
	for (int i = 1; i < length; ++i)
	{
		if (times == 0)
		{
			result = numbers[i];
			times = 1;
		}
		else if (numbers[i] == result)
			times++;
		else
			times--;
	}

	if (!CheckMoreThanHalf(numbers, length, result))
		result = 0;

	return result;
}

// ====================测试代码====================
void Test(char* testName, int* numbers, int length, int expectedValue, bool expectedFlag)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	int* copy = new int[length];
	for (int i = 0; i < length; ++i)
		copy[i] = numbers[i];

	printf("Test for solution1: ");
	int result = MoreThanHalfNum_Solution1(numbers, length);
	if (result == expectedValue && g_bInputInvalid == expectedFlag)
		printf("Passed.\n");
	else
		printf("Failed.\n");

	printf("Test for solution2: ");
	result = MoreThanHalfNum_Solution2(copy, length);
	if (result == expectedValue && g_bInputInvalid == expectedFlag)
		printf("Passed.\n");
	else
		printf("Failed.\n");

	delete[] copy;
}

// 存在出现次数超过数组长度一半的数字
void Test1()
{
	int numbers[] = { 1, 2, 3, 2, 2, 2, 5, 4, 2 };
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), 2, false);
}

// 不存在出现次数超过数组长度一半的数字
void Test2()
{
	int numbers[] = { 1, 2, 3, 2, 4, 2, 5, 2, 3 };
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), 0, true);
}

// 出现次数超过数组长度一半的数字都出现在数组的前半部分
void Test3()
{
	int numbers[] = { 2, 2, 2, 2, 2, 1, 3, 4, 5 };
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), 2, false);
}

// 出现次数超过数组长度一半的数字都出现在数组的后半部分
void Test4()
{
	int numbers[] = { 1, 3, 4, 5, 2, 2, 2, 2, 2 };
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), 2, false);
}

// 输入空指针
void Test5()
{
	int numbers[] = { 1 };
	Test("Test5", numbers, 1, 1, false);
}

// 输入空指针
void Test6()
{
	Test("Test6", nullptr, 0, 0, true);
}


int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	return 0;
}

