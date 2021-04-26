// 51_InversePairs.cpp : 定义控制台应用程序的入口点。
//

// 面试题51：数组中的逆序对
// 题目：在数组中的两个数字如果前面一个数字大于后面的数字，则这两个数字组
// 成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。

#include "stdafx.h"
#include <iostream>
#include <cstdio>
using namespace std;

int InversePairsCore(int* data, int* copy, int start, int end);

int InversePairs(int* data, int length)//本题目的起始位置
{
	if (data == nullptr || length < 0)//判断输入是否合法
		return 0;

	int* copy = new int[length]; // 本数组为输入数组长度的辅助数组
	for (int i = 0; i < length; ++i)
		copy[i] = data[i];

	int count = InversePairsCore(data, copy, 0, length - 1);
	delete[] copy;

	return count;
}

int InversePairsCore(int* data, int* copy, int start, int end)
{
	if (start == end)
	{
		copy[start] = data[start];
		return 0;
	}

	int length = (end - start) / 2;

	int left = InversePairsCore(copy, data, start, start + length);//递归，每次只对拆分后的左右两个子数组进行比较
	int right = InversePairsCore(copy, data, start + length + 1, end);

	// i初始化为前半段最后一个数字的下标
	int i = start + length;
	// j初始化为后半段最后一个数字的下标
	int j = end;
	int indexCopy = end;
	int count = 0;
	while (i >= start && j >= start + length + 1)
	{
		if (data[i] > data[j])//前半段最后一个数字的下标>后半段最后一个数字的下标
		{
			copy[indexCopy--] = data[i--];//将前半段最后的数字添加到辅助数组中对应位置
			count += j - start - length;//此时逆序对的数量等于第二个子数组中剩余数字的个数
		}
		else
		{
			copy[indexCopy--] = data[j--];//前半段最后一个数字的下标<后半段最后一个数字的下标,不构成逆序对
		}
	}

	for (; i >= start; --i)
		copy[indexCopy--] = data[i];

	for (; j >= start + length + 1; --j)
		copy[indexCopy--] = data[j];

	return left + right + count;//返回当前循环下的逆序数
}

// ====================测试代码====================
void Test(char* testName, int* data, int length, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (InversePairs(data, length) == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

void Test1()
{
	int data[] = { 1, 2, 3, 4, 7, 6, 5 };
	int expected = 3;

	Test("Test1", data, sizeof(data) / sizeof(int), expected);
}

// 递减排序数组
void Test2()
{
	int data[] = { 6, 5, 4, 3, 2, 1 };
	int expected = 15;

	Test("Test2", data, sizeof(data) / sizeof(int), expected);
}

// 递增排序数组
void Test3()
{
	int data[] = { 1, 2, 3, 4, 5, 6 };
	int expected = 0;

	Test("Test3", data, sizeof(data) / sizeof(int), expected);
}

// 数组中只有一个数字
void Test4()
{
	int data[] = { 1 };
	int expected = 0;

	Test("Test4", data, sizeof(data) / sizeof(int), expected);
}


// 数组中只有两个数字，递增排序
void Test5()
{
	int data[] = { 1, 2 };
	int expected = 0;

	Test("Test5", data, sizeof(data) / sizeof(int), expected);
}

// 数组中只有两个数字，递减排序
void Test6()
{
	int data[] = { 2, 1 };
	int expected = 1;

	Test("Test6", data, sizeof(data) / sizeof(int), expected);
}

// 数组中有相等的数字
void Test7()
{
	int data[] = { 1, 2, 1, 2, 1 };
	int expected = 3;

	Test("Test7", data, sizeof(data) / sizeof(int), expected);
}

void Test8()
{
	int expected = 0;

	Test("Test8", nullptr, 0, expected);
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

	static double value[6];
	
	for (int i = 0; i <=6; i++)
		value[i] = i;

	for (int i = 0; i <= 6; i++)
		cout << value[i] << endl;

	for (int i = 0; i <= 6; i++)
		value[i] = i+10;

	for (int i = 0; i <= 6; i++)
		cout << value[i] << endl;


	return 0;
}

