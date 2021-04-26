// 63_MaximalProfit.cpp : 定义控制台应用程序的入口点。
//

// 面试题63：股票的最大利润
// 题目：假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖交易该股
// 票可能获得的利润是多少？例如一只股票在某些时间节点的价格为{9, 11, 8, 5,
// 7, 12, 16, 14}。如果我们能在价格为5的时候买入并在价格为16时卖出，则能
// 收获最大的利润11。

#include "stdafx.h"

#include <cstdio>

//思路:动态规划类型，定义函数diff(i)表示当卖出价为数组中第i个数组时可能获得的最大利润，当第i个数字对应的值固定的情况下，显然前面的数字越小越好，
// 也就是说，扫描到数组的第i个数字的时候，只要我们能记住前面i-1个数字中的最小值就可以得到最大利润
int MaxDiff(const int* numbers, unsigned length)
{
	if (numbers == nullptr && length < 2)//输入是否合法，数组长度必须>=2才存在买卖的利润
		return 0;

	int min = numbers[0];//记录数组中最小的数据
	int maxDiff = numbers[1] - min;//计算最大利润

	for (int i = 2; i < length; ++i)//从数组第二项开始计算
	{
		if (numbers[i - 1] < min)//如果当前i处的数据要比之前记录的m要小，则更新最小数据
			min = numbers[i - 1];

		int currentDiff = numbers[i] - min;//一个临时变量存储当前i处的值与最小值的差
		if (currentDiff > maxDiff)//如果得到的利润比之前计算的大，则更新
			maxDiff = currentDiff;
	}

	return maxDiff;
}

// ==================== Test Code ====================
void Test(const char* testName, const int* numbers, unsigned int length, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (MaxDiff(numbers, length) == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

void Test1()
{
	int numbers[] = { 4, 1, 3, 2, 5 };
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), 4);
}

// 价格递增
void Test2()
{
	int numbers[] = { 1, 2, 4, 7, 11, 16 };
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), 15);
}

// 价格递减
void Test3()
{
	int numbers[] = { 16, 11, 7, 4, 2, 1 };
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), -1);
}

// 价格全部相同
void Test4()
{
	int numbers[] = { 16, 16, 16, 16, 16 };
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), 0);
}

void Test5()
{
	int numbers[] = { 9, 11, 5, 7, 16, 1, 4, 2 };
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), 11);
}

void Test6()
{
	int numbers[] = { 2, 4 };
	Test("Test6", numbers, sizeof(numbers) / sizeof(int), 2);
}

void Test7()
{
	int numbers[] = { 4, 2 };
	Test("Test7", numbers, sizeof(numbers) / sizeof(int), -2);
}

void Test8()
{
	Test("Test8", nullptr, 0, 0);
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
	Test8();

	return 0;
}

