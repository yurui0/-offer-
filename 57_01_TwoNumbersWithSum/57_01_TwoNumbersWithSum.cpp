// 57_01_TwoNumbersWithSum.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������57��һ������Ϊs����������
// ��Ŀ������һ����������������һ������s���������в�����������ʹ������
// �ĺ�������s������ж�����ֵĺ͵���s���������һ�Լ��ɡ�


#include "stdafx.h"

#include <cstdio>

bool FindNumbersWithSum(int data[], int length, int sum,int* num1, int* num2)// num1��num2�ֱ��ʾ��Ϊs��ǰ�������ֵ
{
	bool found = false;//�Ƿ��ҵ��ı�ʾ��
	if (length < 1 || num1 == nullptr || num2 == nullptr)//�ж������Ƿ�Ϸ�
		return found;

	int ahead = length - 1;//�൱��ָ����������һ�����ֵ�ָ�룬�������±����
	int behind = 0;//�൱��ָ������ĵ�һ�����ֵ�ָ�룬�������±���棨��Ϊ����ͨ���±��ȡ�����е�ǰλ�õ�ֵ�������ٶ���ָ�룩

	while (ahead > behind)//����ָ�뻹û������������û�ж�����������ȫ������һ��
	{
		long long curSum = data[ahead] + data[behind];//����ǰ��ָ���ֵ֮��

		if (curSum == sum)//�������ĺ���s��ȣ�˵���ҵ��ˣ���󽫶�Ӧֵ�ͱ�ǩ���и�ֵ������
		{
			*num1 = data[behind];
			*num2 = data[ahead];
			found = true;
			break;
		}
		else if (curSum > sum)//����ʹ���s�������ָ��ǰ��
			ahead--;
		else
			behind++;       //����ǰ��ָ�����
	}

	return found;
}

// ====================���Դ���====================
void Test(const char* testName, int data[], int length, int sum, bool expectedReturn)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	int num1, num2;
	int result = FindNumbersWithSum(data, length, sum, &num1, &num2);
	if (result == expectedReturn)
	{
		if (result)
		{
			if (num1 + num2 == sum)
				printf("Passed. \n");
			else
				printf("FAILED. \n");
		}
		else
			printf("Passed. \n");
	}
	else
		printf("FAILED. \n");
}

// ���ں�Ϊs���������֣�����������λ��������м�
void Test1()
{
	int data[] = { 1, 2, 4, 7, 11, 15 };
	Test("Test1", data, sizeof(data) / sizeof(int), 15, true);
}

// ���ں�Ϊs���������֣�����������λ�����������
void Test2()
{
	int data[] = { 1, 2, 4, 7, 11, 16 };
	Test("Test2", data, sizeof(data) / sizeof(int), 17, true);
}

// �����ں�Ϊs����������
void Test3()
{
	int data[] = { 1, 2, 4, 7, 11, 16 };
	Test("Test3", data, sizeof(data) / sizeof(int), 10, false);
}

// ³���Բ���
void Test4()
{
	Test("Test4", nullptr, 0, 0, false);
}


int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();

	return 0;
}

