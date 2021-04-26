// 61_ContinousCards.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������61���˿��Ƶ�˳��
// ��Ŀ�����˿����������5���ƣ��ж��ǲ���һ��˳�ӣ�����5�����ǲ��������ġ�
// 2��10Ϊ���ֱ���AΪ1��JΪ11��QΪ12��KΪ13������С�����Կ����������֡�

#include "stdafx.h"

#include <cstdio>
#include <cstdlib>

int Compare(const void *arg1, const void *arg2);

bool IsContinuous(int* numbers, int length)//�������飬����ĳ���
{
	if (numbers == nullptr || length < 1)//�ж������Ƿ�Ϸ�
		return false;

	qsort(numbers, length, sizeof(int), Compare);//����c���Ե�qsort����ʵ����������
	// qsort����C���Ա������������Դ���������,void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))
	// base-- ָ��Ҫ���������ĵ�һ��Ԫ�ص�ָ�롣nitems-- �� base ָ���������Ԫ�صĸ�����size-- ������ÿ��Ԫ�صĴ�С�����ֽ�Ϊ��λ��
	// compar-- �����Ƚ�����Ԫ�صĺ�����������ָ�루�ص�������

	//����qsortʱ�临�Ӷ�ΪO��nlogn��������Ҳ�����Լ�����һ������Ϊ14��hash��������O(n)�ķ�Χ�ھͿ���ʵ������
	//����ע�⣺��ͬ�����ʱ�临�Ӷ�ֻ�е�n�㹻���ʱ��������塣����ֻ��5���ƣ�O��nlogn����O(n)��಻����˿������еļ򵥺���

	int numberOfZero = 0;//��¼������0�ĸ���
	int numberOfGap = 0;//��¼�����з�0Ԫ��֮��Ŀ�϶�Ĵ�С

	// ͳ��������0�ĸ���
	for (int i = 0; i < length && numbers[i] == 0; ++i)
		++numberOfZero;

	// ͳ�������еļ����Ŀ
	int small = numberOfZero; //��Ϊ֮ǰ�Ѿ����򣨵���������˼���gap����ʼ���Ϊ0�ĸ���������һλ��0�����ֵ��±�
	int big = small + 1;   // �ڶ�λ��0�����ֵ��±�
	while (big < length) //�ڶ�λ���ֵ��±�û�е��������ĩβ---��Ϊֻ����[0,length-1]֮��
	{
		// ��������ȣ��ж��ӣ���������˳��
		if (numbers[small] == numbers[big])
			return false;

		numberOfGap += numbers[big] - numbers[small] - 1;//numbers[big] - numbers[small] - 1����������֮���gap����������ڵľ�Ϊ0
		//  ����ͳ��ֵ��Ϊ0������֮���gap���ܺͣ�����ܺͱ�0�ĸ�������ô��0�������������ֽ�������޷�ʵ��˳������
		// �����������жϺ���������
		small = big;
		++big;
	}

	return (numberOfGap > numberOfZero) ? false : true;//0���������϶��˵������˳�ӣ�������˳��
}

int Compare(const void *arg1, const void *arg2)
{
	return *(int*)arg1 - *(int*)arg2;
	// ���compar����ֵС��0��< 0������ôp1��ָ��Ԫ�ػᱻ����p2��ָ��Ԫ�ص����棻���compar����ֵ����0�� = 0������ôp1��ָ��Ԫ����p2��ָ��Ԫ�ص�˳��ȷ����
	// ���compar����ֵ����0��> 0������ôp1��ָ��Ԫ�ػᱻ����p2��ָ��Ԫ�ص����档

}

// ====================���Դ���====================
void Test(const char* testName, int* numbers, int length, bool expected)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (IsContinuous(numbers, length) == expected)
		printf("Passed.\n");
	else
		printf("Failed.\n");
}

void Test1()
{
	int numbers[] = { 1, 3, 2, 5, 4 };
	Test("Test1", numbers, sizeof(numbers) / sizeof(int), true);
}

void Test2()
{
	int numbers[] = { 1, 3, 2, 6, 4 };
	Test("Test2", numbers, sizeof(numbers) / sizeof(int), false);
}

void Test3()
{
	int numbers[] = { 0, 3, 2, 6, 4 };
	Test("Test3", numbers, sizeof(numbers) / sizeof(int), true);
}

void Test4()
{
	int numbers[] = { 0, 3, 1, 6, 4 };
	Test("Test4", numbers, sizeof(numbers) / sizeof(int), false);
}

void Test5()
{
	int numbers[] = { 1, 3, 0, 5, 0 };
	Test("Test5", numbers, sizeof(numbers) / sizeof(int), true);
}

void Test6()
{
	int numbers[] = { 1, 3, 0, 7, 0 };
	Test("Test6", numbers, sizeof(numbers) / sizeof(int), false);
}

void Test7()
{
	int numbers[] = { 1, 0, 0, 5, 0 };
	Test("Test7", numbers, sizeof(numbers) / sizeof(int), true);
}

void Test8()
{
	int numbers[] = { 1, 0, 0, 7, 0 };
	Test("Test8", numbers, sizeof(numbers) / sizeof(int), false);
}

void Test9()
{
	int numbers[] = { 3, 0, 0, 0, 0 };
	Test("Test9", numbers, sizeof(numbers) / sizeof(int), true);
}

void Test10()
{
	int numbers[] = { 0, 0, 0, 0, 0 };
	Test("Test10", numbers, sizeof(numbers) / sizeof(int), true);
}

// �ж���
void Test11()
{
	int numbers[] = { 1, 0, 0, 1, 0 };
	Test("Test11", numbers, sizeof(numbers) / sizeof(int), false);
}

// ³���Բ���
void Test12()
{
	Test("Test12", nullptr, 0, false);
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
	Test12();

	return 0;
}

