// 59_02_QueueWithMax.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������59�����������е����ֵ
// ��Ŀ������һ������ͻ������ڵĴ�С�����ҳ����л�������������ֵ�����磬
// �����������{2, 3, 4, 2, 6, 2, 5, 1}���������ڵĴ�С3����ôһ������6��
// �������ڣ����ǵ����ֵ�ֱ�Ϊ{4, 4, 6, 6, 6, 5}��

#include "stdafx.h"

#include <cstdio>
#include <deque>
#include <exception>

using namespace std;

template<typename T> //ģ���࣬���ڶ������������Ļ�ö������ֵ����
class QueueWithMax
{
public:
	QueueWithMax() : currentIndex(0)
	{
	} 

	void push_back(T number)
	{
		while (!maximums.empty() && number >= maximums.back().number)//���������ֵ�б�Ϊ�գ��ҵ�ǰԪ�ص�ֵ�������ֵ�б�ĩβ��ֵ����ɾ��ĩβλ�õ�Ԫ��
			maximums.pop_back();                                     //�����Ǳ�֤�������е�Ԫ��Ҫ�ȴ�������ݴ�

		InternalData internalData = { number, currentIndex };//��������ֵ�½��ṹ�壬ͬʱ��¼��ֵ���ֵ������е�˳��index
		data.push_back(internalData);
		maximums.push_back(internalData);

		++currentIndex;
	}

	void pop_front()
	{
		if (maximums.empty())
			throw new exception("queue is empty");

		if (maximums.front().index == data.front().index)//���data������Ҫɾ���Ķ���Ԫ���롰��¼�������ֵ�Ķ��С��Ķ���Ԫ����ͬ����ɾ����¼�������ֵ�Ķ��еĶ���
			maximums.pop_front();                        //��Ϊ��Ԫ���Ѿ�����data�����У���Ȼ�����������ģ�Ҳ���ܴ����ڡ���¼�������ֵ�Ķ��С���

		data.pop_front();// data�����еĶ���Ԫ�س�����
	}

	T max() const
	{
		if (maximums.empty())
			throw new exception("queue is empty");

		return maximums.front().number;//maximums.front()��ʾ�������еĶ���Ԫ�ؾ��Ƕ����е����ֵ
	}

private:
	struct InternalData //�����Զ�����һ���ṹ�壬T number��ʾͨ��push_back�����T���͵����ݣ�int index��ʾ��ǰֵ�Ķ�Ӧ���index
	{
		T number;
		int index;  
	};

	deque<InternalData> data; //�洢����
	deque<InternalData> maximums; //�洢���������ֵ
	int currentIndex; //�������ݵ�index��ֻ������������ɾ��Ҳ��һ�������⸴��
};

// ====================���Դ���====================
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

