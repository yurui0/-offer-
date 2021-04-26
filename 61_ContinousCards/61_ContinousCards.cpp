// 61_ContinousCards.cpp : 定义控制台应用程序的入口点。
//

// 面试题61：扑克牌的顺子
// 题目：从扑克牌中随机抽5张牌，判断是不是一个顺子，即这5张牌是不是连续的。
// 2～10为数字本身，A为1，J为11，Q为12，K为13，而大、小王可以看成任意数字。

#include "stdafx.h"

#include <cstdio>
#include <cstdlib>

int Compare(const void *arg1, const void *arg2);

bool IsContinuous(int* numbers, int length)//输入数组，数组的长度
{
	if (numbers == nullptr || length < 1)//判断输入是否合法
		return false;

	qsort(numbers, length, sizeof(int), Compare);//调用c语言的qsort函数实现数组排序。
	// qsort函数C语言编译器函数库自带的排序函数,void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))
	// base-- 指向要排序的数组的第一个元素的指针。nitems-- 由 base 指向的数组中元素的个数。size-- 数组中每个元素的大小，以字节为单位。
	// compar-- 用来比较两个元素的函数，即函数指针（回调函数）

	//这里qsort时间复杂度为O（nlogn），我们也可以自己定义一个长度为14的hash表，这样在O(n)的范围内就可以实现排序
	//不过注意：不同级别的时间复杂度只有当n足够大的时候才有意义。这里只有5张牌，O（nlogn）与O(n)差距不大，因此可以现有的简单函数

	int numberOfZero = 0;//记录数组中0的个数
	int numberOfGap = 0;//记录数组中非0元素之间的空隙的大小

	// 统计数组中0的个数
	for (int i = 0; i < length && numbers[i] == 0; ++i)
		++numberOfZero;

	// 统计数组中的间隔数目
	int small = numberOfZero; //因为之前已经排序（递增），因此计算gap的起始编号为0的个数，即第一位非0的数字的下标
	int big = small + 1;   // 第二位非0的数字的下标
	while (big < length) //第二位数字的下标没有到达数组的末尾---因为只能在[0,length-1]之间
	{
		// 两个数相等，有对子，不可能是顺子
		if (numbers[small] == numbers[big])
			return false;

		numberOfGap += numbers[big] - numbers[small] - 1;//numbers[big] - numbers[small] - 1就是两个数之间的gap，如果是相邻的就为0
		//  这里统计值不为0的数据之间的gap的总和，如果总和比0的个数大，那么靠0所代表任意数字进行填补就无法实现顺序数组
		// 这里是依次判断后续的数字
		small = big;
		++big;
	}

	return (numberOfGap > numberOfZero) ? false : true;//0不足以填补空隙，说明不是顺子，否则是顺子
}

int Compare(const void *arg1, const void *arg2)
{
	return *(int*)arg1 - *(int*)arg2;
	// 如果compar返回值小于0（< 0），那么p1所指向元素会被排在p2所指向元素的左面；如果compar返回值等于0（ = 0），那么p1所指向元素与p2所指向元素的顺序不确定；
	// 如果compar返回值大于0（> 0），那么p1所指向元素会被排在p2所指向元素的右面。

}

// ====================测试代码====================
void Test(const char* testName, int* numbers, int length, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (IsContinuous(numbers, length) == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

void Test1()
{
	int numbers[] = { 1, 3, 2, 5, 4 };
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), true);
}

void Test2()
{
	int numbers[] = { 1, 3, 2, 6, 4 };
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), false);
}

void Test3()
{
	int numbers[] = { 0, 3, 2, 6, 4 };
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), true);
}

void Test4()
{
	int numbers[] = { 0, 3, 1, 6, 4 };
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), false);
}

void Test5()
{
	int numbers[] = { 1, 3, 0, 5, 0 };
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), true);
}

void Test6()
{
	int numbers[] = { 1, 3, 0, 7, 0 };
	Test("Test6", numbers, sizeof(numbers) / sizeof(int), false);
}

void Test7()
{
	int numbers[] = { 1, 0, 0, 5, 0 };
	Test("Test7", numbers, sizeof(numbers) / sizeof(int), true);
}

void Test8()
{
	int numbers[] = { 1, 0, 0, 7, 0 };
	Test("Test8", numbers, sizeof(numbers) / sizeof(int), false);
}

void Test9()
{
	int numbers[] = { 3, 0, 0, 0, 0 };
	Test("Test9", numbers, sizeof(numbers) / sizeof(int), true);
}

void Test10()
{
	int numbers[] = { 0, 0, 0, 0, 0 };
	Test("Test10", numbers, sizeof(numbers) / sizeof(int), true);
}

// 有对子
void Test11()
{
	int numbers[] = { 1, 0, 0, 1, 0 };
	Test("Test11", numbers, sizeof(numbers) / sizeof(int), false);
}

// 鲁棒性测试
void Test12()
{
	Test("Test12", nullptr, 0, false);
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
	Test9();
	Test10();
	Test11();
	Test12();

	return 0;
}

