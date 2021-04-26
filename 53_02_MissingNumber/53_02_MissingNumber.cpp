// 53_02_MissingNumber.cpp : 定义控制台应用程序的入口点。
//

// 面试题53（二）：0到n-1中缺失的数字
// 题目：一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字
// 都在范围0到n-1之内。在范围0到n-1的n个数字中有且只有一个数字不在该数组
// 中，请找出这个数字。

#include "stdafx.h"

#include <cstdio>

int GetMissingNumber(const int* numbers, int length)//基于二分查找寻找0--n-1中缺少的数字
{
	if (numbers == nullptr || length <= 0)//输入是否合法
		return -1;

	int left = 0;
	int right = length - 1;
	while (left <= right) //这里是运用循环的方法实现类似递归的效果
	{
		int middle = (right + left) >> 1;//数据为正的情况下，a>>1表示数据的二进制表示右移一位，即除法，除2，因为位运算要比普通除法快，对于非负数用位运算更好
		if (numbers[middle] != middle) //如果middle下标的值与该下标处数组中对应的值不相等，此时需要分两个情况
		{
			if (middle == 0 || numbers[middle - 1] == middle - 1)//并且它前一个元素和它的下标相等，这就说明这个中间数字正好就是第一个值和下标不相等的元素
				return middle;
			right = middle - 1;  //否则说话我们下一轮查找只需要在左半边查找，即right = middle - 1
		}
		else                     //如果middle下标的值与该下标处数组中对应的值相等，说明该数组左半部分不存在缺少，让left = middle + 1;然后开始判断右半部分
			left = middle + 1;
	}

	if (left == length)//如果在上面的循环中的右半边判断完后还没有找到，则说明就是缺少length下标处的length
		return length;

	// 无效的输入，比如数组不是按要求排序的，
	// 或者有数字不在0到n-1范围之内
	return -1;
}

// ====================测试代码====================
void Test(const char* testName, int numbers[], int length, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	int result = GetMissingNumber(numbers, length);
	if (result == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// 缺失的是第一个数字0
void Test1()
{
	int numbers[] = { 1, 2, 3, 4, 5 };
	int expected = 0;
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 缺失的是最后一个数字
void Test2()
{
	int numbers[] = { 0, 1, 2, 3, 4 };
	int expected = 5;
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 缺失的是中间某个数字0
void Test3()
{
	int numbers[] = { 0, 1, 2, 4, 5 };
	int expected = 3;
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 数组中只有一个数字，缺失的是第一个数字0
void Test4()
{
	int numbers[] = { 1 };
	int expected = 0;
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 数组中只有一个数字，缺失的是最后一个数字1
void Test5()
{
	int numbers[] = { 0 };
	int expected = 1;
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 空数组
void Test6()
{
	int expected = -1;
	Test("Test6", nullptr, 0, expected);
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

