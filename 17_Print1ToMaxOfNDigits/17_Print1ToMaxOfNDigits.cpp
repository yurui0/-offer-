// 17_Print1ToMaxOfNDigits.cpp : 定义控制台应用程序的入口点。
//

// 面试题17：打印1到最大的n位数
// 题目：输入数字n，按顺序打印出从1最大的n位十进制数。比如输入3，则
// 打印出1、2、3一直到最大的3位数即999。
//注：有大数问题，因此考虑用字符串

//后续多看几遍

#include "stdafx.h"
#include <cstdio>
#include <memory>

void PrintNumber(char* number);
bool Increment(char* number);
void Print1ToMaxOfNDigitsRecursively(char* number, int length, int index);

// ====================方法一====================
void Print1ToMaxOfNDigits_1(int n) //总的方法，在其中调用Increment实现字符串+1,PrintNumber实现打印数字
{
	if (n <= 0)
		return;

	char *number = new char[n + 1];
	memset(number, '0', n);
	number[n] = '\0';

	while (!Increment(number))
	{
		PrintNumber(number);
	}

	delete[]number;
}

// 字符串number表示一个数字，在 number上增加1
// 如果做加法溢出，则返回true；否则为false
bool Increment(char* number)
{
	bool isOverflow = false; //标识，用来反映加法是否 溢出
	int nTakeOver = 0;
	int nLength = strlen(number);//记录字符串的长度，作用是表示对应大数的位数

	for (int i = nLength - 1; i >= 0; i--)
	{
		int nSum = number[i] - '0' + nTakeOver;
		if (i == nLength - 1)
			nSum++;

		if (nSum >= 10)
		{
			if (i == 0)
				isOverflow = true;
			else
			{
				nSum -= 10;
				nTakeOver = 1; //这个是进位运算的原因，每次到新的一位，其起始值为1，之前初始化为0，是因为字符串中最大位（数据中最小位可以为0），
								// 但是其他位数是进位得到的，不能为0,必须从1开始
				number[i] = '0' + nSum;
			}
		}
		else
		{
			number[i] = '0' + nSum;
			break; //表示退出当前循环，因此在这个条件下，for循环只执行一次
		}
	}

	return isOverflow;
}

// ====================方法二====================
void Print1ToMaxOfNDigits_2(int n)  //这个函数的意义是：从数最大的位开始（对应字符串中最小的数），起始值为0-9
{
	if (n <= 0)
		return;

	char* number = new char[n + 1]; //字符串最后一位是\0，所以特意多申请一位
	number[n] = '\0';

	for (int i = 0; i < 10; ++i)
	{
		number[0] = i + '0';
		Print1ToMaxOfNDigitsRecursively(number, n, 0); //最高位数字从0-9，一共循环十次，该函数就是计算当前最高位值下所有可能数据
	}

	delete[] number;
}

void Print1ToMaxOfNDigitsRecursively(char* number, int length, int index) //计算最高位确定的情况下的所有数字
{
	if (index == length - 1)//当前最高位下所有位的数字都计算完了，因此打印
	{
		PrintNumber(number);
		return;
	}

	for (int i = 0; i < 10; ++i)
	{
		number[index + 1] = i + '0';
		Print1ToMaxOfNDigitsRecursively(number, length, index + 1);//递归下一位，结束条件是已经设置了数字的最后一位
	}
}

// ====================公共函数====================
// 字符串number表示一个数字，数字有若干个0开头
// 打印出这个数字，并忽略开头的0
void PrintNumber(char* number)
{
	bool isBeginning0 = true;
	int nLength = strlen(number);

	for (int i = 0; i < nLength; ++i)
	{
		if (isBeginning0 && number[i] != '0')
			isBeginning0 = false;

		if (!isBeginning0)
		{
			printf("%c", number[i]);
		}
	}

	printf("\t");
}

// ====================测试代码====================
void Test(int n)
{
	printf("Test for %d begins:\n", n);

	Print1ToMaxOfNDigits_1(n);
	Print1ToMaxOfNDigits_2(n);

	printf("\nTest for %d ends.\n", n);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test(1);
	Test(2);
	Test(3);
	Test(0);
	Test(-1);
	return 0;
}

