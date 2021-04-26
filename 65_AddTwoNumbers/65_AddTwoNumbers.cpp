// 65_AddTwoNumbers.cpp : 定义控制台应用程序的入口点。
//

// 面试题65：不用加减乘除做加法
// 题目：写一个函数，求两个整数之和，要求在函数体内不得使用＋、－、×、÷
// 四则运算符号。

#include "stdafx.h"

#include <cstdio>

//不让用常规加减乘除，则能进行数字之间运算的方法就是"位运算"，即将其转为二进制之后在进行计算
// 和普通加法一样一共有三个步骤：前提是将两个相加的数字，先看成是两个二进制的数
// 1、两个二进制数对应位相加但是不进位，0加0、1加1的结果为0，0加1、1加0的结果为1，这与两数字的“二进制异或”运算是一致的，因此可以用异或实现这一步
// 2、考虑进位，对于0加0、0加1、1加0都不会产生进位，只有1加1会进位，这个和位与运算&是一致的，因此(num1 & num2)是找出1加1对应的位，后面<< 1表示将其向前移动一步
// 3、把前两个步骤的结果相加，直到第二步没有产生进位为止
int Add(int num1, int num2)
{
	int sum, carry;
	do
	{
		sum = num1 ^ num2;//对应的第一步,^在c++中是位运算符“异或”
		carry = (num1 & num2) << 1;//对应第二步，通过二进制的“与”运算计算进位

		num1 = sum;
		num2 = carry;
	} while (num2 != 0);//对应第三步，将两个步骤的结果相加

	return num1;
}

// ====================测试代码====================
void Test(int num1, int num2, int expected)
{
	int result = Add(num1, num2);
	if (result == expected)
		printf("%d + %d is %d. Passed\n", num1, num2, result);
	else
		printf("%d + %d is %d. FAILED\n", num1, num2, result);
}


int _tmain(int argc, _TCHAR* argv[])
{
	Test(1, 2, 3);
	Test(111, 899, 1010);

	Test(-1, 2, 1);
	Test(1, -2, -1);

	Test(3, 0, 3);
	Test(0, -4, -4);

	Test(-2, -8, -10);

	return 0;
}

