// 41_StreamMedian.cpp : 定义控制台应用程序的入口点。
//
// 面试题41：数据流中的中位数
// 题目：如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么
// 中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，
// 那么中位数就是所有数值排序之后中间两个数的平均值。

#include "stdafx.h"

#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

//两个函数的头文件是<functional> 建堆的时候，默认是大根堆，第三个参数用greater<T>会变成小根堆；
//排序的时候，默认是从小到大，但是第三个参数用greater<T>会变成从大到小
//另外说一句，make_heap等heap操作函数在头文件<algorithm>里

template<typename T> 
class DynamicArray
{
public:
	void Insert(T num) //插入数据流中的新数据
	{
		//注意假如排序的话，数据流左边是对应的最大堆，最后取最大堆中最大值；数据流右边是对应的最小堆，取最小堆的最小值

		if (((min.size() + max.size()) & 1) == 0)//如果当前已经插入的数据中总数目是偶数，则将新数据插入最小堆
		{
			//如果新数据比最大堆中某些数据小（即比最大堆的最大值小），则需要额外操作：

			if (max.size() > 0 && num < max[0])//插入的数据比最大堆中的最大值 要小
			{
				max.push_back(num);//先把新数据插入最大堆
				push_heap(max.begin(), max.end(), less<T>());//less是默认，表示（大顶堆），即第一个元素是最大的，重新排序，使得最前面是最大的

				num = max[0];//把最大堆中的最大数据拿出来（后续需要插入最小堆，以保证最小堆中所有数字都大于最大堆中的数字）

				pop_heap(max.begin(), max.end(), less<T>());//在堆的基础上，弹出堆顶元素，将堆顶元素（即为数组第一个位置）和数组最后一个位置对调
				max.pop_back();//调用数组pop_back，删除这个元素
			}

			min.push_back(num);
			push_heap(min.begin(), min.end(), greater<T>());
		}
		else //如果当前已经插入的数据中总数目是奇数
		{
			//如果新数据比最小堆中某些数据大（即比最小堆的最大值大），则需要额外操作：

			if (min.size() > 0 && min[0] < num) //插入的数据比最小堆中的最小值 要大
			{
				min.push_back(num);//先把新数据插入最小堆
				push_heap(min.begin(), min.end(), greater<T>());//greater表示（小顶堆），即第一个元素是最小的，重新排序，使得最前面是最小的

				num = min[0];//把最小堆中的最小数据拿出来（后续需要插入最大堆，以保证最大堆中所有数字都小于最小堆中的数字）

				pop_heap(min.begin(), min.end(), greater<T>());
				min.pop_back();
			}

			max.push_back(num);
			push_heap(max.begin(), max.end(), less<T>());
		}
	}

	T GetMedian()//返回数据流中的中位数
	{
		int size = min.size() + max.size();
		if (size == 0)
			throw exception("No numbers are available");

		T median = 0;//用来记录输出的中位数
		if ((size & 1) == 1)//如果数据的总数是奇数
			median = min[0];
		else               //如果数据的总数是偶数
			median = (min[0] + max[0]) / 2;

		return median;
	}

private:
	vector<T> min;//最小堆，对应容器右边那部分的数据
	vector<T> max;//最大堆，对应容器左边那部分的数据
};

// ====================测试代码====================
void Test(char* testName, DynamicArray<double>& numbers, double expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (abs(numbers.GetMedian() - expected) < 0.0000001)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}


int _tmain(int argc, _TCHAR* argv[])
{
	DynamicArray<double> numbers;

	printf("Test1 begins: ");
	try
	{
		numbers.GetMedian();
		printf("FAILED.\n");
	}
	catch (const exception&)
	{
		printf("Passed.\n");
	}

	numbers.Insert(5);
	Test("Test2", numbers, 5);

	numbers.Insert(2);
	Test("Test3", numbers, 3.5);

	numbers.Insert(3);
	Test("Test4", numbers, 3);

	numbers.Insert(4);
	Test("Test6", numbers, 3.5);

	numbers.Insert(1);
	Test("Test5", numbers, 3);

	numbers.Insert(6);
	Test("Test7", numbers, 3.5);

	numbers.Insert(7);
	Test("Test8", numbers, 4);

	numbers.Insert(0);
	Test("Test9", numbers, 3.5);

	numbers.Insert(8);
	Test("Test10", numbers, 4);
	return 0;
}

