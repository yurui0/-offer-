// 53_02_MissingNumber.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������53��������0��n-1��ȱʧ������
// ��Ŀ��һ������Ϊn-1�ĵ������������е��������ֶ���Ψһ�ģ�����ÿ������
// ���ڷ�Χ0��n-1֮�ڡ��ڷ�Χ0��n-1��n������������ֻ��һ�����ֲ��ڸ�����
// �У����ҳ�������֡�

#include "stdafx.h"

#include <cstdio>

int GetMissingNumber(const int* numbers, int length)//���ڶ��ֲ���Ѱ��0--n-1��ȱ�ٵ�����
{
	if (numbers == nullptr || length <= 0)//�����Ƿ�Ϸ�
		return -1;

	int left = 0;
	int right = length - 1;
	while (left <= right) //����������ѭ���ķ���ʵ�����Ƶݹ��Ч��
	{
		int middle = (right + left) >> 1;//����Ϊ��������£�a>>1��ʾ���ݵĶ����Ʊ�ʾ����һλ������������2����Ϊλ����Ҫ����ͨ�����죬���ڷǸ�����λ�������
		if (numbers[middle] != middle) //���middle�±��ֵ����±괦�����ж�Ӧ��ֵ����ȣ���ʱ��Ҫ���������
		{
			if (middle == 0 || numbers[middle - 1] == middle - 1)//������ǰһ��Ԫ�غ������±���ȣ����˵������м��������þ��ǵ�һ��ֵ���±겻��ȵ�Ԫ��
				return middle;
			right = middle - 1;  //����˵��������һ�ֲ���ֻ��Ҫ�����߲��ң���right = middle - 1
		}
		else                     //���middle�±��ֵ����±괦�����ж�Ӧ��ֵ��ȣ�˵����������벿�ֲ�����ȱ�٣���left = middle + 1;Ȼ��ʼ�ж��Ұ벿��
			left = middle + 1;
	}

	if (left == length)//����������ѭ���е��Ұ���ж����û���ҵ�����˵������ȱ��length�±괦��length
		return length;

	// ��Ч�����룬�������鲻�ǰ�Ҫ������ģ�
	// ���������ֲ���0��n-1��Χ֮��
	return -1;
}

// ====================���Դ���====================
void Test(const char* testName, int numbers[], int length, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	int result = GetMissingNumber(numbers, length);
	if (result == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// ȱʧ���ǵ�һ������0
void Test1()
{
	int numbers[] = { 1, 2, 3, 4, 5 };
	int expected = 0;
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), expected);
}

// ȱʧ�������һ������
void Test2()
{
	int numbers[] = { 0, 1, 2, 3, 4 };
	int expected = 5;
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), expected);
}

// ȱʧ�����м�ĳ������0
void Test3()
{
	int numbers[] = { 0, 1, 2, 4, 5 };
	int expected = 3;
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), expected);
}

// ������ֻ��һ�����֣�ȱʧ���ǵ�һ������0
void Test4()
{
	int numbers[] = { 1 };
	int expected = 0;
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), expected);
}

// ������ֻ��һ�����֣�ȱʧ�������һ������1
void Test5()
{
	int numbers[] = { 0 };
	int expected = 1;
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), expected);
}

// ������
void Test6()
{
	int expected = -1;
	Test("Test6", nullptr, 0, expected);
}


int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	return 0;
}

