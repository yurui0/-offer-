// 14_CuttingRope.cpp : 定义控制台应用程序的入口点。
//

// 面试题14：剪绳子
// 题目：给你一根长度为n绳子，请把绳子剪成m段（m、n都是整数，n>1并且m≥1）。
// 每段的绳子的长度记为k[0]、k[1]、……、k[m]。k[0]*k[1]*…*k[m]可能的最大乘
// 积是多少？例如当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此
// 时得到最大的乘积18。

#include <iostream>
#include <cmath>
#include "stdafx.h"

// ====================动态规划====================
int maxProductAfterCutting_solution1(int length)
{
	if (length < 2) //绳子为1，无法剪
		return 0;
	if (length == 2)//绳子为2，只能剪成1和1
		return 1;
	if (length == 3)//绳子为3，可以剪成1和2,1/1/1，前者显然乘积更大
		return 2;

	int* products = new int[length + 1]; //创建绳子长度---裁剪后最大乘积，之间的对应关系
	products[0] = 0;
	products[1] = 1;
	products[2] = 2;
	products[3] = 3;

	int max = 0;
	for (int i = 4; i <= length; ++i)
	{
		max = 0;
		for (int j = 1; j <= i / 2; ++j)       //这里就是从下到上，依次比较f(n)=max(f(i)x f(n-1))，从而最终得到长度n的绳子所对应的最大乘积f(n)
		{
			int product = products[j] * products[i - j];
			if (max < product)
				max = product;

			products[i] = max;
		}
	}

	max = products[length];
	delete[] products;

	return max;
}

// ====================贪婪算法====================
int maxProductAfterCutting_solution2(int length)
{
	if (length < 2)
		return 0;
	if (length == 2)
		return 1;
	if (length == 3)
		return 2;

	// 尽可能多地减去长度为3的绳子段
	int timesOf3 = length / 3;

	// 当绳子最后剩下的长度为4的时候，不能再剪去长度为3的绳子段。
	// 此时更好的方法是把绳子剪成长度为2的两段，因为2*2 > 3*1。
	if (length - timesOf3 * 3 == 1)
		timesOf3 -= 1;

	int timesOf2 = (length - timesOf3 * 3) / 2;

	return (int)(pow(3, timesOf3)) * (int)(pow(2, timesOf2));
}

// ====================测试代码====================
void test(const char* testName, int length, int expected)
{
	int result1 = maxProductAfterCutting_solution1(length);
	if (result1 == expected)
		std::cout << "Solution1 for " << testName << " passed." << std::endl;
	else
		std::cout << "Solution1 for " << testName << " FAILED." << std::endl;

	int result2 = maxProductAfterCutting_solution2(length);
	if (result2 == expected)
		std::cout << "Solution2 for " << testName << " passed." << std::endl;
	else
		std::cout << "Solution2 for " << testName << " FAILED." << std::endl;
}

void test1()
{
	int length = 1;
	int expected = 0;
	test("test1", length, expected);
}

void test2()
{
	int length = 2;
	int expected = 1;
	test("test2", length, expected);
}

void test3()
{
	int length = 3;
	int expected = 2;
	test("test3", length, expected);
}

void test4()
{
	int length = 4;
	int expected = 4;
	test("test4", length, expected);
}

void test5()
{
	int length = 5;
	int expected = 6;
	test("test5", length, expected);
}

void test6()
{
	int length = 6;
	int expected = 9;
	test("test6", length, expected);
}

void test7()
{
	int length = 7;
	int expected = 12;
	test("test7", length, expected);
}

void test8()
{
	int length = 8;
	int expected = 18;
	test("test8", length, expected);
}

void test9()
{
	int length = 9;
	int expected = 27;
	test("test9", length, expected);
}

void test10()
{
	int length = 10;
	int expected = 36;
	test("test10", length, expected);
}

void test11()
{
	int length = 50;
	int expected = 86093442;
	test("test11", length, expected);
}



int _tmain(int argc, _TCHAR* argv[])
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();
	test11();

	return 0;
}

