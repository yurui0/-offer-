// 16_Power.cpp : 定义控制台应用程序的入口点。
//

// 面试题16：数值的整数次方
// 题目：实现函数double Power(double base, int exponent)，求base的exponent
// 次方。不得使用库函数，同时不需要考虑大数问题。


#include "stdafx.h"
#include <iostream>
#include <cmath>
using namespace std;

bool g_InvalidInput = false; //全局布尔变量，用来标识是否出错，如果出错则返回true，否则返回false
bool equal(double num1, double num2);
double PowerWithUnsignedExponent(double base, unsigned int exponent);

double Power(double base, int exponent)
{
	g_InvalidInput = false;

	if (equal(base, 0.0) && exponent < 0) //此时说明底数是0，且指数小于0，此时是不合法的，所以设置标识并返回0
	{
		g_InvalidInput = true;
		return 0.0;
	}

	unsigned int absExponent = (unsigned int)(exponent);//对指数取绝对值
	if (exponent < 0)
		absExponent = (unsigned int)(-exponent);

	double result = PowerWithUnsignedExponent(base, absExponent);//计算结果的函数，保证传入的指数是正数
	if (exponent < 0) //如果指数原来是负数，则去结果的倒数
		result = 1.0 / result;

	return result;
}

/*
double PowerWithUnsignedExponent(double base, unsigned int exponent)
{
double result = 1.0;

for (int i = 1; i <= exponent; ++i) //计算指数运算得到的结果
result *= base;
return result;
}
*/

// 此函数的思路是  { a^(n/2) * a^(n/2)
//             an={
//                 { a^(n-1)/2 * a^(n-1)/2 * a
double PowerWithUnsignedExponent(double base, unsigned int exponent)
{
	if (exponent == 0)
		return 1;
	if (exponent == 1)
		return base;

	double result = PowerWithUnsignedExponent(base, exponent >> 1);//用右移替换除法
	result *= result; //把结果进行平方
	if ((exponent & 0x1) == 1) //用位与运算替换求余运算%，这里是说如果指数是奇数，则最后还需要乘以原来的数一次
		result *= base;

	return result;
}

bool equal(double num1, double num2) //判断是否相等
{
	if ((num1 - num2 > -0.0000001) && (num1 - num2 < 0.0000001))
		return true;
	else
		return false;
}

// ====================测试代码====================
void Test(const char* testName, double base, int exponent, double expectedResult, bool expectedFlag)
{
	double result = Power(base, exponent);
	if (equal(result, expectedResult) && g_InvalidInput == expectedFlag)
		cout << testName << " passed" << endl;
	else
		cout << testName << " FAILED" << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	// 底数、指数都为正数
	Test("Test1", 2, 3, 8, false);

	// 底数为负数、指数为正数
	Test("Test2", -2, 3, -8, false);

	// 指数为负数
	Test("Test3", 2, -3, 0.125, false);

	// 指数为0
	Test("Test4", 2, 0, 1, false);

	// 底数、指数都为0
	Test("Test5", 0, 0, 1, false);

	// 底数为0、指数为正数
	Test("Test6", 0, 4, 0, false);

	// 底数为0、指数为负数
	Test("Test7", 0, -4, 0, true);

	return 0;
}

