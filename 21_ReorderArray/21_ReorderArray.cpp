// 21_ReorderArray.cpp : 定义控制台应用程序的入口点。
//
// 面试题21：调整数组顺序使奇数位于偶数前面
// 题目：输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有
// 奇数位于数组的前半部分，所有偶数位于数组的后半部分。

#include "stdafx.h"

#include <cstdio>

void Reorder(int *pData, unsigned int length, bool(*func)(int));
bool isEven(int n);

// ====================方法一====================
void ReorderOddEven_1(int *pData, unsigned int length) //运用双指针方法
{
	if (pData == nullptr || length == 0)//输入的数组不为空，且长度不为空
		return;

	int *pBegin = pData; //首指针
	int *pEnd = pData + length - 1;//尾指针

	while (pBegin < pEnd) //当begin大于end的时候，说明前面都是奇数，后面都是偶数
	{
		// 向后移动pBegin，直到它指向偶数
		while (pBegin < pEnd && (*pBegin & 0x1) != 0)// 0x1表示 最后一位为，其余都是0，如果是奇数，则其&0x01！=0成立，因此首指针往后移，因为没有碰到偶数
			//当找到第一个偶数的时候，就记下其下标
			pBegin++;

		// 向前移动pEnd，直到它指向奇数
		while (pBegin < pEnd && (*pEnd & 0x1) == 0)
			//上面找到第一个偶数之后，下一步就是找到跟他交换的奇数，此时从尾指针开始往前找
			pEnd--;

		if (pBegin < pEnd) //说明满足交换的前提条件
		{
			int temp = *pBegin;
			*pBegin = *pEnd;
			*pEnd = temp;
		}
	}
}

// ====================方法二====================
void ReorderOddEven_2(int *pData, unsigned int length)
{
	Reorder(pData, length, isEven);//最后一个参数是分组标准
}

void Reorder(int *pData, unsigned int length, bool(*func)(int))
{
	if (pData == nullptr || length == 0)
		return;

	int *pBegin = pData;
	int *pEnd = pData + length - 1;

	while (pBegin < pEnd)
	{
		// 向后移动pBegin
		while (pBegin < pEnd && !func(*pBegin))
			pBegin++;

		// 向前移动pEnd
		while (pBegin < pEnd && func(*pEnd))
			pEnd--;

		if (pBegin < pEnd)
		{
			int temp = *pBegin;
			*pBegin = *pEnd;
			*pEnd = temp;
		}
	}
}

bool isEven(int n)//判断一个数是不是偶数，将其单独拿出来
{
	return (n & 1) == 0;
}

// ====================测试代码====================
void PrintArray(int numbers[], int length)
{
	if (length < 0)
		return;

	for (int i = 0; i < length; ++i)
		printf("%d\t", numbers[i]);

	printf("\n");
}

void Test(char* testName, int numbers[], int length)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	int* copy = new int[length];
	for (int i = 0; i < length; ++i)
	{
		copy[i] = numbers[i];
	}

	printf("Test for solution 1:\n");
	PrintArray(numbers, length);
	ReorderOddEven_1(numbers, length);
	PrintArray(numbers, length);

	printf("Test for solution 2:\n");
	PrintArray(copy, length);
	ReorderOddEven_2(copy, length);
	PrintArray(copy, length);

	delete[] copy;
}

void Test1()
{
	int numbers[] = { 1, 2, 3, 4, 5, 6, 7 };
	Test("Test1", numbers, sizeof(numbers) / sizeof(int));
}

void Test2()
{
	int numbers[] = { 2, 4, 6, 1, 3, 5, 7 };
	Test("Test2", numbers, sizeof(numbers) / sizeof(int));
}

void Test3()
{
	int numbers[] = { 1, 3, 5, 7, 2, 4, 6 };
	Test("Test3", numbers, sizeof(numbers) / sizeof(int));
}

void Test4()
{
	int numbers[] = { 1 };
	Test("Test4", numbers, sizeof(numbers) / sizeof(int));
}

void Test5()
{
	int numbers[] = { 2 };
	Test("Test5", numbers, sizeof(numbers) / sizeof(int));
}

void Test6()
{
	Test("Test6", nullptr, 0);
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

