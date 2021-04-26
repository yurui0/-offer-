// 44_DigitsInSequence.cpp : 定义控制台应用程序的入口点。
//

// 面试题44：数字序列中某一位的数字
// 题目：数字以0123456789101112131415…的格式序列化到一个字符序列中。在这
// 个序列中，第5位（从0开始计数）是5，第13位是1，第19位是4，等等。请写一
// 个函数求任意位对应的数字。

#include "stdafx.h"

#include <iostream>
#include <algorithm>

using namespace std;

int countOfIntegers(int digits);
int digitAtIndex(int index, int digits);
int beginNumber(int digits);

int digitAtIndex(int index) //主函数，index表示n位
{
	if (index < 0)//从0开始，因此这里是合法判断
		return -1;

	int digits = 1;
	while (true)
	{
		int numbers = countOfIntegers(digits);//计算当前位下，所对应的数字的个数
		if (index < numbers * digits)//此时说明，要找的n位对应的数字是在当前digits位下，进入另一个函数进行处理
			return digitAtIndex(index, digits);

		index -= digits * numbers;
		digits++;//当前位的情况处理完，位数+1
	}

	return -1;
}

int countOfIntegers(int digits)//返回m位的数字是多少个，比如1位有10个（0-9），2位有90个（10-99），3位有900个（100-999），以此类推
{
	if (digits == 1)
		return 10;

	int count = (int)std::pow(10, digits - 1);//pow(x,y)表示x^y次
	return 9 * count;
}

int digitAtIndex(int index, int digits)
{
	int number = beginNumber(digits) + index / digits;//找到第n位对应的数字是从第一个m位数后面第几个数字
	int indexFromRight = digits - index % digits;// 找到第n位对应的数字是从第一个m位数后面第几个数字中的第几位
	for (int i = 1; i < indexFromRight; ++i)//这一步是通过除以10，找到该位在该数字中的那一个位置
		number /= 10;
	return number % 10;//输出那个数字（数字范围为0-9）
}

int beginNumber(int digits)//求得第一个m位数，比如第一个二位数为10，第一个三位数是100
{
	if (digits == 1)
		return 0;

	return (int)std::pow(10, digits - 1);
}

// ====================测试代码====================
void test(const char* testName, int inputIndex, int expectedOutput)
{
	if (digitAtIndex(inputIndex) == expectedOutput)
		cout << testName << " passed." << endl;
	else
		cout << testName << " FAILED." << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	test("Test1", 0, 0);
	test("Test2", 1, 1);
	test("Test3", 9, 9);
	test("Test4", 10, 1);
	test("Test5", 189, 9);  // 数字99的最后一位，9
	test("Test6", 190, 1);  // 数字100的第一位，1
	test("Test7", 1000, 3); // 数字370的第一位，3
	test("Test8", 1001, 7); // 数字370的第二位，7
	test("Test9", 1002, 0); // 数字370的第三位，0
	return 0;
}

