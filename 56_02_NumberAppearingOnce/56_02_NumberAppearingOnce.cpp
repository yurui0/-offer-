// 56_02_NumberAppearingOnce.cpp : 定义控制台应用程序的入口点。
//

// 面试题56（二）：数组中唯一只出现一次的数字
// 题目：在一个数组中除了一个数字只出现一次之外，其他数字都出现了三次。请
// 找出那个吃出现一次的数字。

#include "stdafx.h"

#include <cstdio>
#include <exception>

int FindNumberAppearingOnce(int numbers[], int length) //这里的思路是，每个数字出现了三次，那么该数字的二进制表示中相同位的数字（0或1）的和（0或3）都能被3整除
{                                                     //既然如此，当把数组中所有数字的二进制表示的每一位加起来（包括出现三次的数字+唯一出现一次的数字），得到总和的二进制
														// 由于三次出现的数字的二进制每一位都可以被3整除，因此 最终包含唯一出现一次的数字的二进制中，对每一位除以3
														// 如果能被整除，则唯一出现一次的那一位数字该二进制位为0，否则为1（因为二进制只能为0或1）
	if (numbers == nullptr || length <= 0) //判断输入是否合法
		throw new std::exception("Invalid input.");

	int bitSum[32] = { 0 }; //长度为32位（int型4个字节，4x8=32）的辅助数组存储二进制表示的每一位的和
	for (int i = 0; i < length; ++i) //这里是将number数组中每一个数字都转为32位二进制后，计算
	{
		int bitMask = 1; //
		for (int j = 31; j >= 0; --j)
		{
			int bit = numbers[i] & bitMask; //两个int进行&运算，即两个整数都转换为二进制表示，然后进行&运算：对应位的两个值同时为1，结果为1，否则为0
			if (bit != 0) //如果该二进制位 与1进行&运算后结果不为1，说明number[i]展开为二进制后，该位为1，所以在bitSum[j]处+1,（该位为0无需处理）
				bitSum[j] += 1;

			bitMask = bitMask << 1;//这里是将bitMask进行乘2的计算，即让其与number[i]转换成的32位二进制依次进行&运算
		}
	}

	int result = 0;
	for (int i = 0; i < 32; ++i)
	{
		result = result << 1; //这里就是根据i位处对应的值，然后通过<<（乘以2）计算其对应到10进制下的结果
		result += bitSum[i] % 3;// 对32位中每一位进行处理，对其进行除3，得到的余数就
	}

	return result;
}

// ====================测试代码====================
void Test(const char* testName, int numbers[], int length, int expected)
{
	int result = FindNumberAppearingOnce(numbers, length);
	if (result == expected)
		printf("%s passed.\n", testName);
	else
		printf("%s FAILED.\n", testName);
}

// 所有数字都是正数，唯一的数字是最小的
void Test1()
{
	int numbers[] = { 1, 1, 2, 2, 2, 1, 3 };
	int expected = 3;
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 所有数字都是正数，唯一的数字的大小位于中间
void Test2()
{
	int numbers[] = { 4, 3, 3, 2, 2, 2, 3 };
	int expected = 4;
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 所有数字都是正数，唯一的数字是最大的
void Test3()
{
	int numbers[] = { 4, 4, 1, 1, 1, 7, 4 };
	int expected = 7;
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 唯一的数字是负数
void Test4()
{
	int numbers[] = { -10, 214, 214, 214 };
	int expected = -10;
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 除了唯一的数字，其他数字都是负数
void Test5()
{
	int numbers[] = { -209, 3467, -209, -209 };
	int expected = 3467;
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 重复的数字有正数也有负数
void Test6()
{
	int numbers[] = { 1024, -1025, 1024, -1025, 1024, -1025, 1023 };
	int expected = 1023;
	Test("Test6", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 所有数字都是负数
void Test7()
{
	int numbers[] = { -1024, -1024, -1024, -1023 };
	int expected = -1023;
	Test("Test7", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 唯一的数字是0
void Test8()
{
	int numbers[] = { -23, 0, 214, -23, 214, -23, 214 };
	int expected = 0;
	Test("Test8", numbers, sizeof(numbers) / sizeof(int), expected);
}

// 除了唯一的数字，其他数字都是0
void Test9()
{
	int numbers[] = { 0, 3467, 0, 0, 0, 0, 0, 0 };
	int expected = 3467;
	Test("Test9", numbers, sizeof(numbers) / sizeof(int), expected);
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

