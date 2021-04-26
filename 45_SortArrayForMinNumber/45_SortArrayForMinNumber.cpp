// 45_SortArrayForMinNumber.cpp : 定义控制台应用程序的入口点。
//

// 面试题45：把数组排成最小的数
// 题目：输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼
// 接出的所有数字中最小的一个。例如输入数组{3, 32, 321}，则打印出这3个数
// 字能排成的最小数字321323。

#include "stdafx.h"

#include "cstdio"
#include <string>
#include <algorithm>

int compare(const void* strNumber1, const void* strNumber2);


const int g_MaxNumberLength = 10;//这里赋值为10的原因是：正整数int（在32和64位中）最大值为2147483647，其为10位数字

//这里用char动态数组的原因是：
char* g_StrCombine1 = new char[g_MaxNumberLength * 2 + 1];//这里记录合并后的mn的长度，最后需要多一位作为保护--给字符串末尾留一位
char* g_StrCombine2 = new char[g_MaxNumberLength * 2 + 1];//这里记录合并后的nm的长度，最后需要多一位作为保护--给字符串末尾留一位

void PrintMinNumber(const int* numbers, int length)//打印拼接出的最小的数字
{
	if (numbers == nullptr || length <= 0)//输入是否合法
		return;

	char** strNumbers = (char**)(new int[length]);// strNumbers是二维char数组，其中每个strNumbers[i]表示
	for (int i = 0; i < length; ++i)
	{
		strNumbers[i] = new char[g_MaxNumberLength + 1];//在二维数组中新创建一位数组，用来存放数组中每个数字
		sprintf(strNumbers[i], "%d", numbers[i]);//将numbers[i]写入strNumbers[i]
	}

	qsort(strNumbers, length, sizeof(char*), compare);//qsort是c语言自带排序函数，参数依次是：待排序数组的指针，待排序数组长度，数组中每个元素大小，回调函数（指定比较方法）

	for (int i = 0; i < length; ++i)
		printf("%s", strNumbers[i]);
	printf("\n");

	for (int i = 0; i < length; ++i)
		delete[] strNumbers[i];
	delete[] strNumbers;
}

// 如果[strNumber1][strNumber2] > [strNumber2][strNumber1], 返回值大于0
// 如果[strNumber1][strNumber2] = [strNumber2][strNumber1], 返回值等于0
// 如果[strNumber1][strNumber2] < [strNumber2][strNumber1], 返回值小于0
int compare(const void* strNumber1, const void* strNumber2)
{
	// [strNumber1][strNumber2]
	strcpy(g_StrCombine1, *(const char**)strNumber1);//strcpy是用来进行复制的
	strcat(g_StrCombine1, *(const char**)strNumber2);//strcat是用来进行字符串连接的

	// [strNumber2][strNumber1]
	strcpy(g_StrCombine2, *(const char**)strNumber2);
	strcat(g_StrCombine2, *(const char**)strNumber1);

	return strcmp(g_StrCombine1, g_StrCombine2);//strcmp用于比较两个字符串并根据比较结果返回整数
}

// ====================测试代码====================
void Test(const char* testName, int* numbers, int length, const char* expectedResult)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	if (expectedResult != nullptr)
		printf("Expected result is: \t%s\n", expectedResult);

	printf("Actual result is: \t");
	PrintMinNumber(numbers, length);

	printf("\n");
}

void Test1()
{
	int numbers[] = { 3, 5, 1, 4, 2 };
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), "12345");
}

void Test2()
{
	int numbers[] = { 3, 32, 321 };
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), "321323");
}

void Test3()
{
	int numbers[] = { 3, 323, 32123 };
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), "321233233");
}

void Test4()
{
	int numbers[] = { 1, 11, 111 };
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), "111111");
}

// 数组中只有一个数字
void Test5()
{
	int numbers[] = { 321 };
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), "321");
}

void Test6()
{
	Test("Test6", nullptr, 0, "Don't print anything.");
}


int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	/* 这里会报错，因为b末尾还一个'/0',所以应该是a[5]
		char a[4], b[] = "COPY";
	//定义字符数组a,b
	strcpy(a, b);
	//将b中的COPY复制到a中
	*/


	return 0;
}

