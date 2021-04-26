// 11_MinNumberInRotatedArray.cpp : 定义控制台应用程序的入口点。
//
// 面试题11：旋转数组的最小数字
// 题目：把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
// 输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。例如数组
// {3, 4, 5, 1, 2}为{1, 2, 3, 4, 5}的一个旋转，该数组的最小值为1。

#include <cstdio>
#include <exception>
#include "stdafx.h"
#include <iostream> //解决error C2039: “exception”: 不是“std”的成员
using namespace std;

int MinInOrder(int* numbers, int index1, int index2);                                          

int Min(int* numbers, int length)
{
	if (numbers == nullptr || length <= 0)
		throw new std::exception("Invalid parameters");

	int index1 = 0; //类似指向第一个的指针
	int index2 = length - 1; // 类似指向最后一个元素的指针
	int indexMid = index1;
	while (numbers[index1] >= numbers[index2]) //此时是针对一个特例： 如果把排序数组的前面的0个元素搬到最后面的情况，即numbers[index1] < numbers[index2]，那么就直接输出第一个
	{    //为此在初始化的时候，将其赋予第一个的编号，即令其值为0；
	
		// 如果index1和index2指向相邻的两个数，  
		// 则index1指向第一个递增子数组的最后一个数字，
		// index2指向第二个子数组的第一个数字，也就是数组中的最小数字
		if (index2 - index1 == 1)
		{
			indexMid = index2;//两指针相遇，此时index2指针对应的就是那个元素的序号
			break;
		}

		// 如果下标为index1、index2和indexMid指向的三个数字相等，  特殊情况例如 10111和11101都可以看成递增序列01111的旋转，在这两个例子中，第一个/最后一个/中间数字都是1，因此
		// 无法确定中间的数字是属于哪个递增序列（第一个还是第二个），则只能顺序查找来判断；
		indexMid = (index1 + index2) / 2;
		if (numbers[index1] == numbers[index2] && numbers[indexMid] == numbers[index1])
			return MinInOrder(numbers, index1, index2);

		// 缩小查找范围
		if (numbers[indexMid] >= numbers[index1])
			index1 = indexMid;
		else if (numbers[indexMid] <= numbers[index2])
			index2 = indexMid;
	}

	return numbers[indexMid];
}

int MinInOrder(int* numbers, int index1, int index2)
{
	int result = numbers[index1];
	for (int i = index1 + 1; i <= index2; ++i) //顺序查找从而得到其中最小的数据
	{
		if (result > numbers[i])
			result = numbers[i];
	}

	return result;
}

// ====================测试代码====================
void Test(int* numbers, int length, int expected)
{
	int result = 0;
	try
	{
		result = Min(numbers, length);

		for (int i = 0; i < length; ++i)
			printf("%d ", numbers[i]);

		if (result == expected)
			printf("\tpassed\n");
		else
			printf("\tfailed\n");
	}
	catch (...)
	{
		if (numbers == nullptr)
			printf("Test passed.\n");
		else
			printf("Test failed.\n");
	}
}



int _tmain(int argc, _TCHAR* argv[])
{

	// 典型输入，单调升序的数组的一个旋转
	int array1[] = { 3, 4, 5, 1, 2 };
	Test(array1, sizeof(array1) / sizeof(int), 1);

	// 有重复数字，并且重复的数字刚好的最小的数字
	int array2[] = { 3, 4, 5, 1, 1, 2 };
	Test(array2, sizeof(array2) / sizeof(int), 1);

	// 有重复数字，但重复的数字不是第一个数字和最后一个数字
	int array3[] = { 3, 4, 5, 1, 2, 2 };
	Test(array3, sizeof(array3) / sizeof(int), 1);

	// 有重复的数字，并且重复的数字刚好是第一个数字和最后一个数字
	int array4[] = { 1, 0, 1, 1, 1 };
	Test(array4, sizeof(array4) / sizeof(int), 0);

	// 单调升序数组，旋转0个元素，也就是单调升序数组本身
	int array5[] = { 1, 2, 3, 4, 5 };
	Test(array5, sizeof(array5) / sizeof(int), 1);

	// 数组中只有一个数字
	int array6[] = { 2 };
	Test(array6, sizeof(array6) / sizeof(int), 2);

	// 输入nullptr
	Test(nullptr, 0, 0);

	return 0;
}

