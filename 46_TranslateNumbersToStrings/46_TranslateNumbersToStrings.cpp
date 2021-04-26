// 46_TranslateNumbersToStrings.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������46�������ַ�����ַ���
// ��Ŀ������һ�����֣����ǰ������¹����������Ϊ�ַ�����0�����"a"��1��
// ���"b"��������11�����"l"��������25�����"z"��һ�����ֿ����ж�����롣��
// ��12258��5�ֲ�ͬ�ķ��룬���Ƿֱ���"bccfi"��"bwfi"��"bczi"��"mcfi"��
// "mzi"������ʵ��һ��������������һ�������ж����ֲ�ͬ�ķ��뷽����

#include "stdafx.h"

#include <string>
#include <iostream>

using namespace std;

int GetTranslationCount(const string& number);

int GetTranslationCount(int number)//�����Ƕ�ȡ���֣���Ϊû�й涨��������ݵĴ�С���ܿ��ܳ���int�ķ�Χ�����Խ���תΪ�ַ���string
{
	if (number < 0)
		return 0;

	string numberInString = to_string(number);
	return GetTranslationCount(numberInString);
}

int GetTranslationCount(const string& number)//��ת��Ϊ�ַ��������ֽ��д���
{
	int length = number.length();//������ֵĳ���
	int* counts = new int[length]; //�������ͳ�Ƶ�iλ���ֿ�ʼ�Ĳ�ͬ�������Ŀ                                            
	int count = 0;//��Ϊ�м�����洢��Ϣ��ͬʱҲ��Ϊ����������

	for (int i = length - 1; i >= 0; --i)//˼·�ǵݹ飬����ʵ���Ǵ�ѭ����ʼʵ��
	{
		count = 0;//ÿ������
		if (i < length - 1)
			count = counts[i + 1];//��ȡǰһ�εĽ��
		else
			count = 1;

		if (i < length - 1)//�Ӻ���ǰ�ڶ�λ��ʼ�����Ƿ����0-25֮�������
		{
			int digit1 = number[i] - '0';
			int digit2 = number[i + 1] - '0';
			int converted = digit1 * 10 + digit2;
			if (converted >= 10 && converted <= 25)//����Ļ�����Ҫ�ۼ�
			{
				if (i < length - 2) //��ǰi����ǴӴӺ���ǰ���������ֵ�λ�ã���ô����Ҫ�ۼ�֮ǰi+2���Ľ��
					count += counts[i + 2];
				else//����ǵ�����1��2�����֣���ֻ��Ҫ��1����Ϊ�Ӻ���ǰ�㣬ֻ��һ�ֿ���
					count += 1;
			}
		}

		counts[i] = count;
	}

	count = counts[0];
	delete[] counts;

	return count;
}

// ====================���Դ���====================
void Test(const string& testName, int number, int expected)
{
	if (GetTranslationCount(number) == expected)
		cout << testName << " passed." << endl;
	else
		cout << testName << " FAILED." << endl;
}

void Test1()
{
	int number = 0;
	int expected = 1;
	Test("Test1", number, expected);
}

void Test2()
{
	int number = 10;
	int expected = 2;
	Test("Test2", number, expected);
}

void Test3()
{
	int number = 125;
	int expected = 3;
	Test("Test3", number, expected);
}

void Test4()
{
	int number = 126;
	int expected = 2;
	Test("Test4", number, expected);
}

void Test5()
{
	int number = 426;
	int expected = 1;
	Test("Test5", number, expected);
}

void Test6()
{
	int number = 100;
	int expected = 2;
	Test("Test6", number, expected);
}

void Test7()
{
	int number = 101;
	int expected = 2;
	Test("Test7", number, expected);
}

void Test8()
{
	int number = 12258;
	int expected = 5;
	Test("Test8", number, expected);
}

void Test9()
{
	int number = -100;
	int expected = 0;
	Test("Test9", number, expected);
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

