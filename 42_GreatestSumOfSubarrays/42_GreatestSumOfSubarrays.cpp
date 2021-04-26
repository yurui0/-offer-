// 42_GreatestSumOfSubarrays.cpp : 定义控制台应用程序的入口点。
//

// 面试题42：连续子数组的最大和
// 题目：输入一个整型数组，数组里有正数也有负数。数组中一个或连续的多个整
// 数组成一个子数组。求所有子数组的和的最大值。要求时间复杂度为O(n)。

#include "stdafx.h"

#include <cstdio>

bool g_InvalidInput = false;//这个是为了判断输入是否合法，false表示合法，当然这种可以随时变更

int FindGreatestSumOfSubArray(int *pData, int nLength)
{
	if ((pData == nullptr) || (nLength <= 0))
	{
		g_InvalidInput = true;//输入不合法
		return 0;
	}

	g_InvalidInput = false;//这里说明输入是合法的

	int nCurSum = 0;// 表示 累加的子数组和
	int nGreatestSum = 0x80000000; //表示 最大的子数组和 ，初始化为32位int最小的负数值(也就是-2147483648),这是补码形式,也是原码
	for (int i = 0; i < nLength; ++i)
	{
		if (nCurSum <= 0)//如果累加的子数组和为负（即上一次循环加了一个负数，使得累加的子数组和为负数）
			nCurSum = pData[i]; //则从当前i开始重新计算，抛弃之前累加的子数组和

		else   // 如果累加的子数组和不为负数，则将其加上新的当前的数字
			nCurSum += pData[i];


		if (nCurSum > nGreatestSum) //如果加了新数字之和的 累加的子数组和 要比我们保存的 最大的子数组和 要大，则更需子数组和
			nGreatestSum = nCurSum;
	}

	return nGreatestSum;
}

// ====================测试代码====================
void Test(char* testName, int* pData, int nLength, int expected, bool expectedFlag)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	int result = FindGreatestSumOfSubArray(pData, nLength);
	if (result == expected && expectedFlag == g_InvalidInput)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// 1, -2, 3, 10, -4, 7, 2, -5
void Test1()
{
	int data[] = { 1, -2, 3, 10, -4, 7, 2, -5 };
	Test("Test1", data, sizeof(data) / sizeof(int), 18, false);
}

// 所有数字都是负数
// -2, -8, -1, -5, -9
void Test2()
{
	int data[] = { -2, -8, -1, -5, -9 };
	Test("Test2", data, sizeof(data) / sizeof(int), -1, false);
}

// 所有数字都是正数
// 2, 8, 1, 5, 9
void Test3()
{
	int data[] = { 2, 8, 1, 5, 9 };
	Test("Test3", data, sizeof(data) / sizeof(int), 25, false);
}

// 无效输入
void Test4()
{
	Test("Test4", nullptr, 0, 0, true);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();

	return 0;
}

