// 53_03_IntegerIdenticalToIndex.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������53����������������ֵ���±���ȵ�Ԫ��
// ��Ŀ������һ�������������������ÿ��Ԫ�ض�������������Ψһ�ġ�����ʵ
// ��һ�������ҳ�����������һ����ֵ�������±��Ԫ�ء����磬������{-3, -1,
// 1, 3, 5}�У�����3�������±���ȡ�

#include "stdafx.h"

#include <cstdio>

int GetNumberSameAsIndex(const int* numbers, int length)//���õ������У��ź��򣩵��ص㣬ʹ�ö��ֲ��ң���ʱ�临�Ӷ�o(n)->o(logn)
{
	if (numbers == nullptr || length <= 0)//�ж������Ƿ����
		return -1;

	int left = 0;
	int right = length - 1;
	while (left <= right) //��С��Χ�����жϣ�ֱ��ǰ��������
	{
		int middle = left + ((right - left) >> 1);//�����м���±�
		if (numbers[middle] == middle)//��ʱ���������ҵ���
			return middle;

		if (numbers[middle] > middle)//������ֵ�ֵ���������±꣬�����ұߵ����ֶ����ڶ�Ӧ���±�
			// ˼·�ǣ���ǰ����ֵm���±�i��m>i,��i��ʼ������һ������0��k�����������ǵ���������±�i+k�����ֵ�ֵһ������m+k�����趼�Ǽ�һ������,����m+k>i+k���ʵõ��������
			right = middle - 1;
		else //��������㣬����һ������ֻ��Ҫ������ߵ������в���
			left = middle + 1;
	}

	return -1;
}

// ====================���Դ���====================
void Test(const char* testName, int numbers[], int length, int expected)
{
	if (GetNumberSameAsIndex(numbers, length) == expected)
		printf("%s passed.\n", testName);
	else
		printf("%s FAILED.\n", testName);
}

void Test1()
{
	int numbers[] = { -3, -1, 1, 3, 5 };
	int expected = 3;
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test2()
{
	int numbers[] = { 0, 1, 3, 5, 6 };
	int expected = 0;
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test3()
{
	int numbers[] = { -1, 0, 1, 2, 4 };
	int expected = 4;
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test4()
{
	int numbers[] = { -1, 0, 1, 2, 5 };
	int expected = -1;
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test5()
{
	int numbers[] = { 0 };
	int expected = 0;
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test6()
{
	int numbers[] = { 10 };
	int expected = -1;
	Test("Test6", numbers, sizeof(numbers) / sizeof(int), expected);
}

void Test7()
{
	Test("Test7", nullptr, 0, -1);
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

