// 59_01_MaxInSlidingWindow.cpp : 定义控制台应用程序的入口点。
//

// 面试题59（一）：滑动窗口的最大值
// 题目：给定一个数组和滑动窗口的大小，请找出所有滑动窗口里的最大值。例如，
// 如果输入数组{2, 3, 4, 2, 6, 2, 5, 1}及滑动窗口的大小3，那么一共存在6个
// 滑动窗口，它们的最大值分别为{4, 4, 6, 6, 6, 5}，

#include "stdafx.h"

#include <cstdio>
#include <vector>
#include <deque>

using namespace std;

vector<int> maxInWindows(const vector<int>& num, unsigned int size)
{
	vector<int> maxInWindows; //存放数组中所有不同滑动窗口下的最大值

	if (num.size() >= size && size >= 1)//输入是否合法，size表示滑动窗口的大小
	{
		deque<int> index;//双端开口的队列，用于保存有可能是滑动窗口最大值的数字的下标，其队首永远是滑动窗口的最大值

		for (unsigned int i = 0; i < size; ++i)//这个是构建初始的滑动窗口（即从数组0-size-1的滑动窗口），以及对应的队列下标队列
		{
			while (!index.empty() && num[i] >= num[index.back()])//如果下标队列不为空，且下标队列中存在数字小于待存入的数字，将他们依次从队尾删除(因其不可能是滑动窗口最大值)
				index.pop_back();//将队列中队首的下标移除一个

			index.push_back(i);//将下标加入队列末端
		}

		for (unsigned int i = size; i < num.size(); ++i)//开始移动滑带窗口直到数组末端
		{
			maxInWindows.push_back(num[index.front()]);//向maxInWindows中存入当前滑动窗口最大值

			while (!index.empty() && num[i] >= num[index.back()])//如果下标队列不为空，且下标队列中存在数字小于待存入的数字，将他们依次从队尾删除(因其不可能是滑动窗口最大值)
				index.pop_back();
			if (!index.empty() && index.front() <= (int)(i - size))//如果下标队列不为空，且队首元素对应的下标超过滑动窗口的范围，则应该将其移除
				index.pop_front();

			index.push_back(i);
		}
		maxInWindows.push_back(num[index.front()]);//最后一次循环执行完后跳出，此时最后一个窗口还需要处理，front是获取deque中队首元素
	}

	return maxInWindows;
}

// ====================测试代码====================
void Test(const char* testName, const vector<int>& num, unsigned int size, const vector<int>& expected) //参数依次是：原数组、滑动窗口大小、滑动窗口最大值数组
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	vector<int> result = maxInWindows(num, size);

	vector<int>::const_iterator iterResult = result.begin();
	vector<int>::const_iterator iterExpected = expected.begin();
	while (iterResult < result.end() && iterExpected < expected.end())
	{
		if (*iterResult != *iterExpected)
			break;

		++iterResult;
		++iterExpected;
	}

	if (iterResult == result.end() && iterExpected == expected.end())
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

void Test1()
{
	int num[] = { 2, 3, 4, 2, 6, 2, 5, 1 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int)); //通过数组地址初始化,例如这种int a[5] = {1,2,3,4,5};
																	//通过数组a的地址初始化，注意地址是从0到5（左闭右开区间）vector<int> b(a, a + 5);

	int expected[] = { 4, 4, 6, 6, 6, 5 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 3;

	Test("Test1", vecNumbers, size, vecExpected);
}

void Test2()
{
	int num[] = { 1, 3, -1, -3, 5, 3, 6, 7 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 3, 3, 5, 5, 6, 7 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 3;

	Test("Test2", vecNumbers, size, vecExpected);
}

// 输入数组单调递增
void Test3()
{
	int num[] = { 1, 3, 5, 7, 9, 11, 13, 15 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 7, 9, 11, 13, 15 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 4;

	Test("Test3", vecNumbers, size, vecExpected);
}

// 输入数组单调递减
void Test4()
{
	int num[] = { 16, 14, 12, 10, 8, 6, 4 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 16, 14, 12 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 5;

	Test("Test4", vecNumbers, size, vecExpected);
}

// 滑动窗口的大小为1
void Test5()
{
	int num[] = { 10, 14, 12, 11 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 10, 14, 12, 11 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 1;

	Test("Test5", vecNumbers, size, vecExpected);
}

// 滑动窗口的大小等于数组的长度
void Test6()
{
	int num[] = { 10, 14, 12, 11 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = { 14 };
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 4;

	Test("Test6", vecNumbers, size, vecExpected);
}

// 滑动窗口的大小为0
void Test7()
{
	int num[] = { 10, 14, 12, 11 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	vector<int> vecExpected;

	unsigned int size = 0;

	Test("Test7", vecNumbers, size, vecExpected);
}

// 滑动窗口的大小大于输入数组的长度
void Test8()
{
	int num[] = { 10, 14, 12, 11 };
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	vector<int> vecExpected;

	unsigned int size = 5;

	Test("Test8", vecNumbers, size, vecExpected);
}

// 输入数组为空
void Test9()
{
	vector<int> vecNumbers;
	vector<int> vecExpected;

	unsigned int size = 5;

	Test("Test9", vecNumbers, size, vecExpected);
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

