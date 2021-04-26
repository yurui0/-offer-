// 53_01_NumberOfK.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������53��һ�������������������г��ֵĴ���
// ��Ŀ��ͳ��һ�����������������г��ֵĴ���������������������{1, 2, 3, 3,
// 3, 3, 4, 5}������3������3����������г�����4�Σ�������4��

#include "stdafx.h"
#include <cstdio>

int GetFirstK(const int* data, int length, int k, int start, int end);//�ú���������ȡ�����е�һ��k�������е��±�
int GetLastK(const int* data, int length, int k, int start, int end);//�ú���������ȡ���������һ��k�������е��±�

int GetNumberOfK(const int* data, int length, int k)//����ȡ�����һ��k�͵�һ��k���±�֮�����������һ�������������������г��ֵĴ���
{
	int number = 0;

	if (data != nullptr && length > 0)
	{
		int first = GetFirstK(data, length, k, 0, length - 1);//��������в�����k������-1������ͷ��ص�һ��k�������е��±�
		int last = GetLastK(data, length, k, 0, length - 1);//��������в�����k������-1������ͷ������һ��k�������е��±�

		if (first > -1 && last > -1)
			number = last - first + 1;
	}

	return number;
}

// �ҵ������е�һ��k���±ꡣ��������в�����k������-1
int GetFirstK(const int* data, int length, int k, int start, int end)
{
	if (start > end)//�����Ƿ�Ϸ�
		return -1;

	int middleIndex = (start + end) / 2;//��ȡ��ǰ�������м���±��
	int middleData = data[middleIndex];//��ȡ�����м��Ԫ��

	if (middleData == k)//����м�λ�ô���Ԫ�ص���k
	{
		if ((middleIndex > 0 && data[middleIndex - 1] != k)//��ʱ�ж��±��Ƿ�Ϸ��Ҹ��±��ǰһ����Ϊk��˵������±괦���ǵ�һ��k��λ��
			|| middleIndex == 0)// middleIndex == 0��ʾԪ��ֵ����k��ʱ����λ���������һ��Ԫ�أ�������ǰһ��Ԫ�أ��Ƕ������ж������Ĳ���
			return middleIndex;
		else
			end = middleIndex - 1; //�����λ�ô�ǰһ��Ԫ�ػ���Ϊk��˵����һ��kһ���ڵ�ǰ�������벿�֣����԰�end��ΪmiddleIndex - 1
	}
	else if (middleData > k)//����м�λ�ô���Ԫ�ش���k��˵����һ��kһ���ڵ�ǰ�������벿�֣����԰�end��ΪmiddleIndex - 1
		end = middleIndex - 1;
	else                   //����м�λ�ô���Ԫ��С��k��˵����һ��kһ���ڵ�ǰ������Ұ벿�֣����԰�start��ΪmiddleIndex + 1
		start = middleIndex + 1;

	return GetFirstK(data, length, k, start, end);//�޸ķ�Χ�󣬿�ʼ�ݹ�ļ���Ѱ�ҵ�һ��k���±꣬�ҵ��ͷ���middleIndex
}

// �ҵ����������һ��k���±ꡣ��������в�����k������-1
int GetLastK(const int* data, int length, int k, int start, int end)
{
	if (start > end)//�����Ƿ�Ϸ�
		return -1;

	int middleIndex = (start + end) / 2;//��ȡ��ǰ�������м���±��
	int middleData = data[middleIndex];//��ȡ�����м��Ԫ��

	if (middleData == k)//����м�λ�ô���Ԫ�ص���k
	{
		if ((middleIndex < length - 1 && data[middleIndex + 1] != k) // ��ʱ�ж��±��Ƿ�Ϸ��Ҹ��±�ĺ�һ����Ϊk��˵������±괦�������һ��k��λ��
			|| middleIndex == length - 1)//middleIndex == length - 1˵��Ԫ��ֵ����k��ʱ����λ�����������һ��Ԫ�أ�������ǰһ��Ԫ�أ��Ƕ������ж������Ĳ���
			return middleIndex;
		else
			start = middleIndex + 1;//�����λ�ô���һ��Ԫ�ػ���Ϊk��˵�����һ��kһ���ڵ�ǰ������Ұ벿�֣����԰�start��ΪmiddleIndex + 1
	}
	else if (middleData < k)
		start = middleIndex + 1;  //����м�λ�ô���Ԫ��С��k��˵����һ��kһ���ڵ�ǰ������Ұ벿�֣����԰�start��ΪmiddleIndex + 1
	else
		end = middleIndex - 1;    //����м�λ�ô���Ԫ�ش���k��˵����һ��kһ���ڵ�ǰ�������벿�֣����԰�end��ΪmiddleIndex - 1

	return GetLastK(data, length, k, start, end);
}

// ====================���Դ���====================
void Test(const char* testName, int data[], int length, int k, int expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	int result = GetNumberOfK(data, length, k);
	if (result == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// ���ҵ����ֳ�����������м�
void Test1()
{
	int data[] = { 1, 2, 3, 3, 3, 3, 4, 5 };
	Test("Test1", data, sizeof(data) / sizeof(int), 3, 4);
}

// ���ҵ��������������Ŀ�ͷ
void Test2()
{
	int data[] = { 3, 3, 3, 3, 4, 5 };
	Test("Test2", data, sizeof(data) / sizeof(int), 3, 4);
}

// ���ҵ��������������Ľ�β
void Test3()
{
	int data[] = { 1, 2, 3, 3, 3, 3 };
	Test("Test3", data, sizeof(data) / sizeof(int), 3, 4);
}

// ���ҵ����ֲ�����
void Test4()
{
	int data[] = { 1, 3, 3, 3, 3, 4, 5 };
	Test("Test4", data, sizeof(data) / sizeof(int), 2, 0);
}

// ���ҵ����ֱȵ�һ�����ֻ�С��������
void Test5()
{
	int data[] = { 1, 3, 3, 3, 3, 4, 5 };
	Test("Test5", data, sizeof(data) / sizeof(int), 0, 0);
}

// ���ҵ����ֱ����һ�����ֻ��󣬲�����
void Test6()
{
	int data[] = { 1, 3, 3, 3, 3, 4, 5 };
	Test("Test6", data, sizeof(data) / sizeof(int), 6, 0);
}

// �����е����ִ�ͷ��β���ǲ��ҵ�����
void Test7()
{
	int data[] = { 3, 3, 3, 3 };
	Test("Test7", data, sizeof(data) / sizeof(int), 3, 4);
}

// �����е����ִ�ͷ��βֻ��һ���ظ������֣����ǲ��ҵ�����
void Test8()
{
	int data[] = { 3, 3, 3, 3 };
	Test("Test8", data, sizeof(data) / sizeof(int), 4, 0);
}

// ������ֻ��һ�����֣��ǲ��ҵ�����
void Test9()
{
	int data[] = { 3 };
	Test("Test9", data, sizeof(data) / sizeof(int), 3, 1);
}

// ������ֻ��һ�����֣����ǲ��ҵ�����
void Test10()
{
	int data[] = { 3 };
	Test("Test10", data, sizeof(data) / sizeof(int), 4, 0);
}

// ³���Բ��ԣ������ָ��
void Test11()
{
	Test("Test11", nullptr, 0, 0, 0);
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
	Test10();
	Test11();

	return 0;
}

