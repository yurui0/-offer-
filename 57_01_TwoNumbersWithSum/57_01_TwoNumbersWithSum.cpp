// 57_01_TwoNumbersWithSum.cpp : 定义控制台应用程序的入口点。
//

// 面试题57（一）：和为s的两个数字
// 题目：输入一个递增排序的数组和一个数字s，在数组中查找两个数，使得它们
// 的和正好是s。如果有多对数字的和等于s，输出任意一对即可。


#include "stdafx.h"

#include <cstdio>

bool FindNumbersWithSum(int data[], int length, int sum,int* num1, int* num2)// num1与num2分别表示合为s的前后的两个值
{
	bool found = false;//是否找到的标示符
	if (length < 1 || num1 == nullptr || num2 == nullptr)//判断输入是否合法
		return found;

	int ahead = length - 1;//相当于指向数组的最后一个数字的指针，这里用下标代替
	int behind = 0;//相当于指向数组的第一个数字的指针，这里用下标代替（因为可以通过下标获取数组中当前位置的值，无需再定义指针）

	while (ahead > behind)//两个指针还没有相遇。即还没有对数组中数据全部搜索一遍
	{
		long long curSum = data[ahead] + data[behind];//计算前后指针的值之和

		if (curSum == sum)//如果计算的和与s相等，说明找到了，随后将对应值和标签进行赋值并传输
		{
			*num1 = data[behind];
			*num2 = data[ahead];
			found = true;
			break;
		}
		else if (curSum > sum)//如果和大于s，则后面指针前移
			ahead--;
		else
			behind++;       //否则前面指针后移
	}

	return found;
}

// ====================测试代码====================
void Test(const char* testName, int data[], int length, int sum, bool expectedReturn)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	int num1, num2;
	int result = FindNumbersWithSum(data, length, sum, &num1, &num2);
	if (result == expectedReturn)
	{
		if (result)
		{
			if (num1 + num2 == sum)
				printf("Passed. \n");
			else
				printf("FAILED. \n");
		}
		else
			printf("Passed. \n");
	}
	else
		printf("FAILED. \n");
}

// 存在和为s的两个数字，这两个数字位于数组的中间
void Test1()
{
	int data[] = { 1, 2, 4, 7, 11, 15 };
	Test("Test1", data, sizeof(data) / sizeof(int), 15, true);
}

// 存在和为s的两个数字，这两个数字位于数组的两段
void Test2()
{
	int data[] = { 1, 2, 4, 7, 11, 16 };
	Test("Test2", data, sizeof(data) / sizeof(int), 17, true);
}

// 不存在和为s的两个数字
void Test3()
{
	int data[] = { 1, 2, 4, 7, 11, 16 };
	Test("Test3", data, sizeof(data) / sizeof(int), 10, false);
}

// 鲁棒性测试
void Test4()
{
	Test("Test4", nullptr, 0, 0, false);
}


int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();

	return 0;
}

