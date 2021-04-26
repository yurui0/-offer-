// 42_GreatestSumOfSubarrays.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������42�����������������
// ��Ŀ������һ���������飬������������Ҳ�и�����������һ���������Ķ����
// �����һ�������顣������������ĺ͵����ֵ��Ҫ��ʱ�临�Ӷ�ΪO(n)��

#include "stdafx.h"

#include <cstdio>

bool g_InvalidInput = false;//�����Ϊ���ж������Ƿ�Ϸ���false��ʾ�Ϸ�����Ȼ���ֿ�����ʱ���

int FindGreatestSumOfSubArray(int *pData, int nLength)
{
	if ((pData == nullptr) || (nLength <= 0))
	{
		g_InvalidInput = true;//���벻�Ϸ�
		return 0;
	}

	g_InvalidInput = false;//����˵�������ǺϷ���

	int nCurSum = 0;// ��ʾ �ۼӵ��������
	int nGreatestSum = 0x80000000; //��ʾ ����������� ����ʼ��Ϊ32λint��С�ĸ���ֵ(Ҳ����-2147483648),���ǲ�����ʽ,Ҳ��ԭ��
	for (int i = 0; i < nLength; ++i)
	{
		if (nCurSum <= 0)//����ۼӵ��������Ϊ��������һ��ѭ������һ��������ʹ���ۼӵ��������Ϊ������
			nCurSum = pData[i]; //��ӵ�ǰi��ʼ���¼��㣬����֮ǰ�ۼӵ��������

		else   // ����ۼӵ�������Ͳ�Ϊ��������������µĵ�ǰ������
			nCurSum += pData[i];


		if (nCurSum > nGreatestSum) //�������������֮�͵� �ۼӵ�������� Ҫ�����Ǳ���� ����������� Ҫ��������������
			nGreatestSum = nCurSum;
	}

	return nGreatestSum;
}

// ====================���Դ���====================
void Test(char* testName, int* pData, int nLength, int expected, bool expectedFlag)
{
	if (testName != nullptr)
		printf("%s begins: \n", testName);

	int result = FindGreatestSumOfSubArray(pData, nLength);
	if (result == expected && expectedFlag == g_InvalidInput)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

// 1, -2, 3, 10, -4, 7, 2, -5
void Test1()
{
	int data[] = { 1, -2, 3, 10, -4, 7, 2, -5 };
	Test("Test1", data, sizeof(data) / sizeof(int), 18, false);
}

// �������ֶ��Ǹ���
// -2, -8, -1, -5, -9
void Test2()
{
	int data[] = { -2, -8, -1, -5, -9 };
	Test("Test2", data, sizeof(data) / sizeof(int), -1, false);
}

// �������ֶ�������
// 2, 8, 1, 5, 9
void Test3()
{
	int data[] = { 2, 8, 1, 5, 9 };
	Test("Test3", data, sizeof(data) / sizeof(int), 25, false);
}

// ��Ч����
void Test4()
{
	Test("Test4", nullptr, 0, 0, true);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();

	return 0;
}

