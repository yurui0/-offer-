// 46_TranslateNumbersToStrings.cpp : 定义控制台应用程序的入口点。
//

// 面试题46：把数字翻译成字符串
// 题目：给定一个数字，我们按照如下规则把它翻译为字符串：0翻译成"a"，1翻
// 译成"b"，……，11翻译成"l"，……，25翻译成"z"。一个数字可能有多个翻译。例
// 如12258有5种不同的翻译，它们分别是"bccfi"、"bwfi"、"bczi"、"mcfi"和
// "mzi"。请编程实现一个函数用来计算一个数字有多少种不同的翻译方法。

#include "stdafx.h"

#include <string>
#include <iostream>

using namespace std;

int GetTranslationCount(const string& number);

int GetTranslationCount(int number)//这里是读取数字，因为没有规定输入的数据的大小，很可能超过int的范围，所以将其转为字符串string
{
	if (number < 0)
		return 0;

	string numberInString = to_string(number);
	return GetTranslationCount(numberInString);
}

int GetTranslationCount(const string& number)//对转换为字符串的数字进行处理
{
	int length = number.length();//获得数字的长度
	int* counts = new int[length]; //这个用来统计第i位数字开始的不同翻译的数目                                            
	int count = 0;//作为中间变量存储信息，同时也作为最后结果的输出

	for (int i = length - 1; i >= 0; --i)//思路是递归，但是实现是从循环开始实现
	{
		count = 0;//每次清零
		if (i < length - 1)
			count = counts[i + 1];//获取前一次的结果
		else
			count = 1;

		if (i < length - 1)//从后往前第二位开始计算是否存在0-25之间的数字
		{
			int digit1 = number[i] - '0';
			int digit2 = number[i + 1] - '0';
			int converted = digit1 * 10 + digit2;
			if (converted >= 10 && converted <= 25)//满足的话就需要累加
			{
				if (i < length - 2) //当前i如果是从从后往前第三个数字的位置，那么就需要累加之前i+2处的结果
					count += counts[i + 2];
				else//如果是倒数第1或2个数字，则只需要加1，因为从后往前算，只有一种可能
					count += 1;
			}
		}

		counts[i] = count;
	}

	count = counts[0];
	delete[] counts;

	return count;
}

// ====================测试代码====================
void Test(const string& testName, int number, int expected)
{
	if (GetTranslationCount(number) == expected)
		cout << testName << " passed." << endl;
	else
		cout << testName << " FAILED." << endl;
}

void Test1()
{
	int number = 0;
	int expected = 1;
	Test("Test1", number, expected);
}

void Test2()
{
	int number = 10;
	int expected = 2;
	Test("Test2", number, expected);
}

void Test3()
{
	int number = 125;
	int expected = 3;
	Test("Test3", number, expected);
}

void Test4()
{
	int number = 126;
	int expected = 2;
	Test("Test4", number, expected);
}

void Test5()
{
	int number = 426;
	int expected = 1;
	Test("Test5", number, expected);
}

void Test6()
{
	int number = 100;
	int expected = 2;
	Test("Test6", number, expected);
}

void Test7()
{
	int number = 101;
	int expected = 2;
	Test("Test7", number, expected);
}

void Test8()
{
	int number = 12258;
	int expected = 5;
	Test("Test8", number, expected);
}

void Test9()
{
	int number = -100;
	int expected = 0;
	Test("Test9", number, expected);
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

	return 0;
}

