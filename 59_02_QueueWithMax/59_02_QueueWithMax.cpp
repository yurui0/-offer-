// 59_02_QueueWithMax.cpp : 定义控制台应用程序的入口点。
//

// 面试题59（二）：队列的最大值
// 题目：给定一个数组和滑动窗口的大小，请找出所有滑动窗口里的最大值。例如，
// 如果输入数组{2, 3, 4, 2, 6, 2, 5, 1}及滑动窗口的大小3，那么一共存在6个
// 滑动窗口，它们的最大值分别为{4, 4, 6, 6, 6, 5}，

#include "stdafx.h"

#include <cstdio>
#include <deque>
#include <exception>

using namespace std;

template<typename T> //模板类，用于定义满足条件的获得队列最大值的类
class QueueWithMax
{
public:
	QueueWithMax() : currentIndex(0)
	{
	} 

	void push_back(T number)
	{
		while (!maximums.empty() && number >= maximums.back().number)//队列中最大值列表不为空，且当前元素的值大于最大值列表末尾的值，则删除末尾位置的元素
			maximums.pop_back();                                     //这里是保证最大队列中的元素要比传入的数据大

		InternalData internalData = { number, currentIndex };//根据输入值新建结构体，同时记录该值与该值加入队列的顺序index
		data.push_back(internalData);
		maximums.push_back(internalData);

		++currentIndex;
	}

	void pop_front()
	{
		if (maximums.empty())
			throw new exception("queue is empty");

		if (maximums.front().index == data.front().index)//如果data队列中要删除的队首元素与“记录队列最大值的队列”的队首元素相同，则删除记录队列最大值的队列的队首
			maximums.pop_front();                        //因为该元素已经不再data队列中，自然即便其是最大的，也不能存在于“记录队列最大值的队列”中

		data.pop_front();// data队列中的队首元素出队列
	}

	T max() const
	{
		if (maximums.empty())
			throw new exception("queue is empty");

		return maximums.front().number;//maximums.front()表示最大队列中的队首元素就是队列中的最大值
	}

private:
	struct InternalData //这里自定义了一个结构体，T number表示通过push_back传入的T类型的数据；int index表示当前值的对应序号index
	{
		T number;
		int index;  
	};

	deque<InternalData> data; //存储队列
	deque<InternalData> maximums; //存储队列中最大值
	int currentIndex; //插入数据的index，只增不减，即便删除也是一样，以免复杂
};

// ====================测试代码====================
void Test(const char* testName, const QueueWithMax<int>& queue, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (queue.max() == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}


int _tmain(int argc, _TCHAR* argv[])
{
	QueueWithMax<int> queue;
	// {2}
	queue.push_back(2);
	Test("Test1", queue, 2);

	// {2, 3}
	queue.push_back(3);
	Test("Test2", queue, 3);

	// {2, 3, 4}
	queue.push_back(4);
	Test("Test3", queue, 4);

	// {2, 3, 4, 2}
	queue.push_back(2);
	Test("Test4", queue, 4);

	// {3, 4, 2}
	queue.pop_front();
	Test("Test5", queue, 4);

	// {4, 2}
	queue.pop_front();
	Test("Test6", queue, 4);

	// {2}
	queue.pop_front();
	Test("Test7", queue, 2);

	// {2, 6}
	queue.push_back(6);
	Test("Test8", queue, 6);

	// {2, 6, 2}
	queue.push_back(2);
	Test("Test9", queue, 6);

	// {2, 6, 2, 5}
	queue.push_back(5);
	Test("Test9", queue, 6);

	// {6, 2, 5}
	queue.pop_front();
	Test("Test10", queue, 6);

	// {2, 5}
	queue.pop_front();
	Test("Test11", queue, 5);

	// {5}
	queue.pop_front();
	Test("Test12", queue, 5);

	// {5, 1}
	queue.push_back(1);
	Test("Test13", queue, 5);


	return 0;
}

