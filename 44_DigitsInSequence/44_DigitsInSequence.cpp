// 44_DigitsInSequence.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������44������������ĳһλ������
// ��Ŀ��������0123456789101112131415���ĸ�ʽ���л���һ���ַ������С�����
// �������У���5λ����0��ʼ��������5����13λ��1����19λ��4���ȵȡ���дһ
// ������������λ��Ӧ�����֡�

#include "stdafx.h"

#include <iostream>
#include <algorithm>

using namespace std;

int countOfIntegers(int digits);
int digitAtIndex(int index, int digits);
int beginNumber(int digits);

int digitAtIndex(int index) //��������index��ʾnλ
{
	if (index < 0)//��0��ʼ����������ǺϷ��ж�
		return -1;

	int digits = 1;
	while (true)
	{
		int numbers = countOfIntegers(digits);//���㵱ǰλ�£�����Ӧ�����ֵĸ���
		if (index < numbers * digits)//��ʱ˵����Ҫ�ҵ�nλ��Ӧ���������ڵ�ǰdigitsλ�£�������һ���������д���
			return digitAtIndex(index, digits);

		index -= digits * numbers;
		digits++;//��ǰλ����������꣬λ��+1
	}

	return -1;
}

int countOfIntegers(int digits)//����mλ�������Ƕ��ٸ�������1λ��10����0-9����2λ��90����10-99����3λ��900����100-999�����Դ�����
{
	if (digits == 1)
		return 10;

	int count = (int)std::pow(10, digits - 1);//pow(x,y)��ʾx^y��
	return 9 * count;
}

int digitAtIndex(int index, int digits)
{
	int number = beginNumber(digits) + index / digits;//�ҵ���nλ��Ӧ�������Ǵӵ�һ��mλ������ڼ�������
	int indexFromRight = digits - index % digits;// �ҵ���nλ��Ӧ�������Ǵӵ�һ��mλ������ڼ��������еĵڼ�λ
	for (int i = 1; i < indexFromRight; ++i)//��һ����ͨ������10���ҵ���λ�ڸ������е���һ��λ��
		number /= 10;
	return number % 10;//����Ǹ����֣����ַ�ΧΪ0-9��
}

int beginNumber(int digits)//��õ�һ��mλ���������һ����λ��Ϊ10����һ����λ����100
{
	if (digits == 1)
		return 0;

	return (int)std::pow(10, digits - 1);
}

// ====================���Դ���====================
void test(const char* testName, int inputIndex, int expectedOutput)
{
	if (digitAtIndex(inputIndex) == expectedOutput)
		cout << testName << " passed." << endl;
	else
		cout << testName << " FAILED." << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	test("Test1", 0, 0);
	test("Test2", 1, 1);
	test("Test3", 9, 9);
	test("Test4", 10, 1);
	test("Test5", 189, 9);  // ����99�����һλ��9
	test("Test6", 190, 1);  // ����100�ĵ�һλ��1
	test("Test7", 1000, 3); // ����370�ĵ�һλ��3
	test("Test8", 1001, 7); // ����370�ĵڶ�λ��7
	test("Test9", 1002, 0); // ����370�ĵ���λ��0
	return 0;
}

