// 51_InversePairs.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������51�������е������
// ��Ŀ���������е������������ǰ��һ�����ִ��ں�������֣���������������
// ��һ������ԡ�����һ�����飬�����������е�����Ե�������

#include "stdafx.h"
#include <iostream>
#include <cstdio>
using namespace std;

int InversePairsCore(int* data, int* copy, int start, int end);

int InversePairs(int* data, int length)//����Ŀ����ʼλ��
{
	if (data == nullptr || length < 0)//�ж������Ƿ�Ϸ�
		return 0;

	int* copy = new int[length]; // ������Ϊ�������鳤�ȵĸ�������
	for (int i = 0; i < length; ++i)
		copy[i] = data[i];

	int count = InversePairsCore(data, copy, 0, length - 1);
	delete[] copy;

	return count;
}

int InversePairsCore(int* data, int* copy, int start, int end)
{
	if (start == end)
	{
		copy[start] = data[start];
		return 0;
	}

	int length = (end - start) / 2;

	int left = InversePairsCore(copy, data, start, start + length);//�ݹ飬ÿ��ֻ�Բ�ֺ������������������бȽ�
	int right = InversePairsCore(copy, data, start + length + 1, end);

	// i��ʼ��Ϊǰ������һ�����ֵ��±�
	int i = start + length;
	// j��ʼ��Ϊ�������һ�����ֵ��±�
	int j = end;
	int indexCopy = end;
	int count = 0;
	while (i >= start && j >= start + length + 1)
	{
		if (data[i] > data[j])//ǰ������һ�����ֵ��±�>�������һ�����ֵ��±�
		{
			copy[indexCopy--] = data[i--];//��ǰ�������������ӵ����������ж�Ӧλ��
			count += j - start - length;//��ʱ����Ե��������ڵڶ�����������ʣ�����ֵĸ���
		}
		else
		{
			copy[indexCopy--] = data[j--];//ǰ������һ�����ֵ��±�<�������һ�����ֵ��±�,�����������
		}
	}

	for (; i >= start; --i)
		copy[indexCopy--] = data[i];

	for (; j >= start + length + 1; --j)
		copy[indexCopy--] = data[j];

	return left + right + count;//���ص�ǰѭ���µ�������
}

// ====================���Դ���====================
void Test(char* testName, int* data, int length, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (InversePairs(data, length) == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

void Test1()
{
	int data[] = { 1, 2, 3, 4, 7, 6, 5 };
	int expected = 3;

	Test("Test1", data, sizeof(data) / sizeof(int), expected);
}

// �ݼ���������
void Test2()
{
	int data[] = { 6, 5, 4, 3, 2, 1 };
	int expected = 15;

	Test("Test2", data, sizeof(data) / sizeof(int), expected);
}

// ������������
void Test3()
{
	int data[] = { 1, 2, 3, 4, 5, 6 };
	int expected = 0;

	Test("Test3", data, sizeof(data) / sizeof(int), expected);
}

// ������ֻ��һ������
void Test4()
{
	int data[] = { 1 };
	int expected = 0;

	Test("Test4", data, sizeof(data) / sizeof(int), expected);
}


// ������ֻ���������֣���������
void Test5()
{
	int data[] = { 1, 2 };
	int expected = 0;

	Test("Test5", data, sizeof(data) / sizeof(int), expected);
}

// ������ֻ���������֣��ݼ�����
void Test6()
{
	int data[] = { 2, 1 };
	int expected = 1;

	Test("Test6", data, sizeof(data) / sizeof(int), expected);
}

// ����������ȵ�����
void Test7()
{
	int data[] = { 1, 2, 1, 2, 1 };
	int expected = 3;

	Test("Test7", data, sizeof(data) / sizeof(int), expected);
}

void Test8()
{
	int expected = 0;

	Test("Test8", nullptr, 0, expected);
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

	static double value[6];
	
	for (int i = 0; i <=6; i++)
		value[i] = i;

	for (int i = 0; i <= 6; i++)
		cout << value[i] << endl;

	for (int i = 0; i <= 6; i++)
		value[i] = i+10;

	for (int i = 0; i <= 6; i++)
		cout << value[i] << endl;


	return 0;
}

