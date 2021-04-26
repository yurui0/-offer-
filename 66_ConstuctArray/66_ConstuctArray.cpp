// 66_ConstuctArray.cpp : 定义控制台应用程序的入口点。
//

// 面试题66：构建乘积数组
// 题目：给定一个数组A[0, 1, …, n-1]，请构建一个数组B[0, 1, …, n-1]，其
// 中B中的元素B[i] =A[0]×A[1]×… ×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。

#include "stdafx.h"

#include <cstdio>
#include <vector>

using namespace std;

void BuildProductionArray(const vector<double>& input, vector<double>& output)//input对应A[]，output对应B[]
{
	int length1 = input.size();
	int length2 = output.size();

	if (length1 == length2 && length2 > 1)//题目要求A与B的长度应该相同，且数组长度要大于1
	{
		output[0] = 1;//长度为1的时候，其初始值为1（A[0]/A[0]）
		//我们将数组B[0,1,..,n-1]看成一个n行矩阵，其对角线元素为1，B[i]为矩阵第i行的乘积，将第i行的乘积看成两部分，也就是下面两个for循环
		// 前半部分是[0,i-1],后半部分是[i+1,n-1]
		for (int i = 1; i < length1; ++i)
		{
			output[i] = output[i - 1] * input[i - 1];
		}

		double temp = 1;
		for (int i = length1 - 2; i >= 0; --i)
		{
			temp *= input[i + 1];
			output[i] *= temp;
		}
	}
}

//================= Test Code =================
static bool EqualArrays(const vector<double>& input, const vector<double>& output) //这个是测试input与output之间是否每一项都相等
{
	int length1 = input.size();
	int length2 = output.size();

	if (length1 != length2)
		return false;

	for (int i = 0; i < length1; ++i)
	{
		if (abs(input[i] - output[i]) > 0.0000001)
			return false;
	}

	return true;
}

static void test(char* testName, const vector<double>& input, vector<double>& output, const vector<double>& expected)
{
	printf("%s Begins: ", testName);

	BuildProductionArray(input, output);
	if (EqualArrays(output, expected))
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

static void test1()
{
	// 输入数组中没有0
	double input[] = { 1, 2, 3, 4, 5 };
	double output[] = { 0, 0, 0, 0, 0 };
	double expected[] = { 120, 60, 40, 30, 24 };

	test("Test1", vector<double>(input, input + sizeof(input) / sizeof(double)),
		vector<double>(output, output + sizeof(output) / sizeof(double)),
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test2()
{
	// 输入数组中有一个0
	double input[] = { 1, 2, 0, 4, 5 };
	double output[] = { 0, 0, 0, 0, 0 };
	double expected[] = { 0, 0, 40, 0, 0 };

	test("Test2", vector<double>(input, input + sizeof(input) / sizeof(double)),
		vector<double>(output, output + sizeof(output) / sizeof(double)),
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test3()
{
	// 输入数组中有两个0
	double input[] = { 1, 2, 0, 4, 0 };
	double output[] = { 0, 0, 0, 0, 0 };
	double expected[] = { 0, 0, 0, 0, 0 };

	test("Test3", vector<double>(input, input + sizeof(input) / sizeof(double)),
		vector<double>(output, output + sizeof(output) / sizeof(double)),
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test4()
{
	// 输入数组中有正、负数
	double input[] = { 1, -2, 3, -4, 5 };
	double output[] = { 0, 0, 0, 0, 0 };
	double expected[] = { 120, -60, 40, -30, 24 };

	test("Test4", vector<double>(input, input + sizeof(input) / sizeof(double)),
		vector<double>(output, output + sizeof(output) / sizeof(double)),
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test5()
{
	// 输入输入中只有两个数字
	double input[] = { 1, -2 };
	double output[] = { 0, 0 };
	double expected[] = { -2, 1 };

	test("Test5", vector<double>(input, input + sizeof(input) / sizeof(double)),
		vector<double>(output, output + sizeof(output) / sizeof(double)),
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

int _tmain(int argc, _TCHAR* argv[])
{
	test1();
	test2();
	test3();
	test4();
	test5();

	return 0;
}

