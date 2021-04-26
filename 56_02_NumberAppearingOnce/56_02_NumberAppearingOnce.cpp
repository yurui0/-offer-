// 56_02_NumberAppearingOnce.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������56��������������Ψһֻ����һ�ε�����
// ��Ŀ����һ�������г���һ������ֻ����һ��֮�⣬�������ֶ����������Ρ���
// �ҳ��Ǹ��Գ���һ�ε����֡�

#include "stdafx.h"

#include <cstdio>
#include <exception>

int FindNumberAppearingOnce(int numbers[], int length) //�����˼·�ǣ�ÿ�����ֳ��������Σ���ô�����ֵĶ����Ʊ�ʾ����ͬλ�����֣�0��1���ĺͣ�0��3�����ܱ�3����
{                                                     //��Ȼ��ˣ������������������ֵĶ����Ʊ�ʾ��ÿһλ�������������������ε�����+Ψһ����һ�ε����֣����õ��ܺ͵Ķ�����
														// �������γ��ֵ����ֵĶ�����ÿһλ�����Ա�3��������� ���հ���Ψһ����һ�ε����ֵĶ������У���ÿһλ����3
														// ����ܱ���������Ψһ����һ�ε���һλ���ָö�����λΪ0������Ϊ1����Ϊ������ֻ��Ϊ0��1��
	if (numbers == nullptr || length <= 0) //�ж������Ƿ�Ϸ�
		throw new std::exception("Invalid input.");

	int bitSum[32] = { 0 }; //����Ϊ32λ��int��4���ֽڣ�4x8=32���ĸ�������洢�����Ʊ�ʾ��ÿһλ�ĺ�
	for (int i = 0; i < length; ++i) //�����ǽ�number������ÿһ�����ֶ�תΪ32λ�����ƺ󣬼���
	{
		int bitMask = 1; //
		for (int j = 31; j >= 0; --j)
		{
			int bit = numbers[i] & bitMask; //����int����&���㣬������������ת��Ϊ�����Ʊ�ʾ��Ȼ�����&���㣺��Ӧλ������ֵͬʱΪ1�����Ϊ1������Ϊ0
			if (bit != 0) //����ö�����λ ��1����&���������Ϊ1��˵��number[i]չ��Ϊ�����ƺ󣬸�λΪ1��������bitSum[j]��+1,����λΪ0���账��
				bitSum[j] += 1;

			bitMask = bitMask << 1;//�����ǽ�bitMask���г�2�ļ��㣬��������number[i]ת���ɵ�32λ���������ν���&����
		}
	}

	int result = 0;
	for (int i = 0; i < 32; ++i)
	{
		result = result << 1; //������Ǹ���iλ����Ӧ��ֵ��Ȼ��ͨ��<<������2���������Ӧ��10�����µĽ��
		result += bitSum[i] % 3;// ��32λ��ÿһλ���д���������г�3���õ���������
	}

	return result;
}

// ====================���Դ���====================
void Test(const char* testName, int numbers[], int length, int expected)
{
	int result = FindNumberAppearingOnce(numbers, length);
	if (result == expected)
		printf("%s passed.\n", testName);
	else
		printf("%s FAILED.\n", testName);
}

// �������ֶ���������Ψһ����������С��
void Test1()
{
	int numbers[] = { 1, 1, 2, 2, 2, 1, 3 };
	int expected = 3;
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), expected);
}

// �������ֶ���������Ψһ�����ֵĴ�Сλ���м�
void Test2()
{
	int numbers[] = { 4, 3, 3, 2, 2, 2, 3 };
	int expected = 4;
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), expected);
}

// �������ֶ���������Ψһ������������
void Test3()
{
	int numbers[] = { 4, 4, 1, 1, 1, 7, 4 };
	int expected = 7;
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), expected);
}

// Ψһ�������Ǹ���
void Test4()
{
	int numbers[] = { -10, 214, 214, 214 };
	int expected = -10;
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), expected);
}

// ����Ψһ�����֣��������ֶ��Ǹ���
void Test5()
{
	int numbers[] = { -209, 3467, -209, -209 };
	int expected = 3467;
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), expected);
}

// �ظ�������������Ҳ�и���
void Test6()
{
	int numbers[] = { 1024, -1025, 1024, -1025, 1024, -1025, 1023 };
	int expected = 1023;
	Test("Test6", numbers, sizeof(numbers) / sizeof(int), expected);
}

// �������ֶ��Ǹ���
void Test7()
{
	int numbers[] = { -1024, -1024, -1024, -1023 };
	int expected = -1023;
	Test("Test7", numbers, sizeof(numbers) / sizeof(int), expected);
}

// Ψһ��������0
void Test8()
{
	int numbers[] = { -23, 0, 214, -23, 214, -23, 214 };
	int expected = 0;
	Test("Test8", numbers, sizeof(numbers) / sizeof(int), expected);
}

// ����Ψһ�����֣��������ֶ���0
void Test9()
{
	int numbers[] = { 0, 3467, 0, 0, 0, 0, 0, 0 };
	int expected = 3467;
	Test("Test9", numbers, sizeof(numbers) / sizeof(int), expected);
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

	return 0;
}

