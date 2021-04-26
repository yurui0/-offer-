// 40_KLeastNumbers.cpp : �������̨Ӧ�ó������ڵ㡣
//
// ������40����С��k����
// ��Ŀ������n���������ҳ�������С��k��������������4��5��1��6��2��7��3��8
// ��8�����֣�����С��4��������1��2��3��4��

#include "stdafx.h"

#include <cstdio>
#include "Array.h"

#include <set>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

// ====================����1====================
//���������ǰ���ǣ�ֻ�е����ǿ����޸����������ʱ���ã�Ҳ������partition�����������
// ����partition�����������������Ȼ����������index��k�Ƚϣ������޸�ֱ��index==k-1����������ɣ�������ǰk�����ݼ��ɣ����յõ�����С��k�����ֲ�һ���Ǵ�С��������ģ�
void GetLeastNumbers_Solution1(int* input, int n, int* output, int k)
{
	if (input == nullptr || output == nullptr || k > n || n <= 0 || k <= 0)
		return;

	int start = 0;
	int end = n - 1;
	int index = Partition(input, n, start, end);//���ѡһ�����ݽ�������Ȼ��index��k���бȽ�
	while (index != k - 1)
	{
		if (index > k - 1)//˵��ǰ���������K��,���Ҫ�ٶ�indexǰ������ݽ������򣬴Ӷ�ֻ��Ҫ�õ�ǰk�����ݣ���Ϊ��ʱǰ��index������ǰk������˵�����ź���ģ�
		{
			end = index - 1;
			index = Partition(input, n, start, end);
		}
		else //˵��ǰindex�����Ѿ��ź��ˣ�����index<k����˻�Ҫ�ٶ�index��������ݽ������򣬴Ӷ��õ�ǰk������
		{
			start = index + 1;
			index = Partition(input, n, start, end);
		}
	}

	for (int i = 0; i < k; ++i)
		output[i] = input[i];
}

// ====================����2====================
// �ʺϴ��������� ʱ�临�Ӷ�O��nlogk��
// ��������STL�е�multiset(��Ϊ�����ظ�)������set��multiset�ǻ��ں����ʵ�ֵģ������ʱ�临�Ӷ���O��logk��
typedef multiset<int, std::greater<int> >            intSet;
typedef multiset<int, std::greater<int> >::iterator  setIterator;

//�ŵ㣺û���޸����������data
//�ŵ�2���ʺϺ������ݵ�����---��Ϊ�ڴ����ޣ���ʱ���޷�������һ���Դ����ڴ棬��ʱ�����ǿ��ԴӸ����洢�ռ�ÿ�ζ�һ�����֣�Ȼ����дGetLeastNumbers_Solution2����
//��������һ��������Ϊ����������I/O֮�ࣩ���ж��Ƿ���Ҫ��������leastNumbers�м��ɣ�����˼·ֻ��ҪleastNumbers �����ڴ��м���

void GetLeastNumbers_Solution2(const vector<int>& data, intSet& leastNumbers, int k)
{
	leastNumbers.clear();//���е�д������������leastNumbers������

	if (k < 1 || data.size() < k)//�ж��Ƿ�Ϸ�
		return;

	vector<int>::const_iterator iter = data.begin();//����������
	for (; iter != data.end(); ++iter)
	{
		if ((leastNumbers.size()) < k)//����leastNumbers�д���k������
			leastNumbers.insert(*iter);

		else
		{
			setIterator iterGreatest = leastNumbers.begin();

			if (*iter < *(leastNumbers.begin()))//��ʼ�Ƚϣ����С��multiset��������С�ģ�����ɾ���������С��
			{                                   //ע�⣺ ���ﲻ�����ݽ��������ԭ���ǣ�set��multiset�����ú����Ĭ���������������--��С���󡱣����ֻ��Ҫ�Ƚ�begin����
				leastNumbers.erase(iterGreatest);
				leastNumbers.insert(*iter);
			}
		}
	}
}

// ====================���Դ���====================
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

// kС������ĳ���
void Test1()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int expected[] = { 1, 2, 3, 4 };
	Test("Test1", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k��������ĳ���
void Test2()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int expected[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	Test("Test2", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k��������ĳ���
void Test3()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int* expected = nullptr;
	Test("Test3", data, sizeof(data) / sizeof(int), expected, 10);
}

// k����1
void Test4()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int expected[] = { 1 };
	Test("Test4", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k����0
void Test5()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	int* expected = nullptr;
	Test("Test5", data, sizeof(data) / sizeof(int), expected, 0);
}

// ����������ͬ������
void Test6()
{
	int data[] = { 4, 5, 1, 6, 2, 7, 2, 8 };
	int expected[] = { 1, 2 };
	Test("Test6", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// �����ָ��
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

