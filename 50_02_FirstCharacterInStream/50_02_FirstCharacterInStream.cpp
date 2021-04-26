// 50_02_FirstCharacterInStream.cpp : 定义控制台应用程序的入口点。
//


// 面试题50（二）：字符流中第一个只出现一次的字符
// 题目：请实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从
// 字符流中只读出前两个字符"go"时，第一个只出现一次的字符是'g'。当从该字
// 符流中读出前六个字符"google"时，第一个只出现一次的字符是'l'。

#include "stdafx.h"

#include <cstdio>
#include <vector>
#include <limits>

using namespace std;

class CharStatistics
{
public:
	CharStatistics() : index(0)
	{
		for (int i = 0; i < 256; ++i)//
			occurrence[i] = -1;
	}

	void Insert(char ch)//这里其实做了一个隐式类型转换，因为数组的下标必须为int，因此这里对char做了类似这样的操作:int test1 = int('a');如果下标为负数也可以，但是没有意义
							// 因为数组a[i]即*(a+i),a为一个地址，如果i小于0，理论上可以，但是不知道a+i后的地址是否存在且有意义，一般会报错或不准确。因此需要保证为正
	{
		if (occurrence[ch] == -1) 
			occurrence[ch] = index;
		else if (occurrence[ch] >= 0)
			occurrence[ch] = -2;

		index++;//这里是为了跟其他的字符对应的值进行区分，有没有都可以，因为>=0都是说明仅出现一次
	}

	char FirstAppearingOnce()
	{
		char ch = '\0';
		int minIndex = numeric_limits<int>::max();//这里是取的int的最大值，其中numeric_limits<T>是编译器允许的T类型值的极限
		for (int i = 0; i < 256; ++i)
		{
			if (occurrence[i] >= 0 && occurrence[i] < minIndex)
			{
				ch = (char)i;
				minIndex = occurrence[i];
			}
		}

		return ch;
	}

private:
	// occurrence[i]: A character with ASCII value i;
	// occurrence[i] = -1: The character has not found;
	// occurrence[i] = -2: The character has been found for mutlple times
	// occurrence[i] >= 0: The character has been found only once
	int occurrence[256];//一个hash表，数组的元素occurrence[i]与ASCLL码的值为i的字符对应
	int index;
};

// ====================测试代码====================
void Test(const char* testName, CharStatistics chars, char expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (chars.FirstAppearingOnce() == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}


int _tmain(int argc, _TCHAR* argv[])
{
	CharStatistics chars;

	Test("Test1", chars, '\0');

	chars.Insert('g');
	Test("Test2", chars, 'g');

	chars.Insert('o');
	Test("Test3", chars, 'g');

	chars.Insert('o');
	Test("Test4", chars, 'g');

	chars.Insert('g');
	Test("Test5", chars, '\0');

	chars.Insert('l');
	Test("Test6", chars, 'l');

	chars.Insert('e');
	Test("Test7", chars, 'l');



	return 0;
}

