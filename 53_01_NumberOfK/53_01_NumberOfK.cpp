// 53_01_NumberOfK.cpp : 定义控制台应用程序的入口点。
//

// 面试题53（一）：数字在排序数组中出现的次数
// 题目：统计一个数字在排序数组中出现的次数。例如输入排序数组{1, 2, 3, 3,
// 3, 3, 4, 5}和数字3，由于3在这个数组中出现了4次，因此输出4。

#include "stdafx.h"
#include <cstdio>

int GetFirstK(const int* data, int length, int k, int start, int end);//该函数用来获取数组中第一个k在数组中的下标
int GetLastK(const int* data, int length, int k, int start, int end);//该函数用来获取数组中最后一个k在数组中的下标

int GetNumberOfK(const int* data, int length, int k)//当获取了最后一个k和第一个k的下标之后，两者相减加一就是数字在排序数组中出现的次数
{
	int number = 0;

	if (data != nullptr && length > 0)
	{
		int first = GetFirstK(data, length, k, 0, length - 1);//如果数组中不包含k，返回-1，否则就返回第一个k在数组中的下标
		int last = GetLastK(data, length, k, 0, length - 1);//如果数组中不包含k，返回-1，否则就返回最后一个k在数组中的下标

		if (first > -1 && last > -1)
			number = last - first + 1;
	}

	return number;
}

// 找到数组中第一个k的下标。如果数组中不存在k，返回-1
int GetFirstK(const int* data, int length, int k, int start, int end)
{
	if (start > end)//输入是否合法
		return -1;

	int middleIndex = (start + end) / 2;//获取当前数组中中间的下标号
	int middleData = data[middleIndex];//获取数组中间的元素

	if (middleData == k)//如果中间位置处的元素等于k
	{
		if ((middleIndex > 0 && data[middleIndex - 1] != k)//此时判断下标是否合法且该下标的前一个不为k，说明这个下标处就是第一个k的位置
			|| middleIndex == 0)// middleIndex == 0表示元素值等于k的时候，其位置是数组第一个元素，不存在前一个元素，是对上面判断条件的补充
			return middleIndex;
		else
			end = middleIndex - 1; //否则该位置处前一个元素还是为k，说明第一个k一定在当前数组的左半部分，所以把end改为middleIndex - 1
	}
	else if (middleData > k)//如果中间位置处的元素大于k，说明第一个k一定在当前数组的左半部分，所以把end改为middleIndex - 1
		end = middleIndex - 1;
	else                   //如果中间位置处的元素小于k，说明第一个k一定在当前数组的右半部分，所以把start改为middleIndex + 1
		start = middleIndex + 1;

	return GetFirstK(data, length, k, start, end);//修改范围后，开始递归的继续寻找第一个k的下标，找到就返回middleIndex
}

// 找到数组中最后一个k的下标。如果数组中不存在k，返回-1
int GetLastK(const int* data, int length, int k, int start, int end)
{
	if (start > end)//输入是否合法
		return -1;

	int middleIndex = (start + end) / 2;//获取当前数组中中间的下标号
	int middleData = data[middleIndex];//获取数组中间的元素

	if (middleData == k)//如果中间位置处的元素等于k
	{
		if ((middleIndex < length - 1 && data[middleIndex + 1] != k) // 此时判断下标是否合法且该下标的后一个不为k，说明这个下标处就是最后一个k的位置
			|| middleIndex == length - 1)//middleIndex == length - 1说明元素值等于k的时候，其位置是数组最后一个元素，不存在前一个元素，是对上面判断条件的补充
			return middleIndex;
		else
			start = middleIndex + 1;//否则该位置处后一个元素还是为k，说明最后一个k一定在当前数组的右半部分，所以把start改为middleIndex + 1
	}
	else if (middleData < k)
		start = middleIndex + 1;  //如果中间位置处的元素小于k，说明第一个k一定在当前数组的右半部分，所以把start改为middleIndex + 1
	else
		end = middleIndex - 1;    //如果中间位置处的元素大于k，说明第一个k一定在当前数组的左半部分，所以把end改为middleIndex - 1

	return GetLastK(data, length, k, start, end);
}

// ====================测试代码====================
void Test(const char* testName, int data[], int length, int k, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	int result = GetNumberOfK(data, length, k);
	if (result == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// 查找的数字出现在数组的中间
void Test1()
{
	int data[] = { 1, 2, 3, 3, 3, 3, 4, 5 };
	Test("Test1", data, sizeof(data) / sizeof(int), 3, 4);
}

// 查找的数组出现在数组的开头
void Test2()
{
	int data[] = { 3, 3, 3, 3, 4, 5 };
	Test("Test2", data, sizeof(data) / sizeof(int), 3, 4);
}

// 查找的数组出现在数组的结尾
void Test3()
{
	int data[] = { 1, 2, 3, 3, 3, 3 };
	Test("Test3", data, sizeof(data) / sizeof(int), 3, 4);
}

// 查找的数字不存在
void Test4()
{
	int data[] = { 1, 3, 3, 3, 3, 4, 5 };
	Test("Test4", data, sizeof(data) / sizeof(int), 2, 0);
}

// 查找的数字比第一个数字还小，不存在
void Test5()
{
	int data[] = { 1, 3, 3, 3, 3, 4, 5 };
	Test("Test5", data, sizeof(data) / sizeof(int), 0, 0);
}

// 查找的数字比最后一个数字还大，不存在
void Test6()
{
	int data[] = { 1, 3, 3, 3, 3, 4, 5 };
	Test("Test6", data, sizeof(data) / sizeof(int), 6, 0);
}

// 数组中的数字从头到尾都是查找的数字
void Test7()
{
	int data[] = { 3, 3, 3, 3 };
	Test("Test7", data, sizeof(data) / sizeof(int), 3, 4);
}

// 数组中的数字从头到尾只有一个重复的数字，不是查找的数字
void Test8()
{
	int data[] = { 3, 3, 3, 3 };
	Test("Test8", data, sizeof(data) / sizeof(int), 4, 0);
}

// 数组中只有一个数字，是查找的数字
void Test9()
{
	int data[] = { 3 };
	Test("Test9", data, sizeof(data) / sizeof(int), 3, 1);
}

// 数组中只有一个数字，不是查找的数字
void Test10()
{
	int data[] = { 3 };
	Test("Test10", data, sizeof(data) / sizeof(int), 4, 0);
}

// 鲁棒性测试，数组空指针
void Test11()
{
	Test("Test11", nullptr, 0, 0, 0);
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

	return 0;
}

