// 40_KLeastNumbers.cpp : 定义控制台应用程序的入口点。
//
// 面试题40：最小的k个数
// 题目：输入n个整数，找出其中最小的k个数。例如输入4、5、1、6、2、7、3、8
// 这8个数字，则最小的4个数字是1、2、3、4。

#include "stdafx.h"

#include <cstdio>
#include "Array.h"

#include <set>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

// ====================方法1====================
//这个方法的前提是：只有当我们可以修改输入的数组时可用，也是运用partition函数来解决。
// 运用partition函数将数组进行排序，然后根据排序的index与k比较，不断修改直到index==k-1，即排序完成，最后输出前k个数据即可（最终得到的最小的k个数字不一定是从小到大排序的）
void GetLeastNumbers_Solution1(int* input, int n, int* output, int k)
{
	if (input == nullptr || output == nullptr || k > n || n <= 0 || k <= 0)
		return;

	int start = 0;
	int end = n - 1;
	int index = Partition(input, n, start, end);//随机选一个数据进行排序，然后将index与k进行比较
	while (index != k - 1)
	{
		if (index > k - 1)//说明前面的数多于K个,因此要再对index前面的数据进行排序，从而只需要得到前k个数据（因为此时前面index个数中前k个不能说明是排好序的）
		{
			end = index - 1;
			index = Partition(input, n, start, end);
		}
		else //说明前index个数已经排好了，但是index<k，因此还要再对index后面的数据进行排序，从而得到前k个数据
		{
			start = index + 1;
			index = Partition(input, n, start, end);
		}
	}

	for (int i = 0; i < k; ++i)
		output[i] = input[i];
}

// ====================方法2====================
// 适合处理海量数据 时间复杂度O（nlogk）
// 这里运用STL中的multiset(因为可能重复)，其中set与multiset是基于红黑树实现的，因此其时间复杂度是O（logk）
typedef multiset<int, std::greater<int> >            intSet;
typedef multiset<int, std::greater<int> >::iterator  setIterator;

//优点：没有修改输入的数据data
//优点2：适合海量数据的输入---因为内存有限，有时候无法把数据一次性传入内存，此时，我们可以从辅助存储空间每次读一个数字，然后重写GetLeastNumbers_Solution2函数
//（即将第一个参数变为数据输入流I/O之类），判断是否需要放入容器leastNumbers中即可，这种思路只需要leastNumbers 能在内存中即可

void GetLeastNumbers_Solution2(const vector<int>& data, intSet& leastNumbers, int k)
{
	leastNumbers.clear();//所有的写操作都包含在leastNumbers容器中

	if (k < 1 || data.size() < k)//判断是否合法
		return;

	vector<int>::const_iterator iter = data.begin();//迭代器访问
	for (; iter != data.end(); ++iter)
	{
		if ((leastNumbers.size()) < k)//先往leastNumbers中传入k个数据
			leastNumbers.insert(*iter);

		else
		{
			setIterator iterGreatest = leastNumbers.begin();

			if (*iter < *(leastNumbers.begin()))//开始比较，如果小于multiset中数据最小的，则将其删除，加入更小的
			{                                   //注意： 这里不对数据进行排序的原因是，set和multiset是运用红黑树默认升序“生序排序的--从小到大”，因此只需要比较begin即可
				leastNumbers.erase(iterGreatest);
				leastNumbers.insert(*iter);
			}
		}
	}
}

// ====================测试代码====================
void Test(char* testName, int* data, int n, int* expectedResult, int k)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	vector<int> vectorData;
	for (int i = 0; i < n; ++i)
		vectorData.push_back(data[i]);

	if (expectedResult == nullptr)
		printf("The input is invalid, we don't expect any result.\n");
	else
	{
		printf("Expected result: \n");
		for (int i = 0; i < k; ++i)
			printf("%d\t", expectedResult[i]);
		printf("\n");
	}

	printf("Result for solution1:\n");
	int* output = new int[k];
	GetLeastNumbers_Solution1(data, n, output, k);
	if (expectedResult != nullptr)
	{
		for (int i = 0; i < k; ++i)
			printf("%d\t", output[i]);
		printf("\n");
	}

	delete[] output;

	printf("Result for solution2:\n");
	intSet leastNumbers;
	GetLeastNumbers_Solution2(vectorData, leastNumbers, k);
	printf("The actual output numbers are:\n");
	for (setIterator iter = leastNumbers.begin(); iter != leastNumbers.end(); ++iter)
		printf("%d\t", *iter);
	printf("\n\n");
}

// k小于数组的长度
void Test1()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int expected[] = { 1, 2, 3, 4 };
	Test("Test1", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k等于数组的长度
void Test2()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int expected[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	Test("Test2", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k大于数组的长度
void Test3()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int* expected = nullptr;
	Test("Test3", data, sizeof(data) / sizeof(int), expected, 10);
}

// k等于1
void Test4()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int expected[] = { 1 };
	Test("Test4", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k等于0
void Test5()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int* expected = nullptr;
	Test("Test5", data, sizeof(data) / sizeof(int), expected, 0);
}

// 数组中有相同的数字
void Test6()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 2, 8 };
	int expected[] = { 1, 2 };
	Test("Test6", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// 输入空指针
void Test7()
{
	int* expected = nullptr;
	Test("Test7", nullptr, 0, expected, 0);
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

	return 0;
}

